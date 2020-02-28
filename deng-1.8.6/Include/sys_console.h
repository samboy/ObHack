/* DE1: $Id: sys_console.h,v 1.6 2004/05/31 15:04:41 skyjake Exp $
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
 * sys_console.h: Win32 Console
 */

#ifndef __DOOMSDAY_WINCONSOLE_H__
#define __DOOMSDAY_WINCONSOLE_H__

void            Sys_ConInit();
void            Sys_ConShutdown();
void            Sys_ConPostEvents();
void            Sys_ConPrint(int clflags, char *text);
void            Sys_ConUpdateCmdLine(char *text);

#endif
