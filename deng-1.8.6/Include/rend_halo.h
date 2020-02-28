/* DE1: $Id: rend_halo.h,v 1.7 2004/07/10 07:43:21 skyjake Exp $
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
 * rend_halo.h: Halos and Flares
 */

#ifndef __DOOMSDAY_RENDER_HALO_H__
#define __DOOMSDAY_RENDER_HALO_H__

#include "con_decl.h"

extern int      haloOccludeSpeed;
extern int      haloMode, haloRealistic, haloBright, haloSize;
extern float    haloFadeMax, haloFadeMin, minHaloSize;

void            H_Register(void);
void            H_SetupState(boolean dosetup);
void            H_RenderHalo(vissprite_t * sourcevis, boolean primary);

// Console commands.
D_CMD(FlareConfig);

#endif
