// DESCRIPTION:
//   All the global variables that store the internal state.
//   Theoretically speaking, the internal state of the engine
//    should be found by looking at the variables collected
//    here, and every relevant module will have to include
//    this header file.
//   In practice, things are a bit messy.

#ifndef __D_STATE__
#define __D_STATE__

// We need globally shared data structures,
//  for defining the global state variables.
#include "doomdata.h"

// We need the playr data structure as well.
#include "d_player.h"

#ifdef __GNUG__
#pragma interface
#endif

// ------------------------
// Command line parameters.
//
extern boolean  nomonsters;		   // checkparm of -nomonsters
extern boolean  respawnparm;	   // checkparm of -respawn
extern boolean  fastparm;		   // checkparm of -fast

extern boolean  devparm;		   // DEBUG: launched with -devparm

// -----------------------------------------------------
// Game Mode - identify IWAD as shareware, retail etc.
//
extern GameMode_t gamemode;
extern GameMission_t gamemission;

// Set if homebrew PWAD stuff has been added.
extern boolean  modifiedgame;

// -------------------------------------------
// Language.
extern Language_t language;

// -------------------------------------------
// Selected skill type, map etc.
//

// Defaults for menu, methinks.
extern skill_t  startskill;
extern int      startepisode;
extern int      startmap;

extern boolean  autostart;

// Selected by user. 
extern skill_t  gameskill;
extern int      gameepisode;
extern int      gamemap;

// Nightmare mode flag, single player.
extern boolean  respawnmonsters;
extern boolean  monsterinfight;

// Flag: true only if started as net deathmatch.
// An enum might handle altdeath/cooperative better.
extern boolean  deathmatch;

#define snd_SfxVolume		(Get(DD_SFX_VOLUME)/17)
#define snd_MusicVolume		(Get(DD_MUSIC_VOLUME)/17)

// -------------------------
// Status flags for refresh.
//

// Depending on view size - no status bar?
// Note that there is no way to disable the
//  status bar explicitely.
extern boolean  statusbaractive;

extern boolean  automapactive;	   // In AutoMap mode?
extern boolean  menuactive;		   // Menu overlayed?
extern boolean  paused;			   // Game Pause?

extern boolean  viewactive;

extern boolean  nodrawers;
extern boolean  noblit;

#define viewwindowx		Get(DD_VIEWWINDOW_X)
#define viewwindowy		Get(DD_VIEWWINDOW_Y)

// This one is related to the 3-screen display mode.
// ANG90 = left side, ANG270 = right
extern int      viewangleoffset;

// Player taking events, and displaying.
#define consoleplayer	Get(DD_CONSOLEPLAYER)
#define displayplayer	Get(DD_DISPLAYPLAYER)

// -------------------------------------
// Scores, rating.
// Statistics on a given map, for intermission.
//
extern int      totalkills;
extern int      totalitems;
extern int      totalsecret;

// Timer, for scores.
extern int      levelstarttic;	   // gametic at level start
extern int      leveltime;		   // tics in game play for par

// --------------------------------------
// DEMO playback/recording related stuff.
// No demo, there is a human player in charge?
// Disable save/end game?
extern boolean  usergame;

//?
//extern  boolean   demoplayback;
//extern  boolean   demorecording;

// Quit after playing a demo from cmdline.
extern boolean  singledemo;

//?
extern gamestate_t gamestate;

//-----------------------------
// Internal parameters, fixed.
// These are set by the engine, and not changed
//  according to user inputs. Partly load from
//  WAD, partly set at startup time.

#define gametic		Get(DD_GAMETIC)

// Bookkeeping on players - state.
extern player_t players[MAXPLAYERS];

// Player spawn spots for deathmatch.
#define MAX_DM_STARTS   16
extern mapthing_t deathmatchstarts[MAX_DM_STARTS];
extern mapthing_t *deathmatch_p;

// Player spawn spots.
//extern  mapthing_t      playerstarts[MAXPLAYERS];
//extern  mapthing_t*       playerstart_p;

// Intermission stats.
// Parameters for world map / intermission.
extern wbstartstruct_t wminfo;

// LUT of ammunition limits for each kind.
// This doubles with BackPack powerup item.
extern int      maxammo[NUMAMMO];

//-----------------------------------------
// Internal parameters, used for engine.
//

// File handling stuff.
extern char     basedefault[1024];
extern FILE    *debugfile;

// if true, load all graphics at level load
extern boolean  precache;

// wipegamestate can be set to -1
//  to force a wipe on the next draw
extern gamestate_t wipegamestate;

extern int      mouseSensitivity;

//?
// debug flag to cancel adaptiveness
extern boolean  singletics;

extern int      bodyqueslot;

// Needed to store the number of the dummy sky flat.
// Used for rendering, as well as tracking projectiles etc.
#define	skyflatnum	Get(DD_SKYFLATNUM)

extern int      rndindex;
extern int      prndindex;

#define	maketic		Get(DD_MAKETIC)
#define ticdup		1

#endif
