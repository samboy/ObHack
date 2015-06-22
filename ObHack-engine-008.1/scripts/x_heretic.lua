----------------------------------------------------------------
-- GAME DEF : Heretic
----------------------------------------------------------------
--
--  Oblige Level Maker (C) 2006,2007 Andrew Apted
--
--  This program is free software; you can redistribute it and/or
--  modify it under the terms of the GNU General Public License
--  as published by the Free Software Foundation; either version 2
--  of the License, or (at your option) any later version.
--
--  This program is distributed in the hope that it will be useful,
--  but WITHOUT ANY WARRANTY; without even the implied warranty of
--  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
--  GNU General Public License for more details.
--
----------------------------------------------------------------

HC_THINGS =
{
  --- special stuff ---
  player1 = { id=1, kind="other", r=16,h=56 },
  player2 = { id=2, kind="other", r=16,h=56 },
  player3 = { id=3, kind="other", r=16,h=56 },
  player4 = { id=4, kind="other", r=16,h=56 },

  dm_player     = { id=11, kind="other", r=16,h=56 },
  teleport_spot = { id=14, kind="other", r=16,h=56 },

  ctf_player_blue = { id=5080, kind="other", r=16,h=56 },
  ctf_player_red  = { id=5081, kind="other", r=16,h=56 },
  ctf_flag_blue =   { id=5130, kind="other", r=16,h=56 },
  ctf_flag_red  =   { id=5131, kind="other", r=16,h=56 },

  --- monsters ---
  gargoyle    = { id=66, kind="monster", r=16,h=36 },
  fire_garg   = { id=5,  kind="monster", r=16,h=36 },
  golem       = { id=68, kind="monster", r=22,h=64 },
  golem_inv   = { id=69, kind="monster", r=22,h=64 },

  nitro       = { id=45, kind="monster", r=22,h=64 },
  nitro_inv   = { id=46, kind="monster", r=22,h=64 },
  warrior     = { id=64, kind="monster", r=24,h=80 },
  warrior_inv = { id=65, kind="monster", r=24,h=80 },

  disciple   = { id=15, kind="monster", r=16,h=72 },
  sabreclaw  = { id=90, kind="monster", r=20,h=64 },
  weredragon = { id=70, kind="monster", r=34,h=80 },
  ophidian   = { id=92, kind="monster", r=22,h=72 },

  ironlich   = { id=6,  kind="monster", r=80,h=72 },
  maulotaur  = { id=9,  kind="monster", r=28,h=104 },
  d_sparil   = { id=7,  kind="monster", r=28,h=120 },

  --- pickups ---
  k_yellow   = { id=80, kind="pickup", r=20,h=16, pass=true },
  k_green    = { id=73, kind="pickup", r=20,h=16, pass=true },
  k_blue     = { id=79, kind="pickup", r=20,h=16, pass=true },

  gauntlets  = { id=2005, kind="pickup", r=20,h=16, pass=true },
  crossbow   = { id=2001, kind="pickup", r=20,h=16, pass=true },
  claw       = { id=53,   kind="pickup", r=20,h=16, pass=true },
  hellstaff  = { id=2004, kind="pickup", r=20,h=16, pass=true },
  phoenix    = { id=2003, kind="pickup", r=20,h=16, pass=true },
  firemace   = { id=2002, kind="pickup", r=20,h=16, pass=true },

  crystal    = { id=10, kind="pickup", r=20,h=16, pass=true },
  geode      = { id=12, kind="pickup", r=20,h=16, pass=true },
  arrows     = { id=18, kind="pickup", r=20,h=16, pass=true },
  quiver     = { id=19, kind="pickup", r=20,h=16, pass=true },
  claw_orb1  = { id=54, kind="pickup", r=20,h=16, pass=true },
  claw_orb2  = { id=55, kind="pickup", r=20,h=16, pass=true },
  runes1     = { id=20, kind="pickup", r=20,h=16, pass=true },
  runes2     = { id=21, kind="pickup", r=20,h=16, pass=true },
  flame_orb1 = { id=22, kind="pickup", r=20,h=16, pass=true },
  flame_orb2 = { id=23, kind="pickup", r=20,h=16, pass=true },
  mace_orbs  = { id=13, kind="pickup", r=20,h=16, pass=true },
  mace_pile  = { id=16, kind="pickup", r=20,h=16, pass=true },

  h_vial  = { id=81, kind="pickup", r=20,h=16, pass=true },
  h_flask = { id=82, kind="pickup", r=20,h=16, pass=true },
  h_urn   = { id=32, kind="pickup", r=20,h=16, pass=true },
  shield1 = { id=85, kind="pickup", r=20,h=16, pass=true },
  shield2 = { id=31, kind="pickup", r=20,h=16, pass=true },

  bag     = { id=8,  kind="pickup", r=20,h=16, pass=true },
  wings   = { id=23, kind="pickup", r=20,h=16, pass=true },
  ovum    = { id=30, kind="pickup", r=20,h=16, pass=true },
  torch   = { id=33, kind="pickup", r=20,h=16, pass=true },
  bomb    = { id=34, kind="pickup", r=20,h=16, pass=true },
  map     = { id=35, kind="pickup", r=20,h=16, pass=true },
  chaos   = { id=36, kind="pickup", r=20,h=16, pass=true },
  shadow  = { id=75, kind="pickup", r=20,h=16, pass=true },
  ring    = { id=84, kind="pickup", r=20,h=16, pass=true },
  tome    = { id=86, kind="pickup", r=20,h=16, pass=true },

  --- The names used by SETTINGS.iweapon (Start weapon) for starting weapon ---
  iw_basic = { id=2001, kind="pickup", r=20,h=16, pass=true }, -- Crossbow
  iw_hardcore = { id=2003, kind="pickup", r=20,h=16, pass=true }, -- Phoenix
  iw_hardcore2 = { id=53, kind="pickup", r=20,h=16, pass=true }, -- Claw
  --iw_berserk = { id=32, kind="pickup", r=20,h=16, pass=true }, -- Mystic Urn

  --- scenery ---
  wall_torch    = { id=50, kind="scenery", r=10,h=64, light=255, pass=true, add_mode="extend" },
  serpent_torch = { id=27, kind="scenery", r=12,h=54, light=255 },
  fire_brazier  = { id=76, kind="scenery", r=16,h=44, light=255 },
  chandelier    = { id=28, kind="scenery", r=31,h=60, light=255, pass=true, ceil=true, add_mode="island" },

  barrel  = { id=44,   kind="scenery", r=12,h=32 },
  pod     = { id=2035, kind="scenery", r=16,h=54 },

  blue_statue   = { id=94, kind="scenery", r=16,h=54 },
  green_statue  = { id=95, kind="scenery", r=16,h=54 },
  yellow_statue = { id=96, kind="scenery", r=16,h=54 },

  moss1   = { id=48, kind="scenery", r=16,h=24, ceil=true, pass=true },
  moss2   = { id=49, kind="scenery", r=16,h=28, ceil=true, pass=true },
  volcano = { id=87, kind="scenery", r=12,h=32 },
  
  small_pillar = { id=29, kind="scenery", r=16,h=36 },
  brown_pillar = { id=47, kind="scenery", r=16,h=128 },
  glitter_red  = { id=74, kind="scenery", r=20,h=16, pass=true },
  glitter_blue = { id=52, kind="scenery", r=20,h=16, pass=true },

  stal_small_F = { id=37, kind="scenery", r=12,h=36 },
  stal_small_C = { id=39, kind="scenery", r=16,h=36, ceil=true },
  stal_big_F   = { id=38, kind="scenery", r=12,h=72 },
  stal_big_C   = { id=40, kind="scenery", r=16,h=72, ceil=true },

  hang_skull_1 = { id=17, kind="scenery", r=20,h=64, ceil=true, pass=true },
  hang_skull_2 = { id=24, kind="scenery", r=20,h=64, ceil=true, pass=true },
  hang_skull_3 = { id=25, kind="scenery", r=20,h=64, ceil=true, pass=true },
  hang_skull_4 = { id=26, kind="scenery", r=20,h=64, ceil=true, pass=true },
  hang_corpse  = { id=51, kind="scenery", r=12,h=104,ceil=true },

  --- ambient sounds ---
  amb_scream = { id=1200, kind="other", r=20,h=16, pass=true },
  amb_squish = { id=1201, kind="other", r=20,h=16, pass=true },
  amb_drip   = { id=1202, kind="other", r=20,h=16, pass=true },
  amb_feet   = { id=1203, kind="other", r=20,h=16, pass=true },
  amb_heart  = { id=1204, kind="other", r=20,h=16, pass=true },
  amb_bells  = { id=1205, kind="other", r=20,h=16, pass=true },
  amb_growl  = { id=1206, kind="other", r=20,h=16, pass=true },
  amb_magic  = { id=1207, kind="other", r=20,h=16, pass=true },
  amb_laugh  = { id=1208, kind="other", r=20,h=16, pass=true },
  amb_run    = { id=1209, kind="other", r=20,h=16, pass=true },

  env_water  = { id=41, kind="other", r=20,h=16, pass=true },
  env_wind   = { id=42, kind="other", r=20,h=16, pass=true },
}

-- The following is *not* used; ignore this
HC_LINE_TYPES =  -- NOTE: only includes differences to DOOM
{
  A1_scroll_right = { kind=99 },
  W1_secret_exit  = { kind=105 },

  P1_green_door = { kind=33 },
  PR_green_door = { kind=28 },
}

HC_SECTOR_TYPES =
{
  secret   = { kind=9 },
  friction = { kind=15 },

  random_off = { kind=1 },
  blink_fast = { kind=2 },
  blink_slow = { kind=3 },
  glow       = { kind=8 },

  damage_5  = { kind=7 },
  damage_10 = { kind=5 },
  damage_20 = { kind=16 },
}


----------------------------------------------------------------

HC_COMBOS =
{
  ---- INDOOR ------------

  GOLD =
  {
    theme_probs = { CITY=20, EGYPT=20 },
    mat_pri = 6,

    wall  = "SANDSQ2",
    floor = "FLOOR06",
    ceil  = "FLOOR11",

--  void = "SNDBLCKS",
    pillar = "SNDCHNKS",

    scenery =  {wall_torch=60},

    wall_fabs = { wall_pic_BANNER5= 10, wall_pic_GLASS1=20, wall_pic_GLASS2=15, other=10 },
  },

  BLOCK =
  {
    theme_probs = { CITY=20 },
    mat_pri = 7,

    wall  = "GRSTNPB",
    floor = "FLOOR03",
    ceil  = "FLOOR03",

    void = "GRSTNPBW",
    pillar = "WOODWL",

    scenery =  {wall_torch=20, barrel=20},
    
    wall_fabs = { wall_pic_BANNER3= 10, wall_pic_BANNER4= 10 }, 
  },

  MOSSY =
  {
    theme_probs = { CITY=20, DOME=20 },
    mat_pri = 2,

    wall  = "MOSSRCK1",
    floor = "FLOOR00",
    ceil  = "FLOOR04",

    pillar = "SKULLSB1", -- SPINE1

    scenery =  {chandelier=20, wall_torch=20},
    
    wall_fabs = { wall_pic_BANNER1= 10, wall_pic_BANNER2= 10 }, 
  },

  WOOD =
  {
    theme_probs = { CITY=20, EGYPT=20 },
    mat_pri = 2,

    wall  = "WOODWL",
    floor = "FLOOR10",
    ceil  = "FLOOR12",

--  void = "CTYSTUC3",

    scenery = {hang_skull_1=20, wall_torch=20},

    wall_fabs = { wall_pic_BANNER5= 10, wall_pic_BANNER6= 10 },
  },

  HUT =
  {
    theme_probs = { CITY=20, DOME=20 },
    mat_pri = 1,
    
    wall  = "CTYSTUC3",
    floor = "FLOOR10",
    ceil  = "FLOOR11",

--  void = "CTYSTUC4",

    scenery =  {wall_torch=20, barrel=20},
    wall_fabs = { wall_pic_BANNER5= 10, wall_pic_BANNER6= 10 },
  },

  DISCO1 = 
  {
    theme_probs = { EGYPT=20 },
    mat_pri = 1,
    
    wall  = "SPINE2",
    floor = "FLAT522",
    ceil  = "FLOOR06",
    step  = "SNDBLCKS",

--  void = "CTYSTUC4",
    wall_fabs = { wall_pic_BANNER5= 10, wall_pic_BANNER6= 10 },  
    scenery =  {wall_torch=20, barrel=25},

  },
 
  --- Grey-walls, pink/brown floors 
  DISCO2 = 
  {
    theme_probs = { DOME=20 },
    mat_pri = 1,
    
    wall  = "SQPEB1",
    floor = "FLAT522",
    ceil  = "FLOOR06",
    step  = "SPINE2",

--  void = "CTYSTUC4",
    wall_fabs = { wall_pic_BANNER7= 10, wall_pic_BANNER8= 10 },
    scenery =  {wall_torch=50, barrel=20},
},
  
  PYRAMID =
  {
    theme_probs = { EGYPT=20 },
    mat_pri = 1,
    
    wall  = "SNDPLAIN",
    floor = "FLOOR27",
    ceil  = "FLOOR10",
    step  = "SPINE2",

--  void = "CTYSTUC4",
    scenery =  {wall_torch=25, barrel=20},
  },

  PHAROAH =
  {
    theme_probs = { EGYPT=15 },
    mat_pri = 1,
    
    wall  = "TRISTON2",
    floor = "FLAT522",
    ceil  = "FLOOR20",
    step  = "SQPEB2",

--  void = "CTYSTUC4",
	scenery = "wall_torch",
  },

  PARLOR =
  {
    theme_probs = { EGYPT=15 },
    mat_pri = 1,
    
    wall  = "SQPEB2",
    floor = "FLOOR06",
    ceil  = "FLOOR06",
    step  = "SQPEB2",

--  void = "CTYSTUC4",

    scenery = "wall_torch",
  },

  SBLOCK =
  {
    theme_probs = { EGYPT=20 },
    mat_pri = 1,
    
    wall  = "SNDBLCKS",
    floor = "FLOOR27",
    ceil  = "FLOOR10",
    step  = "SPINE2",

--  void = "CTYSTUC4",
	scenery =  {wall_torch=20, barrel=25},
  },


  CAVE1 = 
  {
    theme_probs = { CAVE=20 },
    mat_pri = 1,
    wall = "LOOSERCK",
    floor = "FLAT516",
    ceil = "FLOOR01",

    scenery = {stal_big_C=40, wall_torch=70},
 
  }, 

  CAVE2 = 
  {
    theme_probs = { CAVE=20 },
    mat_pri = 1,
    wall = "LAVA1",
    floor = "FLAT516",
    ceil = "FLAT506",

    scenery = {stal_small_C=50, wall_torch=70},
 
  }, 

  CAVE3 =  -- Muddy walls, but one of the few outdoor textures
  {
    theme_probs = { CAVE=20, EGYPT=10 },
    mat_pri = 1,
    wall = "BRWNRCKS",
    floor = "FLOOR01",
    ceil = "FLAT516",

    scenery = {stal_small_C=50, wall_torch=20},
 
  }, 

  PURPLE =
  {
    theme_probs = { GARISH=20 },
    mat_pri = 1,

    wall  = "BLUEFRAG",
    floor = "FLOOR07",
    ceil  = "FLOOR07",

--  void = "CTYSTCI4",
    scenery = {wall_torch=70},
  },

  BLUE =
  {
    theme_probs = { GARISH=20 },
    mat_pri = 1,

    wall  = "MOSAIC1",
    floor = "FLAT502",
    ceil  = "FLOOR16",

--  void = "CTYSTCI4",
    scenery = {wall_torch=50},
  },

--- The greens don't look that great in Heretic
  GREEN =
  {
    theme_probs = { UNUSED=20 },
    mat_pri = 1,

    wall  = "GRNBLOK1",
    floor = "FLAT513",
    ceil  = "FLOOR18",

--  void = "CTYSTCI4",
	scenery =  {wall_torch=50, barrel=25},
  },

  ICE =
  {
    theme_probs = { GARISH=20 },
    mat_pri = 1,

    wall  = "STNGLS1",
    floor = "FLAT502",
    ceil  = "FLAT517",

--  void = "CTYSTCI4",
scenery =  {wall_torch=20, barrel=25},
  },

  ROOT =
  {
    theme_probs = { CAVE=15 },
    mat_pri = 1,

    wall  = "ROOTWALL",
    floor = "FLAT506",
    ceil  = "FLAT506",

--  void = "CTYSTCI4",
scenery =  {wall_torch=30, barrel=40},
  },

  ---- OUTDOOR ------------

  CAVEO1 = 
  {
    theme_probs = { CAVE=20 },
    mat_pri = 2,
    outdoor = true,
    wall = "LOOSERCK",
    floor = "FLAT516",
    ceil = "FLOOR01",

    scenery =  {stal_big_F=70, wall_torch=30 },
 
  }, 

  CAVEO2 = 
  {
    theme_probs = { CAVE=20 },
    mat_pri = 2,
    outdoor = true,
    wall = "LAVA1",
    floor = "FLAT516",
    ceil = "FLAT506",

    scenery =  {wall_torch=30, stal_small_F=45},
 
  }, 

  CAVEMUD = 
  {
    theme_probs = { CAVE=15 },
    mat_pri = 2,
    outdoor = true,
    wall = "RCKSNMUD",
    floor = "FLAT510",
    ceil = "FLAT510",

    scenery =  {wall_torch=30, stal_small_F=45},
  }, 

  --- Looks obnoxious outdoors; disabled
  ROOTO =
  {
    theme_probs = { UNUSED=15 },
    mat_pri = 2,
    outdoor = true,

    wall  = "ROOTWALL",
    floor = "FLAT506",
    ceil  = "FLAT506",

--  void = "CTYSTCI4",
scenery =  {wall_torch=20, barrel=25},
  },


  ODISCO1 = 
  {
    theme_probs = { EGYPT=20 },
    mat_pri = 1,
    outdoor = true,
    
    wall  = "SPINE2",
    floor = "FLAT522",
    ceil  = "FLOOR06",
    step  = "SNDBLCKS",

--  void = "CTYSTUC4",
    wall_fabs = { wall_torch=20, wall_pic_BANNER7= 10, wall_pic_BANNER8= 10 },
  },
  
  ODISCO2 = 
  {
    theme_probs = { DOME=20 },
    mat_pri = 1,
    outdoor = true,
    
    wall  = "SQPEB1",
    floor = "FLAT522",
    ceil  = "FLOOR06",
    step  = "SPINE2",

--  void = "CTYSTUC4",
scenery =  {wall_torch=20, barrel=25},
  },

  PYRAMIDO =
  {
    theme_probs = { EGYPT=20 },
    mat_pri = 1,
    outdoor = true,
    
    wall  = "SNDPLAIN",
    floor = "FLOOR27",
    ceil  = "FLOOR27",
    step  = "SPINE2",

--  void = "CTYSTUC4",
scenery =  {wall_torch=20, barrel=25},
  },

  PHAROAHO =
  {
    theme_probs = { EGYPT=15 },
    mat_pri = 1,
    outdoor = true,
    
    wall  = "TRISTON2",
    --- floor = "FLAT521", -- Grey and red-brown is kinda ugly
    floor = "FLAT522",
    ceil  = "FLAT503",
    step  = "SQPEB2",

--  void = "CTYSTUC4",
scenery =  {wall_torch=20, barrel=25},
  },
  
  WATER =
  {
    theme_probs = { GARISH=20 },
    outdoor = true,
    mat_pri = 1,

    wall  = "WATRWAL1",
    floor = "FLTWAWA1",
    ceil  = "FLTWAWA1",

--  void = "CTYSTCI4",
scenery =  {wall_torch=20},
    liquid_prob = 0,
  },

  PURPLEO =
  {
    theme_probs = { GARISH=20 },
    outdoor = true,
    mat_pri = 1,

    wall  = "REDWALL",
    floor = "FLOOR07",
    ceil  = "FLOOR07",

--  void = "CTYSTCI4",
scenery =  {wall_torch=20, barrel=25},
  },

  GREENO =
  {
    theme_probs = { UNUSED=20 },
    outdoor = true,
    mat_pri = 1,

    wall  = "GRNBLOK1",
    floor = "FLOOR18",
    ceil  = "FLOOR18",

--  void = "CTYSTCI4",
scenery =  {wall_torch=20, barrel=25},
  },

  STONY =
  {
    theme_probs = { CITY=20 },
    outdoor = true,
    mat_pri = 3,

    wall  = "GRSTNPB",
    floor = "FLOOR00",
    ceil  = "FLOOR00",

--  void = "GRSTNPBV",
    scenery =  {serpent_torch=40, barrel=25},
  },

  MUDDY =
  {
    theme_probs = { CITY=20, DOME=20 },
    outdoor = true,
    mat_pri = 3,

    wall  = "CSTLRCK",
    floor = "FLOOR17",
    ceil  = "FLOOR17",

--  void = "SQPEB1",
    pillar = "SPINE1",

    scenery =  {fire_brazier=50, barrel=15},

  },
  
  SANDZ =
  {
    theme_probs = { EGYPT=20 },
    outdoor = true,
    mat_pri = 1,

    wall  = "SNDBLCKS",
    floor = "FLOOR27",
    ceil  = "FLOOR27",

--  void = "CTYSTCI4",
scenery =  {wall_torch=20, barrel=25},
    liquid_prob = 0,
  },

  SANDY =
  {
    theme_probs = { CITY=20, DOME=20 },
    outdoor = true,
    mat_pri = 2,
    
    wall  = "CTYSTUC2",
    floor = "FLOOR27",
    ceil  = "FLOOR27",

--  void = "CTYSTUC3",
    pillar = "SPINE2",

    scenery =  {wall_torch=20, small_pillar=50},
  },
  
}

HC_EXITS =
{
  METAL =
  {
    mat_pri = 9,

    wall  = "METL2",
    floor = "FLOOR03",
    ceil  = "FLOOR19",

    switch =
    {
      prefab="SWITCH_NICHE_TINY",
      add_mode="wall",
      skin =
      {
        switch_w="SW2OFF", wall="METL2",
--      switch_f="FLOOR28",

        switch_h=32, x_offset=16, y_offset=48,
        kind=11, tag=0,
      }    
    },
	wall_fabs = { wall_pic_SKULL1= 20},
  },
  BLOODY = -- name hardcoded in planner.lua for secret exit
  {
    secret_exit = true,
    mat_pri = 9,

    wall  = "METL2",
    floor = "FLOOR03",
    ceil  = "FLOOR19",

    switch =
    {
      prefab="SWITCH_NICHE_TINY",
      add_mode="wall",
      skin =
      {
        switch_w="SW1OFF", wall="METL2",
--      switch_f="FLOOR28",

        switch_h=32, x_offset=16, y_offset=48,
        kind=51, tag=0,
      }
    },
  wall_fabs = { wall_pic_SKULL1= 20},
  },
}

HC_HALLWAYS =
{
 
  -- Hall with set stone walls 
  RCKHALL = {
        mat_pri = 0,
	theme_probs = { CITY=20, DOME=20 },
    	wall = "GRSTNPB",
	void = "GRSTNPB",
    	step  = "GRSTNPB",
	pillar = "WOODWL",
	
    floor = "FLOOR03",
    ceil  = "FLOOR03",
	trim_mode = "guillotine",	
	
  },

  -- Hall with natural stone walls
  STHALL = {
        mat_pri = 0,
	theme_probs = { CITY=20, CAVE=20 },
    	wall = "LOOSERCK",
	void = "LOOSERCK",
    	step  = "GRSTNPB",
	pillar = "GRSTNPB",
	
    floor = "FLOOR00",
    ceil  = "FLOOR00",
	trim_mode = "guillotine",	
	
  },

  -- Hall with roots on the walls
  RTHALL = {
        mat_pri = 0,
	theme_probs = { CAVE=20 },
    	wall = "ROOTWALL",
	void = "ROOTWALL",
    	step  = "ROOTWALL",
	pillar = "ROOTWALL",
	
    floor = "FLAT506",
    ceil  = "FLAT506",
	trim_mode = "guillotine",	
	
  },

  -- Hall with sandy walls
  SDHALL = {
        mat_pri = 0,
	theme_probs = { EGYPT=20 },
    	wall = "SNDPLAIN",
	void = "SNDPLAIN",
    	step  = "SPINE2",
	pillar = "SPINE2",
	
    floor = "FLOOR27",
    ceil  = "FLOOR10",
	trim_mode = "guillotine",	
	
  },

  -- Hall with wooden walls
  WDHALL = {
        mat_pri = 0,
	theme_probs = { CITY=20, EGYPT=20 },
    	wall = "SQPEB2",
	void = "SQPEB2",
    	step  = "SQPEB2",
	pillar = "SQPEB2",
	
    floor = "FLOOR06",
    ceil  = "FLOOR06",
	trim_mode = "guillotine",	
	
  },

  -- Garish blue watery hall
  WHALL = {
        mat_pri = 0,
	theme_probs = { GARISH=20, DOME=20 },
    	wall = "MOSAIC1",
	void = "MOSAIC1",
    	step  = "WATRWAL1",
	pillar = "WATRWAL1",
	
    floor = "FLTWAWA1",
    ceil  = "FLAT502",
	trim_mode = "guillotine",	
	
  }
}


---- BASE MATERIALS ------------

HC_MATS =
{
  METAL =
  {
    mat_pri = 5,

    wall  = "METL2",
    void  = "METL1",
    floor = "FLOOR28",
    ceil  = "FLOOR28",
  },

  STEP =
  {
    wall  = "SNDPLAIN",
    floor = "FLOOR27",
  },

  LIFT =
  {
    wall = "DOORSTON",
    floor = "FLOOR08"
  },

  TRACK =
  {
    wall  = "METL2",
    floor = "FLOOR28",
  },

  DOOR_FRAME =
  {
    wall  = nil,  -- this means: use plain wall
    floor = "FLOOR04",
    ceil  = "FLOOR04",
  },
}

--- PEDESTALS --------------

HC_PEDESTALS =
{
  PLAYER =
  {
    wall  = "CTYSTCI4", void = "CTYSTCI4",
    floor = "FLOOR11",   ceil = "FLOOR11",
    h = 8,
  },

  QUEST = -- FIXME
  {
    wall  = "CTYSTCI4", void = "CTYSTCI4",
    floor = "FLOOR11",   ceil = "FLOOR11",
    h = 8,
  },

  WEAPON = -- FIXME
  {
    wall  = "CTYSTCI4", void = "CTYSTCI4",
    floor = "FLOOR11",  ceil = "FLOOR11",
    h = 8,
  },
    
}

---- OVERHANGS ------------

HC_OVERHANGS =
{
  WOOD =
  {
    ceil = "FLOOR10",
    upper = "CTYSTUC3",
    thin = "WOODWL",
  },
}

---- MISC STUFF ------------

HC_LIQUIDS =
{
  water  = { floor="FLTFLWW1", wall="WATRWAL1" },
  lava   = { floor="FLATHUH1", wall="LAVAFL1", sec_kind=16 },
  magma  = { floor="FLTLAVA1", wall="LAVA1",   sec_kind=5 },
  sludge = { floor="FLTSLUD1", wall="LAVA1",   sec_kind=7 },
}

HC_SWITCHES =
{
  sw_demon =
  {
    switch =
    {
      prefab = "SWITCH_NICHE_TINY",
      add_mode = "island",
      skin =
      {
        wall="GRSKULL1",
        switch_w="SW1OFF", switch_h=32,
        x_offset=16, y_offset=48, kind=103,
      }
    },

    door =
    {
      w=128, h=128,
      prefab = "DOOR",
      skin =
      {
        door_w="DMNMSK", door_c="FLOOR10",
        track_w="METL2",
        door_h=128,
        door_kind=0, tag=0,
      }
    },
  },

  sw_celtic =
  {
    switch =
    {
      prefab="SWITCH_NICHE_TINY",
      add_mode = "island",
      skin =
      {
        wall="CELTIC",
        switch_w="SW1OFF", switch_h=32,
        x_offset=16, y_offset=48, kind=103,
      }
    },

    door =
    {
      w=128, h=128,
      prefab = "DOOR",
      skin =
      {
        door_w="CELTIC", door_c="FLAT522",
        track_w="METL2",
        door_h=128,
        door_kind=0, tag=0,
      }
    },
  },

  sw_green =
  {
    switch =
    {
      prefab = "SWITCH_NICHE_TINY",
      add_mode = "island",
      skin =
      {
        wall="GRNBLOK1",
        switch_w="SW1OFF", switch_h=32,
        x_offset=16, y_offset=48, kind=103,
      }
    },

    door =
    {
      w=128, h=128,
      prefab = "DOOR",
      skin =
      {
        door_w="GRNBLOK4", door_c="FLOOR18",
        track_w="METL2",
        door_h=128,
        door_kind=0, tag=0,
      }
    },
  },
}

HC_DOORS =
{
  d_demon = { prefab="DOOR", w=128, h=128,

               skin =
               {
                 door_w="DMNMSK", door_c="FLOOR10",
                 track_w="METL2",
                 door_h=128,

---              lite_w="LITE5", step_w="STEP1",
---              frame_f="FLAT1", frame_c="TLITE6_6",
               }
             },
  
 d_wood   = { wall="DOORWOOD", w=64,  h=128, ceil="FLOOR10" },
---  d_wood   = { wall="DOORWOOD", w=64,  h=128 },
---  d_wood = { prefab="DOOR", w=64, h=128,

---               skin =
---               {
---                 door_w="DOORWOOD", door_c="FLOOR10",
---                 track_w="METL2",
---                 door_h=128,

---              lite_w="LITE5", step_w="STEP1",
---              frame_f="FLAT1", frame_c="TLITE6_6",
---               }
---             },
  
--  d_stone  = { wall="DOORSTON", w=64,  h=128 },
}

HC_KEY_DOORS =
{
  k_blue =
  {
    w=128, h=128,

    prefab = "DOOR", -- DOOR_LOCKED

    skin =
    {
      door_w="DOORSTON", door_c="FLOOR28",
      track_w="METL2",
      frame_f="FLOOR04",
      door_h=128, 
      door_kind=32, tag=0,  -- kind_rep=26
    },

    thing = "blue_statue",
  },

  k_green =
  {
    w=128, h=128,

    prefab = "DOOR", -- DOOR_LOCKED

    skin =
    {
      door_w="DOORSTON", door_c="FLOOR28",
      track_w="METL2",
      frame_f="FLOOR04",
      door_h=128, 
      door_kind=33, tag=0, -- kind_rep=28,
    },

    thing = "green_statue",
  },

  k_yellow =
  {
    w=128, h=128,

    prefab = "DOOR", -- DOOR_LOCKED

    skin =
    {
      door_w="DOORSTON", door_c="FLOOR28",
      track_w="METL2",
      frame_f="FLOOR04",
      door_h=128, 
      door_kind=34, tag=0, -- kind_rep=27,
    },

    thing = "yellow_statue",
  },
}

HC_LIFTS =
{
  slow = { kind=62,  walk=88 },
}

HC_DOOR_PREFABS =
{
  d_wood =
  {
    w=128, h=128, prefab="DOOR",

    skin =
    {
      door_w="DOORWOOD", door_c="FLOOR10",
      track_w="METL2",
      frame_f="FLOOR04",
      door_h=128,
      door_kind=1, tag=0,
    },

  theme_probs = { CITY=20 },
  },
}

HC_WALL_PREFABS =
{
  
wall_pic_GLASS1 =
  {
    prefab = "WALL_PIC_SHALLOW",
    min_height = 160,
    skin = { pic_w="STNGLS1", pic_h=128 },
  },

wall_pic_GLASS2 =
  {
    prefab = "WALL_PIC_SHALLOW",
    min_height = 160,
    skin = { pic_w="STNGLS2", pic_h=128 },
  },

wall_pic_SKULL1 =
  {
    prefab = "WALL_PIC_SHALLOW",
    --min_height = 160,
    skin = { pic_w="GRSKULL3", pic_h=88 },
  },

wall_pic_BANNER1 =
  {
    prefab = "WALL_PIC_NARROW",
    min_height = 160,
    skin = { pic_w="BANNER1", pic_h=128 },
  },

wall_pic_BANNER2 =
  {
    prefab = "WALL_PIC_NARROW",
    min_height = 160,
    skin = { pic_w="BANNER2", pic_h=128 },
  },

wall_pic_BANNER3 =
  {
    prefab = "WALL_PIC_NARROW",
    min_height = 160,
    skin = { pic_w="BANNER3", pic_h=128 },
  },

wall_pic_BANNER4 =
  {
    prefab = "WALL_PIC_NARROW",
    min_height = 160,
    skin = { pic_w="BANNER4", pic_h=128 },
  },
  
wall_pic_BANNER5 =
  {
    prefab = "WALL_PIC_NARROW",
    min_height = 160,
    skin = { pic_w="BANNER5", pic_h=128 },
  },

wall_pic_BANNER6 =
  {
    prefab = "WALL_PIC_NARROW",
    min_height = 160,
    skin = { pic_w="BANNER6", pic_h=128 },
  },

wall_pic_BANNER7 =
  {
    prefab = "WALL_PIC_NARROW",
    min_height = 160,
    skin = { pic_w="BANNER7", pic_h=128 },
  },

wall_pic_BANNER8 =
  {
    prefab = "WALL_PIC_NARROW",
    min_height = 160,
    skin = { pic_w="BANNER8", pic_h=128 },
  },




--secret_enclosure_1 =
--  {
--     prefab = "ENCLOSURE_SECRET1",

--    skin = { track_x="GRSKULL1", track_w="METL2", --door_h=128,
--             door_kind=109, tag=0, kind=109,
--		 pickup = "arrows", x_offset = 0 
--		},             
--   --prob = 3,
--  },







-- This is the small Obhack Level Maker Marble wall watermark
  obhack_small =
  {
    prefab = "WALL_PIC_NARROW",    
    skin = { pic_w="CHAINSD", pic_h=64}, 
        
  },

-- This is the small Obhack Level Maker Pic wall watermark
  obhack_small_2 =
  {
    prefab = "WALL_PIC_NARROW_OBHACK",    
    skin = { pic_w="CHAINSD", pic_h=64},
         
  },
}

HC_MISC_PREFABS =
{
  pedestal_PLAYER =
  {
    prefab = "PEDESTAL",
    skin = { wall="TMBSTON2", floor="FLOOR26", ped_h=8 },
  },

  pedestal_ITEM =
  {
    prefab = "PEDESTAL",
    skin = { wall="SAINT1", floor="FLAT500", ped_h=12 },
  },

  pedestal_BOSS =
  {
    prefab = "PEDESTAL_BIG",
    --add_mode = "island",
    skin = { ped_h=0 },
  },

  image_1 =
  {
    prefab = "CRATE",
    add_mode = "island",
    skin = { crate_h=64, crate_w="CHAINSD", crate_f="FLOOR27" },
  },

  image_2 =
  {
    prefab = "WALL_PIC_SHALLOW",
    add_mode = "wall",
    min_height = 144,
    skin = { pic_w="GRSKULL2", pic_h=128 },
  },

  exit_DOOR =
  {
    w=64, h=96, prefab = "DOOR_NARROW",

    skin =
    {
      door_w="DOOREXIT",
      door_h=96,
      door_kind=1, tag=0,
    },
  },

  secret_DOOR =
  {
    w=128, h=128, prefab = "DOOR_SECRET",

    skin =
    {
      track_x="GRSKULL1", track_w="METL2",
      door_h=128, door_kind=31, tag=0
    },
  },

secret_DOOR_WIDE =
  {
    w=128, h=128, prefab = "DOOR_SECRET_WIDE",

    skin = { 
		 track_x="GRSKULL1", track_w="METL2", door_h=128,
             door_kind=31, tag=0,
           }
  },


}

HC_DEATHMATCH_EXITS =
{
  exit_dm_METAL =
  {
    prefab = "EXIT_DEATHMATCH",

    skin = { wall="METL2", front_w="METL2",
             floor="FLAT502", ceil="FLAT502",
             switch_w="SW2OFF", side_w="METL2", switch_f="FLOOR03",
             frame_f="FLAT504", frame_c="FLAT504", -- step_w="STEP1",
             door_w="DOOREXIT", door_c="FLOOR08", -- track_w="DOORTRAK",

             inside_h=128, door_h=96,
             switch_yo=32,
             door_kind=1, tag=0, switch_kind=11
           },
  },
}

HC_RAILS =
{
  r_1 = { wall="WDGAT64", w=128, h=64  },
  r_2 = { wall="WDGAT64", w=128, h=128 },  -- FIXME!!
}

HC_IMAGES =
{
  { wall = "GRSKULL2", w=128, h=128, glow=true },
  { wall = "GRSKULL1", w=64,  h=64,  floor="FLOOR27" }
}

HC_LIGHTS =
{
  round = { floor="FLOOR26",  side="ORNGRAY" },
}

HC_WALL_LIGHTS =
{
  redwall = { wall="REDWALL", w=32 },
}

HC_PICS =
{
  skull3 = { wall="GRSKULL3", w=128, h=128 },
  glass1 = { wall="STNGLS1",  w=128, h=128 },
banner5 = { wall="BANNER5",  w=128, h=128 },

}

---- QUEST STUFF ----------------

HC_QUESTS =
{
  key =
  {
    k_blue=30, k_green=45, k_yellow=60
  },

  key2 =
  {
    k_blue=30, k_green=45, k_yellow=60
  },

  switch =
  {
    sw_demon=60, sw_green=45, sw_celtic=30,
  },

  -- No firemace because it sometimes doesn't appear in the map;
  -- we just have more tomes of power
  weapon =
  {
    claw=60, hellstaff=40,
    phoenix=40, tome=20
  },

  item =
  {
    shadow=60, bag=50, wings=40, ovum=30,
    bomb=25, tome=20, chaos=15,
  },
}

HC_ROOMS =
{
  PLAIN =
  {
  },

  HALLWAY =
  {
    room_heights = { [96]=50, [128]=50 },
    door_probs   = { out_diff=75, combo_diff=50, normal=5 },
    window_probs = { out_diff=1, combo_diff=1, normal=1 },
    space_range  = { 20, 65 },
  },
 
  SCENIC =
  {
  },

  -- TODO: check in-game level names for ideas
}

HC_THEMES =
{
  --- City (E1 Castle) is both indoors and outdoors
  CITY =
  {
    room_probs=
    {
      PLAIN=50,
    },
    has_outdoors = true,
  },
  --- Cave (used in Hell) is both outdoors and indoors
  CAVE =
  {
    room_probs=
    {
      PLAIN=50,
    },
    has_outdoors = true,
  },
  --- Dome is a variation on City used in E3
  DOME =
  {
    room_probs=
    {
      PLAIN=50,
    },
    has_outdoors = true,
  },
  --- Egypt is a sandy-looking theme used in E4
  EGYPT =
  {
    room_probs=
    {
      PLAIN=50,
    },
    has_outdoors = true,
  },
  --- Garish is a surrealistic very garish theme of blue and some red;
  --- used in E5
  GARISH =
  {
    room_probs=
    {
      PLAIN=50,
    },
    has_outdoors = true,
  },

}

HC_QUEST_LEN_PROBS =
{
  ----------  2   3   4   5   6   7   8  9  10  -------

  key    = {  0, 25, 50, 90, 65, 30, 10, 2 },
  exit   = {  0, 25, 50, 90, 65, 30, 10, 2 },

  switch = {  0, 50, 90, 50, 25,  5,  1 },

  weapon = { 25, 90, 50, 10,  2 },
  item   = { 15, 70, 70, 15,  2 },
}

HC_QUEST_LEN_PROBS_SHORT =
{
  ----------  2   3   4   5   -------

  key    = {  65, 70, 45, 10 },
  exit   = {  65, 70, 45, 10 },

  switch = {  70, 60, 25, 10 },

  weapon = {  35, 60, 40, 5 },
  item   = {  35, 60, 50, 5 },
}

HC_QUEST_LEN_PROBS_LONG =
{
  ----------  2   3   4   5   6   7   8   9  10   -------

  key    = {  0,  0,  0, 10, 25, 45, 60, 30,  5 },
  exit   = {  0,  0,  0, 10, 25, 45, 60, 25,  5 },
  
  switch = {  0,  0, 10, 20, 55, 65, 10},   

  weapon = {  0,  0,  0, 10, 25, 50, 60, 30,  5 },
  item   = {  0,  0,  0, 10, 15, 50, 60, 25,  5 },
}

------------------------------------------------------------

HC_MONSTERS =
{
  -- FIXME: dm and fp values are CRAP!
  gargoyle    = { prob=30, hp=20,  dm= 7, fp=1.0, cage_fallback=10, float=true, melee=true, wuss=30 },
  fire_garg   = { prob=20, hp=80,  dm=21, fp=2.0, float=true, wuss=20 },
  golem       = { prob=60, hp=80,  dm= 7, fp=1.1, melee=true, wuss=60 },
  golem_inv   = { prob=20, hp=80,  dm= 7, fp=2.1, melee=true, wuss=20 },

  nitro       = { prob=70, hp=100, dm=21, fp=2.5, },
  nitro_inv   = { prob=10, hp=100, dm=21, fp=2.7, },
  warrior     = { prob=70, hp=200, dm=15, fp=2.5, },
  warrior_inv = { prob=20, hp=200, dm=15, fp=2.7, },

  disciple    = { prob=25, hp=180, dm=30, fp=3.0, float=true, wuss=-25 },
  sabreclaw   = { prob=25, hp=150, dm=30, fp=2.3, melee=true, wuss=15 },
  weredragon  = { prob=20, hp=220, dm=50, fp=3.0, },
  ophidian    = { prob=20, hp=280, dm=50, fp=3.0, wuss=-20},  
  ironlich    = { prob=15, hp=700, dm=99, fp=3.0, boss=true, wuss=-25 },  
  maulotaur   = { prob=10, hp=800, dm=99, fp=3.0, boss=true, wuss=-50 },
  --d_sparil    = { prob=5,  hp=1000,dm=99, fp=3.0, boss=true, wuss=-40 },

  pod = { prob=5, hp=45, dm=2, fp=1.0, melee=true, passive=true },
}

HC_BOSSES =
{
  ironlich    = { prob= 4, hp=700,  r=80, dm=99, fp=3.0, float=true },
  maulotaur   = { prob= 1, hp=3000, r=28, dm=99, fp=3.0, },
  d_sparil    = { prob= 1, hp=2000, r=28, dm=99, fp=3.0, },
}

HC_WEAPONS =
{
  -- FIXME: all these stats are CRAP!
  staff      = { fp=0, melee=true, rate=3.0, dm=10, freq= 2, held=true },
  gauntlets  = { fp=1, melee=true, rate=6.0, dm=50, freq= 8 },

  wand       = { fp=1, ammo="crystal",           per=1, rate=1.1, dm=10, freq=15, held=true },
  crossbow   = { fp=2, ammo="arrow",     give=4, per=1, rate=1.1, dm=30, freq=90 },
  claw       = { fp=2, ammo="claw_orb",  give=4, per=1, rate=1.1, dm=50, freq=50 },

  hellstaff  = { fp=3, ammo="runes",     give=4, per=1, rate=1.1, dm=60, freq=50 },
  phoenix    = { fp=3, ammo="flame_orb", give=4, per=1, rate=1.1, dm=70, freq=50 },
  firemace   = { fp=4, ammo="mace_orb",  give=4, per=1, rate=1.1, dm=90, freq=25 },
}

HC_PICKUPS =
{
  -- FIXME: the ammo 'give' numbers are CRAP!
  crystal = { stat="crystal", give=5,  },
  geode   = { stat="crystal", give=20, },
  arrows  = { stat="arrow",   give=5,  },
  quiver  = { stat="arrow",   give=20, },

  claw_orb1 = { stat="claw_orb", give=5,  },
  claw_orb2 = { stat="claw_orb", give=20, },
  runes1    = { stat="runes",    give=5,  },
  runes2    = { stat="runes",    give=20, },

  flame_orb1 = { stat="flame_orb", give=5,  },
  flame_orb2 = { stat="flame_orb", give=20, },
  mace_orbs  = { stat="mace_orb",  give=5,  },
  mace_pile  = { stat="mace_orb",  give=20, },

  h_vial  = { stat="health", give=10,  prob=70 },
  h_flask = { stat="health", give=25,  prob=25 },
  h_urn   = { stat="health", give=100, prob=5, clu_max=1 },

  shield1 = { stat="armor", give=100, prob=70 },
  shield2 = { stat="armor", give=200, prob=10 },
}

HC_NICENESS =
{
  w1 = { weapon="crossbow",  quest=1, prob=70, always=true  },

  w3 = { weapon="gauntlets", quest=1, prob=33, always=false },
  w4 = { weapon="gauntlets", quest=3, prob=50, always=false },

  a1 = { pickup="shield1", prob=2.0 },
  a2 = { pickup="shield2", prob=0.7 },

  p1 = { pickup="torch",   prob=2.0 },
}

HC_DEATHMATCH =
{
  weapons =
  {
    gauntlets=10, crossbow=60,
    claw=30, hellstaff=30, phoenix=30
  },

  health =
  { 
    h_vial=70, h_flask=25, h_urn=5
  },

  ammo =
  { 
    crystal=10, geode=20,
    arrows=20, quiver=60,
    claw_orb1=10, claw_orb2=40,
    runes1=10, runes2=30,
    flame_orb1=10, flame_orb2=30,
  },

  items =
  {
    shield1=70, shield2=10,
    bag=10, torch=10,
    wings=50, ovum=50,
    bomb=30, chaos=30,
    shadow=50, tome=30,
  },

  cluster = {}
}

HC_INITIAL_MODEL =
{
  cleric =
  {
    health=100, armor=0,
    crystal=30, arrow=0, runes=0,
    claw_orb=0, flame_orb=0, mace_orb=0,
    staff=true, wand=true,
  }
}


------------------------------------------------------------

HC_EPISODE_THEMES =
{
  { CITY=5 },
  { CAVE=5 },
  { DOME=5 },

  { EGYPT=5 },
  { GARISH=5, CAVE = 5, CITY = 5, EGYPT = 5, DOME = 5 },
  { CITY=5, EGYPT=5 },
}

HC_SECRET_EXITS =
{
  E1M6 = true,
  E2M4 = true,
  E3M4 = true,
  E4M4 = true,
  E5M3 = true,
  E6M8 = true,
}

HC_EPISODE_BOSSES =
{
  "ironlich",
  "maulotaur",
  "d_sparil",

  "ironlich",
  "maulotaur",
  "d_sparil",
}

HC_EPISODE_BOSSES_INSANE =
{
  "d_sparil", 
  "d_sparil", 
  "d_sparil",

  "d_sparil",
  "d_sparil",
  "d_sparil",
}

HC_SKY_INFO =
{
  { color="gray",  light=176 },
  { color="red",   light=192 },
  { color="blue",  light=176 },

  { color="gray",  light=176 },
  { color="blue",  light=176 },
  { color="gray",  light=176 },
}

function heretic_get_levels(episode)

  local level_list = {}

  local theme_probs = HC_EPISODE_THEMES[episode]
  -- If we only make a single map or episode, use the castle or hell theme
  if SETTINGS.length ~= "full" then
    theme_probs = HC_EPISODE_THEMES[rand_irange(1,4)]
  end

  -- Here's the deal with Heretic and episode 6.  Back when Heretic came
  -- out, Raven added three secret maps to Heretic: E6M1, E6M2, and E6M3.
  -- These maps could only be accessed by the "warp" command line option,
  -- or the "engage61" (or 62 or 63) cheat code.  
  -- E6M3, which was a Heretic conversion of a deathmatch level by
  -- American McGee, was a level without an exit. 
  -- The original DOS Heretic also has songs defined and what not for
  -- E6M4, etc., but no actual maps.
  -- If you play E6M4, etc. in DOS Heretic, it will eventually crash.
  -- However, Deng (Doomsday) 1.8.6 can handle having 10 (yes, 10) levels
  -- in E6.  Basically, the normal exit in E6M8 does nothing, the secret
  -- exit in E6M8 takes you to E6M9, the exit in E6M9 takes you to E6M0 (!!),
  -- and the exit in E6M0 takes you to E6M1.  So, it's a big 10-level loop.
  -- If dos_heretic has a value of 1, we only make E6M1, E6M2, and E6M3, 
  -- and E6M3 has no exit.  Otherwise, we make all 10 E6 levels and have
  -- a secret exit in E6M9

  local maps_in_episode = 9
  local low_map = 1
  local dos_heretic = 0

  if episode == 6 then 
        if dos_heretic == 1 then
		maps_in_episode = 3 
        else
        	low_map = 0
	end
  end

  for map = low_map,maps_in_episode do
    local Level =
    {
      name = string.format("E%dM%d", episode, map),

      episode   = episode,
      ep_along  = map,
      ep_length = maps_in_episode,

      theme_probs = theme_probs,
      sky_info = HC_SKY_INFO[episode],

      boss_kind   = (map == 8) and HC_EPISODE_BOSSES[episode],
      boss_kind_insane   = (map == 8) and HC_EPISODE_BOSSES_INSANE[episode],
	secret_kind = (map == 9) and "plain",

      toughness_factor = sel(map==9, 1.2, 1 + (map-1) / 7),
    }

    if episode == 6 and map == 3 and dos_heretic == 1 then
      Level.no_exit = true
    end

    if HC_SECRET_EXITS[Level.name] then
      Level.secret_exit = true
    end

    if SETTINGS.questlength == "long" then
    	   std_decide_quests(Level, HC_QUESTS, HC_QUEST_LEN_PROBS_LONG)
    elseif SETTINGS.questlength == "short" then
	   std_decide_quests(Level, HC_QUESTS, HC_QUEST_LEN_PROBS_SHORT)
    else
   	   std_decide_quests(Level, HC_QUESTS, HC_QUEST_LEN_PROBS)
    end

    table.insert(level_list, Level)
  end

  return level_list
end

------------------------------------------------------------

GAME_FACTORIES["heretic"] = function()

  return
  {
    doom_format = true,
    noblaze_door = true,

    plan_size = 10,
    cell_size = 9,
    cell_min_size = 6,

    caps = { heights=true, sky=true, 
             fragments=true, move_frag=true, rails=true,
             closets=true,   depots=true,
             switches=true,  liquids=true,
             teleporters=true,
             prefer_stairs=true,
           },

    SKY_TEX    = "F_SKY1",
    ERROR_TEX  = "DRIPWALL",
    ERROR_FLAT = "FLOOR09",

    episodes   = 6,
    level_func = heretic_get_levels,

    classes  = { "cleric" },

    things     = HC_THINGS,
    monsters   = HC_MONSTERS,
    bosses     = HC_BOSSES,
    weapons    = HC_WEAPONS,

    pickups = HC_PICKUPS,
    pickup_stats = { "health", "crystal", "arrow", "claw_orb",
                     "runes", "flame_orb", "mace_orb" },
    niceness = HC_NICENESS,

    initial_model = HC_INITIAL_MODEL,

    quests  = HC_QUESTS,

    dm = HC_DEATHMATCH,
    dm_exits = HC_DEATHMATCH_EXITS,

    combos    = HC_COMBOS,
    exits     = HC_EXITS,
    hallways  = HC_HALLWAYS,

    rooms     = HC_ROOMS,
    themes    = HC_THEMES,

    hangs     = HC_OVERHANGS,
    pedestals = HC_PEDESTALS,
    mats      = HC_MATS,
    rails     = HC_RAILS,

    liquids   = HC_LIQUIDS,
    switches  = HC_SWITCHES,
    doors     = HC_DOORS,
    key_doors = HC_KEY_DOORS,
    lifts     = HC_LIFTS,

    pics      = HC_PICS,
    images    = HC_IMAGES,
    lights    = HC_LIGHTS,
    wall_lights = HC_WALL_LIGHTS,

    door_fabs   = HC_DOOR_PREFABS,
    wall_fabs   = HC_WALL_PREFABS,
    misc_fabs   = HC_MISC_PREFABS,

    toughness_factor = 0.80,

    depot_info  = { teleport_kind=97 },

    room_heights = { [96]=5, [128]=25, [192]=70, [256]=70, [320]=12 },
    space_range  = { 20, 90 },
    
    diff_probs = { [0]=20, [16]=40, [32]=80, [64]=30, [96]=5 },
    bump_probs = { [0]=30, [16]=30, [32]=20, [64]=5 },
    
    door_probs   = { out_diff=75, combo_diff=50, normal=15 },
    
    hallway_probs = { 20, 30, 41, 53, 66 },
    hallway_probs2 = { 8, 14, 18, 25, 33 },
    hallway_probs3 = { 0,  0,  0,  0,  0 },

    window_probs = { out_diff=80, combo_diff=50, normal=30 },
  }
end

