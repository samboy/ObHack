/* DE1: $Id: cl_sound.h,v 1.7 2004/05/31 15:04:41 skyjake Exp $
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
 * cl_sound.h: Clientside Sounds
 */

#ifndef __DOOMSDAY_CLIENT_SOUND_H__
#define __DOOMSDAY_CLIENT_SOUND_H__

void            Cl_ReadSoundDelta2(deltatype_t type, boolean skip);
void            Cl_Sound(void);

#endif
