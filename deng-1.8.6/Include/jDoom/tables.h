// Emacs style mode select   -*- C++ -*- 
//-----------------------------------------------------------------------------
//
// $Id: tables.h,v 1.6 2004/05/29 09:53:11 skyjake Exp $
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
//  Lookup tables.
//  Do not try to look them up :-).
//  In the order of appearance: 
//
//  int finetangent[4096]   - Tangens LUT.
//   Should work with BAM fairly well (12 of 16bit,
//      effectively, by shifting).
//
//  int finesine[10240]     - Sine lookup.
//   Guess what, serves as cosine, too.
//   Remarkable thing is, how to use BAMs with this? 
//
//  int tantoangle[2049]    - ArcTan LUT,
//    maps tan(angle) to angle fast. Gotta search.  
//    
//-----------------------------------------------------------------------------

#ifndef __TABLES__
#define __TABLES__

#include "doomsday.h"

#define PI				3.141592657

//#include "m_fixed.h"

#define FINEANGLES		8192
#define FINEMASK		(FINEANGLES-1)

// 0x100000000 to 0x2000
#define ANGLETOFINESHIFT	19

// Effective size is 10240.
extern fixed_t  finesine[5 * FINEANGLES / 4];

// Re-use data, is just PI/2 pahse shift.
extern fixed_t *finecosine;

// Effective size is 4096.
extern fixed_t  finetangent[FINEANGLES / 2];

// Binary Angle Measument, BAM.
#define ANG45		0x20000000
#define ANG90		0x40000000
#define ANG180		0x80000000
#define ANG270		0xc0000000

#define SLOPERANGE		2048
#define SLOPEBITS		11
#define DBITS			(FRACBITS-SLOPEBITS)

// Effective size is 2049;
// The +1 size is to handle the case when x==y
//  without additional checking.
extern angle_t  tantoangle[SLOPERANGE + 1];

// Utility function,
//  called by R_PointToAngle.
int             SlopeDiv(unsigned num, unsigned den);

#endif
//-----------------------------------------------------------------------------
//
// $Log: tables.h,v $
// Revision 1.6  2004/05/29 09:53:11  skyjake
// Consistent style (using GNU Indent)
//
// Revision 1.5  2004/05/28 17:16:36  skyjake
// Resolved conflicts (branch-1-7 overrides)
//
// Revision 1.2.2.2  2004/05/23 15:22:57  skyjake
// Resolved conflict
//
// Revision 1.2.2.1  2004/05/16 10:01:30  skyjake
// Merged good stuff from branch-nix for the final 1.7.15
//
// Revision 1.2.4.1  2003/11/19 17:08:47  skyjake
// Modified to compile with gcc and -DUNIX
//
// Revision 1.2  2003/02/27 23:14:31  skyjake
// Obsolete jDoom files removed
//
// Revision 1.1  2003/02/26 19:18:49  skyjake
// Initial checkin
//
//-----------------------------------------------------------------------------
