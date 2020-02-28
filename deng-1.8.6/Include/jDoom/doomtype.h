// Emacs style mode select   -*- C++ -*- 
//-----------------------------------------------------------------------------
//
// $Id: doomtype.h,v 1.5 2004/07/24 21:51:39 skyjake Exp $
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
// DESCRIPTION:
//  Simple basic typedefs, isolated here to make it easier
//   separating modules.
//    
//-----------------------------------------------------------------------------

#ifndef __DOOMTYPE__
#define __DOOMTYPE__

// Predefined with some OS.
#ifdef UNIX

#include <limits.h>

#define MAXCHAR     SCHAR_MAX
#define MAXSHORT    SHRT_MAX
#define MAXINT      INT_MAX
#define MAXLONG     LONG_MAX

#define MINCHAR     SCHAR_MIN
#define MINSHORT    SHRT_MIN
#define MININT      INT_MIN
#define MINLONG     LONG_MIN

#else /* not UNIX */

#define MAXCHAR		((char)0x7f)
#define MAXSHORT	((short)0x7fff)

// Max pos 32-bit int.
#define MAXINT		((int)0x7fffffff)
#define MAXLONG		((long)0x7fffffff)
#define MINCHAR		((char)0x80)
#define MINSHORT	((short)0x8000)

// Max negative 32-bit integer.
#define MININT		((int)0x80000000)
#define MINLONG		((long)0x80000000)
#endif

#endif
