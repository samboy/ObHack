// Emacs style mode select   -*- C++ -*- 
//-----------------------------------------------------------------------------
//
// $Id: wi_stuff.h,v 1.6 2004/05/29 09:53:11 skyjake Exp $
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
//  Intermission.
//
//-----------------------------------------------------------------------------

#ifndef __WI_STUFF__
#define __WI_STUFF__

#include "doomdef.h"
#include "r_defs.h"

// States for the intermission

typedef enum {
	NoState = -1,
	StatCount,
	ShowNextLoc
} stateenum_t;

// Called by main loop, animate the intermission.
void            WI_Ticker(void);

// Called by main loop,
// draws the intermission directly into the screen buffer.
void            WI_Drawer(void);

// Setup for an intermission screen.
void            WI_Start(wbstartstruct_t * wbstartstruct);

void            WI_SetState(stateenum_t st);
void            WI_End(void);

// Implements patch replacement.
void            WI_DrawPatch(int x, int y, int lump);

void            WI_DrawParamText(int x, int y, char *string,
								 dpatch_t * defFont, float defRed,
								 float defGreen, float defBlue,
								 boolean defCase, boolean defTypeIn);

#endif
//-----------------------------------------------------------------------------
//
// $Log: wi_stuff.h,v $
// Revision 1.6  2004/05/29 09:53:11  skyjake
// Consistent style (using GNU Indent)
//
// Revision 1.5  2004/05/28 17:16:36  skyjake
// Resolved conflicts (branch-1-7 overrides)
//
// Revision 1.3.2.1  2004/05/16 10:01:30  skyjake
// Merged good stuff from branch-nix for the final 1.7.15
//
// Revision 1.3.4.1  2003/11/19 17:08:47  skyjake
// Modified to compile with gcc and -DUNIX
//
// Revision 1.3  2003/08/24 00:26:17  skyjake
// More advanced patch replacements
//
// Revision 1.2  2003/08/17 23:29:36  skyjake
// Implemented Patch Replacement
//
// Revision 1.1  2003/02/26 19:18:52  skyjake
// Initial checkin
//
// Revision 1.1  2002/09/29 01:04:14  Jaakko
// Added all headers
//
//
//-----------------------------------------------------------------------------
