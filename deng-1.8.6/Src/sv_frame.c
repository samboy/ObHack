/* DE1: $Id: sv_frame.c,v 1.17 2004/05/31 15:04:44 skyjake Exp $
 * Copyright (C) 2003, 2004 Jaakko Ker�nen <jaakko.keranen@iki.fi>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not: http://www.opensource.org/
 */

/*
 * sv_frame.c: Frame Generation and Transmission
 */

// HEADER FILES ------------------------------------------------------------

#include "de_base.h"
#include "de_console.h"
#include "de_network.h"
#include "de_system.h"
#include "de_refresh.h"
#include "de_misc.h"

#include "def_main.h"

// MACROS ------------------------------------------------------------------

// Hitting the maximum packet size allows checks for raising BWR.
#define BWR_ADJUST_TICS		(TICSPERSEC / 2)

// The minimum frame size is used when bandwidth rating is zero (poorest
// possible connection).
#define MINIMUM_FRAME_SIZE	75	// bytes

// The frame size is calculated by multiplying the bandwidth rating
// (max 100) with this factor (+min).
#define FRAME_SIZE_FACTOR 	13
#define FIXED8_8(x)			(((x)*256) >> 16)
#define FIXED10_6(x)		(((x)*64) >> 16)
#define CLAMPED_CHAR(x)		((x)>127? 127 : (x)<-128? -128 : (x))

// If movement is faster than this, we'll adjust the place of the point.
#define MOM_FAST_LIMIT		(127*FRACUNIT)

// TYPES -------------------------------------------------------------------

// EXTERNAL FUNCTION PROTOTYPES --------------------------------------------

// PUBLIC FUNCTION PROTOTYPES ----------------------------------------------

void    Sv_SendFrame(int playerNumber);

// PRIVATE FUNCTION PROTOTYPES ---------------------------------------------

// EXTERNAL DATA DECLARATIONS ----------------------------------------------

// PUBLIC DATA DEFINITIONS -------------------------------------------------

int     allowFrames = false;
int     send_all_players = false;	// Obsolete
int     frameInterval = 1;		// Skip every second frame by default (17.5fps)

// PRIVATE DATA DEFINITIONS ------------------------------------------------

#ifdef _DEBUG
static int byteCounts[256];
static int totalFrameCount;
#endif

static int lastTransmitTic = 0;

// CODE --------------------------------------------------------------------

/*
 * Send all the relevant information to each client.
 */
void Sv_TransmitFrame(void)
{
	int     i, cTime, numInGame, pCount;

	// Obviously clients don't transmit anything.
	if(!allowFrames || isClient)
	{
		return;
	}

	if(!netgame)
	{
		// When not running a netgame, only generate deltas when somebody
		// is recording a demo.
		for(i = 0; i < MAXPLAYERS; i++)
			if(Sv_IsFrameTarget(i))
				break;

		if(i == MAXPLAYERS)
		{
			// Nobody is a frame target.
			return;
		}
	}

	if(SECONDS_TO_TICKS(gameTime) == lastTransmitTic)
	{
		// We were just here!
		return;
	}
	lastTransmitTic = SECONDS_TO_TICKS(gameTime);

	// Generate new deltas for the frame.
	Sv_GenerateFrameDeltas();

	// How many players currently in the game?
	numInGame = Sv_GetNumPlayers();

	for(i = 0, pCount = 0; i < MAXPLAYERS; i++)
	{
		if(!Sv_IsFrameTarget(i))
		{
			// This player is not a valid target for frames.
			continue;
		}

		// When the interval is greater than zero, this causes the frames
		// to be sent at different times for each player.
		pCount++;
		cTime = SECONDS_TO_TICKS(gameTime);
		if(frameInterval > 0 && numInGame > 1)
		{
			cTime += (pCount * frameInterval) / numInGame;
		}
		if(cTime <= clients[i].lastTransmit + frameInterval)
		{
			// Still too early to send.
			continue;
		}
		clients[i].lastTransmit = cTime;

		/*#if _DEBUG
		   ST_Message("gt:%i (%i) -> cl%i\n", gametic, ctime, i);
		   #endif */

		if(clients[i].ready && clients[i].updateCount > 0)
		{
			// A frame will be sent to this client. If the client 
			// doesn't send ticcmds, the updatecount will eventually
			// decrease back to zero.
			clients[i].updateCount--;

			Sv_SendFrame(i);
		}
	}
}

/*
 * Shutdown routine for the server.
 */
void Sv_Shutdown(void)
{
#ifdef _DEBUG
	if(totalFrameCount > 0)
	{
		int     i;

		// Byte probabilities.
		for(i = 0; i < 256; i++)
		{
			Con_Printf("Byte %02x: %f\n", i,
					   byteCounts[i] / (float) totalFrameCount);
		}
	}
#endif

	Sv_ShutdownPools();
}

/*
 * The delta is written to the message buffer. 
 */
void Sv_WriteMobjDelta(const void *deltaPtr)
{
	const mobjdelta_t *delta = deltaPtr;
	const dt_mobj_t *d = &delta->mo;
	int     df = delta->delta.flags;
	byte    moreFlags = 0;

	// Do we have fast momentum?
	if(abs(d->momx) >= MOM_FAST_LIMIT || abs(d->momy) >= MOM_FAST_LIMIT ||
	   abs(d->momz) >= MOM_FAST_LIMIT)
	{
		df |= MDF_MORE_FLAGS;
		moreFlags |= MDFE_FAST_MOM;
	}

	// Any translucency?
	if(df & MDFC_TRANSLUCENCY)
	{
		df |= MDF_MORE_FLAGS;
		moreFlags |= MDFE_TRANSLUCENCY;
	}

	// Do we need the longer floorclip entry?
	if(d->floorclip > 64 * FRACUNIT)
		df |= MDF_LONG_FLOORCLIP;

	// Flags. What elements are included in the delta?
	if(d->selector & ~DDMOBJ_SELECTOR_MASK)
		df |= MDF_SELSPEC;

	// Floor/ceiling z?
	if(df & MDF_POS_Z)
	{
		if(d->z == DDMININT || d->z == DDMAXINT)
		{
			df &= ~MDF_POS_Z;
			df |= MDF_MORE_FLAGS;
			moreFlags |= (d->z == DDMININT ? MDFE_Z_FLOOR : MDFE_Z_CEILING);
		}
	}

#ifdef _DEBUG
	if(df & MDFC_NULL)
	{
		Con_Error("Sv_WriteMobjDelta: We don't write Null deltas.\n", df);
	}
	if((df & 0xffff) == 0)
	{
		Con_Printf("Sv_WriteMobjDelta: This delta id%i [%x] is empty.\n",
				   delta->delta.id, df);
	}
#endif

	// First the mobj ID number and flags.
	Msg_WriteShort(delta->delta.id);
	Msg_WriteShort(df & 0xffff);

	// More flags?
	if(df & MDF_MORE_FLAGS)
	{
		Msg_WriteByte(moreFlags);
	}

	// Coordinates with three bytes.
	if(df & MDF_POS_X)
	{
		Msg_WriteShort(d->x >> FRACBITS);
		Msg_WriteByte(d->x >> 8);
	}
	if(df & MDF_POS_Y)
	{
		Msg_WriteShort(d->y >> FRACBITS);
		Msg_WriteByte(d->y >> 8);
	}
	if(df & MDF_POS_Z)
	{
		Msg_WriteShort(d->z >> FRACBITS);
		Msg_WriteByte(d->z >> 8);
	}

	// Momentum using 8.8 fixed point.
	if(df & MDF_MOM_X)
	{
		Msg_WriteShort(moreFlags & MDFE_FAST_MOM ? FIXED10_6(d->momx) :
					   FIXED8_8(d->momx));
	}
	if(df & MDF_MOM_Y)
	{
		Msg_WriteShort(moreFlags & MDFE_FAST_MOM ? FIXED10_6(d->momy) :
					   FIXED8_8(d->momy));
	}
	if(df & MDF_MOM_Z)
	{
		Msg_WriteShort(moreFlags & MDFE_FAST_MOM ? FIXED10_6(d->momz) :
					   FIXED8_8(d->momz));
	}

	// Angles with 16-bit accuracy.
	if(df & MDF_ANGLE)
		Msg_WriteShort(d->angle >> 16);

	if(df & MDF_SELECTOR)
		Msg_WritePackedShort(d->selector);
	if(df & MDF_SELSPEC)
		Msg_WriteByte(d->selector >> 24);

	if(df & MDF_STATE)
		Msg_WritePackedShort(d->state - states);

	// Pack flags into a word (3 bytes?).
	// FIXME: Do the packing!
	if(df & MDF_FLAGS)
		Msg_WriteLong(d->ddflags & DDMF_PACK_MASK);

	// Radius, height and floorclip are all bytes.
	if(df & MDF_RADIUS)
		Msg_WriteByte(d->radius >> FRACBITS);
	if(df & MDF_HEIGHT)
		Msg_WriteByte(d->height >> FRACBITS);
	if(df & MDF_FLOORCLIP)
	{
		if(df & MDF_LONG_FLOORCLIP)
			Msg_WritePackedShort(d->floorclip >> 14);
		else
			Msg_WriteByte(d->floorclip >> 14);
	}

	if(df & MDFC_TRANSLUCENCY)
		Msg_WriteByte(d->translucency);
}

/*
 * The delta is written to the message buffer. 
 */
void Sv_WritePlayerDelta(const void *deltaPtr)
{
	const playerdelta_t *delta = deltaPtr;
	const dt_player_t *d = &delta->player;
	const ddpsprite_t *psp;
	int     df = delta->delta.flags;
	int     psdf, i, k;

	// First the player number. Upper three bits contain flags.
	Msg_WriteByte(delta->delta.id | (df >> 8));

	// Flags. What elements are included in the delta?
	Msg_WriteByte(df & 0xff);

	if(df & PDF_MOBJ)
		Msg_WriteShort(d->mobj);
	if(df & PDF_FORWARDMOVE)
		Msg_WriteByte(d->forwardMove);
	if(df & PDF_SIDEMOVE)
		Msg_WriteByte(d->sideMove);
	if(df & PDF_ANGLE)
		Msg_WriteByte(d->angle >> 24);
	if(df & PDF_TURNDELTA)
		Msg_WriteByte((d->turnDelta * 16) >> 24);
	if(df & PDF_FRICTION)
		Msg_WriteByte(d->friction >> 8);
	if(df & PDF_EXTRALIGHT)
	{
		// Three bits is enough for fixedcolormap.
		i = d->fixedColorMap;
		if(i < 0)
			i = 0;
		if(i > 7)
			i = 7;
		// Write the five upper bytes of extralight.
		Msg_WriteByte(i | (d->extraLight & 0xf8));
	}
	if(df & PDF_FILTER)
		Msg_WriteLong(d->filter);
	if(df & PDF_CLYAW)
		Msg_WriteShort(d->clYaw >> 16);
	if(df & PDF_CLPITCH)
		Msg_WriteShort(d->clPitch / 110 * DDMAXSHORT);
	if(df & PDF_PSPRITES)		// Only set if there's something to write.
	{
		for(i = 0; i < 2; i++)
		{
			psdf = df >> (16 + i * 8);
			psp = d->psp + i;
			// First the flags.
			Msg_WriteByte(psdf);
			if(psdf & PSDF_STATEPTR)
			{
				if(psp->stateptr)
					Msg_WritePackedShort(psp->stateptr - states + 1);
				else
					Msg_WritePackedShort(0);
			}
			if(psdf & PSDF_LIGHT)
			{
				k = psp->light * 255;
				if(k < 0)
					k = 0;
				if(k > 255)
					k = 255;
				Msg_WriteByte(k);
			}
			if(psdf & PSDF_ALPHA)
			{
				k = psp->alpha * 255;
				if(k < 0)
					k = 0;
				if(k > 255)
					k = 255;
				Msg_WriteByte(k);
			}
			if(psdf & PSDF_STATE)
			{
				Msg_WriteByte(psp->state);
			}
			if(psdf & PSDF_OFFSET)
			{
				Msg_WriteByte(CLAMPED_CHAR(psp->offx / 2));
				Msg_WriteByte(CLAMPED_CHAR(psp->offy / 2));
			}
		}
	}

}

/*
 * The delta is written to the message buffer. 
 */
void Sv_WriteSectorDelta(const void *deltaPtr)
{
	const sectordelta_t *delta = deltaPtr;
	const dt_sector_t *d = &delta->sector;
	int     df = delta->delta.flags, spd;
	byte    floorspd, ceilspd;

	// Is there need to use 4.4 fixed-point speeds?
	// (7.1 is too inaccurate for very slow movement)
	if(df & SDF_FLOOR_SPEED)
	{
		spd = abs(d->planes[PLN_FLOOR].speed);
		floorspd = spd >> 15;
		if(!floorspd)
		{
			df |= SDF_FLOOR_SPEED_44;
			floorspd = spd >> 12;
		}
	}
	if(df & SDF_CEILING_SPEED)
	{
		spd = abs(d->planes[PLN_CEILING].speed);
		ceilspd = spd >> 15;
		if(!ceilspd)
		{
			df |= SDF_CEILING_SPEED_44;
			ceilspd = spd >> 12;
		}
	}

	// Sector number first.
	Msg_WriteShort(delta->delta.id);

	// Flags as a packed short. (Usually only one byte, though.)
	Msg_WriteShort(df & 0xffff);

	if(df & SDF_FLOORPIC)
		Msg_WritePackedShort(d->floorPic);
	if(df & SDF_CEILINGPIC)
		Msg_WritePackedShort(d->ceilingPic);
	if(df & SDF_LIGHT)
	{
		// Must fit into a byte.
		Msg_WriteByte(d->lightlevel < 0 ? 0 : d->lightlevel >
					  255 ? 255 : d->lightlevel);
	}
	if(df & SDF_FLOOR_HEIGHT)
		Msg_WriteShort(d->floorHeight >> 16);
	if(df & SDF_CEILING_HEIGHT)
		Msg_WriteShort(d->ceilingHeight >> 16);
	if(df & SDF_FLOOR_TARGET)
		Msg_WriteShort(d->planes[PLN_FLOOR].target >> 16);
	if(df & SDF_FLOOR_SPEED)	// 7.1/4.4 fixed-point
		Msg_WriteByte(floorspd);
	if(df & SDF_FLOOR_TEXMOVE)
	{
		Msg_WriteShort(d->planes[PLN_FLOOR].texmove[0] >> 8);
		Msg_WriteShort(d->planes[PLN_FLOOR].texmove[1] >> 8);
	}
	if(df & SDF_CEILING_TARGET)
		Msg_WriteShort(d->planes[PLN_CEILING].target >> 16);
	if(df & SDF_CEILING_SPEED)	// 7.1/4.4 fixed-point
		Msg_WriteByte(ceilspd);
	if(df & SDF_CEILING_TEXMOVE)
	{
		Msg_WriteShort(d->planes[PLN_CEILING].texmove[0] >> 8);
		Msg_WriteShort(d->planes[PLN_CEILING].texmove[1] >> 8);
	}
	if(df & SDF_COLOR_RED)
		Msg_WriteByte(d->rgb[0]);
	if(df & SDF_COLOR_GREEN)
		Msg_WriteByte(d->rgb[1]);
	if(df & SDF_COLOR_BLUE)
		Msg_WriteByte(d->rgb[2]);
}

/*
 * The delta is written to the message buffer. 
 */
void Sv_WriteSideDelta(const void *deltaPtr)
{
	const sidedelta_t *delta = deltaPtr;
	const dt_side_t *d = &delta->side;
	int     df = delta->delta.flags;

	// Side number first.
	Msg_WriteShort(delta->delta.id);

	// Flags.
	Msg_WriteByte(df & 0xff);

	if(df & SIDF_TOPTEX)
		Msg_WritePackedShort(d->topTexture);
	if(df & SIDF_MIDTEX)
		Msg_WritePackedShort(d->midTexture);
	if(df & SIDF_BOTTOMTEX)
		Msg_WritePackedShort(d->bottomTexture);
	if(df & SIDF_LINE_FLAGS)
		Msg_WriteByte(d->lineFlags);
}

/*
 * The delta is written to the message buffer. 
 */
void Sv_WritePolyDelta(const void *deltaPtr)
{
	const polydelta_t *delta = deltaPtr;
	const dt_poly_t *d = &delta->po;
	int     df = delta->delta.flags;

	if(d->destAngle == (unsigned) -1)
	{
		// Send Perpetual Rotate instead of Dest Angle flag.
		df |= PODF_PERPETUAL_ROTATE;
		df &= ~PODF_DEST_ANGLE;
	}

	// Poly number first.
	Msg_WritePackedShort(delta->delta.id);

	// Flags.
	Msg_WriteByte(df & 0xff);

	if(df & PODF_DEST_X)
	{
		Msg_WriteShort(d->dest.x >> 16);
		Msg_WriteByte(d->dest.x >> 8);
	}
	if(df & PODF_DEST_Y)
	{
		Msg_WriteShort(d->dest.y >> 16);
		Msg_WriteByte(d->dest.y >> 8);
	}
	if(df & PODF_SPEED)
		Msg_WriteShort(d->speed >> 8);
	if(df & PODF_DEST_ANGLE)
		Msg_WriteShort(d->destAngle >> 16);
	if(df & PODF_ANGSPEED)
		Msg_WriteShort(d->angleSpeed >> 16);
}

/*
 * The delta is written to the message buffer. 
 */
void Sv_WriteSoundDelta(const void *deltaPtr)
{
	const sounddelta_t *delta = deltaPtr;
	int     df = delta->delta.flags;

	// This is either the sound ID, emitter ID or sector index.
	Msg_WriteShort(delta->delta.id);

	// First the flags byte.
	Msg_WriteByte(df & 0xff);

	switch (delta->delta.type)
	{
	case DT_MOBJ_SOUND:
	case DT_SECTOR_SOUND:
	case DT_POLY_SOUND:
		// The sound ID.
		Msg_WriteShort(delta->sound);
		break;

	default:
		break;
	}

	// The common parts.
	if(df & SNDDF_VOLUME)
	{
		if(delta->volume > 1)
		{
			// Very loud indeed.
			Msg_WriteByte(255);
		}
		else if(delta->volume <= 0)
		{
			// Silence.
			Msg_WriteByte(0);
		}
		else
		{
			Msg_WriteByte(delta->volume * 127 + 0.5f);
		}
	}
}

/*
 * Write the type and possibly the set number (for Unacked deltas).
 */
void Sv_WriteDeltaHeader(byte type, const delta_t * delta)
{
	if(delta->state == DELTA_UNACKED)
	{
		// Flag this as Resent.
		type |= DT_RESENT;
	}

	Msg_WriteByte(type);

	// Include the set number?
	if(type & DT_RESENT)
	{
		// The client will use this to avoid dupes. If the client has already
		// received the set this delta belongs to, it means the delta has
		// already been received. This is needed in the situation where the
		// ack is lost or delayed.
		Msg_WriteByte(delta->set);

		// Also send the unique ID of this delta. If the client has already 
		// received a delta with this ID, the delta is discarded. This is
		// needed in the situation where the set is lost.
		Msg_WriteByte(delta->resend);
	}
}

/*
 * The delta is written to the message buffer. 
 */
void Sv_WriteDelta(const delta_t * delta)
{
	byte    type = delta->type;

	// Null mobj deltas are special.
	if(type == DT_MOBJ)
	{
		if(delta->flags & MDFC_NULL)
		{
			// This'll be the entire delta. No more data is needed.
			Sv_WriteDeltaHeader(DT_NULL_MOBJ, delta);
			Msg_WriteShort(delta->id);
			return;
		}

		if(delta->flags & MDFC_CREATE)
		{
			// This mobj was just created, let's use a different 
			// delta type number.
			type = DT_CREATE_MOBJ;
			/*#ifdef _DEBUG
			   Con_Printf("Written: create mo %i [%08x, s%i]\n", delta->id,
			   delta->flags, delta->state);
			   #endif */
		}
	}

	// First the type of the delta.
	Sv_WriteDeltaHeader(type, delta);

	switch (delta->type)
	{
	case DT_MOBJ:
		Sv_WriteMobjDelta(delta);
		break;

	case DT_PLAYER:
		Sv_WritePlayerDelta(delta);
		break;

	case DT_SECTOR:
		Sv_WriteSectorDelta(delta);
		break;

	case DT_SIDE:
		Sv_WriteSideDelta(delta);
		break;

	case DT_POLY:
		Sv_WritePolyDelta(delta);
		break;

	case DT_SOUND:
	case DT_MOBJ_SOUND:
	case DT_SECTOR_SOUND:
	case DT_POLY_SOUND:
		Sv_WriteSoundDelta(delta);
		break;

		/*case DT_LUMP:
		   Sv_WriteLumpDelta(delta);
		   break; */

	default:
		Con_Error("Sv_WriteDelta: Unknown delta type %i.\n", delta->type);
	}
}

/*
 * Returns an estimate for the maximum frame size appropriate for the
 * client. The bandwidth rating is updated whenever a frame is sent.
 */
int Sv_GetMaxFrameSize(int playerNumber)
{
	int     size =
		MINIMUM_FRAME_SIZE +
		FRAME_SIZE_FACTOR * clients[playerNumber].bandwidthRating;

	// What about the communications medium?
	if((uint) size > maxDatagramSize)
		size = maxDatagramSize;

	return size;
}

/*
 * Returns a unique resend ID. Never returns zero.
 */
byte Sv_GetNewResendID(pool_t * pool)
{
	byte    id = pool->resendDealer;

	// Advance to next ID, skipping zero.
	while(!++pool->resendDealer);

	return id;
}

/*
 * Send a sv_frame packet to the specified player. The amount of data sent 
 * depends on the player's bandwidth rating. 
 */
void Sv_SendFrame(int playerNumber)
{
	pool_t *pool = Sv_GetPool(playerNumber);
	int     maxFrameSize, lastStart;
	byte    oldResend;
	delta_t *delta;

	// Does the send queue allow us to send this packet?
	// Bandwidth rating is updated during the check.
	if(!Sv_CheckBandwidth(playerNumber))
	{
		// We cannot send anything at this time. This will only happen if
		// the send queue has too many packets waiting to be sent.
		return;
	}

	// The priority queue of the client needs to be rebuilt before 
	// a new frame can be sent. 
	Sv_RatePool(pool);

	// This will be a new set.
	pool->setDealer++;

	// Determine the maximum size of the frame packet.
	maxFrameSize = Sv_GetMaxFrameSize(playerNumber);

	// Allow more info for the first frame.
	if(pool->isFirst)
		maxFrameSize = maxDatagramSize;

	// If this is the first frame after a map change, use the special
	// first frame packet type.
	Msg_Begin(pool->isFirst ? psv_first_frame2 : psv_frame2);

	// The first byte contains the set number, which identifies this 
	// frame. The client will keep track of the numbers to detect 
	// duplicates.
	Msg_WriteByte(pool->setDealer);

	/*#ifdef _DEBUG
	   Con_Printf("set%i\n", pool->setDealer);
	   #endif */

	// Keep writing until the maximum size is reached.
	while((delta = Sv_PoolQueueExtract(pool)) != NULL &&
		  (lastStart = Msg_Offset()) < maxFrameSize)
	{
		oldResend = 0;

		// Is this going to be a resent?
		if(delta->state == DELTA_UNACKED && !delta->resend)
		{
			oldResend = pool->resendDealer;

			// Assign a new unique ID for this delta. 
			// This ID won't be changed after this.
			delta->resend = Sv_GetNewResendID(pool);
		}

		Sv_WriteDelta(delta);

		// Did we go over the limit?
		if(Msg_Offset() > maxFrameSize)
		{
			// Time to see if BWR needs to be adjusted.
			if(clients[playerNumber].bwrAdjustTime <= 0)
			{
				clients[playerNumber].bwrAdjustTime = BWR_ADJUST_TICS;
			}

			// Cancel the last delta.
			Msg_SetOffset(lastStart);

			// Restore the resend dealer.
			if(oldResend)
				pool->resendDealer = oldResend;
			break;
		}

		/*#ifdef _DEBUG
		   if(delta->state == DELTA_UNACKED)
		   {
		   Con_Printf("Resend: %i, type%i[%x], set%i, rsid%i\n",
		   delta->id, delta->type, delta->flags,
		   delta->set, delta->resend);
		   }
		   #endif */

		// Update the sent delta's state.
		if(delta->state == DELTA_NEW)
		{
			// New deltas are assigned to this set. Unacked deltas will
			// remain in the set they were initially sent in.
			delta->set = pool->setDealer;
		}
		delta->timeStamp = Sv_GetTimeStamp();
		delta->state = DELTA_UNACKED;
	}

	// The psv_first_frame2 packet is sent Ordered, which means it'll
	// always arrive in the correct order when compared to the other
	// game setup packets.
	Net_SendBuffer(playerNumber, pool->isFirst ? SPF_ORDERED : 0);

	// If the target is local, ack immediately. This effectively removes
	// all the sent deltas from the pool.
	if(players[playerNumber].flags & DDPF_LOCAL)
	{
		Sv_AckDeltaSet(playerNumber, pool->setDealer, 0);
	}

	// Now a frame has been sent.
	pool->isFirst = false;
}
