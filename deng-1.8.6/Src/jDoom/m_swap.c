// Emacs style mode select   -*- C++ -*- 
//-----------------------------------------------------------------------------
//
// $Id: m_swap.c,v 1.6 2005/01/01 22:58:52 skyjake Exp $
//
// Copyright (C) 1993-1996 by id Software, Inc.
//
// This source is available for distribution and/or modification
// only under the terms of the DOOM Source Code License as
// published by id Software. All rights reserved.
//
// The source is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// FITNESS FOR A PARTICULAR PURPOSE. See the DOOM Source Code License
// for more details.
//
// $Log: m_swap.c,v $
// Revision 1.6  2005/01/01 22:58:52  skyjake
// Resolved a bunch of compiler warnings
//
// Revision 1.5  2004/05/29 09:53:29  skyjake
// Consistent style (using GNU Indent)
//
// Revision 1.4  2004/05/28 19:52:58  skyjake
// Finished switch from branch-1-7 to trunk, hopefully everything is fine
//
// Revision 1.1.2.1  2004/05/16 10:01:36  skyjake
// Merged good stuff from branch-nix for the final 1.7.15
//
// Revision 1.1.4.1  2003/11/19 17:07:12  skyjake
// Modified to compile with gcc and -DUNIX
//
// Revision 1.1  2003/02/26 19:21:52  skyjake
// Initial checkin
//
// Revision 1.1  2002/09/29 01:11:46  Jaakko
// Added Doomsday sources
//
//
// DESCRIPTION:
//  Endianess handling, swapping 16bit and 32bit.
//
//-----------------------------------------------------------------------------

#include "m_swap.h"

// Not needed with big endian.
#ifndef __BIG_ENDIAN__

// Swap 16bit, that is, MSB and LSB byte.
unsigned short SwapSHORT(unsigned short x)
{
	// No masking with 0xFF should be necessary. 
	return (x >> 8) | (x << 8);
}

// Swapping 32bit.
unsigned long SwapLONG(unsigned long x)
{
	return (x >> 24) | ((x >> 8) & 0xff00) | ((x << 8) & 0xff0000) | (x << 24);
}

#endif
