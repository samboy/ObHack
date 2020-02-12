//------------------------------------------------------------------------
//  IMAGE manipulations
//------------------------------------------------------------------------
//
//  Oblige Level Maker (C) 2006,2007 Andrew Apted
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//------------------------------------------------------------------------

#ifndef __OBLIGE_IMAGE_H__
#define __OBLIGE_IMAGE_H__

void Image_Setup(void);

const byte *Image_MakePatch(int what, int *length, int dest_w);

void Image_FreePatch(const byte *pat);

#endif /* __OBLIGE_IMAGE_H__ */
