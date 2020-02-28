/* DE1: $Id: p_think.c,v 1.10 2004/05/31 15:04:43 skyjake Exp $
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
 *
 * Based on Hexen by Raven Software.
 */

/*
 * p_think.c: Thinkers
 */

// HEADER FILES ------------------------------------------------------------

#include "de_base.h"
#include "de_defs.h"
#include "de_console.h"
#include "de_network.h"

// MACROS ------------------------------------------------------------------

// TYPES -------------------------------------------------------------------

// EXTERNAL FUNCTION PROTOTYPES --------------------------------------------

// PUBLIC FUNCTION PROTOTYPES ----------------------------------------------

// PRIVATE FUNCTION PROTOTYPES ---------------------------------------------

// EXTERNAL DATA DECLARATIONS ----------------------------------------------

// PUBLIC DATA DEFINITIONS -------------------------------------------------

int     idtable[2048];			// 65536 bits telling which IDs are in use
unsigned short iddealer = 0;

thinker_t thinkercap;			// The head and tail of the thinker list

// PRIVATE DATA DEFINITIONS ------------------------------------------------

// CODE --------------------------------------------------------------------

//==========================================================================
//
// P_IsMobjThinker
//
//==========================================================================
boolean P_IsMobjThinker(think_t thinker)
{
	think_t altfunc = (think_t) gx.Get(DD_ALT_MOBJ_THINKER);

	return (thinker == gx.MobjThinker || (altfunc && thinker == altfunc));
}

//==========================================================================
//
// P_ClearMobjIDs
//
//==========================================================================
void P_ClearMobjIDs(void)
{
	memset(idtable, 0, sizeof(idtable));
	idtable[0] |= 1;			// ID zero is always "used" (it's not a valid ID).
}

//==========================================================================
//
// P_IsUsedMobjID
//
//==========================================================================
boolean P_IsUsedMobjID(thid_t id)
{
	return idtable[id >> 5] & (1 << (id & 31) /*(id % 32) */ );
}

//==========================================================================
//
// P_SetMobjID
//
//==========================================================================
void P_SetMobjID(thid_t id, boolean state)
{
	int     c = id >> 5, bit = 1 << (id & 31);	//(id % 32);

	if(state)
		idtable[c] |= bit;
	else
		idtable[c] &= ~bit;
}

//==========================================================================
//
// P_NewMobjID
//
//==========================================================================
thid_t P_NewMobjID(void)
{
	// Increment the ID dealer until a free ID is found.
	// FIXME: What if all IDs are in use? 65535 thinkers!?
	while(P_IsUsedMobjID(++iddealer));
	// Mark this ID as used.
	P_SetMobjID(iddealer, true);
	return iddealer;
}

//==========================================================================
// P_RunThinkers
//==========================================================================
void P_RunThinkers(void)
{
	thinker_t *currentthinker;

	currentthinker = thinkercap.next;
	while(currentthinker != &thinkercap)
	{
		if(currentthinker->function == (think_t) - 1)
		{						// Time to remove it
			currentthinker->next->prev = currentthinker->prev;
			currentthinker->prev->next = currentthinker->next;
			Z_Free(currentthinker);
		}
		else if(currentthinker->function)
		{
			currentthinker->function(currentthinker);
		}
		currentthinker = currentthinker->next;
	}
}

//==========================================================================
// P_InitThinkers
//==========================================================================
void P_InitThinkers(void)
{
	thinkercap.prev = thinkercap.next = &thinkercap;
	P_ClearMobjIDs();
}

//==========================================================================
// P_AddThinker
//  Adds a new thinker at the end of the list.
//==========================================================================
void P_AddThinker(thinker_t *thinker)
{
	// Link the thinker to the thinker list.
	thinkercap.prev->next = thinker;
	thinker->next = &thinkercap;
	thinker->prev = thinkercap.prev;
	thinkercap.prev = thinker;

	// Will it need an ID?
	if(P_IsMobjThinker(thinker->function))
	{
		// It is a mobj, give it an ID.
		thinker->id = P_NewMobjID();
	}
	else
	{
		// Zero is not a valid ID.
		thinker->id = 0;
	}
}

//==========================================================================
// P_RemoveThinker
//  Deallocation is lazy -- it will not actually be freed until its
//  thinking turn comes up.
//==========================================================================
void P_RemoveThinker(thinker_t *thinker)
{
	// Has got an ID?
	if(thinker->id)
	{
		// Then it must be a mobj.
		mobj_t *mo = (mobj_t *) thinker;

		// Flag the ID as free.
		P_SetMobjID(thinker->id, false);

		// If the state of the mobj is the NULL state, this is a 
		// predictable mobj removal (result of animation reaching its
		// end) and shouldn't be included in netgame deltas. 
		if(!isClient)
		{
			if(!mo->state || mo->state == states)
			{
				Sv_MobjRemoved(thinker->id);
			}
		}
	}
	thinker->function = (think_t) - 1;
}
