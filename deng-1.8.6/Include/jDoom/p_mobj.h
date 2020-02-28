// Emacs style mode select   -*- C++ -*- 
//-----------------------------------------------------------------------------
//
// $Id: p_mobj.h,v 1.7 2004/05/29 09:53:11 skyjake Exp $
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
//  Map Objects, MObj, definition and handling.
//
//-----------------------------------------------------------------------------

#ifndef __P_MOBJ__
#define __P_MOBJ__

// Basics.
#include "tables.h"

// We need the thinker_t stuff.
#include "d_think.h"

// We need the WAD data structure for Map things,
// from the THINGS lump.
#include "doomdata.h"

// States are tied to finite states are
//  tied to animation frames.
// Needs precompiled tables/data structures.
#include "info.h"

#ifdef __GNUG__
#pragma interface
#endif

//
// NOTES: mobj_t
//
// mobj_ts are used to tell the refresh where to draw an image,
// tell the world simulation when objects are contacted,
// and tell the sound driver how to position a sound.
//
// The refresh uses the next and prev links to follow
// lists of things in sectors as they are being drawn.
// The sprite, frame, and angle elements determine which patch_t
// is used to draw the sprite if it is visible.
// The sprite and frame values are allmost allways set
// from state_t structures.
// The statescr.exe utility generates the states.h and states.c
// files that contain the sprite/frame numbers from the
// statescr.txt source file.
// The xyz origin point represents a point at the bottom middle
// of the sprite (between the feet of a biped).
// This is the default origin position for patch_ts grabbed
// with lumpy.exe.
// A walking creature will have its z equal to the floor
// it is standing on.
//
// The sound code uses the x,y, and subsector fields
// to do stereo positioning of any sound effited by the mobj_t.
//
// The play simulation uses the blocklinks, x,y,z, radius, height
// to determine when mobj_ts are touching each other,
// touching lines in the map, or hit by trace lines (gunshots,
// lines of sight, etc).
// The mobj_t->flags element has various bit flags
// used by the simulation.
//
// Every mobj_t is linked into a single sector
// based on its origin coordinates.
// The subsector_t is found with R_PointInSubsector(x,y),
// and the sector_t can be found with subsector->sector.
// The sector links are only used by the rendering code,
// the play simulation does not care about them at all.
//
// Any mobj_t that needs to be acted upon by something else
// in the play world (block movement, be shot, etc) will also
// need to be linked into the blockmap.
// If the thing has the MF_NOBLOCK flag set, it will not use
// the block links. It can still interact with other things,
// but only as the instigator (missiles will run into other
// things, but nothing can run into a missile).
// Each block in the grid is 128*128 units, and knows about
// every line_t that it contains a piece of, and every
// interactable mobj_t that has its origin contained.  
//
// A valid mobj_t is a mobj_t that has the proper subsector_t
// filled in for its xy coordinates and is linked into the
// sector from which the subsector was made, or has the
// MF_NOSECTOR flag set (the subsector_t needs to be valid
// even if MF_NOSECTOR is set), and is linked into a blockmap
// block or has the MF_NOBLOCKMAP flag set.
// Links should only be modified by the P_[Un]SetThingPosition()
// functions.
// Do not change the MF_NO? flags while a thing is valid.
//
// Any questions?
//

//
// Misc. mobj flags
//
typedef enum {
	// Call P_SpecialThing when touched.
	MF_SPECIAL = 1,
	// Blocks.
	MF_SOLID = 2,
	// Can be hit.
	MF_SHOOTABLE = 4,
	// Don't use the sector links (invisible but touchable).
	MF_NOSECTOR = 8,
	// Don't use the blocklinks (inert but displayable)
	MF_NOBLOCKMAP = 16,

	// Not to be activated by sound, deaf monster.
	MF_AMBUSH = 32,
	// Will try to attack right back.
	MF_JUSTHIT = 64,
	// Will take at least one step before attacking.
	MF_JUSTATTACKED = 128,
	// On level spawning (initial position),
	//  hang from ceiling instead of stand on floor.
	MF_SPAWNCEILING = 256,
	// Don't apply gravity (every tic),
	//  that is, object will float, keeping current height
	//  or changing it actively.
	MF_NOGRAVITY = 512,

	// Movement flags.
	// This allows jumps from high places.
	MF_DROPOFF = 0x400,
	// For players, will pick up items.
	MF_PICKUP = 0x800,
	// Player cheat. ???
	MF_NOCLIP = 0x1000,
	// Player: keep info about sliding along walls.
	MF_SLIDE = 0x2000,
	// Allow moves to any height, no gravity.
	// For active floaters, e.g. cacodemons, pain elementals.
	MF_FLOAT = 0x4000,
	// Don't cross lines
	//   ??? or look at heights on teleport.
	MF_TELEPORT = 0x8000,
	// Don't hit same species, explode on block.
	// Player missiles as well as fireballs of various kinds.
	MF_MISSILE = 0x10000,
	// Dropped by a demon, not level spawned.
	// E.g. ammo clips dropped by dying former humans.
	MF_DROPPED = 0x20000,
	// Use fuzzy draw (shadow demons or spectres),
	//  temporary player invisibility powerup.
	MF_SHADOW = 0x40000,
	// Flag: don't bleed when shot (use puff),
	//  barrels and shootable furniture shall not bleed.
	MF_NOBLOOD = 0x80000,
	// Don't stop moving halfway off a step,
	//  that is, have dead bodies slide down all the way.
	MF_CORPSE = 0x100000,
	// Floating to a height for a move, ???
	//  don't auto float to target's height.
	MF_INFLOAT = 0x200000,

	// On kill, count this enemy object
	//  towards intermission kill total.
	// Happy gathering.
	MF_COUNTKILL = 0x00400000,

	// On picking up, count this item object
	//  towards intermission item total.
	MF_COUNTITEM = 0x00800000,

	// Special handling: skull in flight.
	// Neither a cacodemon nor a missile.
	MF_SKULLFLY = 0x01000000,

	// Don't spawn this object
	//  in death match mode (e.g. key cards).
	MF_NOTDMATCH = 0x02000000,

	// Player sprites in multiplayer modes are modified
	//  using an internal color lookup table for re-indexing.
	// If 0x4 0x8 or 0xc,
	//  use a translation table for player colormaps
	MF_TRANSLATION = 0x0c000000,
	// Hmm ???.
	MF_TRANSSHIFT = 26,

	MF_LOCAL = 0x10000000,
	MF_BRIGHTEXPLODE = 0x20000000,
	MF_BRIGHTSHADOW = 0x40000000,
	MF_VIEWALIGN = 0x80000000
} mobjflag_t;

#define MF2_ALWAYSLIT	0x1

// killough $dropoff_fix
enum {
	MIF_FALLING = 1,
};

// killough $dropoff_fix
// For torque simulation:

#define OVERDRIVE 6
#define MAXGEAR (OVERDRIVE+16)

// Map Object definition.
typedef struct mobj_s {
	// Defined in dd_share.h; required mobj elements.
	DD_BASE_MOBJ_ELEMENTS() mobjinfo_t *info;	// &mobjinfo[mobj->type]
	int             flags;
	int             health;

	// Movement direction, movement generation (zig-zagging).
	int             movedir;	   // 0-7
	int             movecount;	   // when 0, select a new dir

	// Thing being chased/attacked (or NULL),
	// also the originator for missiles.
	struct mobj_s  *target;

	// Reaction time: if non 0, don't attack yet.
	// Used by player to freeze a bit after teleporting.
	int             reactiontime;

	// If >0, the target will be chased
	// no matter what (even if shot)
	int             threshold;

	int             intflags;	   // killough $dropoff_fix: internal flags
	fixed_t         dropoffz;	   // killough $dropoff_fix
	short           gear;		   // killough 11/98: used in torque simulation

	// Additional info record for player avatars only.
	// Only valid if type == MT_PLAYER
	struct player_s *player;

	// Player number last looked for.
	int             lastlook;

	// For nightmare respawn.
	mapthing_t      spawnpoint;

	// Thing being chased/attacked for tracers.
	struct mobj_s  *tracer;

	int             turntime;	   // $visangle-facetarget
	int             corpsetics;	   // $vanish: how long has this been dead?

} mobj_t;

#endif
//-----------------------------------------------------------------------------
//
// $Log: p_mobj.h,v $
// Revision 1.7  2004/05/29 09:53:11  skyjake
// Consistent style (using GNU Indent)
//
// Revision 1.6  2004/05/28 17:16:35  skyjake
// Resolved conflicts (branch-1-7 overrides)
//
// Revision 1.4.2.1  2004/05/16 10:01:30  skyjake
// Merged good stuff from branch-nix for the final 1.7.15
//
// Revision 1.4.4.1  2003/11/19 17:08:47  skyjake
// Modified to compile with gcc and -DUNIX
//
// Revision 1.4  2003/06/23 08:16:28  skyjake
// Removed alpha
//
// Revision 1.3  2003/04/29 13:10:56  skyjake
// Missile puff ptcgen issue fixed
//
// Revision 1.2  2003/02/27 23:14:31  skyjake
// Obsolete jDoom files removed
//
// Revision 1.1  2003/02/26 19:18:32  skyjake
// Initial checkin
//
//-----------------------------------------------------------------------------
