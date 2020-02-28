// Extended generalized sector types.
#ifndef __XG_SECTORTYPE_H__
#define __XG_SECTORTYPE_H__

// Sector chain event types.
enum {
	XSCE_FLOOR,
	XSCE_CEILING,
	XSCE_INSIDE,
	XSCE_TICKER,
	XSCE_NUM_CHAINS,

	XSCE_FUNCTION
};

// Sector Type flags.
#define STF_GRAVITY			0x00000001	// Use custom gravity gravity.
#define STF_FRICTION		0x00000002	// Use custom friction.
#define STF_CRUSH			0x00000004
#define STF_PLAYER_WIND		0x00000008	// Wind affects players.
#define STF_OTHER_WIND		0x00000010
#define STF_MONSTER_WIND	0x00000020
#define STF_MISSILE_WIND	0x00000040
#define STF_ANY_WIND		0x00000018	// Player + nonplayer.
#define STF_ACT_TAG_TEXMOVE	0x00000080	// Texmove from act tagged line.
#define STF_ACT_TAG_WIND	0x00000100
#define STF_FLOOR_WIND		0x00000200	// Wind only when touching the floor.
#define STF_CEILING_WIND	0x00000400

// Sector Chain Event flags.
#define SCEF_PLAYER_A		0x00000001	// Activate for players.
#define SCEF_OTHER_A		0x00000002	// Act. for non-players.
#define SCEF_MONSTER_A		0x00000004	// Countkills.
#define SCEF_MISSILE_A		0x00000008	// Missiles.
#define SCEF_ANY_A			0x00000010	// All mobjs.
#define SCEF_TICKER_A		0x00000020	// Activate by ticker.

#define SCEF_PLAYER_D		0x00000040	// Deactivate for players.
#define SCEF_OTHER_D		0x00000080	// Deact. for non-players.
#define SCEF_MONSTER_D		0x00000100	// Countkills.
#define SCEF_MISSILE_D		0x00000200	// Missiles.
#define SCEF_ANY_D			0x00000400	// All mobjs.
#define SCEF_TICKER_D		0x00000800	// Deactivate by ticker.

// Plane mover flags.
#define PMF_CRUSH					0x1	// Crush things inside.

// (De)activate origin if move is blocked (when not crushing) and 
// destroy mover. Normally the mover waits until it can move again.
#define PMF_ACTIVATE_ON_ABORT		0x2
#define PMF_DEACTIVATE_ON_ABORT		0x4

// (De)activate origin when move is done.
#define PMF_ACTIVATE_WHEN_DONE		0x8
#define PMF_DEACTIVATE_WHEN_DONE	0x10

#define PMF_OTHER_FOLLOWS			0x20	// Other plane follows.
#define PMF_WAIT					0x40	// Wait until timer counts to 0.
#define PMF_SET_ORIGINAL			0x80	// Set origfloor/ceil.

// Only play sound for one sector.
#define PMF_ONE_SOUND_ONLY			0x100

typedef struct function_s {
	struct function_s *link;	   // Linked to another func?
	char           *func;
	int             flags;
	int             pos;
	int             repeat;
	int             timer, maxtimer;
	int             mininterval, maxinterval;
	float           scale, offset;
	float           value, oldvalue;
} function_t;

enum {
	XGSP_FLOOR,
	XGSP_CEILING,

	XGSP_RED = 0,
	XGSP_GREEN,
	XGSP_BLUE
};

typedef struct {
	boolean         disabled;
	function_t      rgb[3];		   // Don't move the functions around in the struct.
	function_t      plane[2];
	function_t      light;
	sectortype_t    info;
	int             timer;
	int             chain_timer[DDLT_MAX_CHAINS];
} xgsector_t;

typedef struct {
	thinker_t       thinker;

	struct sector_s *sector;
	boolean         ceiling;	   // True if operates on the ceiling.

	int             flags;
	struct line_s  *origin;

	fixed_t         destination;
	fixed_t         speed;		   // Signed.
	fixed_t         crushspeed;	   // Signed (speed to use when crushing).

	int             setflat;	   // Set flat when move done.
	int             setsector;	   // Sector type to set when move done
	// (-1 if no change).
	int             startsound;	   // Played after waiting.
	int             endsound;	   // Play when move done.
	int             movesound;	   // Sound to play while moving.
	int             mininterval, maxinterval;	// Sound playing intervals.

	int             timer;		   // Counts down to zero.

} xgplanemover_t;

void            XS_Init(void);
void            XS_Ticker(void);
void            XS_Update(void);

int             XS_Gravity(struct sector_s *sector);
int             XS_Friction(struct sector_s *sector);
int             XS_ThrustMul(struct sector_s *sector);

int             XSTrav_MovePlane(struct sector_s *sector, boolean ceiling,
								 int data, void *context);
int             XSTrav_SectorType(struct sector_s *sec, boolean ceiling,
								  int data, void *context);
int             XSTrav_SectorLight(struct sector_s *sector, boolean ceiling,
								   int data, void *context);
int             XSTrav_PlaneTexture(struct sector_s *sec, boolean ceiling,
									int data, void *context);
void            XS_InitStairBuilder(void);
int             XSTrav_BuildStairs(struct sector_s *sector, boolean ceiling,
								   int data, void *context);
int             XSTrav_SectorSound(struct sector_s *sec, boolean ceiling,
								   int data, void *context);
int             XSTrav_MimicSector(struct sector_s *sector, boolean ceiling,
								   int data, void *context);
void            XS_SetSectorType(struct sector_s *sec, int special);
void            XS_ChangePlaneTexture(struct sector_s *sector, boolean ceiling,
									  int tex);
xgplanemover_t *XS_GetPlaneMover(struct sector_s *sector, boolean ceiling);
void            XS_PlaneMover(xgplanemover_t * mover);	// A thinker for plane movers.

void            SV_WriteXGSector(struct sector_s *sec);
void            SV_ReadXGSector(struct sector_s *sec);
void            SV_WriteXGPlaneMover(thinker_t *th);
void            SV_ReadXGPlaneMover(void);

#endif
