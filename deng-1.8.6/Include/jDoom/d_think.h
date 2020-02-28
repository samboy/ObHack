// Emacs style mode select   -*- C++ -*- 
//-----------------------------------------------------------------------------
//
// $Id: d_think.h,v 1.4 2004/05/29 09:53:11 skyjake Exp $
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
//  MapObj data. Map Objects or mobjs are actors, entities,
//  thinker, take-your-pick... anything that moves, acts, or
//  suffers state changes of more or less violent nature.
//
//-----------------------------------------------------------------------------

#ifndef __D_THINK__
#define __D_THINK__

#ifdef __GNUG__
#pragma interface
#endif

//
// Experimental stuff.
// To compile this as "ANSI C with classes"
//  we will need to handle the various
//  action functions cleanly.
//
typedef void    (*actionf_v) ();
typedef void    (*actionf_p1) (void *);
typedef void    (*actionf_p2) (void *, void *);

typedef union {
	actionf_p1      acp1;
	actionf_v       acv;
	actionf_p2      acp2;

} actionf_t;

/*

   // Historically, "think_t" is yet another
   //  function pointer to a routine to handle
   //  an actor.
   typedef actionf_t  think_t;

   // Doubly linked list of actors.
   typedef struct thinker_s
   {
   struct thinker_s*    prev;
   struct thinker_s*    next;
   think_t      function;

   } thinker_t;
 */

#endif
//-----------------------------------------------------------------------------
//
// $Log: d_think.h,v $
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
// Revision 1.1  2003/02/26 19:18:26  skyjake
// Initial checkin
//
// Revision 1.1  2002/09/29 01:04:12  Jaakko
// Added all headers
//
//
//-----------------------------------------------------------------------------
