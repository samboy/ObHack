/* DE1: $Id: m_huffman.h,v 1.7 2004/05/31 15:04:41 skyjake Exp $
 * Copyright (C) 2003, 2004 Jaakko Keränen <jaakko.keranen@iki.fi>
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
 * m_huffman.h: Huffman Codes
 */

#ifndef __DOOMSDAY_MISC_HUFFMAN_H__
#define __DOOMSDAY_MISC_HUFFMAN_H__

void            Huff_Init(void);
void            Huff_Shutdown(void);
void           *Huff_Encode(byte *data, uint size, uint *encodedSize);
byte           *Huff_Decode(void *data, uint size, uint *decodedSize);

#endif
