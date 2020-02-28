/* DE1: $Id: r_extres.h,v 1.12 2005/01/08 15:34:13 skyjake Exp $
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
 * r_extres.h: External Resources
 */

#ifndef __DOOMSDAY_REFRESH_EXT_RES_H__
#define __DOOMSDAY_REFRESH_EXT_RES_H__

/*
 * Resource classes. Each has its own subdir under Data\Game\.
 */
typedef enum resourceclass_e {
	RC_TEXTURE,
    RC_FLAT,
	RC_PATCH,				   // Not sprites, mind you. Names == lumpnames.
	RC_LIGHTMAP,
	RC_MUSIC,				   // Names == lumpnames.
	RC_SFX,					   // Names == lumpnames.
	RC_GRAPHICS,			   // Doomsday graphics.
	NUM_RESOURCE_CLASSES
} resourceclass_t;

void            R_InitExternalResources(void);
void            R_SetDataPath(const char *path);
void            R_InitDataPaths(const char *path, boolean justGamePaths);
const char     *R_GetDataPath(void);
void            R_PrependDataPath(const char *origPath, char *newPath);
boolean         R_FindResource(resourceclass_t resClass, const char *name,
							   const char *optionalSuffix, char *fileName);

#endif
