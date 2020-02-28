/* DE1: $Id: dd_share.h,v 1.40 2005/01/06 22:10:29 skyjake Exp $
 * Copyright (C) 2003, 2004 Jaakko Ker�nen <jaakko.keranen@iki.fi>
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
 * dd_share.h: Shared Macros and Constants
 *
 * Macros and constants used by the engine and games.
 */

#ifndef __DOOMSDAY_SHARED_H__
#define __DOOMSDAY_SHARED_H__

#ifdef __cplusplus
extern          "C" {
#endif

	/*
	 * Caller cleans the stack in the __cdecl calling convention.
	 * This means the caller doesn't have to know the right number 
	 * of arguments for the function. Most Doomsday functions use
	 * __stdcall, where the function clears up the stack itself.
	 * This means the caller must put the right number of arguments
	 * on the stack or Bad Things will happen.
	 */

#include <stdlib.h>
#include "dd_version.h"
#include "dd_types.h"
#include "p_think.h"
#include "def_share.h"

	//------------------------------------------------------------------------
	//
	// General Definitions and Macros
	//
	//------------------------------------------------------------------------

#define DDMAXPLAYERS			16

	// The case-independent strcmps have different names.
#ifdef WIN32
#	define strcasecmp	stricmp
#	define strncasecmp	strnicmp
#endif
#ifdef UNIX
#	define stricmp 		strcasecmp
#	define strnicmp		strncasecmp
	/*
	 * There are manual implementations for these string handling
	 * routines:
	 */
	char           *strupr(char *string);
	char           *strlwr(char *string);
#endif

#ifdef __BIG_ENDIAN__
	short           ShortSwap(short);
	long            LongSwap(long);
    float           FloatSwap(float);
#define SHORT(x)	ShortSwap(x)
#define LONG(x)		LongSwap(x)
#define FLOAT(x)    FloatSwap(x)
#else
#define SHORT(x)	(x)
#define LONG(x)		(x)
#define FLOAT(x)    (x)
#endif

#define USHORT(x)   ((unsigned short) SHORT(x))
#define ULONG(x)    ((unsigned long) LONG(x))

#define MAX_OF(x, y)	((x) > (y)? (x) : (y))
#define MIN_OF(x, y)	((x) < (y)? (x) : (y))

	enum {
		// TexFilterMode targets
		DD_TEXTURES = 0,
		DD_RAWSCREENS,

		// Filter/mipmap modes
		DD_NEAREST = 0,
		DD_LINEAR,
		DD_NEAREST_MIPMAP_NEAREST,
		DD_LINEAR_MIPMAP_NEAREST,
		DD_NEAREST_MIPMAP_LINEAR,
		DD_LINEAR_MIPMAP_LINEAR,

		// Music devices
		DD_MUSIC_NONE = 0,
		DD_MUSIC_MIDI,
		DD_MUSIC_CDROM,

		// Integer values for Set/Get
		DD_FIRST_VALUE = -1,
		DD_SCREEN_WIDTH,
		DD_SCREEN_HEIGHT,
		DD_NETGAME,
		DD_SERVER,
		DD_CLIENT,
		DD_ALLOW_FRAMES,
		DD_SKYFLATNUM,
		DD_GAMETIC,
		DD_VIEWWINDOW_X,
		DD_VIEWWINDOW_Y,
		DD_VIEWWINDOW_WIDTH,
		DD_VIEWWINDOW_HEIGHT,
		DD_VIEWWINDOW_SCREEN_WIDTH,
		DD_VIEWWINDOW_SCREEN_HEIGHT,
		DD_VIEWX,
		DD_VIEWY,
		DD_VIEWZ,
		DD_VIEWX_OFFSET,
		DD_VIEWY_OFFSET,
		DD_VIEWZ_OFFSET,
		DD_VIEWANGLE,
		DD_VIEWANGLE_OFFSET,
		DD_CONSOLEPLAYER,
		DD_DISPLAYPLAYER,
		DD_MUSIC_DEVICE,
		DD_MIPMAPPING,
		DD_SMOOTH_IMAGES,
		DD_DEFAULT_RES_X,
		DD_DEFAULT_RES_Y,
		DD_SKY_DETAIL,
		DD_SFX_VOLUME,
		DD_MUSIC_VOLUME,
		DD_MOUSE_INVERSE_Y,
		DD_GAMMA,
		DD_QUERY_RESULT,
		DD_FULLBRIGHT,			   // Render everything fullbright?
		DD_CCMD_RETURN,
		DD_GAME_READY,
		DD_OPENRANGE,
		DD_OPENTOP,
		DD_OPENBOTTOM,
		DD_LOWFLOOR,
		DD_DEDICATED,
		DD_NOVIDEO,
		DD_NUMMOBJTYPES,
		DD_GRAVITY,
		DD_GOTFRAME,
		DD_PLAYBACK,
		DD_NUMSOUNDS,
		DD_NUMMUSIC,
		DD_NUMLUMPS,
		DD_SEND_ALL_PLAYERS,
		DD_PSPRITE_OFFSET_X,	   // 10x
		DD_PSPRITE_OFFSET_Y,	   // 10x
		DD_PSPRITE_SPEED,
		DD_CPLAYER_THRUST_MUL,
		DD_CLIENT_PAUSED,
		DD_WEAPON_OFFSET_SCALE_Y,  // 1000x
		DD_LAST_VALUE,

		// General constants (not to be used with Get/Set).
		DD_NEW = -2,
		DD_SKY = -1,
		DD_DISABLE,
		DD_ENABLE,
		DD_MASK,
		DD_YES,
		DD_NO,
		DD_TEXTURE,
		DD_OFFSET,
		DD_HEIGHT,
		DD_COLUMNS,
		DD_ROWS,
		DD_COLOR_LIMIT,
		DD_PRE,
		DD_POST,
		DD_VERSION_SHORT,
		DD_VERSION_LONG,
		DD_PROTOCOL,
		DD_NUM_SERVERS,
		DD_TCPIP_ADDRESS,
		DD_TCPIP_PORT,
		DD_COM_PORT,
		DD_BAUD_RATE,
		DD_STOP_BITS,
		DD_PARITY,
		DD_FLOW_CONTROL,
		DD_MODEM,
		DD_PHONE_NUMBER,
		DD_HORIZON,
		DD_GAME_ID,
		DD_DEF_MOBJ,
		DD_DEF_STATE,
		DD_DEF_SPRITE,
		DD_DEF_SOUND,
		DD_DEF_MUSIC,
		DD_DEF_MAP_INFO,
		DD_DEF_TEXT,
		DD_DEF_VALUE,
		DD_DEF_LINE_TYPE,
		DD_DEF_SECTOR_TYPE,
		DD_PSPRITE_BOB_X,
		DD_PSPRITE_BOB_Y,
		DD_ALT_MOBJ_THINKER,
		DD_DEF_FINALE_AFTER,
		DD_DEF_FINALE_BEFORE,
		DD_RENDER_RESTART_PRE,
		DD_RENDER_RESTART_POST,
		DD_DEF_SOUND_BY_NAME,
		DD_DEF_SOUND_LUMPNAME,
		DD_ID,
		DD_LUMP,
		DD_CD_TRACK,
		DD_FLAT,
		DD_GAME_MODE,			   // 16 chars max (swdoom, doom1, udoom, tnt, heretic...) 
		DD_GAME_CONFIG,			   // String: dm/co-op, jumping, etc.
		DD_DEF_FINALE,

		// Queries
		DD_TEXTURE_HEIGHT_QUERY = 0x2000,
		DD_NET_QUERY,
		DD_SERVER_DATA_QUERY,
		DD_MODEM_DATA_QUERY,

		// Non-integer/special values for Set/Get
		DD_SKYFLAT_NAME = 0x4000,
		DD_TRANSLATIONTABLES_ADDRESS,
		DD_TRANSLATED_SPRITE_TEXTURE,	// Make parameter with DD_TSPR_PARM.
		DD_TRACE_ADDRESS,		   // divline 'trace' used by PathTraverse.
		DD_TEXTURE_GLOW,
		DD_SPRITE_REPLACEMENT,	   // Sprite <-> model replacement.
		DD_ACTION_LINK,			   // State action routine addresses.
		DD_MAP_NAME,
		DD_MAP_AUTHOR,
		DD_MAP_MUSIC,
		DD_HIGHRES_TEXTURE_PATH,   // TGA texture directory (obsolete).
		DD_WINDOW_HANDLE,
		DD_DYNLIGHT_TEXTURE,
		DD_GAME_EXPORTS
	};

	// Macro for preparing the parameter for DD_TRANSLATED_SPRITE_TEXTURE.
#define DD_TSPR_PARM(Lump,Class,TableNum)	(((Lump)&0xffffff) + ((Class)<<24) + ((TableNum)<<28))

	// Macro for preparing the parameter for DD_TEXTURE_GLOW.
#define DD_TGLOW_PARM(TNum,IsTexture,Glow)	((TNum & 0xffff) | (IsTexture? 0x80000000 : 0) | (Glow? 0x10000 : 0))

	// Bounding box coordinates.
	enum {
		BOXTOP = 0,
		BOXBOTTOM = 1,
		BOXLEFT = 2,
		BOXRIGHT = 3
	};

	//------------------------------------------------------------------------
	//
	// Fixed-Point Math
	//
	//------------------------------------------------------------------------

#define	FRACBITS			16
#define	FRACUNIT			(1<<FRACBITS)

#define	FINEANGLES			8192
#define	FINEMASK			(FINEANGLES-1)
#define	ANGLETOFINESHIFT	19	   // 0x100000000 to 0x2000

#define ANGLE_45			0x20000000
#define ANGLE_90			0x40000000
#define ANGLE_180			0x80000000
#define ANGLE_MAX			0xffffffff
#define ANGLE_1				(ANGLE_45/45)
#define ANGLE_60			(ANGLE_180/3)

#define	ANG45				0x20000000
#define	ANG90				0x40000000
#define	ANG180				0x80000000
#define	ANG270				0xc0000000

#define FIX2FLT(x)		( (x) / (float) FRACUNIT )
#define Q_FIX2FLT(x)	( (float)((x)>>FRACBITS) )
#define FLT2FIX(x)		( (fixed_t) ((x)*FRACUNIT) )

#if !defined( NO_FIXED_ASM ) && !defined( GNU_X86_FIXED_ASM )

	/* *INDENT-OFF* */
	__inline fixed_t FixedMul(fixed_t a, fixed_t b) {
		__asm {
			// The parameters in eax and ebx.
			mov	eax, a 
			mov ebx, b
			// The multiplying.
			imul ebx 
			shrd eax, edx, 16
			// eax should hold the return value.
		}
		// A value is returned regardless of the compiler warning. 
	} 
	__inline fixed_t FixedDiv2(fixed_t a, fixed_t b) {
		__asm {
			// The parameters.
			mov eax, a 
			mov ebx, b
			// The operation.
			cdq 
			shld edx, eax, 16 
			sal eax, 16 
			idiv ebx
			// And the value returns in eax.
		}
		// A value is returned regardless of the compiler warning. 
	}
	/* *INDENT-ON* */

#else

	// Don't use inline assembler in fixed-point calculations.
	// (link with Src/Common/m_fixed.c)
	fixed_t         FixedMul(fixed_t a, fixed_t b);
	fixed_t         FixedDiv2(fixed_t a, fixed_t b);

#endif

	// This one is always in Src/Common/m_fixed.c.
	fixed_t         FixedDiv(fixed_t a, fixed_t b);

	//------------------------------------------------------------------------
	//
	// Key Codes
	//
	//------------------------------------------------------------------------

	// Most key data is simple ASCII.
#define	DDKEY_ESCAPE			27
#define	DDKEY_ENTER				13
#define DDKEY_TAB				9
#define	DDKEY_BACKSPACE			127
#define DDKEY_EQUALS			0x3d
#define DDKEY_MINUS				0x2d
#define DDKEY_FIVE				0x35
#define DDKEY_SIX				0x36
#define DDKEY_SEVEN				0x37
#define DDKEY_EIGHT				0x38
#define DDKEY_NINE				0x39
#define DDKEY_ZERO				0x30
#define DDKEY_BACKSLASH			0x5C

	// Extended keys (above 127).
	enum {
		DDKEY_RIGHTARROW = 0x80,
		DDKEY_LEFTARROW,
		DDKEY_UPARROW,
		DDKEY_DOWNARROW,
		DDKEY_F1,
		DDKEY_F2,
		DDKEY_F3,
		DDKEY_F4,
		DDKEY_F5,
		DDKEY_F6,
		DDKEY_F7,
		DDKEY_F8,
		DDKEY_F9,
		DDKEY_F10,
		DDKEY_F11,
		DDKEY_F12,
		DDKEY_NUMLOCK,
		DDKEY_SCROLL,
		DDKEY_NUMPAD7,
		DDKEY_NUMPAD8,
		DDKEY_NUMPAD9,
		DDKEY_NUMPAD4,
		DDKEY_NUMPAD5,
		DDKEY_NUMPAD6,
		DDKEY_NUMPAD1,
		DDKEY_NUMPAD2,
		DDKEY_NUMPAD3,
		DDKEY_NUMPAD0,
		DDKEY_DECIMAL,
		DDKEY_PAUSE,
		DDKEY_RSHIFT,
		DDKEY_LSHIFT = DDKEY_RSHIFT,
		DDKEY_RCTRL,
		DDKEY_RALT,
		DDKEY_LALT = DDKEY_RALT,
		DDKEY_INS,
		DDKEY_DEL,
		DDKEY_PGUP,
		DDKEY_PGDN,
		DDKEY_HOME,
		DDKEY_END,
		DDKEY_SUBTRACT,			   /* - on numeric keypad */
		DDKEY_ADD,				   /* + on numeric keypad */
		DD_HIGHEST_KEYCODE
	};

	//------------------------------------------------------------------------
	//
	// Events
	//
	//------------------------------------------------------------------------

	typedef enum {
		ev_keydown,
		ev_keyup,
		ev_keyrepeat,
		ev_mouse,
		ev_mousebdown,
		ev_mousebup,
		ev_joystick,			   // Joystick main axes (xyz + Rxyz)
		ev_joyslider,			   // Joystick sliders
		ev_joybdown,
		ev_joybup,
		ev_povdown,
		ev_povup
	} evtype_t;

	typedef struct {
		evtype_t        type;
		int             data1;	   // keys/mouse/joystick buttons
		int             data2;	   // mouse/joystick x move
		int             data3;	   // mouse/joystick y move
		int             data4;
		int             data5;
		int             data6;
	} event_t;

	// The mouse wheel is considered two extra mouse buttons.
#define DDMB_MWHEELUP		0x1000
#define DDMB_MWHEELDOWN		0x2000

	//------------------------------------------------------------------------
	//
	// Purge Levels
	//
	//------------------------------------------------------------------------

#define	PU_STATIC		1		   // static entire execution time
#define	PU_SOUND		2		   // static while playing
#define	PU_MUSIC		3		   // static while playing

#define PU_USER1		40
#define PU_USER2		41
#define PU_USER3		42
#define PU_USER4		43
#define PU_USER5		44
#define PU_USER6		45
#define PU_USER7		46
#define PU_USER8		47
#define PU_USER9		48
#define PU_USER10		49

#define	PU_LEVEL		50		   // static until level exited
#define	PU_LEVSPEC		51		   /* a special thinker in a level
								      tags >= 100 are purgable whenever needed */
#define	PU_PURGELEVEL	100
#define	PU_CACHE		101

	// Special purgelevel.
#define PU_GETNAME		100000L

	//------------------------------------------------------------------------
	//
	// Map Data
	//
	//------------------------------------------------------------------------

	// Each sector has two of these. A plane_t contains information about
	// a plane's movement.
	typedef struct {
		int             target;	   // Target height.
		int             speed;	   // Move speed.
		int             texmove[2];	// Texture movement X and Y.
	} plane_t;

	enum {
		PLN_FLOOR,
		PLN_CEILING
	};

	// SetupLevel flags.
#define DDSLF_POLYGONIZE	0x1	   // Create sector floor/ceiling triangles.
#define DDSLF_DONT_CLIP		0x2	   /* Don't clip sector polys: use subsectors
								      as they are (use with DDSLF_POLYGONIZE). */
#define DDSLF_FIX_SKY		0x4	   // Fix walls between sky-ceiling sectors.
#define DDSLF_REVERB		0x8	   // Calculate sector reverbs.
#define DDSLF_NO_SERVER		0x10   // Do not initialize server.
#define DDSLF_SERVER_ONLY	0x20   // Server init only, nothing else.
#define DDSLF_AFTER_LOADING	0x40   // After loading a savegame...
#define DDSLF_INIT_LINKS	0x80   // Init linelinks.
#define DDSLF_FINALIZE		0x100  // After everything else is done.
#define DDSLF_INITIALIZE    0x200  // Before anything else if done.

	enum						   // Sector reverb data indices.
	{
		SRD_VOLUME,
		SRD_SPACE,
		SRD_DECAY,
		SRD_DAMPING,
		NUM_REVERB_DATA
	};

	// each sector has a degenmobj_t in it's center for sound origin purposes
	typedef struct {
		thinker_t       thinker;   // not used for anything
		fixed_t         x, y, z;
	} degenmobj_t;

#define DDSUBF_MIDPOINT			0x80	// Midpoint is tri-fan centre.

	typedef struct {
		fixed_t         x, y, dx, dy;
	} divline_t;

	typedef struct {
		float           x, y, dx, dy;
	} fdivline_t;

	// For PathTraverse.
#define PT_ADDLINES		1
#define	PT_ADDTHINGS	2
#define	PT_EARLYOUT		4

	// Mapblocks are used to check movement against lines and things.
#define MAPBLOCKUNITS	128
#define	MAPBLOCKSIZE	(MAPBLOCKUNITS*FRACUNIT)
#define	MAPBLOCKSHIFT	(FRACBITS+7)
#define	MAPBMASK		(MAPBLOCKSIZE-1)
#define	MAPBTOFRAC		(MAPBLOCKSHIFT-FRACBITS)

	typedef enum {
		ST_HORIZONTAL, ST_VERTICAL, ST_POSITIVE, ST_NEGATIVE
	} slopetype_t;

	// For (un)linking.
#define DDLINK_SECTOR		0x1
#define DDLINK_BLOCKMAP		0x2
#define DDLINK_NOLINE		0x4

	typedef struct intercept_s {
		fixed_t         frac;	   // along trace line
		boolean         isaline;
		union {
			struct mobj_s  *thing;
			struct line_s  *line;
		} d;
	} intercept_t;

	typedef boolean (*traverser_t) (intercept_t * in);

	// Polyobjs.
#define PO_MAXPOLYSEGS 64

	typedef struct vertex_s {
		fixed_t         x, y;
	} vertex_t;

	typedef struct fvertex_s {
		float           x, y;
	} fvertex_t;

	typedef struct seg_s {
		vertex_t       *v1, *v2;
		float           length;	   // Accurate length of the segment (v1 -> v2).
		fixed_t         offset;
		struct side_s  *sidedef;
		struct line_s  *linedef;
		struct sector_s *frontsector;
		struct sector_s *backsector;	// NULL for one sided lines
		byte            flags;
		angle_t         angle;
	} seg_t;

	typedef struct subsector_s {
		struct sector_s *sector;
		unsigned short  linecount;
		unsigned short  firstline;
		struct polyobj_s *poly;	   // NULL if there is no polyobj
		// Sorted edge vertices for rendering floors and ceilings.
		char            numverts;
		fvertex_t      *verts;	   // A list of edge vertices.
		fvertex_t       bbox[2];   // Min and max points.
		fvertex_t       midpoint;  // Center of vertices.
		byte            flags;
	} subsector_t;

	//------------------------------------------------------------------------
	//
	// Mobjs
	//
	//------------------------------------------------------------------------

	/* 
	 * Linknodes are used when linking mobjs to lines. Each mobj has a ring
	 * of linknodes, each node pointing to a line the mobj has been linked to.
	 * Correspondingly each line has a ring of nodes, with pointers to the 
	 * mobjs that are linked to that particular line. This way it is possible
	 * that a single mobj is linked simultaneously to multiple lines (which 
	 * is common).
	 * 
	 * All these rings are maintained by P_(Un)LinkThing(). 
	 */
	typedef struct linknode_s {
		nodeindex_t     prev, next;
		void           *ptr;
		int             data;
	} linknode_t;

	// Frame flags.
#define	FF_FULLBRIGHT		0x8000 // flag in thing->frame
#define FF_FRAMEMASK		0x7fff

	// Doomsday mobj flags.
#define DDMF_DONTDRAW		0x00000001
#define DDMF_SHADOW			0x00000002
#define DDMF_ALTSHADOW		0x00000004
#define DDMF_BRIGHTSHADOW	0x00000008
#define DDMF_VIEWALIGN		0x00000010
#define DDMF_FITTOP			0x00000020	// Don't let the sprite go into the ceiling.
#define DDMF_NOFITBOTTOM	0x00000040
#define DDMF_LIGHTSCALE		0x00000180	// Light scale (0: full, 3: 1/4).
#define DDMF_LIGHTOFFSET	0x0000f000	// How to offset light (along Z axis)
#define DDMF_RESERVED		0x00030000	// don't touch these!! (translation class)
#define DDMF_BOB			0x00040000	// Bob the Z coord up and down.
#define DDMF_LOWGRAVITY		0x00080000	// 1/8th gravity (predict)
#define DDMF_MISSILE		0x00100000	// client removes mobj upon impact
#define DDMF_FLY			0x00200000	// flying object (doesn't matter if airborne)
#define DDMF_NOGRAVITY		0x00400000	// isn't affected by gravity (predict)
#define DDMF_ALWAYSLIT		0x00800000	// Always process DL even if hidden
#define	DDMF_TRANSLATION	0x1c000000	// use a translation table (>>MF_TRANSHIFT)
#define DDMF_SOLID			0x20000000	// Solid on client side.
#define DDMF_LOCAL			0x40000000
#define DDMF_REMOTE			0x80000000	// This mobj is really on the server.

	// Clear masks (flags the Game DLL is not allowed to touch).
#define DDMF_CLEAR_MASK		0xc0000000

#define	DDMF_TRANSSHIFT			26 // table for player colormaps
#define DDMF_CLASSTRSHIFT		16
#define DDMF_LIGHTSCALESHIFT	7
#define DDMF_LIGHTOFFSETSHIFT	12

	// The high byte of the selector is not used for modeldef selecting.
	// 1110 0000 = alpha level (0: opaque => 7: transparent 7/8)
#define DDMOBJ_SELECTOR_MASK	0x00ffffff
#define DDMOBJ_SELECTOR_SHIFT	24

	// Base mobj_t elements. Games MUST use this as the basis for mobj_t.
#define DD_BASE_MOBJ_ELEMENTS() \
	thinker_t		thinker; 			/* thinker node */ \
	fixed_t			x,y,z;				/* position */ \
\
	struct mobj_s	*bnext, *bprev;		/* links in blocks (if needed) */ \
	nodeindex_t		lineroot;			/* lines to which this is linked */ \
	struct mobj_s	*snext, **sprev;	/* links in sector (if needed) */ \
\
	struct subsector_s *subsector;		/* subsector in which this resides */ \
	fixed_t			momx, momy, momz;	\
	angle_t			angle;				\
	spritenum_t		sprite;				/* used to find patch_t and \
										 * flip value */ \
	int				frame;				/* might be ord with FF_FULLBRIGHT */ \
	fixed_t			radius;	\
	fixed_t			height;	\
	int				ddflags;			/* Doomsday mobj flags (DDMF_*) */ \
	fixed_t			floorclip;			/* value to use for floor clipping */ \
	int				valid;				/* if == valid, already checked */ \
	int				type;				/* mobj type */ \
	struct state_s	*state;	\
	int 			tics;				/* state tic counter */ \
    fixed_t			floorz;				/* highest contacted floor */ \
    fixed_t			ceilingz;			/* lowest contacted ceiling */ \
	struct mobj_s*	onmobj;				/* the mobj this one is on top of. */ \
	boolean			wallhit;			/* the mobj is hitting a wall. */ \
	struct ddplayer_s *dplayer;			/* NULL if not a player mobj. */ \
	short			srvo[3];			/* short-range visual offset (xyz) */ \
	short			visangle;			/* visual angle ("angle-servo") */ \
	int				selector;			/* multipurpose info */ \
	int				validcount;			/* used in iterating */ \
	int				light;				/* index+1 of the lumobj, or 0 */ \
	byte			halofactor;			/* strength of halo */ \
	byte			translucency;  /* default = 0 = opaque */

	typedef struct ddmobj_base_s {
	DD_BASE_MOBJ_ELEMENTS()} ddmobj_base_t;

	//------------------------------------------------------------------------
	//
	// Refresh
	//
	//------------------------------------------------------------------------

#define TICRATE			35		   // number of tics / second
#define TICSPERSEC		35

#define SCREENWIDTH		320
#define SCREENHEIGHT	200

#define I_NOUPDATE	0
#define I_FULLVIEW	1
#define I_STATBAR	2
#define I_MESSAGES	4
#define I_FULLSCRN	8

	// Update flags.
#define DDUF_BORDER		0x1		   // BorderNeedRefresh = true
#define DDUF_TOP		0x2		   // BorderTopRefresh = true
#define DDUF_FULLVIEW	0x10	   // Request update for the view.
#define DDUF_STATBAR	0x20	   // Request update for the status bar.
#define DDUF_MESSAGES	0x40	   // Request update for the messages.
#define DDUF_FULLSCREEN	0x80	   // Request update for the whole screen.
#define DDUF_UPDATE		0x10000	   // Really calls I_Update.

	//------------------------------------------------------------------------
	//
	// Sound
	//
	//------------------------------------------------------------------------

#define DDSF_FLAG_MASK			0xff000000
#define DDSF_NO_ATTENUATION		0x80000000
#define DDSF_REPEAT				0x40000000

	// Which fields are valid?
#define DDSOUNDF_VOLUME			0x1
#define DDSOUNDF_PITCH			0x2
#define DDSOUNDF_POS			0x4
#define DDSOUNDF_MOV			0x8

#define DDSOUNDF_LOCAL			0x10000	// The sound is inside the listener's head.
#define DDSOUNDF_VERY_LOUD		0x20000	// The sound has virtually no rolloff.

	typedef struct {
		int             flags;
		int             volume;	   // 0..1000
		int             pitch;	   // 1000 is normal.
		fixed_t         pos[3];
		fixed_t         mov[3];
	} sound3d_t;

	typedef struct {
		float           volume;	   // 0..1
		float           decay;	   // Decay factor: 0 (acoustically dead) ... 1 (live)
		float           damping;   // High frequency damping factor: 0..1
		float           space;	   // 0 (small space) ... 1 (large space)
	} reverb_t;

	// Which fields are valid?
#define DDLISTENERF_POS				0x1
#define DDLISTENERF_MOV				0x2
#define DDLISTENERF_YAW				0x4
#define DDLISTENERF_PITCH			0x8
	// Reverb control:
#define DDLISTENERF_SET_REVERB		0x10
#define DDLISTENERF_DISABLE_REVERB	0x20

	typedef struct {
		int             flags;
		fixed_t         pos[3];
		fixed_t         mov[3];
		float           yaw, pitch;	// In degrees: (0,0) is to the east.
		reverb_t        reverb;
	} listener3d_t;

	// Use with PlaySong().
#define DDMUSICF_EXTERNAL	0x80000000

	//------------------------------------------------------------------------
	//
	// Graphics
	//
	//------------------------------------------------------------------------

	// posts are runs of non masked source pixels
	typedef struct {
		byte            topdelta;  // -1 is the last post in a column
		byte            length;
		// length data bytes follows
	} post_t;

	// column_t is a list of 0 or more post_t, (byte)-1 terminated
	typedef post_t  column_t;

	// a patch holds one or more columns
	// patches are used for sprites and all masked pictures
	typedef struct patch_s {
		short           width;	   // bounding box size
		short           height;
		short           leftoffset;	// pixels to the left of origin
		short           topoffset; // pixels below the origin
		int             columnofs[8];	// only [width] used
		// the [0] is &columnofs[width]
	} patch_t;

	// a pic is an unmasked block of pixels
	typedef struct {
		byte            width, height;
		byte            data;
	} pic_t;

	typedef struct {
		int             lump;	   // Sprite lump number.
		int             realLump;  // Real lump number.
		int             flip;
		int             offset;
		int             topOffset;
		int             width;
		int             height;
		int             numFrames; // Number of frames the sprite has.
	} spriteinfo_t;

	typedef struct {
		int             spritenum;
		char           *modelname;
	} spritereplacement_t;

	// Anim group flags.
#define AGF_SMOOTH		0x1
#define AGF_FIRST_ONLY	0x2

	//------------------------------------------------------------------------
	//
	// Texture definition
	//
	//------------------------------------------------------------------------

	typedef struct {
		short           originx;
		short           originy;
		short           patch;
		short           stepdir;
		short           colormap;
	} mappatch_t;

	typedef struct {
		char            name[8];
		boolean         masked;
		short           width;
		short           height;
		void          **columndirectory;	// OBSOLETE
		short           patchcount;
		mappatch_t      patches[1];
	} maptexture_t;

	//------------------------------------------------------------------------
	//
	// Console
	//
	//------------------------------------------------------------------------

	// These correspond the good old text mode VGA colors.
#define CBLF_BLACK		0x00000001
#define CBLF_BLUE		0x00000002
#define CBLF_GREEN		0x00000004
#define CBLF_CYAN		0x00000008
#define CBLF_RED		0x00000010
#define CBLF_MAGENTA	0x00000020
#define CBLF_YELLOW		0x00000040
#define CBLF_WHITE		0x00000080
#define CBLF_LIGHT		0x00000100
#define CBLF_RULER		0x00000200
#define CBLF_CENTER		0x00000400
#define CBLF_TRANSMIT	0x80000000 // If server, sent to all clients.

	// Font flags.
#define DDFONT_WHITE		0x1	   // The font data is white, can be colored.

	// Windows sure is fun... <sound of teeth being ground>
#ifdef TextOut
#undef TextOut
#define _RedefineTextOut_
#endif

	typedef struct {
		int             flags;
		float           sizeX, sizeY;	// The scale.
		int             height;
		int             (*TextOut) (char *text, int x, int y);
		int             (*Width) (char *text);
		void            (*Filter) (char *text);
	} ddfont_t;

#ifdef _RedefineTextOut_
#undef _RedefineTextOut_
#define TextOut TextOutA
#endif

	// Console command.
	typedef struct ccmd_s {
		char           *name;
		int             (*func) (int argc, char **argv);
		char           *help;	   // A short help text.
	} ccmd_t;

	// Console variable flags.
#define CVF_NO_ARCHIVE		0x1	   // Not written in/read from the defaults file.
#define CVF_PROTECTED		0x2	   // Can't be changed unless forced.
#define CVF_NO_MIN			0x4	   // Don't use the minimum.
#define CVF_NO_MAX			0x8	   // Don't use the maximum.
#define CVF_CAN_FREE		0x10   // The string can be freed.
#define CVF_HIDE			0x20

	// Console variable types.
	typedef enum {
		CVT_NULL,
		CVT_BYTE,
		CVT_INT,
		CVT_FLOAT,
		CVT_CHARPTR				   // ptr points to a char*, which points to the string.
	} cvartype_t;

	// Console variable.
	typedef struct cvar_s {
		char           *name;
		int             flags;
		cvartype_t      type;
		void           *ptr;	   // Pointer to the data.
		float           min, max;  /* Minimum and maximum values
								      (for ints and floats). */
		const char     *help;	   // A short help text.
	} cvar_t;

	//------------------------------------------------------------------------
	//
	// Networking
	//
	//------------------------------------------------------------------------

	// Network Player Events
	enum {
		DDPE_ARRIVAL,			   // A player has arrived.
		DDPE_EXIT,				   // A player has exited the game.
		DDPE_CHAT_MESSAGE,		   // A player has sent a chat message.
		DDPE_DATA_CHANGE,		   // The data for this player has been changed.
		DDPE_WRITE_COMMANDS,
		DDPE_READ_COMMANDS
	};

	// World events (handled by clients)
	enum {
		DDWE_HANDSHAKE,			   // Shake hands with a new player.
		DDWE_PROJECTILE,		   // Spawn a projectile.
		DDWE_SECTOR_SOUND,		   // Play a sector sound.
		DDWE_DEMO_END			   // Demo playback ends.
	};

	/*
	 * Do not modify this structure: Servers send it as-is to clients.
	 * Only add elements to the end.
	 */
	typedef struct serverinfo_s {
		int             version;
		char            name[64];
		char            description[80];
		int             numPlayers, maxPlayers;
		char            canJoin;
		char            address[64];
		int             port;
		unsigned short  ping;	   // milliseconds
		char            game[32];  // DLL and version
		char            gameMode[17];
		char            gameConfig[40];
		char            map[20];
		char            clientNames[128];
		unsigned int    wadNumber;
		char            iwad[32];
		char            pwads[128];
		int             data[3];
	} serverinfo_t;

	typedef struct {
		int             num;	   // How many serverinfo_t's in data?
		int             found;	   // How many servers were found?
		serverinfo_t   *data;
	} serverdataquery_t;

	// For querying the list of available modems.
	typedef struct {
		int             num;
		char          **list;
	} modemdataquery_t;

	// All packet types handled by the game should be >= 64.
#define DDPT_HELLO				0
#define DDPT_OK					1
#define DDPT_CANCEL				2
#define DDPT_COMMANDS			32
#define DDPT_FIRST_GAME_EVENT	64
#define DDPT_MESSAGE			67

	// SendPacket flags (OR with to_player).
#define DDSP_ORDERED		0x20000000	// Confirm delivery in correct order.
#define DDSP_CONFIRM		0x40000000	// Confirm delivery.
#define DDSP_ALL_PLAYERS	0x80000000	// Broadcast (for server).

	// World handshake: update headers. A varying number of
	// data follows, depending on the flags. Notice: must be not
	// be padded, needs to be byte-aligned.
#pragma pack(1)
	typedef struct {
		byte            flags;
		unsigned short  sector;
	} packet_sectorupdate_t;

	typedef struct {
		byte            flags;
		unsigned short  side;
	} packet_wallupdate_t;
#pragma pack()

	// World handshake flags. Sent by the game server:
	// Sector update flags.
#define DDSU_FLOOR_HEIGHT	0x01
#define DDSU_FLOOR_MOVING	0x02   // Destination and speed sent.
#define DDSU_CEILING_HEIGHT	0x04
#define DDSU_CEILING_MOVING	0x08   // Destination and speed.
#define DDSU_FLOORPIC		0x10   // Floorpic changed.
#define DDSU_CEILINGPIC		0x20   // Ceilingpic changed.
#define DDSU_LIGHT_LEVEL	0x40

	// Wall update flags.
#define DDWU_TOP			0x01   // Top texture.
#define DDWU_MID			0x02   // Mid texture.
#define DDWU_BOTTOM			0x04   // Bottom texture.

	// Missile spawn request flags.
#define DDMS_FLAG_MASK		0xc000
#define DDMS_MOVEMENT_XY	0x4000 // XY movement included.
#define DDMS_MOVEMENT_Z		0x8000 // Z movement included.

	//------------------------------------------------------------------------
	//
	// Player Data
	//
	//------------------------------------------------------------------------

	// Player flags.
#define DDPF_FIXANGLES		0x1	   // Server: send angle/pitch to client.
#define DDPF_FILTER			0x2	   // Server: send filter to client.
#define DDPF_FIXPOS			0x4	   // Server: send coords to client.
#define DDPF_DEAD			0x8	   // Cl & Sv: player is dead.
#define DDPF_CAMERA			0x10   // Player is a cameraman.
#define DDPF_LOCAL			0x20   // Player is local (e.g. player zero).
#define DDPF_FIXMOM			0x40   // Server: send momentum to client.
#define DDPF_NOCLIP			0x80   // Client: don't clip movement.

#define PLAYERNAMELEN		81

	// Normally one for the weapon and one for the muzzle flash.
#define DDMAXPSPRITES 2

	// Player sprite flags.
#define DDPSPF_RENDERED		0x1	   // Was rendered.

	enum						   // Psprite states.
	{
		DDPSP_BOBBING,
		DDPSP_FIRE,
		DDPSP_DOWN,
		DDPSP_UP
	};

	// Player sprites.
	typedef struct {
		state_t        *stateptr;
		int             tics;
		float           light, alpha;
		float           x, y;
		int             flags;
		int             state;
		int             offx, offy;
	} ddpsprite_t;

	// Lookdir conversions.
#define LOOKDIR2DEG(x)	((x) * 85.0/110.0)
#define LOOKDIR2RAD(x)	(LOOKDIR2DEG(x)/180*PI)

	struct mobj_s;

	typedef struct ddplayer_s {
		struct mobj_s  *mo;		   // pointer to a (game specific) mobj
		fixed_t         viewz;	   // focal origin above r.z
		fixed_t         viewheight;	// base height above floor for viewz
		fixed_t         deltaviewheight;
		float           lookdir;   // It's now a float, for mlook.
		int             fixedcolormap;	// can be set to REDCOLORMAP, etc
		int             extralight;	// so gun flashes light up areas
		int             ingame;	   // is this player in game?
		int             flags;
		int             filter;	   // RGBA filter for the camera
		int             clAngle;   // client side
		float           clLookDir; // client side
		angle_t         lastangle; // For calculating turndeltas.
		ddpsprite_t     psprites[DDMAXPSPRITES];	// Player sprites.
		void           *extradata; // Pointer to any game-specific data.
	} ddplayer_t;

	// Actions.
	typedef struct {
		char            name[9];   // The name of the action.
		boolean         on;		   // True if action is active.
	} action_t;

#ifdef __cplusplus
}
#endif
#endif
