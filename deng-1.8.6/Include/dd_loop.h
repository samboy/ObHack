/* DE1: $Id: dd_loop.h,v 1.11 2005/01/02 01:03:12 skyjake Exp $
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
 * dd_loop.h: Main Loop
 */

#ifndef __DOOMSDAY_BASELOOP_H__
#define __DOOMSDAY_BASELOOP_H__

extern timespan_t sysTime, gameTime, demoTime, levelTime;

void            DD_RegisterLoop(void);
void            DD_GameLoop(void);
void            DD_DrawAndBlit(void);
void            DD_StartFrame(void);
void            DD_EndFrame(void);
float			DD_GetFrameRate(void);
void			DD_ResetTimer(void);

#endif
