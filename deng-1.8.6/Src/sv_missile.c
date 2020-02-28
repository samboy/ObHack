/* DE1: $Id: sv_missile.c,v 1.7 2004/05/31 15:04:44 skyjake Exp $
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
 * sv_missile.c: Delta Pool Missile Record
 */

// HEADER FILES ------------------------------------------------------------

#include "de_base.h"
#include "de_console.h"
#include "de_network.h"
#include "de_refresh.h"
#include "de_play.h"

// MACROS ------------------------------------------------------------------

// TYPES -------------------------------------------------------------------

// EXTERNAL FUNCTION PROTOTYPES --------------------------------------------

// PUBLIC FUNCTION PROTOTYPES ----------------------------------------------

// PRIVATE FUNCTION PROTOTYPES ---------------------------------------------

// EXTERNAL DATA DECLARATIONS ----------------------------------------------

// PUBLIC DATA DEFINITIONS -------------------------------------------------

// PRIVATE DATA DEFINITIONS ------------------------------------------------

// CODE --------------------------------------------------------------------

/*
 * Returns a pointer to the hash chain.
 */
mislink_t *Sv_MRHash(pool_t * pool, thid_t id)
{
	return &pool->misHash[(unsigned) id % POOL_MISSILE_HASH_SIZE];
}

/*
 * Returns a pointer to the missile record for the specified ID.
 * If no record exits, returns NULL.
 */
misrecord_t *Sv_MRFind(pool_t * pool, thid_t id)
{
	mislink_t *hash = Sv_MRHash(pool, id);
	misrecord_t *mis;

	for(mis = hash->first; mis; mis = mis->next)
	{
		if(mis->id == id)
		{
			// This is it.
			return mis;
		}
	}
	return NULL;
}

/*
 * Adds an entry for the mobj into the missile record.
 */
void Sv_MRAdd(pool_t * pool, const mobjdelta_t * delta)
{
	thid_t  id = delta->delta.id;
	mislink_t *hash = Sv_MRHash(pool, id);
	misrecord_t *mis;

#ifdef _DEBUG
	if(!(delta->mo.ddflags & DDMF_MISSILE))
	{
		Con_Error("Sv_MRAdd: Not a missile.\n");
	}
#endif

	// Try to find an existing entry.
	mis = Sv_MRFind(pool, id);

	// Create a new record if necessary.
	if(!mis)
	{
		mis = Z_Malloc(sizeof(misrecord_t), PU_LEVEL, 0);
		mis->id = id;

		// Link it in.
		mis->next = NULL;
		mis->prev = hash->last;
		if(hash->last)
			hash->last->next = mis;
		hash->last = mis;
		if(!hash->first)
			hash->first = mis;
	}

	// Update the momentum.
	/*
	   mis->momx = delta->mo.momx;
	   mis->momy = delta->mo.momy;
	   mis->momz = delta->mo.momz;
	 */
}

/*
 * Remove the missile from the record. This is called when the missile
 * mobj is destroyed.
 */
void Sv_MRRemove(pool_t * pool, thid_t id)
{
	mislink_t *hash = Sv_MRHash(pool, id);
	misrecord_t *mis;

	for(mis = hash->first; mis; mis = mis->next)
	{
		if(mis->id == id)
		{
			// This will be removed.
			if(hash->first == mis)
				hash->first = mis->next;
			if(hash->last == mis)
				hash->last = mis->prev;
			if(mis->next)
				mis->next->prev = mis->prev;
			if(mis->prev)
				mis->prev->next = mis->next;

			// There will be no more records to remove.
			break;
		}
	}
}

/*
 * Returns the flags that should be excluded from the missile delta.
 */
int Sv_MRCheck(pool_t * pool, const mobjdelta_t * mobj)
{
	misrecord_t *mis;
	int     exclude = 0;

#ifdef _DEBUG
	if(!(mobj->mo.ddflags & DDMF_MISSILE))
	{
		Con_Error("Sv_MRCheck: Not a missile.\n");
	}
#endif

	if((mis = Sv_MRFind(pool, mobj->delta.id)) == NULL)
	{
		// No record for this; no basis for exclusion.
		return 0;
	}

	// Exclude each axis separately. If no change in momentum, exclude coord.
	if(!(mobj->delta.flags & MDF_MOM_X))
		exclude |= MDF_POS_X;
	if(!(mobj->delta.flags & MDF_MOM_Y))
		exclude |= MDF_POS_Y;
	if(!(mobj->delta.flags & MDF_MOM_Z))
		exclude |= MDF_POS_Z;

	return exclude;
}
