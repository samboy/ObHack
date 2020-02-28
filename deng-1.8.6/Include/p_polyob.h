/* DE1: $Id: p_polyob.h,v 1.7 2004/05/31 15:04:41 skyjake Exp $
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
 * p_polyob.h: Polygon Objects
 */

#ifndef __DOOMSDAY_POLYOB_H__
#define __DOOMSDAY_POLYOB_H__

//==========================================================================
// Data
//==========================================================================
extern byte    *polyobjs;		   // list of all poly-objects on the level
extern int      po_NumPolyobjs;

//==========================================================================
// Functions
//==========================================================================
void            PO_SetCallback(void (*func) (mobj_t *, void *, void *));
boolean         PO_MovePolyobj(int num, int x, int y);
boolean         PO_RotatePolyobj(int num, angle_t angle);
void            PO_UnLinkPolyobj(polyobj_t * po);
void            PO_LinkPolyobj(polyobj_t * po);
int             PO_GetNumForDegen(void *degenMobj);

#endif
