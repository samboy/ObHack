// Emacs style mode select   -*- C++ -*- 
//-----------------------------------------------------------------------------
//
// $Id: m_argv.h,v 1.4 2004/05/29 09:53:11 skyjake Exp $
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
//  Nil.
//    
//-----------------------------------------------------------------------------

#ifndef __M_ARGV__
#define __M_ARGV__

//
// MISC
//
//extern  int   myargc;
//extern  char**    myargv;
#define myargc		Argc()
//#define myargv        Argv

// Returns the position of the given parameter
// in the arg list (0 if not found).
//int M_CheckParm (char* check);

#define	M_CheckParm		gi.CheckParm

#endif
//-----------------------------------------------------------------------------
//
// $Log: m_argv.h,v $
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
// Revision 1.1  2003/02/26 19:18:30  skyjake
// Initial checkin
//
// Revision 1.1  2002/09/29 01:04:13  Jaakko
// Added all headers
//
//
//-----------------------------------------------------------------------------
