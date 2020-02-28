/* DE1: $Id: gl_hq2x.h,v 1.3 2004/05/29 09:53:10 skyjake Exp $
 * Copyright (C) 2004 Jaakko Ker�nen <jaakko.keranen@iki.fi>
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
 * gl_hq2x.h: High-Quality 2x Graphics Resizing
 */

#ifndef __DOOMSDAY_HQ2X_H__
#define __DOOMSDAY_HQ2X_H__

void            GL_InitSmartFilter(void);
void            GL_SmartFilter2x(unsigned char *pIn, unsigned char *pOut,
								 int Xres, int Yres, int BpL);

#endif
