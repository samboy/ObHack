// Emacs style mode select   -*- C++ -*- 
//-----------------------------------------------------------------------------
//
// $Id: hu_stuff.h,v 1.5 2004/05/29 18:19:58 skyjake Exp $
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
// DESCRIPTION:  Head up display
//
//-----------------------------------------------------------------------------

#ifndef __HU_STUFF_H__
#define __HU_STUFF_H__

#include "d_event.h"
#include "r_defs.h"

//
// Globally visible constants.
//
#define HU_FONTSTART	'!'		   // the first font characters
#define HU_FONTEND	'_'			   // the last font characters

// Calculate # of glyphs in font.
#define HU_FONTSIZE	(HU_FONTEND - HU_FONTSTART + 1)

#define HU_BROADCAST	5

#define HU_MSGREFRESH	DDKEY_ENTER
#define HU_MSGX		0
#define HU_MSGY		0
#define HU_MSGWIDTH	64			   // in characters
#define HU_MSGHEIGHT	1		   // in lines

#define HU_MSGTIMEOUT	(4*TICRATE)

#define HU_TITLEX	0
#define HU_TITLEY	(167 - SHORT(hu_font[0].height))

//
// HEADS UP TEXT
//
extern boolean  message_noecho;

void            HU_Init(void);
void            HU_Start(void);

boolean         HU_Responder(event_t *ev);

void            HU_Ticker(void);
void            HU_Drawer(void);
char            HU_dequeueChatChar(void);
void            HU_Erase(void);

// The fonts.
extern dpatch_t hu_font[HU_FONTSIZE];
extern dpatch_t hu_font_a[HU_FONTSIZE];
extern dpatch_t hu_font_b[HU_FONTSIZE];

// Plutonia and TNT map names.
extern char    *mapnamesp[32], *mapnamest[32];

#define PLUT_AUTHOR	"Dario Casali and Milo Casali"
#define TNT_AUTHOR	"Team TNT"

#endif
//-----------------------------------------------------------------------------
//
// $Log: hu_stuff.h,v $
// Revision 1.5  2004/05/29 18:19:58  skyjake
// Refined indentation style
//
// Revision 1.4  2004/05/29 09:53:11  skyjake
// Consistent style (using GNU Indent)
//
// Revision 1.3  2004/05/28 17:16:35  skyjake
// Resolved conflicts (branch-1-7 overrides)
//
// Revision 1.1.2.1  2004/05/16 10:01:30  skyjake
// Merged good stuff from branch-nix for the final 1.7.15
//
// Revision 1.1.4.1  2003/11/19 17:08:47  skyjake
// Modified to compile with gcc and -DUNIX
//
// Revision 1.1  2003/02/26 19:18:28  skyjake
// Initial checkin
//
// Revision 1.1  2002/09/29 01:04:12  Jaakko
// Added all headers
//
//
//-----------------------------------------------------------------------------
