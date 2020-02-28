/* DE1: $Id: sv_pool.c,v 1.23 2004/05/31 15:04:44 skyjake Exp $
 * Copyright (C) 2003, 2004 Jaakko Ker�en <jaakko.keranen@iki.fi>
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
 * sv_pool.c: Delta Pools
 *
 * Delta Pools use PU_LEVEL, which means all the memory allocated for them
 * is deallocated when the level changes. Sv_InitPools() is called in 
 * R_SetupLevel() to clear out all the old data.
 */

// HEADER FILES ------------------------------------------------------------

#include "de_base.h"
#include "de_console.h"
#include "de_network.h"
#include "de_refresh.h"
#include "de_play.h"

#include "s_main.h"
#include "sys_timer.h"

// MACROS ------------------------------------------------------------------

#define REG_MOBJ_HASH_SIZE			1024
#define REG_MOBJ_HASH_FUNCTION_MASK	0x3ff

// Maximum difference in plane height where the absolute height doesn't
// need to be sent.

#define PLANE_SKIP_LIMIT	(40*FRACUNIT)

// TYPES -------------------------------------------------------------------

typedef struct reg_mobj_s {
	// Links to next and prev mobj in the register hash.
	struct reg_mobj_s *next, *prev;

	// The state of the mobj.
	dt_mobj_t mo;
} reg_mobj_t;

typedef struct mobjhash_s {
	reg_mobj_t *first, *last;
} mobjhash_t;

/*
 * One cregister_t holds the state of the entire world.
 */
typedef struct cregister_s {
	// The time the register was last updated.
	int     gametic;

	// True if this register contains a read-only copy of the initial state
	// of the world.
	boolean isInitial;

	// The mobjs are stored in a hash for efficiency (ID is the key).
	mobjhash_t mobjs[REG_MOBJ_HASH_SIZE];

	dt_player_t players[MAXPLAYERS];
	dt_sector_t *sectors;
	dt_side_t *sides;
	dt_poly_t *polys;
} cregister_t;

/*
 * Each entity (mobj, sector, side, etc.) has an origin the world.
 */
typedef struct origin_s {
	fixed_t x, y;
} origin_t;

// EXTERNAL FUNCTION PROTOTYPES --------------------------------------------

// PUBLIC FUNCTION PROTOTYPES ----------------------------------------------

void    Sv_RegisterWorld(cregister_t * reg, boolean isInitial);
void    Sv_NewDelta(void *deltaPtr, deltatype_t type, uint id);
boolean Sv_IsVoidDelta(const void *delta);
void    Sv_PoolQueueClear(pool_t * pool);
void    Sv_GenerateNewDeltas(cregister_t * reg, int clientNumber,
							 boolean doUpdate);

// PRIVATE FUNCTION PROTOTYPES ---------------------------------------------

// EXTERNAL DATA DECLARATIONS ----------------------------------------------

// PUBLIC DATA DEFINITIONS -------------------------------------------------

// The register contains the previous state of the world.
cregister_t worldRegister;

// The initial register is used when generating deltas for a new client.
cregister_t initialRegister;

// Each client has its own pool for deltas.
pool_t  pools[MAXPLAYERS];

// PRIVATE DATA DEFINITIONS ------------------------------------------------

// Keep this zeroed out. Used if the register doesn't have data for 
// the mobj being compared.
static dt_mobj_t dummyZeroMobj;

// Origins of stuff. Calculated at the beginning of a map.
static origin_t *sectorOrigins, *sideOrigins;

// Pointer to the owner line for each side.
static line_t **sideOwners;

// CODE --------------------------------------------------------------------

/*
 * Called once for each level, from R_SetupLevel(). Initialize the world
 * register and drain all pools.
 */
void Sv_InitPools(void)
{
	int     i;

	// Clients don't register anything.
	if(isClient)
		return;

	// Since the level has changed, PU_LEVEL memory has been freed.
	// Reset all pools (set numbers are kept, though).
	for(i = 0; i < MAXPLAYERS; i++)
	{
		pools[i].owner = i;
		pools[i].resendDealer = 1;
		memset(pools[i].hash, 0, sizeof(pools[i].hash));
		memset(pools[i].misHash, 0, sizeof(pools[i].misHash));
		pools[i].queueSize = 0;
		pools[i].allocatedSize = 0;
		pools[i].queue = NULL;

		// This will be set to false when a frame is sent.
		pools[i].isFirst = true;
	}

	// Find the owners of all sides.
	sideOwners = Z_Malloc(sizeof(line_t *) * numsides, PU_LEVEL, 0);
	for(i = 0; i < numsides; i++)
	{
		sideOwners[i] = R_GetLineForSide(i);
	}

	// Origins of sectors.
	sectorOrigins = Z_Malloc(sizeof(origin_t) * numsectors, PU_LEVEL, 0);
	for(i = 0; i < numsectors; i++)
	{
		sectorOrigins[i].x =
			FRACUNIT * (secinfo[i].bounds[BRIGHT] +
						secinfo[i].bounds[BLEFT]) / 2;
		sectorOrigins[i].y =
			FRACUNIT * (secinfo[i].bounds[BBOTTOM] +
						secinfo[i].bounds[BTOP]) / 2;
	}

	// Origins of sides.
	sideOrigins = Z_Malloc(sizeof(origin_t) * numsides, PU_LEVEL, 0);
	for(i = 0; i < numsides; i++)
	{
		// The side must be owned by a line.
		if(sideOwners[i] == NULL)
			continue;

		sideOrigins[i].x = sideOwners[i]->v1->x + sideOwners[i]->dx / 2;
		sideOrigins[i].y = sideOwners[i]->v1->y + sideOwners[i]->dy / 2;
	}

	// Store the current state of the world into both the registers.
	Sv_RegisterWorld(&worldRegister, false);
	Sv_RegisterWorld(&initialRegister, true);

#ifdef _DEBUG
	Con_Printf("Sv_InitPools: World has been registered.\n");
#endif
}

/*
 * Called during server shutdown (when shutting down the engine).
 */
void Sv_ShutdownPools(void)
{
}

/*
 * Called when a client joins the game.
 */
void Sv_InitPoolForClient(int clientNumber)
{
	// Free everything that might exist in the pool.
	Sv_DrainPool(clientNumber);

	// Generate deltas by comparing against the initial state of the world.
	// The initial register remains unmodified.
	Sv_GenerateNewDeltas(&initialRegister, clientNumber, false);

	// No frames have yet been sent for this client.
	// The first frame is processed a bit more thoroughly than the others
	// (e.g. *all* sides are compared, not just a portion).
	pools[clientNumber].isFirst = true;
}

/*
 * Returns a pointer to the console's delta pool.
 */
pool_t *Sv_GetPool(int consoleNumber)
{
	return &pools[consoleNumber];
}

/*
 * The hash function for the register mobj hash.
 */
uint Sv_RegisterHashFunction(thid_t id)
{
	return (uint) id & REG_MOBJ_HASH_FUNCTION_MASK;
}

/*
 * Returns a pointer to the register-mobj, if it already exists.
 */
reg_mobj_t *Sv_RegisterFindMobj(cregister_t * reg, thid_t id)
{
	mobjhash_t *hash = &reg->mobjs[Sv_RegisterHashFunction(id)];
	reg_mobj_t *iter;

	// See if there already is a register-mobj for this id.
	for(iter = hash->first; iter; iter = iter->next)
	{
		// Is this the one?
		if(iter->mo.thinker.id == id)
		{
			return iter;
		}
	}

	return NULL;
}

/*
 * Adds a new reg_mobj_t to the register's mobj hash.
 */
reg_mobj_t *Sv_RegisterAddMobj(cregister_t * reg, thid_t id)
{
	mobjhash_t *hash = &reg->mobjs[Sv_RegisterHashFunction(id)];
	reg_mobj_t *newRegMo;

	// Try to find an existing register-mobj.
	if((newRegMo = Sv_RegisterFindMobj(reg, id)) != NULL)
	{
		return newRegMo;
	}

	// Allocate the new register-mobj.
	newRegMo = Z_Calloc(sizeof(reg_mobj_t), PU_LEVEL, 0);

	// Link it to the end of the hash list.
	if(hash->last)
	{
		hash->last->next = newRegMo;
		newRegMo->prev = hash->last;
	}
	hash->last = newRegMo;

	if(!hash->first)
	{
		hash->first = newRegMo;
	}

	return newRegMo;
}

/*
 * Removes a reg_mobj_t from the register's mobj hash.
 */
void Sv_RegisterRemoveMobj(cregister_t * reg, reg_mobj_t * regMo)
{
	mobjhash_t *hash =
		&reg->mobjs[Sv_RegisterHashFunction(regMo->mo.thinker.id)];

	// Update the first and last links.
	if(hash->last == regMo)
	{
		hash->last = regMo->prev;
	}
	if(hash->first == regMo)
	{
		hash->first = regMo->next;
	}

	// Link out of the list.
	if(regMo->next)
	{
		regMo->next->prev = regMo->prev;
	}
	if(regMo->prev)
	{
		regMo->prev->next = regMo->next;
	}

	// Destroy the register-mobj.
	Z_Free(regMo);
}

/*
 * If the mobj is on the floor, returns MININT. If the mobj is touching the
 * ceiling, returns MAXINT. Otherwise returns the Z coordinate. The maxed-out
 * coordinate is stored in the register.
 */
fixed_t Sv_GetMaxedMobjZ(const mobj_t *mo)
{
	if(mo->z == mo->floorz)
	{
		return DDMININT;
	}
	if(mo->z + mo->height == mo->ceilingz)
	{
		return DDMAXINT;
	}
	return mo->z;
}

/*
 * Store the state of the mobj into the register-mobj.
 * Called at register init and after each delta generation cycle.
 */
void Sv_RegisterMobj(dt_mobj_t * reg, const mobj_t *mo)
{
	// (dt_mobj_t <=> mobj_t)
	// Just copy the data we need.
	reg->thinker.id = mo->thinker.id;
	reg->dplayer = mo->dplayer;
	reg->subsector = mo->subsector;
	reg->x = mo->x;
	reg->y = mo->y;
	reg->z = Sv_GetMaxedMobjZ(mo);
	reg->floorz = mo->floorz;
	reg->ceilingz = mo->ceilingz;
	reg->momx = mo->momx;
	reg->momy = mo->momy;
	reg->momz = mo->momz;
	reg->angle = mo->angle;
	reg->selector = mo->selector;
	reg->state = mo->state;
	reg->radius = mo->radius;
	reg->height = mo->height;
	reg->ddflags = mo->ddflags;
	reg->floorclip = mo->floorclip;
	reg->translucency = mo->translucency;
}

/*
 * Reset the data of the registered mobj to reasonable defaults.
 * In effect, forces a resend of the zeroed entries as deltas.
 */
void Sv_RegisterResetMobj(dt_mobj_t * reg)
{
	reg->x = 0;
	reg->y = 0;
	reg->z = 0;
	reg->angle = 0;
	reg->selector = 0;
	reg->state = 0;
	reg->radius = 0;
	reg->height = 0;
	reg->ddflags = 0;
	reg->floorclip = 0;
	reg->translucency = 0;
}

/*
 * Store the state of the player into the register-player.
 * Called at register init and after each delta generation cycle.
 */
void Sv_RegisterPlayer(dt_player_t * reg, int number)
{
	ddplayer_t *p = players + number;
	client_t *c = clients + number;

	reg->mobj = p->mo ? p->mo->thinker.id : 0;
	reg->forwardMove = c->lastCmd->forwardMove;
	reg->sideMove = c->lastCmd->sideMove;
	reg->angle = p->mo ? p->mo->angle : 0;
	reg->turnDelta = p->mo ? p->mo->angle - p->lastangle : 0;
	reg->friction = p->mo &&
		gx.MobjFriction ? gx.MobjFriction(p->mo) : DEFAULT_FRICTION;
	reg->extraLight = p->extralight;
	reg->fixedColorMap = p->fixedcolormap;
	reg->filter = p->filter;
	reg->clYaw = p->mo ? p->mo->angle : 0;
	reg->clPitch = p->lookdir;
	memcpy(reg->psp, p->psprites, sizeof(ddpsprite_t) * 2);
}

/*
 * Store the state of the sector into the register-sector.
 * Called at register init and after each delta generation.
 */
void Sv_RegisterSector(dt_sector_t * reg, int number)
{
	sector_t *sec = SECTOR_PTR(number);

	reg->floorPic = sec->floorpic;
	reg->ceilingPic = sec->ceilingpic;
	reg->lightlevel = sec->lightlevel;
	memcpy(reg->rgb, sec->rgb, 3);
	reg->floorHeight = sec->floorheight;
	reg->ceilingHeight = sec->ceilingheight;
	memcpy(reg->planes, sec->planes, sizeof(sec->planes));
}

/*
 * Store the state of the side into the register-side.
 * Called at register init and after each delta generation.
 */
void Sv_RegisterSide(dt_side_t * reg, int number)
{
	side_t *side = SIDE_PTR(number);
	line_t *line = sideOwners[number];

	reg->topTexture = side->toptexture;
	reg->midTexture = side->midtexture;
	reg->bottomTexture = side->bottomtexture;
	reg->lineFlags = (line ? line->flags & 0xff : 0);
}

/*
 * Store the state of the polyobj into the register-poly.
 * Called at register init and after each delta generation.
 */
void Sv_RegisterPoly(dt_poly_t * reg, int number)
{
	polyobj_t *poly = PO_PTR(number);

	reg->dest.x = poly->dest.x;
	reg->dest.y = poly->dest.y;
	reg->speed = poly->speed;
	reg->destAngle = poly->destAngle;
	reg->angleSpeed = poly->angleSpeed;
}

/*
 * Returns true if the result is not void.
 */
boolean Sv_RegisterCompareMobj(cregister_t * reg, const mobj_t *s,
							   mobjdelta_t * d)
{
	int     df;
	const reg_mobj_t *regMo;
	const dt_mobj_t *r = &dummyZeroMobj;

	//int age = gametic - reg->gametic; // Always > 0

	if((regMo = Sv_RegisterFindMobj(reg, s->thinker.id)) != NULL)
	{
		// Use the registered data.
		r = &regMo->mo;
		df = 0;
	}
	else
	{
		// This didn't exist in the register, so it's a new mobj.
		df = MDFC_CREATE;
	}

	if(r->x != s->x)
		df |= MDF_POS_X;
	if(r->y != s->y)
		df |= MDF_POS_Y;
	if(r->z != Sv_GetMaxedMobjZ(s))
		df |= MDF_POS_Z;

	if(r->momx != s->momx)
		df |= MDF_MOM_X;
	if(r->momy != s->momy)
		df |= MDF_MOM_Y;
	if(r->momz != s->momz)
		df |= MDF_MOM_Z;

	if(r->angle != s->angle)
		df |= MDF_ANGLE;
	if(r->selector != s->selector)
		df |= MDF_SELECTOR;
	if(r->translucency != s->translucency)
		df |= MDFC_TRANSLUCENCY;

	if(!Def_SameStateSequence(r->state, s->state))
		df |= MDF_STATE;

	if(r->radius != s->radius)
		df |= MDF_RADIUS;
	if(r->height != s->height)
		df |= MDF_HEIGHT;
	if((r->ddflags & DDMF_PACK_MASK) != (s->ddflags & DDMF_PACK_MASK))
	{
		df |= MDF_FLAGS;
	}
	if(r->floorclip != s->floorclip)
		df |= MDF_FLOORCLIP;

	if(df)
	{
		// Init the delta with current data.
		Sv_NewDelta(d, DT_MOBJ, s->thinker.id);
		Sv_RegisterMobj(&d->mo, s);
	}

	d->delta.flags = df;

	return !Sv_IsVoidDelta(d);
}

/*
 * Returns true if the result is not void.
 */
boolean Sv_RegisterComparePlayer(cregister_t * reg, int number,
								 playerdelta_t * d)
{
	const dt_player_t *r = &reg->players[number];
	dt_player_t *s = &d->player;
	int     df = 0, i;

	// Init the delta with current data.
	Sv_NewDelta(d, DT_PLAYER, number);
	Sv_RegisterPlayer(&d->player, number);

	// Determine which data is different.
	if(r->mobj != s->mobj)
		df |= PDF_MOBJ;
	if(r->forwardMove != s->forwardMove)
		df |= PDF_FORWARDMOVE;
	if(r->sideMove != s->sideMove)
		df |= PDF_SIDEMOVE;
	if(r->angle != s->angle)
		df |= PDF_ANGLE;
	if(r->turnDelta != s->turnDelta)
		df |= PDF_TURNDELTA;
	if(r->friction != s->friction)
		df |= PDF_FRICTION;
	if(r->extraLight != s->extraLight || r->fixedColorMap != s->fixedColorMap)
	{
		df |= PDF_EXTRALIGHT;
	}
	if(r->filter != s->filter)
		df |= PDF_FILTER;
	if(r->clYaw != s->clYaw)
		df |= PDF_CLYAW;
	if(r->clPitch != s->clPitch)
		df |= PDF_CLPITCH;

	// The player sprites are a bit more complicated to check.
	for(i = 0; i < 2; i++)
	{
		int     off = 16 + i * 8;
		const ddpsprite_t *rps = r->psp + i;
		const ddpsprite_t *sps = s->psp + i;

		if(rps->stateptr != sps->stateptr)
			df |= PSDF_STATEPTR << off;

		if(rps->light != sps->light)
			df |= PSDF_LIGHT << off;
		if(rps->alpha != sps->alpha)
			df |= PSDF_ALPHA << off;
		if(rps->state != sps->state)
			df |= PSDF_STATE << off;
		if((rps->offx != sps->offx || rps->offy != sps->offy) && !i)
		{
			df |= PSDF_OFFSET << off;
		}
	}
	// Check for any psprite flags.
	if(df & 0xffff0000)
		df |= PDF_PSPRITES;

	d->delta.flags = df;
	return !Sv_IsVoidDelta(d);
}

/*
 * Returns true if the result is not void.
 */
boolean Sv_RegisterCompareSector(cregister_t * reg, int number,
								 sectordelta_t * d, byte doUpdate)
{
	dt_sector_t *r = &reg->sectors[number];
	const sector_t *s = SECTOR_PTR(number);
	int     df = 0;

	// Determine which data is different.
	if(r->floorPic != s->floorpic)
		df |= SDF_FLOORPIC;
	if(r->ceilingPic != s->ceilingpic)
		df |= SDF_CEILINGPIC;
	if(r->lightlevel != s->lightlevel)
		df |= SDF_LIGHT;
	if(r->rgb[0] != s->rgb[0])
		df |= SDF_COLOR_RED;
	if(r->rgb[1] != s->rgb[1])
		df |= SDF_COLOR_GREEN;
	if(r->rgb[2] != s->rgb[2])
		df |= SDF_COLOR_BLUE;

	// The cases where an immediate change to a plane's height is needed:
	// 1) Plane is not moving, but the heights are different. This means
	//    the plane's height was changed unpredictably.
	// 2) Plane is moving, but there is a large difference in the heights.
	//    The clientside height should be fixed.

	// Should we make an immediate change in floor height?
	if(!r->planes[PLN_FLOOR].speed && !s->planes[PLN_FLOOR].speed)
	{
		if(r->floorHeight != s->floorheight)
			df |= SDF_FLOOR_HEIGHT;
	}
	else
	{
		if(abs(r->floorHeight - s->floorheight) > PLANE_SKIP_LIMIT)
			df |= SDF_FLOOR_HEIGHT;
	}

	// How about the ceiling?
	if(!r->planes[PLN_CEILING].speed && !s->planes[PLN_CEILING].speed)
	{
		if(r->ceilingHeight != s->ceilingheight)
			df |= SDF_CEILING_HEIGHT;
	}
	else
	{
		if(abs(r->ceilingHeight - s->ceilingheight) > PLANE_SKIP_LIMIT)
			df |= SDF_CEILING_HEIGHT;
	}

	// Check planes, too.
	if(r->planes[PLN_FLOOR].target != s->planes[PLN_FLOOR].target)
	{
		df |= SDF_FLOOR_TARGET;
	}
	if(r->planes[PLN_FLOOR].speed != s->planes[PLN_FLOOR].speed)
	{
		df |= SDF_FLOOR_SPEED;
	}
	if(r->planes[PLN_FLOOR].texmove[0] != s->planes[PLN_FLOOR].texmove[0] ||
	   r->planes[PLN_FLOOR].texmove[1] != s->planes[PLN_FLOOR].texmove[1])
	{
		df |= SDF_FLOOR_TEXMOVE;
	}
	if(r->planes[PLN_CEILING].target != s->planes[PLN_CEILING].target)
	{
		df |= SDF_CEILING_TARGET;
	}
	if(r->planes[PLN_CEILING].speed != s->planes[PLN_CEILING].speed)
	{
		df |= SDF_CEILING_SPEED;
	}
	if(r->planes[PLN_CEILING].texmove[0] != s->planes[PLN_CEILING].texmove[0]
	   || r->planes[PLN_CEILING].texmove[1] !=
	   s->planes[PLN_CEILING].texmove[1])
	{
		df |= SDF_CEILING_TEXMOVE;
	}

	// Only do a delta when something changes.
	if(df)
	{
		// Init the delta with current data.
		Sv_NewDelta(d, DT_SECTOR, number);
		Sv_RegisterSector(&d->sector, number);

		if(doUpdate)
		{
			Sv_RegisterSector(r, number);
		}
	}

	if(doUpdate)
	{
		// The plane heights should be tracked regardless of the 
		// change flags.
		r->floorHeight = s->floorheight;
		r->ceilingHeight = s->ceilingheight;
	}

	d->delta.flags = df;
	return !Sv_IsVoidDelta(d);
}

/*
 * Returns true if the result is not void.
 */
boolean Sv_RegisterCompareSide(cregister_t * reg, int number, sidedelta_t * d,
							   byte doUpdate)
{
	const side_t *s = SIDE_PTR(number);
	const line_t *line = sideOwners[number];
	dt_side_t *r = &reg->sides[number];
	int     df = 0;
	byte    lineFlags = (line ? line->flags & 0xff : 0);

	if(r->topTexture != s->toptexture)
	{
		df |= SIDF_TOPTEX;
		if(doUpdate)
			r->topTexture = s->toptexture;
	}

	if(r->midTexture != s->midtexture)
	{
		df |= SIDF_MIDTEX;
		if(doUpdate)
			r->midTexture = s->midtexture;
	}

	if(r->bottomTexture != s->bottomtexture)
	{
		df |= SIDF_BOTTOMTEX;
		if(doUpdate)
			r->bottomTexture = s->bottomtexture;
	}

	if(r->lineFlags != lineFlags)
	{
		df |= SIDF_LINE_FLAGS;
		if(doUpdate)
			r->lineFlags = lineFlags;
	}

	// Was there any change?
	if(df)
	{
		// This happens quite rarely.
		// Init the delta with current data.
		Sv_NewDelta(d, DT_SIDE, number);
		Sv_RegisterSide(&d->side, number);
	}

	d->delta.flags = df;
	return !Sv_IsVoidDelta(d);
}

/*
 * Returns true if the result is not void.
 */
boolean Sv_RegisterComparePoly(cregister_t * reg, int number, polydelta_t * d)
{
	const dt_poly_t *r = &reg->polys[number];
	dt_poly_t *s = &d->po;
	int     df = 0;

	// Init the delta with current data.
	Sv_NewDelta(d, DT_POLY, number);
	Sv_RegisterPoly(&d->po, number);

	// What is different?
	if(r->dest.x != s->dest.x)
		df |= PODF_DEST_X;
	if(r->dest.y != s->dest.y)
		df |= PODF_DEST_Y;
	if(r->speed != s->speed)
		df |= PODF_SPEED;
	if(r->destAngle != s->destAngle)
		df |= PODF_DEST_ANGLE;
	if(r->angleSpeed != s->angleSpeed)
		df |= PODF_ANGSPEED;

	d->delta.flags = df;
	return !Sv_IsVoidDelta(d);
}

/*
 * Returns true if the mobj can be excluded from delta processing.
 */
boolean Sv_IsMobjIgnored(mobj_t *mo)
{
	return (mo->ddflags & DDMF_LOCAL) != 0;
}

/*
 * Returns true if the player can be excluded from delta processing.
 */
boolean Sv_IsPlayerIgnored(int number)
{
	return !players[number].ingame;
}

/*
 * Initialize the register with the current state of the world.
 * The arrays are allocated and the data is copied, nothing else is done.
 *
 * An initial register doesn't contain any mobjs. When new clients enter,
 * they know nothing about any mobjs. If the mobjs were included in the 
 * initial register, clients wouldn't receive much info from mobjs that
 * haven't moved since the beginning.
 */
void Sv_RegisterWorld(cregister_t * reg, boolean isInitial)
{
	int     i;

	memset(reg, 0, sizeof(*reg));
	reg->gametic = SECONDS_TO_TICKS(gameTime);

	// Is this the initial state?
	reg->isInitial = isInitial;

	// Init sectors.
	reg->sectors = Z_Calloc(sizeof(dt_sector_t) * numsectors, PU_LEVEL, 0);
	for(i = 0; i < numsectors; i++)
	{
		Sv_RegisterSector(&reg->sectors[i], i);
	}

	// Init sides.
	reg->sides = Z_Calloc(sizeof(dt_side_t) * numsides, PU_LEVEL, 0);
	for(i = 0; i < numsides; i++)
	{
		Sv_RegisterSide(&reg->sides[i], i);
	}

	// Init polyobjs.
	reg->polys =
		(po_NumPolyobjs ?
		 Z_Calloc(sizeof(dt_poly_t) * po_NumPolyobjs, PU_LEVEL, 0) : NULL);
	for(i = 0; i < po_NumPolyobjs; i++)
	{
		Sv_RegisterPoly(&reg->polys[i], i);
	}
}

/*
 * Update the pool owner's info.
 */
void Sv_UpdateOwnerInfo(pool_t * pool)
{
	ddplayer_t *player = &players[pool->owner];
	ownerinfo_t *info = &pool->ownerInfo;

	memset(info, 0, sizeof(*info));

	// Pointer to the owner's pool.
	info->pool = pool;

	if(player->mo)
	{
		info->x = player->mo->x;
		info->y = player->mo->y;
		info->z = player->mo->z;
		info->angle = player->mo->angle;
		info->speed = P_ApproxDistance(player->mo->momx, player->mo->momy);
	}

	// The acknowledgement threshold is a multiple of the average
	// ack time of the client. If an unacked delta is not acked within
	// the threshold, it'll be re-included in the ratings.
	info->ackThreshold = Net_GetAckThreshold(pool->owner);
}

/*
 * Returns a timestamp that is used to track how old deltas are.
 */
uint Sv_GetTimeStamp(void)
{
	return Sys_GetRealTime();
}

/*
 * Initialize a new delta.
 */
void Sv_NewDelta(void *deltaPtr, deltatype_t type, uint id)
{
	delta_t *delta = deltaPtr;

	// NOTE: This only clears the common delta_t part, not the extra data.
	memset(delta, 0, sizeof(*delta));

	delta->id = id;
	delta->type = type;
	delta->state = DELTA_NEW;
	delta->timeStamp = Sv_GetTimeStamp();
}

/*
 * Returns true if the delta contains no information.
 */
boolean Sv_IsVoidDelta(const void *delta)
{
	return ((const delta_t *) delta)->flags == 0;
}

/*
 * Returns true if the delta is a Sound delta.
 */
boolean Sv_IsSoundDelta(const void *delta)
{
	const delta_t *d = delta;

	return (d->type == DT_SOUND || d->type == DT_MOBJ_SOUND ||
			d->type == DT_SECTOR_SOUND || d->type == DT_POLY_SOUND);
}

/*
 * Returns true if the delta is a Start Sound delta.
 */
boolean Sv_IsStartSoundDelta(const void *delta)
{
	const sounddelta_t *d = delta;

	return Sv_IsSoundDelta(delta) && (d->delta.flags & SNDDF_VOLUME &&
									  d->volume > 0);
}

/*
 * Returns true if the delta is Stop Sound delta.
 */
boolean Sv_IsStopSoundDelta(const void *delta)
{
	const sounddelta_t *d = delta;

	return Sv_IsSoundDelta(delta) && (d->delta.flags & SNDDF_VOLUME &&
									  d->volume <= 0);
}

/*
 * Returns true if the delta is a Null Mobj delta.
 */
boolean Sv_IsNullMobjDelta(const void *delta)
{
	return ((const delta_t *) delta)->type == DT_MOBJ &&
		((const delta_t *) delta)->flags & MDFC_NULL;
}

/*
 * Returns true if the delta is a Create Mobj delta.
 */
boolean Sv_IsCreateMobjDelta(const void *delta)
{
	return ((const delta_t *) delta)->type == DT_MOBJ &&
		((const delta_t *) delta)->flags & MDFC_CREATE;
}

/*
 * Returns true if the deltas refer to the same object.
 */
boolean Sv_IsSameDelta(const void *delta1, const void *delta2)
{
	const delta_t *a = delta1, *b = delta2;

	return (a->type == b->type) && (a->id == b->id);
}

/*
 * Makes a copy of the delta. 
 */
void   *Sv_CopyDelta(void *deltaPtr)
{
	void   *newDelta;
	delta_t *delta = deltaPtr;
	int     size =
		(delta->type == DT_MOBJ ? sizeof(mobjdelta_t) : delta->type ==
		 DT_PLAYER ? sizeof(playerdelta_t) : delta->type ==
		 DT_SECTOR ? sizeof(sectordelta_t) : delta->type ==
		 DT_SIDE ? sizeof(sidedelta_t) : delta->type ==
		 DT_POLY ? sizeof(polydelta_t) : delta->type ==
		 DT_SOUND ? sizeof(sounddelta_t) : delta->type ==
		 DT_MOBJ_SOUND ? sizeof(sounddelta_t) : delta->type ==
		 DT_SECTOR_SOUND ? sizeof(sounddelta_t) : delta->type ==
		 DT_POLY_SOUND ? sizeof(sounddelta_t)
		 /* : delta->type == DT_LUMP?   sizeof(lumpdelta_t) */
		 : 0);

	if(size == 0)
	{
		Con_Error("Sv_CopyDelta: Unknown delta type %i.\n", delta->type);
	}

	newDelta = Z_Malloc(size, PU_LEVEL, 0);
	memcpy(newDelta, deltaPtr, size);
	return newDelta;
}

/*
 * Subtracts the contents of the second delta from the first delta.
 * Subtracting means that if a given flag is defined for both 1 and 2, 
 * the flag for 1 is cleared (2 overrides 1). The result is that the 
 * deltas can be applied in any order and the result is still correct.
 *
 * 1 and 2 must refer to the same entity!
 */
void Sv_SubtractDelta(void *deltaPtr1, const void *deltaPtr2)
{
	delta_t *delta = deltaPtr1;
	const delta_t *sub = deltaPtr2;

#ifdef _DEBUG
	if(!Sv_IsSameDelta(delta, sub))
	{
		Con_Error("Sv_SubtractDelta: Not the same!\n");
	}
#endif

	if(Sv_IsNullMobjDelta(sub))
	{
		// Null deltas kill everything.
		delta->flags = 0;
	}
	else
	{
		// Clear the common flags.
		delta->flags &= ~(delta->flags & sub->flags);
	}
}

/*
 * Applies the data in the source delta to the destination delta.
 * Both must be in the NEW state. Handles all types of deltas.
 */
void Sv_ApplyDeltaData(void *destDelta, const void *srcDelta)
{
	const delta_t *src = srcDelta;
	delta_t *dest = destDelta;
	int     sf = src->flags;

	if(src->type == DT_MOBJ)
	{
		const dt_mobj_t *s = &((const mobjdelta_t *) src)->mo;
		dt_mobj_t *d = &((mobjdelta_t *) dest)->mo;

		// *Always* set the player pointer.
		d->dplayer = s->dplayer;

		if(sf & (MDF_POS_X | MDF_POS_Y))
			d->subsector = s->subsector;
		if(sf & MDF_POS_X)
			d->x = s->x;
		if(sf & MDF_POS_Y)
			d->y = s->y;
		if(sf & MDF_POS_Z)
			d->z = s->z;
		if(sf & MDF_MOM_X)
			d->momx = s->momx;
		if(sf & MDF_MOM_Y)
			d->momy = s->momy;
		if(sf & MDF_MOM_Z)
			d->momz = s->momz;
		if(sf & MDF_ANGLE)
			d->angle = s->angle;
		if(sf & MDF_SELECTOR)
			d->selector = s->selector;
		if(sf & MDF_STATE)
		{
			d->state = s->state;
			d->tics = (s->state ? s->state->tics : 0);
		}
		if(sf & MDF_RADIUS)
			d->radius = s->radius;
		if(sf & MDF_HEIGHT)
			d->height = s->height;
		if(sf & MDF_FLAGS)
			d->ddflags = s->ddflags;
		if(sf & MDF_FLOORCLIP)
			d->floorclip = s->floorclip;
		if(sf & MDFC_TRANSLUCENCY)
			d->translucency = s->translucency;
	}
	else if(src->type == DT_PLAYER)
	{
		const dt_player_t *s = &((const playerdelta_t *) src)->player;
		dt_player_t *d = &((playerdelta_t *) dest)->player;

		if(sf & PDF_MOBJ)
			d->mobj = s->mobj;
		if(sf & PDF_FORWARDMOVE)
			d->forwardMove = s->forwardMove;
		if(sf & PDF_SIDEMOVE)
			d->sideMove = s->sideMove;
		if(sf & PDF_ANGLE)
			d->angle = s->angle;
		if(sf & PDF_TURNDELTA)
			d->turnDelta = s->turnDelta;
		if(sf & PDF_FRICTION)
			d->friction = s->friction;
		if(sf & PDF_EXTRALIGHT)
		{
			d->extraLight = s->extraLight;
			d->fixedColorMap = s->fixedColorMap;
		}
		if(sf & PDF_FILTER)
			d->filter = s->filter;
		if(sf & PDF_CLYAW)
			d->clYaw = s->clYaw;
		if(sf & PDF_CLPITCH)
			d->clPitch = s->clPitch;
		if(sf & PDF_PSPRITES)
		{
			int     i;

			for(i = 0; i < 2; i++)
			{
				int     off = 16 + i * 8;

				if(sf & (PSDF_STATEPTR << off))
				{
					d->psp[i].stateptr = s->psp[i].stateptr;
					d->psp[i].tics =
						(s->psp[i].stateptr ? s->psp[i].stateptr->tics : 0);
				}
				if(sf & (PSDF_LIGHT << off))
					d->psp[i].light = s->psp[i].light;
				if(sf & (PSDF_ALPHA << off))
					d->psp[i].alpha = s->psp[i].alpha;
				if(sf & (PSDF_STATE << off))
					d->psp[i].state = s->psp[i].state;
				if(sf & (PSDF_OFFSET << off))
				{
					d->psp[i].offx = s->psp[i].offx;
					d->psp[i].offy = s->psp[i].offy;
				}
			}
		}
	}
	else if(src->type == DT_SECTOR)
	{
		const dt_sector_t *s = &((const sectordelta_t *) src)->sector;
		dt_sector_t *d = &((sectordelta_t *) dest)->sector;

		if(sf & SDF_FLOORPIC)
			d->floorPic = s->floorPic;
		if(sf & SDF_CEILINGPIC)
			d->ceilingPic = s->ceilingPic;
		if(sf & SDF_LIGHT)
			d->lightlevel = s->lightlevel;
		if(sf & SDF_FLOOR_TARGET)
			d->planes[PLN_FLOOR].target = s->planes[PLN_FLOOR].target;
		if(sf & SDF_FLOOR_SPEED)
			d->planes[PLN_FLOOR].speed = s->planes[PLN_FLOOR].speed;
		if(sf & SDF_FLOOR_TEXMOVE)
		{
			memcpy(d->planes[PLN_FLOOR].texmove, s->planes[PLN_FLOOR].texmove,
				   sizeof(int) * 2);
		}
		if(sf & SDF_CEILING_TARGET)
			d->planes[PLN_CEILING].target = s->planes[PLN_CEILING].target;
		if(sf & SDF_CEILING_SPEED)
			d->planes[PLN_CEILING].speed = s->planes[PLN_CEILING].speed;
		if(sf & SDF_CEILING_TEXMOVE)
		{
			memcpy(d->planes[PLN_CEILING].texmove,
				   s->planes[PLN_CEILING].texmove, sizeof(int) * 2);
		}
		if(sf & SDF_FLOOR_HEIGHT)
			d->floorHeight = s->floorHeight;
		if(sf & SDF_CEILING_HEIGHT)
			d->ceilingHeight = s->ceilingHeight;
		if(sf & SDF_COLOR_RED)
			d->rgb[0] = s->rgb[0];
		if(sf & SDF_COLOR_GREEN)
			d->rgb[1] = s->rgb[1];
		if(sf & SDF_COLOR_BLUE)
			d->rgb[2] = s->rgb[2];
	}
	else if(src->type == DT_SIDE)
	{
		const dt_side_t *s = &((const sidedelta_t *) src)->side;
		dt_side_t *d = &((sidedelta_t *) dest)->side;

		if(sf & SIDF_TOPTEX)
			d->topTexture = s->topTexture;
		if(sf & SIDF_MIDTEX)
			d->midTexture = s->midTexture;
		if(sf & SIDF_BOTTOMTEX)
			d->bottomTexture = s->bottomTexture;
		if(sf & SIDF_LINE_FLAGS)
			d->lineFlags = s->lineFlags;
	}
	else if(src->type == DT_POLY)
	{
		const dt_poly_t *s = &((const polydelta_t *) src)->po;
		dt_poly_t *d = &((polydelta_t *) dest)->po;

		if(sf & PODF_DEST_X)
			d->dest.x = s->dest.x;
		if(sf & PODF_DEST_Y)
			d->dest.y = s->dest.y;
		if(sf & PODF_SPEED)
			d->speed = s->speed;
		if(sf & PODF_DEST_ANGLE)
			d->destAngle = s->destAngle;
		if(sf & PODF_ANGSPEED)
			d->angleSpeed = s->angleSpeed;
	}
	else if(Sv_IsSoundDelta(src))
	{
		const sounddelta_t *s = srcDelta;
		sounddelta_t *d = destDelta;

		if(sf & SNDDF_VOLUME)
			d->volume = s->volume;
		d->sound = s->sound;
	}
	else
	{
		Con_Error("Sv_ApplyDeltaData: Unknown delta type %i.\n", src->type);
	}
}

/*
 * Merges the second delta with the first one.
 * The source and destination must refer to the same entity.
 * Returns false if the result of the merge is a void delta.
 */
boolean Sv_MergeDelta(void *destDelta, const void *srcDelta)
{
	const delta_t *src = srcDelta;
	delta_t *dest = destDelta;

#ifdef _DEBUG
	if(!Sv_IsSameDelta(src, dest))
	{
		Con_Error("Sv_MergeDelta: Not the same!\n");
	}
	if(dest->state != DELTA_NEW)
	{
		Con_Error("Sv_MergeDelta: Dest is not NEW.\n");
	}
#endif

	if(Sv_IsNullMobjDelta(dest))
	{
		// Nothing can be merged with a null mobj delta.
		return true;
	}
	if(Sv_IsNullMobjDelta(src))
	{
		// Null mobj deltas kill the destination.
		dest->flags = MDFC_NULL;
		return true;
	}
	if(Sv_IsCreateMobjDelta(dest) && Sv_IsNullMobjDelta(src))
	{
		// Applying a Null mobj delta on a Create mobj delta causes
		// the two deltas to negate each other. Returning false 
		// signifies that both should be removed from the pool.
		dest->flags = 0;
		return false;
	}
	if(Sv_IsStartSoundDelta(src) || Sv_IsStopSoundDelta(src))
	{
		// Sound deltas completely override what they're being 
		// merged with. (Only one sound per source.) Stop Sound deltas must
		// kill NEW sound deltas, because what is the benefit of sending 
		// both in the same frame: first start a sound and then immediately
		// stop it? We don't want that.

		sounddelta_t *destSound = destDelta;
		const sounddelta_t *srcSound = srcDelta;

		// Destination becomes equal to source.
		dest->flags = src->flags;

		destSound->sound = srcSound->sound;
		destSound->mobj = srcSound->mobj;
		destSound->volume = srcSound->volume;
		return true;
	}

	// The destination will contain all of source's data in addition
	// to the existing data.
	dest->flags |= src->flags;

	// The time stamp must NOT be always updated: the delta already 
	// contains data which should've been sent some time ago. If we 
	// update the time stamp now, the overdue data might not be sent.
	/* dest->timeStamp = src->timeStamp; */

	Sv_ApplyDeltaData(dest, src);
	return true;
}

/*
 * Returns the age of the delta, in milliseconds.
 */
uint Sv_DeltaAge(const delta_t * delta)
{
	return Sv_GetTimeStamp() - delta->timeStamp;
}

/*
 * Approximate the distance to the given sector. Set 'mayBeGone' to true
 * if the mobj may have been destroyed and should not be processed.
 */
fixed_t Sv_MobjDistance(const mobj_t *mo, const ownerinfo_t * info,
						boolean isReal)
{
	fixed_t z;

	if(isReal && !P_IsUsedMobjID(mo->thinker.id))
	{
		// This mobj does not exist any more!
		return DDMAXINT;
	}

	z = mo->z;

	// Registered mobjs may have a maxed out Z coordinate.
	if(!isReal)
	{
		if(z == DDMININT)
			z = mo->floorz;
		if(z == DDMAXINT)
			z = mo->ceilingz - mo->height;
	}

	return P_ApproxDistance3(info->x - mo->x, info->y - mo->y,
							 info->z - (z + mo->height / 2));
}

/*
 * Approximate the distance to the given sector.
 */
fixed_t Sv_SectorDistance(int index, const ownerinfo_t * info)
{
	sector_t *sector = SECTOR_PTR(index);

	return P_ApproxDistance3(info->x - sectorOrigins[index].x,
							 info->y - sectorOrigins[index].y,
							 info->z -
							 ((sector->ceilingheight +
							   sector->floorheight) / 2));
}

/*
 * Returns the distance to the origin of the delta's entity.
 */
fixed_t Sv_DeltaDistance(const void *deltaPtr, const ownerinfo_t * info)
{
	const delta_t *delta = deltaPtr;

	if(delta->type == DT_MOBJ)
	{
#ifdef _DEBUG
		if(delta->flags & MDFC_NULL)
		{
			delta = delta;
		}
#endif
		// Use the delta's registered mobj position. For old unacked data,
		// it may be somewhat inaccurate.
		return Sv_MobjDistance(&((mobjdelta_t *) deltaPtr)->mo, info, false);
	}

	if(delta->type == DT_PLAYER)
	{
		// Use the player's actual position.
		const mobj_t *mo = players[delta->id].mo;

		if(mo)
		{
			return Sv_MobjDistance(mo, info, true);
		}
	}

	if(delta->type == DT_SECTOR)
	{
		return Sv_SectorDistance(delta->id, info);
	}

	if(delta->type == DT_SIDE)
	{
		return P_ApproxDistance(info->x - sideOrigins[delta->id].x,
								info->y - sideOrigins[delta->id].y);
	}

	if(delta->type == DT_POLY)
	{
		polyobj_t *po = PO_PTR(delta->id);

		return P_ApproxDistance(info->x - po->startSpot.x,
								info->y - po->startSpot.y);
	}

	if(delta->type == DT_MOBJ_SOUND)
	{
		const sounddelta_t *sound = deltaPtr;

		return Sv_MobjDistance(sound->mobj, info, true);
	}

	if(delta->type == DT_SECTOR_SOUND)
	{
		return Sv_SectorDistance(delta->id, info);
	}

	if(delta->type == DT_POLY_SOUND)
	{
		polyobj_t *po = PO_PTR(delta->id);

		return P_ApproxDistance(info->x - po->startSpot.x,
								info->y - po->startSpot.y);
	}

	// Unknown distance.
	return FRACUNIT;
}

/*
 * The hash function for the pool delta hash.
 */
deltalink_t *Sv_PoolHash(pool_t * pool, int id)
{
	return &pool->hash[(uint) id & POOL_HASH_FUNCTION_MASK];
}

/*
 * The delta is removed from the pool's delta hash.
 */
void Sv_RemoveDelta(pool_t * pool, void *deltaPtr)
{
	delta_t *delta = deltaPtr;
	deltalink_t *hash = Sv_PoolHash(pool, delta->id);

	// Update first and last links.
	if(hash->last == delta)
	{
		hash->last = delta->prev;
	}
	if(hash->first == delta)
	{
		hash->first = delta->next;
	}

	// Link the delta out of the list.
	if(delta->next)
	{
		delta->next->prev = delta->prev;
	}
	if(delta->prev)
	{
		delta->prev->next = delta->next;
	}

	// Destroy it.
	Z_Free(delta);
}

/*
 * Draining the pool means emptying it of all contents. (Doh?)
 */
void Sv_DrainPool(int clientNumber)
{
	pool_t *pool = &pools[clientNumber];
	delta_t *delta;
	misrecord_t *mis;
	void   *next = NULL;
	int     i;

	// Update the number of the owner.
	pool->owner = clientNumber;

	// Reset the counters.
	pool->setDealer = 0;
	pool->resendDealer = 0;

	Sv_PoolQueueClear(pool);

	// Free all deltas stored in the hash.
	for(i = 0; i < POOL_HASH_SIZE; i++)
	{
		for(delta = pool->hash[i].first; delta; delta = next)
		{
			next = delta->next;
			Z_Free(delta);
		}
	}

	// Free all missile records in the pool.
	for(i = 0; i < POOL_MISSILE_HASH_SIZE; i++)
	{
		for(mis = pool->misHash[i].first; mis; mis = next)
		{
			next = mis->next;
			Z_Free(mis);
		}
	}

	// Clear all the chains.
	memset(pool->hash, 0, sizeof(pool->hash));
	memset(pool->misHash, 0, sizeof(pool->misHash));
}

/*
 * Returns the maximum distance for the sound. If the origin is any
 * farther, the delta will not be sent to the client in question.
 */
fixed_t Sv_GetMaxSoundDistance(const sounddelta_t * delta)
{
	float   volume = 1;

	// Volume shortens the maximum distance (why send it if it's not 
	// audible?).
	if(delta->delta.flags & SNDDF_VOLUME)
	{
		volume = delta->volume;
	}
	if(volume <= 0)
	{
		// Silence is heard all over the world.
		return DDMAXINT;
	}
	return volume * sound_max_distance * FRACUNIT;
}

/*
 * Returns the flags that remain after exclusion.
 */
int Sv_ExcludeDelta(pool_t * pool, const void *deltaPtr)
{
	const delta_t *delta = deltaPtr;
	ddplayer_t *player = &players[pool->owner];
	mobj_t *poolViewer = player->mo;
	int     flags = delta->flags;

	// Can we exclude information from the delta? (for this player only)
	if(delta->type == DT_MOBJ)
	{
		const mobjdelta_t *mobjDelta = deltaPtr;

		if(poolViewer && poolViewer->thinker.id == delta->id)
		{
			// This is the mobj the owner of the pool uses as a camera.
			flags &= ~MDF_CAMERA_EXCLUDE;

			// We may have to exclude the pos/mom.
			if(!(player->flags & DDPF_FIXPOS))
			{
				flags &= ~MDF_POS;
			}
			if(!(player->flags & DDPF_FIXMOM))
			{
				flags &= ~MDF_MOM;
			}
		}

		// What about missiles? We might be allowed to exclude some 
		// information.
		if(mobjDelta->mo.ddflags & DDMF_MISSILE)
		{
			if(!Sv_IsCreateMobjDelta(delta))
			{
				// This'll might exclude the coordinates.
				// The missile is put on record when the client acknowledges
				// the Create Mobj delta.
				flags &= ~Sv_MRCheck(pool, mobjDelta);
			}
			else if(Sv_IsNullMobjDelta(delta))
			{
				// The missile is being removed entirely.
				// Remove the entry from the missile record.
				Sv_MRRemove(pool, delta->id);
			}
		}
	}
	else if(delta->type == DT_PLAYER)
	{
		if(pool->owner == delta->id)
		{
			// All information does not need to be sent.
			flags &= ~PDF_CAMERA_EXCLUDE;

			if(!(player->flags & DDPF_FIXANGLES))
			{
				// Fixangles means that the server overrides the clientside
				// view angles. Normally they are always clientside, so
				// exclude them here.
				flags &= ~(PDF_CLYAW | PDF_CLPITCH);
			}
		}
		else
		{
			// This is a remote player, the owner of the pool doesn't need
			// to know everything about it (like psprites).
			flags &= ~PDF_NONCAMERA_EXCLUDE;
		}
	}
	else if(Sv_IsSoundDelta(delta))
	{
		// Sounds that originate from too far away are not added to a pool.
		// Stop Sound deltas have an infinite max distance, though.
		if(Sv_DeltaDistance(delta, &pool->ownerInfo) >
		   Sv_GetMaxSoundDistance(deltaPtr))
		{
			// Don't add it.
			return 0;
		}
	}

	// These are the flags that remain.
	return flags;
}

/*
 * When adding a delta to the pool, it subtracts from the unacked deltas 
 * there and is merged with matching new deltas. If a delta becomes void 
 * after subtraction, it's removed from the pool. All the processing is 
 * done based on the ID number of the delta (and type), so to make things 
 * more efficient, a hash table is used (key is ID).
 *
 * Deltas are unique only in the NEW state. There may be multiple UNACKED
 * deltas for the same entity.
 *
 * The contents of the delta must not be modified.
 */
void Sv_AddDelta(pool_t * pool, void *deltaPtr)
{
	delta_t *iter;
	delta_t *next = NULL;
	delta_t *existingNew = NULL;
	delta_t *delta = deltaPtr;
	deltalink_t *hash = Sv_PoolHash(pool, delta->id);
	int     flags, originalFlags;

	// Sometimes we can exclude a part of the data, if the client has no
	// use for it.
	flags = Sv_ExcludeDelta(pool, delta);

	if(!flags)
	{
		// No data remains... No need to add this delta.
		return;
	}

	// Temporarily use the excluded flags.
	originalFlags = delta->flags;
	delta->flags = flags;

	// While subtracting from old deltas, we'll look for a pointer to
	// an existing NEW delta.
	for(iter = hash->first; iter; iter = next)
	{
		// Iter is removed if it becomes void.
		next = iter->next;

		// Sameness is determined with type and ID.
		if(Sv_IsSameDelta(iter, delta))
		{
			if(iter->state == DELTA_NEW)
			{
				// We'll merge with this instead of adding a new delta.
				existingNew = iter;
			}
			else if(iter->state == DELTA_UNACKED)
			{
				// The new information in the delta overrides the info in 
				// this unacked delta. Let's subtract. This way, if the 
				// unacked delta needs to be resent, it won't contain
				// obsolete data.
				Sv_SubtractDelta(iter, delta);

				// Was everything removed?
				if(Sv_IsVoidDelta(iter))
				{
					Sv_RemoveDelta(pool, iter);
					continue;
				}
			}
		}
	}

	if(existingNew)
	{
		// Merge the new delta with the older NEW delta.
		if(!Sv_MergeDelta(existingNew, delta))
		{
			// The deltas negated each other (Null -> Create).
			// The existing delta must be removed.
			Sv_RemoveDelta(pool, existingNew);
		}
	}
	else
	{
		// Add it to the end of the hash chain. We must take a copy 
		// of the delta so it can be stored in the hash.
		iter = Sv_CopyDelta(delta);

		if(hash->last)
		{
			hash->last->next = iter;
			iter->prev = hash->last;
		}
		hash->last = iter;

		if(!hash->first)
		{
			hash->first = iter;
		}
	}

	// This delta may yet be added to other pools. They should use the 
	// original flags, not the ones we might've used (hackish: copying the
	// whole delta is not really an option, though).
	delta->flags = originalFlags;
}

/*
 * Add the delta to all the pools in the NULL-terminated array.
 */
void Sv_AddDeltaToPools(void *deltaPtr, pool_t ** targets)
{
	for(; *targets; targets++)
	{
		Sv_AddDelta(*targets, deltaPtr);
	}
}

/*
 * All NEW deltas for the mobj are removed from the pool as obsolete.
 */
void Sv_PoolMobjRemoved(pool_t * pool, thid_t id)
{
	deltalink_t *hash = Sv_PoolHash(pool, id);
	delta_t *delta, *next = NULL;

	for(delta = hash->first; delta; delta = next)
	{
		next = delta->next;

		if(delta->state == DELTA_NEW && delta->type == DT_MOBJ &&
		   delta->id == id)
		{
			// This must be removed!
			Sv_RemoveDelta(pool, delta);
		}
	}

	// Also check the missile record.
	Sv_MRRemove(pool, id);
}

/*
 * This is called when a mobj is removed in a predictable fashion.
 * (Mobj state is NULL when it's destroyed. Assumption: The NULL state
 * is set only when animation reaches its end.) Because the register-mobj
 * is removed, no Null Mobj delta is generated for the mobj.
 */
void Sv_MobjRemoved(thid_t id)
{
	reg_mobj_t *mo = Sv_RegisterFindMobj(&worldRegister, id);
	int     i;

	if(mo)
	{
		Sv_RegisterRemoveMobj(&worldRegister, mo);

		// We must remove all NEW deltas for this mobj from the pools.
		// One possibility: there are mobj deltas waiting in the pool, 
		// but the mobj is removed here. Because it'll be no longer in 
		// the register, no Null Mobj delta is generated, and thus the 
		// client will eventually receive those mobj deltas unnecessarily.

		for(i = 0; i < MAXPLAYERS; i++)
		{
			if(clients[i].connected)
			{
				Sv_PoolMobjRemoved(&pools[i], id);
			}
		}
	}
}

/*
 * When a player leaves the game, his data is removed from the register.
 * Otherwise he'll not get all the data if he reconnects before the map
 * is changed.
 */
void Sv_PlayerRemoved(int playerNumber)
{
	dt_player_t *p = &worldRegister.players[playerNumber];

	memset(p, 0, sizeof(*p));
}

/*
 * Returns true if the pool is in the targets array.
 */
boolean Sv_IsPoolTargeted(pool_t * pool, pool_t ** targets)
{
	for(; *targets; targets++)
	{
		if(pool == *targets)
			return true;
	}
	return false;
}

/*
 * Fills the array with pointers to the pools of the connected clients,
 * if specificClient is < 0. Returns the number of pools in the list.
 */
int Sv_GetTargetPools(pool_t ** targets, int specificClient)
{
	int     i, numTargets = 0;

	if(specificClient >= 0)
	{
		targets[0] = &pools[specificClient];
		targets[1] = NULL;
		return 1;
	}

	for(i = 0; i < MAXPLAYERS; i++)
	{
		// Deltas must be generated for all connected players, even
		// if they aren't yet ready to receive them.
		if(clients[i].connected)
		{
			targets[numTargets++] = &pools[i];
		}
	}

	// A NULL pointer marks the end of target pools.
	targets[numTargets] = NULL;

	return numTargets;
}

/*
 * Null deltas are generated for mobjs that have been destroyed.
 * The register's mobj hash is scanned to see which mobjs no longer exist.
 *
 * When updating, the destroyed mobjs are removed from the register.
 */
void Sv_NewNullDeltas(cregister_t * reg, boolean doUpdate, pool_t ** targets)
{
	mobjhash_t *hash;
	reg_mobj_t *obj, *next = 0;
	mobjdelta_t null;
	int     i;

	for(i = 0, hash = reg->mobjs; i < REG_MOBJ_HASH_SIZE; i++, hash++)
	{
		for(obj = hash->first; obj; obj = next)
		{
			// This reg_mobj_t might be removed.
			next = obj->next;

			if(!P_IsUsedMobjID(obj->mo.thinker.id))
			{
				// This object no longer exists!
				Sv_NewDelta(&null, DT_MOBJ, obj->mo.thinker.id);
				null.delta.flags = MDFC_NULL;

				// We need all the data for positioning.
				memcpy(&null.mo, &obj->mo, sizeof(dt_mobj_t));

				Sv_AddDeltaToPools(&null, targets);

				/*#ifdef _DEBUG
				   Con_Printf("New null: %i, %s\n", obj->mo.thinker.id,
				   defs.states[obj->mo.state - states].id);
				   #endif */

				if(doUpdate)
				{
					// Keep the register up to date.
					Sv_RegisterRemoveMobj(reg, obj);
				}
			}
		}
	}
}

/*
 * Mobj deltas are generated for all mobjs that have changed.
 */
void Sv_NewMobjDeltas(cregister_t * reg, boolean doUpdate, pool_t ** targets)
{
	thinker_t *th;
	mobj_t *mo;
	mobjdelta_t delta;

	// All existing mobjs are processed.
	for(th = thinkercap.next; th != &thinkercap; th = th->next)
	{
		if(!P_IsMobjThinker(th->function))
			continue;

		mo = (mobj_t *) th;

		// Some objects should not be processed.
		if(Sv_IsMobjIgnored(mo))
			continue;

		// Compare to produce a delta.
		if(Sv_RegisterCompareMobj(reg, mo, &delta))
		{
			Sv_AddDeltaToPools(&delta, targets);

			if(doUpdate)
			{
				reg_mobj_t *obj;

				// This'll add a new register-mobj if it doesn't already exist.
				obj = Sv_RegisterAddMobj(reg, mo->thinker.id);
				Sv_RegisterMobj(&obj->mo, mo);
			}
		}
	}
}

/*
 * Player deltas are generated for changed player data.
 */
void Sv_NewPlayerDeltas(cregister_t * reg, boolean doUpdate, pool_t ** targets)
{
	playerdelta_t player;
	int     i;

	for(i = 0; i < MAXPLAYERS; i++)
	{
		if(Sv_IsPlayerIgnored(i))
			continue;

		// Compare to produce a delta.
		if(Sv_RegisterComparePlayer(reg, i, &player))
		{
			// Did the mobj change? If so, the old mobj must be zeroed
			// in the register. Otherwise, the clients may not receive
			// all the data they need (because of viewpoint exclusion 
			// flags).
			if(doUpdate && player.delta.flags & PDF_MOBJ)
			{
				reg_mobj_t *registered = Sv_RegisterFindMobj(reg,
															 reg->players[i].
															 mobj);
				if(registered)
				{
					Sv_RegisterResetMobj(&registered->mo);
				}
			}

			Sv_AddDeltaToPools(&player, targets);
		}

		if(doUpdate)
		{
			Sv_RegisterPlayer(&reg->players[i], i);
		}

		// What about forced deltas?
		if(Sv_IsPoolTargeted(&pools[i], targets))
		{
			if(players[i].flags & DDPF_FIXANGLES)
			{
				Sv_NewDelta(&player, DT_PLAYER, i);
				Sv_RegisterPlayer(&player.player, i);
				player.delta.flags = PDF_CLYAW | PDF_CLPITCH;

				// Once added to the pool, the information will not get lost.
				Sv_AddDelta(&pools[i], &player);

				// Doing this once is enough.
				players[i].flags &= ~DDPF_FIXANGLES;
			}

			// Generate a FIXPOS/FIXMOM mobj delta, too?
			if(players[i].mo && players[i].flags & (DDPF_FIXPOS | DDPF_FIXMOM))
			{
				const mobj_t *mo = players[i].mo;
				mobjdelta_t mobj;

				Sv_NewDelta(&mobj, DT_MOBJ, mo->thinker.id);
				Sv_RegisterMobj(&mobj.mo, mo);
				if(players[i].flags & DDPF_FIXPOS)
				{
					mobj.delta.flags |= MDF_POS;
				}
				if(players[i].flags & DDPF_FIXMOM)
				{
					mobj.delta.flags |= MDF_MOM;
				}

				Sv_AddDelta(&pools[i], &mobj);

				// Doing this once is enough.
				players[i].flags &= ~(DDPF_FIXPOS | DDPF_FIXMOM);
			}
		}
	}
}

/*
 * Sector deltas are generated for changed sectors.
 */
void Sv_NewSectorDeltas(cregister_t * reg, boolean doUpdate, pool_t ** targets)
{
	sectordelta_t delta;
	int     i;

	for(i = 0; i < numsectors; i++)
	{
		if(Sv_RegisterCompareSector(reg, i, &delta, doUpdate))
		{
			Sv_AddDeltaToPools(&delta, targets);
		}
	}
}

/*
 * Side deltas are generated for changed sides (and line flags).
 * Changes in sides (textures) are so rare that all sides need not be
 * checked on every tic.
 */
void Sv_NewSideDeltas(cregister_t * reg, boolean doUpdate, pool_t ** targets)
{
	static int numShifts = 2;
	static int shift = 0;
	sidedelta_t delta;
	int     i, start, end;

	// When comparing against an initial register, always compare all
	// sides (since the comparing is only done once, not continuously).
	if(reg->isInitial)
	{
		start = 0;
		end = numsides;
	}
	else
	{
		// Because there are so many sides in a typical map, the number
		// of compared sides soon accumulates to millions. To reduce the
		// load, we'll check only a portion of all sides for a frame.
		start = shift * numsides / numShifts;
		end = ++shift * numsides / numShifts;
		shift %= numShifts;
	}

	for(i = start; i < end; i++)
	{
		// The side must be owned by a line.
		if(sideOwners[i] == NULL)
			continue;

		if(Sv_RegisterCompareSide(reg, i, &delta, doUpdate))
		{
			Sv_AddDeltaToPools(&delta, targets);
		}
	}
}

/*
 * Poly deltas are generated for changed polyobjs.
 */
void Sv_NewPolyDeltas(cregister_t * reg, boolean doUpdate, pool_t ** targets)
{
	polydelta_t delta;
	int     i;

	for(i = 0; i < po_NumPolyobjs; i++)
	{
		if(Sv_RegisterComparePoly(reg, i, &delta))
		{
#ifdef _DEBUG
			Con_Printf("Sv_NewPolyDeltas: Change in %i\n", i);
#endif
			Sv_AddDeltaToPools(&delta, targets);
		}

		if(doUpdate)
		{
			Sv_RegisterPoly(&reg->polys[i], i);
		}
	}
}

/*
 * Adds a new sound delta to the appropriate pools.
 * Set 'justForClient' to < 0, if all clients should be targeted.
 * Because the starting of a sound is in itself a 'delta-like' event,
 * there is no need for comparing or to have a register.
 * Set 'volume' to zero to create a sound-stopping delta.
 *
 * ASSUME: No two sounds with the same ID play at the same time from the 
 *         same origin.
 */
void Sv_NewSoundDelta(int soundId, mobj_t *emitter, int sourceSector,
					  int sourcePoly, float volume, boolean isRepeating,
					  int justForClient)
{
	pool_t *targets[MAXPLAYERS + 1];
	sounddelta_t soundDelta;
	int     type = DT_SOUND;
	uint    id = soundId;
	int     df = 0;

	// Determine the target pools.
	Sv_GetTargetPools(targets, justForClient);

	if(sourceSector >= 0)
	{
		type = DT_SECTOR_SOUND;
		id = sourceSector;
	}
	else if(sourcePoly >= 0)
	{
		type = DT_POLY_SOUND;
		id = sourcePoly;
	}
	else if(emitter)
	{
		type = DT_MOBJ_SOUND;
		id = emitter->thinker.id;
		soundDelta.mobj = emitter;
	}

	// Init to the right type.
	Sv_NewDelta(&soundDelta, type, id);

	// Always set volume.
	df |= SNDDF_VOLUME;
	soundDelta.volume = volume;

	if(isRepeating)
		df |= SNDDF_REPEAT;

	// This is used by mobj/sector sounds.
	soundDelta.sound = soundId;

	soundDelta.delta.flags = df;
	Sv_AddDeltaToPools(&soundDelta, targets);
}

/*
 * Returns true if the client should receive frames.
 */
boolean Sv_IsFrameTarget(int number)
{
	// Local players receive frames only when they're recording a demo.
	// Clients must tell us they are ready before we can begin sending.
	return (players[number].ingame && !(players[number].flags & DDPF_LOCAL) &&
			clients[number].ready) || (players[number].flags & DDPF_LOCAL &&
									   clients[number].recording);
}

/*
 * Compare the current state of the world with the register and add the
 * deltas to all the pools, or if a specific client number is given, only
 * to its pool (done when a new client enters the game). No deltas will be
 * generated for predictable changes (state changes, linear movement...).
 *
 * Updating the register means that the current state of the world is stored
 * in the register after the deltas have been generated.
 *
 * clientNumber < 0: All ingame clients should get the deltas.
 */
void Sv_GenerateNewDeltas(cregister_t * reg, int clientNumber,
						  boolean doUpdate)
{
	pool_t *targets[MAXPLAYERS + 1], **pool;

	// Determine the target pools.
	Sv_GetTargetPools(targets, clientNumber);

	// Update the info of the pool owners.
	for(pool = targets; *pool; pool++)
	{
		Sv_UpdateOwnerInfo(*pool);
	}

	// Generate null deltas (removed mobjs).
	Sv_NewNullDeltas(reg, doUpdate, targets);

	// Generate mobj deltas.
	Sv_NewMobjDeltas(reg, doUpdate, targets);

	// Generate player deltas.
	Sv_NewPlayerDeltas(reg, doUpdate, targets);

	// Generate sector deltas.
	Sv_NewSectorDeltas(reg, doUpdate, targets);

	// Generate side deltas.
	Sv_NewSideDeltas(reg, doUpdate, targets);

	// Generate poly deltas.
	Sv_NewPolyDeltas(reg, doUpdate, targets);

	if(doUpdate)
	{
		// The register has now been updated to the current time.
		reg->gametic = SECONDS_TO_TICKS(gameTime);
	}
}

/*
 * This is called once for each frame, in Sv_TransmitFrame().
 */
void Sv_GenerateFrameDeltas(void)
{
	// Generate new deltas for all clients and update the world register.
	Sv_GenerateNewDeltas(&worldRegister, -1, true);
}

/*
 * Clears the priority queue of the pool.
 */
void Sv_PoolQueueClear(pool_t * pool)
{
	pool->queueSize = 0;
}

/*
 * Exchanges two elements in the queue.
 */
void Sv_PoolQueueExchange(pool_t * pool, int index1, int index2)
{
	delta_t *temp = pool->queue[index1];

	pool->queue[index1] = pool->queue[index2];
	pool->queue[index2] = temp;
}

/*
 * Adds the delta to the priority queue. More memory is allocated for 
 * the queue if necessary.
 */
void Sv_PoolQueueAdd(pool_t * pool, delta_t * delta)
{
	int     i, parent;

	// Do we need more memory?
	if(pool->allocatedSize == pool->queueSize)
	{
		delta_t **newQueue;

		// Double the memory.
		pool->allocatedSize *= 2;
		if(!pool->allocatedSize)
		{
			// At least eight.
			pool->allocatedSize = 8;
		}

		// Allocate the new queue.
		newQueue =
			Z_Malloc(pool->allocatedSize * sizeof(delta_t *), PU_LEVEL, 0);

		// Copy the old data.
		if(pool->queue)
		{
			memcpy(newQueue, pool->queue, sizeof(delta_t *) * pool->queueSize);

			// Get rid of the old queue.
			Z_Free(pool->queue);
		}

		pool->queue = newQueue;
	}

	// Add the new delta to the end of the queue array.
	i = pool->queueSize;
	pool->queue[i] = delta;
	++pool->queueSize;

	// Rise in the heap until the correct place is found.
	while(i > 0)
	{
		parent = HEAP_PARENT(i);

		// Is it good now?
		if(pool->queue[parent]->score >= delta->score)
			break;

		// Exchange with the parent.
		Sv_PoolQueueExchange(pool, parent, i);

		i = parent;
	}
}

/*
 * Extracts the delta with the highest priority from the queue.
 * Returns NULL if there are no more deltas.
 */
delta_t *Sv_PoolQueueExtract(pool_t * pool)
{
	delta_t *max;
	int     i = 0, left, right, big;

	if(!pool->queueSize)
	{
		// There is nothing in the queue.
		return NULL;
	}

	// This is what we'll return.
	max = pool->queue[0];

	// Remove the first element from the queue.
	pool->queue[0] = pool->queue[--pool->queueSize];

	// Heapify the heap. This is O(log n).
	while(true)
	{
		left = HEAP_LEFT(i);
		right = HEAP_RIGHT(i);
		big = i;

		// Which child is more important?
		if(left < pool->queueSize &&
		   pool->queue[left]->score > pool->queue[i]->score)
		{
			big = left;
		}
		if(right < pool->queueSize &&
		   pool->queue[right]->score > pool->queue[big]->score)
		{
			big = right;
		}

		// Can we stop now?
		if(big == i)
		{
			// Heapifying is complete.
			break;
		}

		// Exchange and continue.
		Sv_PoolQueueExchange(pool, i, big);
		i = big;
	}

	return max;
}

/*
 * Postponed deltas can't be sent yet.
 */
boolean Sv_IsPostponedDelta(void *deltaPtr, ownerinfo_t * info)
{
	delta_t *delta = deltaPtr;
	uint    age = Sv_DeltaAge(delta);

	if(delta->state == DELTA_UNACKED)
	{
		// Is it old enough? If not, it's still possible that the ack 
		// has not reached us yet. 
		return age < info->ackThreshold;
	}
	else if(delta->state == DELTA_NEW)
	{
		// Normally NEW deltas are never postponed. They are sent as soon 
		// as possible.
		if(Sv_IsStopSoundDelta(delta))
		{
			// Stop Sound deltas require a bit of care. To make sure they 
			// arrive to the client in the correct order, we won't send 
			// a Stop Sound until we can be sure all the Start Sound deltas
			// have arrived. (i.e. the pool must contain no Unacked Start 
			// Sound deltas for the same source.)

			delta_t *iter;

			for(iter = Sv_PoolHash(info->pool, delta->id)->first; iter;
				iter = iter->next)
			{
				if(iter->state == DELTA_UNACKED && Sv_IsSameDelta(iter, delta)
				   && Sv_IsStartSoundDelta(iter))
				{
					// Must postpone this Stop Sound delta until this one
					// has been sent.
#ifdef _DEBUG
					Con_Printf("POSTPONE: Stop %i\n", delta->id);
#endif
					return true;
				}
			}
		}
	}

	// This delta is not postponed.
	return false;
}

/*
 * Calculate a priority score for the delta. A higher score indicates 
 * greater importance. Returns true if the delta should be included
 * in the queue.
 */
boolean Sv_RateDelta(void *deltaPtr, ownerinfo_t * info)
{
	float   baseScores[NUM_DELTA_TYPES] = {
		1000,					// DT_MOBJ
		1000,					// DT_PLAYER
		2000,					// DT_SECTOR
		800,					// DT_SIDE
		2000,					// DT_POLY
		0,						// DT_LUMP
		2000,					// DT_SOUND
		3000,					// DT_MOBJ_SOUND
		5000,					// DT_SECTOR_SOUND
		5000,					// DT_POLY_SOUND
	};

	float   score, distance, size;
	delta_t *delta = deltaPtr;
	int     df = delta->flags;
	uint    age = Sv_DeltaAge(delta);

	// The importance doubles normally in 5 seconds.
	float   ageScoreDouble = 5.0f;

	if(Sv_IsPostponedDelta(delta, info))
	{
		// This delta will not be considered at this time.
		return false;
	}

	// Calculate the distance to the delta's origin.
	// If no distance can be determined, it's 1.0.
	distance = FIX2FLT(Sv_DeltaDistance(delta, info));

	// What is the base score?
	score = baseScores[delta->type] / distance;

	// It's very important to send sound deltas in time.
	if(Sv_IsSoundDelta(delta))
	{
		// Score doubles very quickly.
		ageScoreDouble = 1;
	}

	// Deltas become more important with age (milliseconds).
	score *= 1 + age / (ageScoreDouble * 1000.0f);

	// FIXME: Consider viewpoint speed and angle.

	// Priority bonuses based on the contents of the delta.
	if(delta->type == DT_MOBJ)
	{
		const mobj_t *mo = &((mobjdelta_t *) delta)->mo;

		// Seeing new mobjs is interesting.
		if(df & MDFC_CREATE)
			score *= 1.1f;

		// Position changes are important.
		if(df & (MDF_POS_X | MDF_POS_Y))
			score *= 1.2f;

		// Small objects are not that important.
		size = FIX2FLT(MAX_OF(mo->radius, mo->height));
		if(size < 16)
		{
			// Not too small, though.
			if(size < 2)
				size = 2;

			score *= size / 16;
		}
		else if(size > 50)
		{
			// Large objects are important.
			score *= size / 50;
		}
	}
	else if(delta->type == DT_PLAYER)
	{
		// Knowing the player's mobj is quite important.
		if(df & PDF_MOBJ)
			score *= 2;
	}
	else if(delta->type == DT_SECTOR)
	{
		// Lightlevel changes are very noticeable.
		if(df & SDF_LIGHT)
			score *= 1.2f;

		// Plane movements are very important (can be seen from far away).
		if(df &
		   (SDF_FLOOR_HEIGHT | SDF_CEILING_HEIGHT | SDF_FLOOR_SPEED |
			SDF_CEILING_SPEED | SDF_FLOOR_TARGET | SDF_CEILING_TARGET))
		{
			score *= 3;
		}
	}
	else if(delta->type == DT_POLY)
	{
		// Changes in speed are noticeable.
		if(df & PODF_SPEED)
			score *= 1.2f;
	}

	// This is the final score. Only positive scores are accepted in
	// the frame (deltas with nonpositive scores as ignored).
	return (delta->score = score) > 0;
}

/*
 * Calculate a priority score for each delta and build the priority queue.
 * The most important deltas will be included in a frame packet.
 * A pool is rated after new deltas have been generated. 
 */
void Sv_RatePool(pool_t * pool)
{
#ifdef _DEBUG
	ddplayer_t *player = &players[pool->owner];
	client_t *client = &clients[pool->owner];
#endif
	delta_t *delta;
	int     i;

#ifdef _DEBUG
	if(!player->mo)
	{
		Con_Error("Sv_RatePool: Player %i has no mobj.\n", pool->owner);
	}
#endif

	// Clear the queue.
	Sv_PoolQueueClear(pool);

	// We will rate all the deltas in the pool. After each delta 
	// has been rated, it's added to the priority queue.
	for(i = 0; i < POOL_HASH_SIZE; i++)
	{
		for(delta = pool->hash[i].first; delta; delta = delta->next)
		{
			if(Sv_RateDelta(delta, &pool->ownerInfo))
			{
				Sv_PoolQueueAdd(pool, delta);
			}
		}
	}
}

/*
 * Do special things that need to be done when the delta has been acked.
 */
void Sv_AckDelta(pool_t * pool, delta_t * delta)
{
	if(Sv_IsCreateMobjDelta(delta))
	{
		mobjdelta_t *mobjDelta = (mobjdelta_t *) delta;

		// Created missiles are put on record.
		if(mobjDelta->mo.ddflags & DDMF_MISSILE)
		{
			// Once again, we're assuming the delta is always completely
			// filled with valid information. (There are no 'partial' deltas.)
			Sv_MRAdd(pool, mobjDelta);
		}
	}
}

/*
 * Acknowledged deltas are removed from the pool, never to be seen again.
 * Clients ack deltas to tell the server they've received them.
 * If 'resent' is nonzero, ignore 'set' and ack by resend ID.
 */
void Sv_AckDeltaSet(int consoleNumber, int set, byte resent)
{
	pool_t *pool = &pools[consoleNumber];
	delta_t *delta, *next = NULL;
	boolean ackTimeRegistered = false;
	int     i;

	// Iterate through the entire hash table. 
	for(i = 0; i < POOL_HASH_SIZE; i++)
	{
		for(delta = pool->hash[i].first; delta; delta = next)
		{
			next = delta->next;
			if(delta->state == DELTA_UNACKED &&
			   ((!resent && delta->set == set) ||
				(resent && delta->resend == resent)))
			{
				// Register the ack time only for the first acked delta.
				if(!ackTimeRegistered)
				{
					Net_SetAckTime(consoleNumber, Sv_DeltaAge(delta));
					ackTimeRegistered = true;
				}

				// There may be something that we need to do now that the
				// delta has been acknowledged.
				Sv_AckDelta(pool, delta);

				// This delta is now finished! 
				Sv_RemoveDelta(pool, delta);
			}
		}
	}
}
