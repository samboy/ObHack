/* DE1: $Id: sv_missile.h,v 1.6 2004/05/31 15:04:41 skyjake Exp $
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
 * sv_missile.h: Delta Pool Missile Record
 */

#ifndef __DOOMSDAY_SERVER_POOL_MISSILE_H__
#define __DOOMSDAY_SERVER_POOL_MISSILE_H__

#include "sv_def.h"
#include "sv_pool.h"

misrecord_t    *Sv_MRFind(pool_t * pool, thid_t id);
void            Sv_MRAdd(pool_t * pool, const mobjdelta_t * delta);
int             Sv_MRCheck(pool_t * pool, const mobjdelta_t * mobj);
void            Sv_MRRemove(pool_t * pool, thid_t id);

#endif
