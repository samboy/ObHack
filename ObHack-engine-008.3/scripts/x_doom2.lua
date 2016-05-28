----------------------------------------------------------------
-- GAME DEF : Doom II
----------------------------------------------------------------
--
--  Oblige Level Maker (C) 2006,2007 Andrew Apted
--  Changes copyright 2007-2016 Sam Trenholme and Fritz
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

DM_THINGS =
{
  --- PLAYERS ---

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


  --- MONSTERS ---

  zombie    = { id=3004,kind="monster", r=20,h=56 },
  shooter   = { id=9,   kind="monster", r=20,h=56 },
  gunner    = { id=65,  kind="monster", r=20,h=56 },
  imp       = { id=3001,kind="monster", r=20,h=56 },

  caco      = { id=3005,kind="monster", r=31,h=56 },
  revenant  = { id=66,  kind="monster", r=20,h=64 },
  knight    = { id=69,  kind="monster", r=24,h=64 },
  baron     = { id=3003,kind="monster", r=24,h=64 },

  mancubus  = { id=67,  kind="monster", r=96,h=64 },
  arach     = { id=68,  kind="monster", r=128,h=64 },
  pain      = { id=71,  kind="monster", r=31,h=56 },
  vile      = { id=64,  kind="monster", r=20,h=56 }, --is truely 64
  demon     = { id=3002,kind="monster", r=30,h=56 },
  spectre   = { id=58,  kind="monster", r=30,h=56 },
  skull     = { id=3006,kind="monster", r=16,h=56 },

  spider    = { id=7,  kind="monster", r=256,h=100 },
  cyber     = { id=16, kind="monster", r=80, h=110 }, 
  ss_dude   = { id=84, kind="monster", r=20, h=56 },
  keen      = { id=72, kind="monster", r=16, h=72, ceil=true },

  --- PICKUPS ---
  
  k_red     = { id=38, kind="pickup", r=20,h=16, pass=true },
  k_yellow  = { id=39, kind="pickup", r=20,h=16, pass=true },
  k_blue    = { id=40, kind="pickup", r=20,h=16, pass=true },

  kc_blue   = { id=5,  kind="pickup", r=20,h=16, pass=true },
  kc_yellow = { id=6,  kind="pickup", r=20,h=16, pass=true },
  kc_red    = { id=13, kind="pickup", r=20,h=16, pass=true },

  shotty = { id=2001, kind="pickup", r=20,h=16, pass=true },
  super  = { id=  82, kind="pickup", r=20,h=16, pass=true },
  chain  = { id=2002, kind="pickup", r=20,h=16, pass=true },
  launch = { id=2003, kind="pickup", r=20,h=16, pass=true },
  plasma = { id=2004, kind="pickup", r=20,h=16, pass=true },
  saw    = { id=2005, kind="pickup", r=20,h=16, pass=true },
  bfg    = { id=2006, kind="pickup", r=20,h=16, pass=true },

  backpack = { id=   8, kind="pickup", r=20,h=16, pass=true },
  mega     = { id=  83, kind="pickup", r=20,h=16, pass=true },
  invul    = { id=2022, kind="pickup", r=20,h=16, pass=true },
  berserk  = { id=2023, kind="pickup", r=20,h=16, pass=true },
  invis    = { id=2024, kind="pickup", r=20,h=16, pass=true },
  suit     = { id=2025, kind="pickup", r=20,h=60, pass=true },
  map      = { id=2026, kind="pickup", r=20,h=16, pass=true },
  goggle   = { id=2045, kind="pickup", r=20,h=16, pass=true },

  potion   = { id=2014, kind="pickup", r=20,h=16, pass=true },
  stimpack = { id=2011, kind="pickup", r=20,h=16, pass=true },
  medikit  = { id=2012, kind="pickup", r=20,h=16, pass=true },
  soul     = { id=2013, kind="pickup", r=20,h=16, pass=true },

  helmet      = { id=2015, kind="pickup", r=20,h=16, pass=true },
  green_armor = { id=2018, kind="pickup", r=20,h=16, pass=true },
  blue_armor  = { id=2019, kind="pickup", r=20,h=16, pass=true },

  bullets    = { id=2007, kind="pickup", r=20,h=16, pass=true },
  bullet_box = { id=2048, kind="pickup", r=20,h=16, pass=true },
  shells     = { id=2008, kind="pickup", r=20,h=16, pass=true },
  shell_box  = { id=2049, kind="pickup", r=20,h=16, pass=true },
  rockets    = { id=2010, kind="pickup", r=20,h=16, pass=true },
  rocket_box = { id=2046, kind="pickup", r=20,h=16, pass=true },
  cells      = { id=2047, kind="pickup", r=20,h=16, pass=true },
  cell_pack  = { id=  17, kind="pickup", r=20,h=16, pass=true },

  --- SETTINGS.iweapon (Start weapon) starting weapons
  iw_basic = { id=2001, kind="pickup", r=20,h=16, pass=true }, -- Shotgun
  iw_hardcore = { id=2003, kind="pickup", r=20,h=16, pass=true }, -- RL
  iw_hardcore2 = { id=2002, kind="pickup", r=20,h=16, pass=true }, -- Chaingun
  


  --- SCENERY ---

  -- lights --
  lamp         = { id=2028,kind="scenery", r=16,h=48, light=255, },
  mercury_lamp = { id=85,  kind="scenery", r=16,h=80, light=255, },
  short_lamp   = { id=86,  kind="scenery", r=16,h=60, light=255, },
  tech_column  = { id=48,  kind="scenery", r=16,h=128,light=255, },

  candle         = { id=34, kind="scenery", r=16,h=16, light=111, pass=true },
  candelabra     = { id=35, kind="scenery", r=16,h=56, light=255, },
  burning_barrel = { id=70, kind="scenery", r=16,h=44, light=255, },

  blue_torch     = { id=44, kind="scenery", r=16,h=96, light=255, },
  blue_torch_sm  = { id=55, kind="scenery", r=16,h=72, light=255, },
  green_torch    = { id=45, kind="scenery", r=16,h=96, light=255, },
  green_torch_sm = { id=56, kind="scenery", r=16,h=72, light=255, },
  red_torch      = { id=46, kind="scenery", r=16,h=96, light=255, },
  red_torch_sm   = { id=57, kind="scenery", r=16,h=72, light=255, },

  -- decoration --
  barrel = { id=2035, kind="scenery", r=12, h=44 },

  green_pillar     = { id=30, kind="scenery", r=16,h=56, },
  green_column     = { id=31, kind="scenery", r=16,h=40, },
  green_column_hrt = { id=36, kind="scenery", r=16,h=56, add_mode="island" },

  red_pillar     = { id=32, kind="scenery", r=16,h=52, },
  red_column     = { id=33, kind="scenery", r=16,h=56, },
  red_column_skl = { id=37, kind="scenery", r=16,h=56, add_mode="island" },

  burnt_tree = { id=43, kind="scenery", r=16,h=56, add_mode="island" },
  brown_stub = { id=47, kind="scenery", r=16,h=56, add_mode="island" },
  big_tree   = { id=54, kind="scenery", r=31,h=120,add_mode="island" },

  -- gore --
  evil_eye    = { id=41, kind="scenery", r=16,h=56, add_mode="island" },
  skull_rock  = { id=42, kind="scenery", r=16,h=48, },
  skull_pole  = { id=27, kind="scenery", r=16,h=52, },
  skull_kebab = { id=28, kind="scenery", r=20,h=64, },
  skull_cairn = { id=29, kind="scenery", r=20,h=40, add_mode="island" },

  impaled_human  = { id=25,kind="scenery", r=20,h=64, },
  impaled_twitch = { id=26,kind="scenery", r=16,h=64, },

  gutted_victim1 = { id=73, kind="scenery", r=16,h=88, ceil=true },
  gutted_victim2 = { id=74, kind="scenery", r=16,h=88, ceil=true },
  gutted_torso1  = { id=75, kind="scenery", r=16,h=64, ceil=true },
  gutted_torso2  = { id=76, kind="scenery", r=16,h=64, ceil=true },
  gutted_torso3  = { id=77, kind="scenery", r=16,h=64, ceil=true },
  gutted_torso4  = { id=78, kind="scenery", r=16,h=64, ceil=true },

  hang_arm_pair  = { id=59, kind="scenery", r=20,h=84, ceil=true, pass=true },
  hang_leg_pair  = { id=60, kind="scenery", r=20,h=68, ceil=true, pass=true },
  hang_leg_gone  = { id=61, kind="scenery", r=20,h=52, ceil=true, pass=true },  
  hang_leg       = { id=62, kind="scenery", r=20,h=52, ceil=true, pass=true },
  hang_twitching = { id=63, kind="scenery", r=20,h=68, ceil=true, pass=true },

  gibs          = { id=24, kind="scenery", r=20,h=16, pass=true },
  gibbed_player = { id=10, kind="scenery", r=20,h=16, pass=true },
  pool_blood_1  = { id=79, kind="scenery", r=20,h=16, pass=true },
  pool_blood_2  = { id=80, kind="scenery", r=20,h=16, pass=true },
  pool_brains   = { id=81, kind="scenery", r=20,h=16, pass=true },

  -- Note: id=12 exists, but is exactly the same as id=10

  dead_player  = { id=15, kind="scenery", r=16,h=16, pass=true },
  dead_zombie  = { id=18, kind="scenery", r=16,h=16, pass=true },
  dead_shooter = { id=19, kind="scenery", r=16,h=16, pass=true },
  dead_imp     = { id=20, kind="scenery", r=16,h=16, pass=true },
  dead_demon   = { id=21, kind="scenery", r=16,h=16, pass=true },
  dead_caco    = { id=22, kind="scenery", r=16,h=16, pass=true },
  dead_skull   = { id=23, kind="scenery", r=16,h=16, pass=true },
}


-----==============######################==============-----

D2_COMBOS =
{
  ---- URBAN ------------

  URBAN_PANEL =
  {
    theme_probs = { URBAN=50 },
    mat_pri = 6,

    wall  = "PANEL7",
    floor = "FLAT5_5",
    ceil  = "RROCK09",

    step = "STEP2",
    pillar = "PANBLACK",
    pic_wd = "MARBFAC2",

    scenery = { candelabra=6, evil_eye=2, red_torch=5, blue_torch=5, green_torch=5, dead_player=1, gibbed_player=1, red_torch_sm=3, green_torch_sm=3, blue_torch_sm=3 },

    -- FIXME: 'LIBRARY" room type
    sc_fabs = { bookcase_WIDE=50, bookcase_WIDE_enclosure_drop=60, bookcase_WIDE_enclosure_raise=60, other=20 },

    wall_fabs = { solid_PANEL8=30, solid_PANEL9=30, other=50 },
  },

  URBAN_PANEL2 =
  {
    theme_probs = { URBAN=50 },
    mat_pri = 6,

    wall  = "PANEL6",
    floor = "FLAT5_5",
    ceil  = "RROCK09",

    step = "STEP6",
    pillar = "PANRED",
    pic_wd = "MARBFAC3",

    scenery = { candelabra=6, evil_eye=2, red_torch=5, blue_torch=5, green_torch=5, dead_player=1, gibbed_player=1, red_torch_sm=3, green_torch_sm=3, blue_torch_sm=3 },

    -- FIXME: 'LIBRARY" room type
    sc_fabs = { bookcase_WIDE=50, bookcase_WIDE_enclosure_drop=60, bookcase_WIDE_enclosure_raise=60, pillar_4_Panred=25, other=30 },

    wall_fabs = { solid_PANEL8=30, solid_PANEL9=30, other=50 },
  },

  URBAN_PANEL3 =
  {
    theme_probs = { URBAN=50 },
    mat_pri = 6,

    wall  = "PANCASE2",
    floor = "FLAT5_5",
    ceil  = "RROCK09",

    step = "STEP2",
    pillar = "PANBLUE",
    pic_wd = "MARBFAC2",

    scenery = { candelabra=6, evil_eye=2, red_torch=5, blue_torch=5, green_torch=5, dead_player=1, gibbed_player=1, red_torch_sm=3, green_torch_sm=3, blue_torch_sm=3 },

    -- FIXME: 'LIBRARY" room type
    sc_fabs = { bookcase_WIDE=30, bookcase_WIDE_enclosure_drop=60, bookcase_WIDE_enclosure_raise=60, other=40 },

  },

  URBAN_PANEL4 =
  {
    theme_probs = { URBAN=40 },
    mat_pri = 6,

    wall  = "PANEL7",
    floor = "FLOOR5_1",
    ceil  = "RROCK09",

    step = "STEP4",
    pillar = "PANBLUE",
    pic_wd = "MARBFACE",

    scenery = { candelabra=6, evil_eye=2, red_torch=5, blue_torch=5, green_torch=5, dead_player=1, gibbed_player=1, red_torch_sm=3, green_torch_sm=3, blue_torch_sm=3 },

    -- FIXME: 'LIBRARY" room type
    sc_fabs = { bookcase_WIDE=50, bookcase_WIDE_enclosure_drop=30, bookcase_WIDE_enclosure_raise=60, other=50 },

    wall_fabs = { solid_PANEL8=30, solid_PANEL9=30, other=50 },
  },

  URBAN_BRICK =
  {
    theme_probs = { URBAN=30 },
    mat_pri = 6,

    wall  = "BRICK7",
    floor = "FLOOR0_1",
    ceil  = "FLOOR5_4",

    step = "STEP2",
    pillar = "BRICKLIT",
    pic_wd = "BRWINDOW",

    scenery = { red_torch=5, red_torch_sm=3, green_torch=5, green_torch_sm=3, blue_torch=5, blue_torch_sm=3, dead_player=2, gibbed_player=1, gibs=1 },
    bad_liquid = "slime",
  },

  URBAN_BRICK2 =
  {
    theme_probs = { URBAN=20 },
    mat_pri = 6,

    wall = "BIGBRIK2",
    void = "BIGBRIK3",
    step = "STEP4",
    pillar = "BIGBRIK1",

    floor = "FLOOR0_3",
    ceil = "FLAT5_4",

    scenery = { red_torch=5, red_torch_sm=3, green_torch=5, green_torch_sm=3, blue_torch=5, blue_torch_sm=3, dead_player=2, gibbed_player=1, gibs=1 },
  },

  URBAN_BRICK3 =
  {
    theme_probs = { URBAN=30 },
    mat_pri = 6,

    wall  = "BRICK8",
    floor = "FLOOR0_1",
    ceil  = "FLOOR5_4",

    step = "STEP2",
    pillar = "BRICKLIT",
    pic_wd = "MARBFAC3",

    scenery = { red_torch=5, red_torch_sm=3, green_torch=5, green_torch_sm=3, blue_torch=5, blue_torch_sm=3, dead_player=2, gibbed_player=1, gibs=1 },
    bad_liquid = "slime",
  },

  URBAN_BRICK4 =
  {
    theme_probs = { URBAN=20 },
    mat_pri = 6,

    wall = "BIGBRIK1",
    void = "BIGBRIK1",
    step = "STEP6",
    pillar = "BIGBRIK1",

    floor = "FLOOR5_4",
    ceil = "FLAT1_1",

    scenery = { red_torch=5, red_torch_sm=3, green_torch=5, green_torch_sm=3, blue_torch=5, blue_torch_sm=3, dead_player=2, gibbed_player=1, gibs=1 },
  },

  URBAN_BRICK5 =
  {
    theme_probs = { URBAN=30 },
    mat_pri = 6,

    wall  = "BRICK9",
    floor = "FLOOR0_1",
    ceil  = "FLOOR5_4",

    step = "STEP2",
    pillar = "BRICKLIT",
    pic_wd = "MARBFAC2",

    scenery = { red_torch=5, red_torch_sm=3, green_torch=5, green_torch_sm=3, blue_torch=5, blue_torch_sm=3, dead_player=2, gibbed_player=1, gibs=1 },
    bad_liquid = "slime",
  },

  URBAN_BRICK6 =
  {
    theme_probs = { URBAN=30 },
    mat_pri = 6,

    wall  = "BRICK2",
    floor = "FLOOR0_2",
    ceil  = "FLOOR5_4",

    step = "STEP6",
    pillar = "BRICKLIT",
    pic_wd = "MARBFACE",

    scenery = { red_torch=5, red_torch_sm=3, green_torch=5, green_torch_sm=3, blue_torch=5, blue_torch_sm=3, dead_player=2, gibbed_player=1, gibs=1 },
    bad_liquid = "slime",
  },

  URBAN_BRICK7 =
  {
    theme_probs = { URBAN=30 },
    mat_pri = 6,

    wall  = "BRICK5",
    floor = "FLOOR5_3",
    ceil  = "RROCK09",

    step = "STEP2",
    pillar = "BRICK1",
    pic_wd = "MARBFACE",

    scenery = { red_torch=5, red_torch_sm=3, green_torch=5, green_torch_sm=3, blue_torch=5, blue_torch_sm=3, dead_player=2, gibbed_player=1, gibs=1 },
    bad_liquid = "slime",
  },

  URBAN_BRICK8 =
  {
    theme_probs = { URBAN=30 },
    mat_pri = 6,

    wall  = "BRICK1",
    floor = "FLAT1_1",
    ceil  = "RROCK10",

    step = "STEP6",
    pillar = "BRICK4",
    pic_wd = "MARBFAC3",

    scenery = { red_torch=5, red_torch_sm=3, green_torch=5, green_torch_sm=3, blue_torch=5, blue_torch_sm=3, dead_player=2, gibbed_player=1, gibs=1 },
    bad_liquid = "slime",
  },

  URBAN_STUCCO =
  {
    theme_probs = { URBAN=30 },
    mat_pri = 2,

    wall  = "STUCCO3",
    floor = "FLAT8",
    ceil  = "CRATOP2",
    step = "STEP2",

    sc_fabs = { pillar_PANBLUE=20, pillar_PANRED=20, pillar_4_Panblue=25, pillar_4_Panred=25, other=70 },
    scenery = { candelabra=5, burning_barrel=4, red_torch=5, red_torch_sm=3, green_torch=5, green_torch_sm=3, blue_torch=5, blue_torch_sm=3, dead_player=2, gibbed_player=1, gibs=1 },

    wall_fabs = { solid_STUCCO2=30, other=60 },
  },

  URBAN_STUCCO2 =
  {
    theme_probs = { URBAN=30 },
    mat_pri = 2,

    wall  = "STUCCO1",
    floor = "FLAT8",
    ceil  = "CRATOP2",
    step = "STEP2",

    scenery = { candelabra=5, burning_barrel=4, red_torch=5, red_torch_sm=3, green_torch=5, green_torch_sm=3, blue_torch=5, blue_torch_sm=3, dead_player=2, gibbed_player=1, gibs=1 },
    sc_fabs = { pillar_PANBLUE=20, pillar_PANRED=20, pillar_4_Panblue=25, pillar_4_Panred=25, other=70 },

    wall_fabs = { solid_STUCCO2=30, other=60 },
  },

--Outside urban themes--

  URBAN_GREENBRK =
  {
    theme_probs = { URBAN=40 },
    outdoor = true,
    mat_pri = 2,

    wall  = "BRICK10",
    floor = "SLIME13",
    ceil  = "SLIME13",

    step  = "BRICK10",  -- BIGBRIK1
    scenery = { red_torch=10, red_torch_sm=5, green_torch=10, green_torch_sm=5, blue_torch=10, blue_torch_sm=5, dead_player=2, gibbed_player=1, gibs=1, impaled_human=1, skull_kebab=1, skull_pole=1 },
  },

  URBAN_REDBRK =
  {
    theme_probs = { URBAN=40 },
    outdoor = true,
    mat_pri = 2,

    wall  = "BRICK11",
    floor = "FLAT5_3",
    ceil  = "FLAT5_3",

    step  = "REDWALL",  -- BIGBRIK1
    scenery = { red_torch=10, red_torch_sm=5, green_torch=10, green_torch_sm=5, blue_torch=10, blue_torch_sm=5, dead_player=2, gibbed_player=1, gibs=1, impaled_human=1, skull_kebab=1, skull_pole=1 },
  },

  URBAN_WHTBRK =
  {
    theme_probs = { URBAN=40 },
    outdoor = true,
    mat_pri = 2,

    wall  = "BRICK12",
    floor = "FLAT19",
    ceil  = "FLAT19",

    step  = "STEP4",
    scenery = { red_torch=10, red_torch_sm=5, green_torch=10, green_torch_sm=5, blue_torch=10, blue_torch_sm=5, dead_player=2, gibbed_player=1, gibs=1, impaled_human=1, skull_kebab=1, skull_pole=1 },
  },

  URBAN_BLACK =
  {
    theme_probs = { URBAN=20 },
    outdoor = true,
    mat_pri = 6,

    wall  = "BLAKWAL1",
    floor = "MFLR8_4",
    ceil  = "CEIL5_1",

    step = "STEP4",

    piller = "MODWALL3",
    pic_wd = "MODWALL2", pic_wd_h = 64,  -- FIXME

    scenery = { blue_torch_sm=3, red_torch_sm=3, green_torch_sm=3, skull_rock=2, brown_stub=3, evil_eye=2, red_torch=10, blue_torch=10, green_torch=10, impaled_human=2, impaled_twitch=2, dead_player=2, gibbed_player=1 },
  },

  URBAN_CEM9 =
  {
    theme_probs = { URBAN=35 },
    outdoor = true,
    mat_pri = 2,

    wall  = "CEMENT9",
    floor = "FLAT19",
    ceil  = "FLAT19",

    step  = "STEP4",
    scenery = { red_torch=10, red_torch_sm=5, green_torch=10, green_torch_sm=5, blue_torch=10, blue_torch_sm=5, dead_player=2, gibbed_player=1, gibs=1, impaled_human=1, skull_kebab=1, skull_pole=1 },
  },


--End outdoor urban themes--

  URBAN_MOD =
  {
    theme_probs = { URBAN=30 },
    mat_pri = 6,

    wall  = "MODWALL1",
    floor = "MFLR8_2",
    ceil  = "CEIL5_1",

    step = "STEP3",
    pillar = "MODWALL2",
    pic_wd = "MARBFACE",

    scenery = { red_torch=10, red_torch_sm=5, green_torch=10, green_torch_sm=5, blue_torch=10, blue_torch_sm=5, dead_player=2, gibbed_player=1, gibs=1, impaled_human=1, skull_kebab=1, skull_pole=1 },
    bad_liquid = "slime",
  },

  URBAN_REDBRKIN =
  {
    theme_probs = { URBAN=30 },
    mat_pri = 2,

    wall  = "BRICK11",
    floor = "FLAT5_4",
    ceil  = "FLAT19",

    step  = "REDWALL",  -- BIGBRIK1
    scenery = { red_torch=10, red_torch_sm=5, green_torch=10, green_torch_sm=5, blue_torch=10, blue_torch_sm=5, dead_player=1, gibbed_player=1, gibs=1, impaled_human=1, skull_kebab=1, skull_pole=1 },
  },

  URBAN_WHTBRKIN =
  {
    theme_probs = { URBAN=30 },
    mat_pri = 2,

    wall  = "BRICK12",
    floor = "FLAT19",
    ceil  = "FLAT5_4",

    step  = "STEP4",
    scenery = { red_torch=10, red_torch_sm=5, green_torch=10, green_torch_sm=5, blue_torch=10, blue_torch_sm=5, dead_player=1, gibbed_player=1, gibs=1, impaled_human=1, skull_kebab=1, skull_pole=1 },
  },

  ---- INDUSTRIAL ------------

  INDY_STONE =
  {
    theme_probs = { INDUSTRIAL=20 },
    mat_pri = 2,

    wall  = "STONE",
    floor = "FLAT5_4",
    ceil  = "FLAT19",

    step  = "STEP4",
    scenery = { lamp=5, mercury_lamp=5, short_lamp=5, dead_player=3, gibbed_player=2, gibs=1 },
  },

  INDY_STONE2 =
  {
    theme_probs = { INDUSTRIAL=20 },
    mat_pri = 2,

    wall  = "STONE2",
    floor = "FLOOR0_3",
    ceil  = "CEIL3_5",

    step  = "STEP4",
    scenery = { lamp=10, mercury_lamp=10, short_lamp=7, dead_player=2, gibbed_player=2, gibs=1 },
  },

  INDY_STONE4 =
  {
    theme_probs = { INDUSTRIAL=20 },
    mat_pri = 2,

    wall  = "STONE4",
    floor = "FLOOR0_3",
    ceil  = "FLAT5_4",

    step  = "STEP4",
    scenery = { lamp=10, mercury_lamp=10, short_lamp=7, dead_player=2, gibbed_player=2, gibs=1 },
  },

  INDY_STONE5 =
  {
    theme_probs = { INDUSTRIAL=20 },
    mat_pri = 2,

    wall  = "STONE6",
    floor = "FLOOR0_1",
    ceil  = "FLAT5_5",

    step  = "STEP2",
    scenery = { lamp=10, mercury_lamp=10, short_lamp=7, dead_player=2, gibbed_player=2, gibs=1 },
  },

  ---- TECH -----------------

  TECH_BLUECARPET =
  {
    theme_probs = { TECH=25 },
    mat_pri = 4,

    wall  = "TEKGREN2",
    floor = "FLAT14",
    ceil  = "RROCK20",

    step = "STEP3",
    pillar = "TEKLITE2",

    pic_wd = "COMPSTA1", pic_wd_h = 64,

    scenery = { lamp=10, mercury_lamp=10, short_lamp=7, dead_player=2, gibbed_player=2, gibs=1 },
    bad_liquid = "nukage",

    sc_fabs = { crate_rotnar_SILVER=30, other=50 },

    wall_fabs = { solid_TEKGREN3=30, solid_TEKGREN4=30, other=30 },
  },

  TECH_TEKGREN1 =
  {
    theme_probs = { TECH=50 },
    mat_pri = 4,

    wall  = "TEKGREN2",
    floor = "FLOOR3_3",
    ceil  = "GRNLITE1",

    step = "STEP6",
    pillar = "TEKLITE2",

    pic_wd = "COMPSTA1", pic_wd_h = 64,

    scenery = { tech_column=5, lamp=10, mercury_lamp=10, short_lamp=7, dead_player=1, gibbed_player=1, gibs=1 },
    bad_liquid = "nukage",

    sc_fabs = { crate_rotnar_SILVER=30, other=50 },

    wall_fabs = { solid_TEKGREN3=30, solid_TEKGREN4=30, other=30 },
  },


  TECH_TEKGREN1B =
  {
    theme_probs = { TECH=50 },
    mat_pri = 4,

    wall  = "TEKGREN2",
    floor = "SLIME15",
    ceil  = "GRNLITE1",

    step = "STEP4",
    pillar = "TEKLITE2",

    pic_wd = "COMPSTA1", pic_wd_h = 64,

    scenery = { tech_column=5, lamp=10, mercury_lamp=10, short_lamp=7, dead_player=1, gibbed_player=1, gibs=1 },
    bad_liquid = "nukage",

    sc_fabs = { crate_rotnar_SILVER=30, other=50 },

    wall_fabs = { solid_TEKGREN3=30, solid_TEKGREN4=30, other=30 },
  },

  TECH_TEKGREN1C =
  {
    theme_probs = { TECH=50 },
    mat_pri = 4,

    wall  = "TEKGREN2",
    floor = "SLIME16",
    ceil  = "RROCK20",

    step = "STEP4",
    pillar = "TEKLITE2",

    pic_wd = "COMPSTA2", pic_wd_h = 64,

    scenery = { tech_column=5, lamp=10, mercury_lamp=10, short_lamp=7, dead_player=1, gibbed_player=1, gibs=1 },
    bad_liquid = "nukage",

    sc_fabs = { crate_rotnar_SILVER=30, other=50 },

    wall_fabs = { solid_TEKGREN3=30, solid_TEKGREN4=30, other=30 },
  },


  TECH_BRONZE =
  {
    theme_probs = { TECH=30 },
    mat_pri = 4,

    wall  = "BRONZE1",
    floor = "SLIME15",
    ceil  = "CEIL5_2",

    step = "STEP4",
    pillar = "TEKLITE2",

    pic_wd = "COMPSTA1", pic_wd_h = 64,

    scenery = { lamp=10, mercury_lamp=10, short_lamp=7, dead_player=1, gibbed_player=1, gibs=1 },
    bad_liquid = "nukage",

    sc_fabs = { crate_rotnar_SILVER=20, other=50 },
  },

  TECH_BRONZE2 =
  {
    theme_probs = { TECH=30 },
    mat_pri = 4,

    wall  = "BRONZE3",
    floor = "SLIME14",
    ceil  = "CEIL5_2",

    step = "STEP4",
    pillar = "TEKLITE2",

    pic_wd = "COMPSTA1", pic_wd_h = 64,

    scenery = { lamp=10, mercury_lamp=10, short_lamp=7, dead_player=1, gibbed_player=1, gibs=1 },
    bad_liquid = "nukage",

    sc_fabs = { crate_rotnar_SILVER=20, other=50 },
  },

  TECH_METAL =
  {
    theme_probs = { TECH=30 },
    mat_pri = 4,

    wall  = "METAL2",
    floor = "SLIME15",
    ceil  = "CEIL5_1",

    step = "STEP4",
    pillar = "TEKLITE2",

    pic_wd = "COMPSTA2", pic_wd_h = 64,

    scenery = { lamp=10, mercury_lamp=10, short_lamp=7, dead_player=1, gibbed_player=1, gibs=1 },
    bad_liquid = "nukage",

    sc_fabs = { crate_rotnar_SILVER=20, other=50 },
  },

  TECH_METAL1 =
  {
    theme_probs = { TECH=30 },
    mat_pri = 4,

    wall  = "METAL1",
    floor = "FLOOR4_8",
    ceil  = "CEIL4_1",

    step = "STEP4",
    pillar = "TEKLITE2",

    pic_wd = "COMPSTA1", pic_wd_h = 64,

    scenery = { tech_column=5, lamp=10, mercury_lamp=10, short_lamp=7, dead_player=1, gibbed_player=1, gibs=1 },
    bad_liquid = "nukage",

    sc_fabs = { crate_rotnar_SILVER=20, other=50 },
  },

  TECH_BVINE =
  {
    theme_probs = { TECH=20 },
    mat_pri = 4,

    wall  = "BROVINE2",
    floor = "FLOOR7_1",
    ceil  = "CEIL5_2",

    step = "STEP6",
    pillar = "TEKLITE2",  -- TODO: doom 1: "COMPUTE1"

    pic_wd = "COMPSTA2", pic_wd_h = 64,

    scenery = { lamp=10, mercury_lamp=10, short_lamp=7, dead_player=1, gibbed_player=1, gibs=1 },
    bad_liquid = "nukage",

    sc_fabs = { crate_rotnar_SILVER=20, other=50 },
  },

  ---- HELL ----------------

  HELL_MARBLE =
  {
    theme_probs = { HELL=70 },
    mat_pri = 6,

    wall  = "MARBLE1",
    floor = "DEM1_6",
    ceil  = "FLOOR7_2",

    lift = "SUPPORT3",
    lift_floor = "CEIL5_2",

    step = "MARBLE1",
    pic_wd  = "SP_DUDE1",

    scenery = { green_pillar=5, green_column=5, green_column_hrt=3, red_torch=10, green_torch=10, blue_torch=10, impaled_human=3, impaled_twitch=3, skull_pole=2, skull_kebab=2, dead_player=2, gibbed_player=1, gibs=1, skull_cairn=2, evil_eye=2, hang_arm_pair=2, hang_leg_pair=2, hang_leg_gone=1, hang_leg=1, gutted_victim1=2, gutted_victim2=2, gutted_torso1=2, gutted_torso2=2, gutted_torso3=2, gutted_torso4=2 },

    bad_liquid = "lava",
    good_liquid = "water",

    sc_fabs = { pillar_MARBFAC4=30, secret_enclosure_4_Marbface=40, other=50 },
  },

  HELL_MARBLE2 =
  {
    theme_probs = { HELL=70 },
    mat_pri = 6,

    wall  = "MARBLE2",
    floor = "DEM1_6",
    ceil  = "FLOOR7_2",

    lift = "SUPPORT3",
    lift_floor = "CEIL5_2",

    step = "MARBLE1",
    pic_wd  = "SP_DUDE1",

    scenery = { green_pillar=5, green_column=5, green_column_hrt=3, red_torch=10, green_torch=10, blue_torch=10, impaled_human=3, impaled_twitch=3, skull_pole=2, skull_kebab=2, dead_player=2, gibbed_player=1, gibs=1, skull_cairn=2, evil_eye=2, hang_arm_pair=2, hang_leg_pair=2, hang_leg_gone=1, hang_leg=1, gutted_victim1=2, gutted_victim2=2, gutted_torso1=2, gutted_torso2=2, gutted_torso3=2, gutted_torso4=2, hang_twitching=2 },

    bad_liquid = "lava",
    good_liquid = "water",

    sc_fabs = { pillar_MARBFAC4=30, secret_enclosure_4_Marbface=40, other=50 },
  },

--  gutted_victim1 = { id=73, kind="scenery", r=16,h=88, ceil=true },
--  gutted_victim2 = { id=74, kind="scenery", r=16,h=88, ceil=true },
--  gutted_torso1  = { id=75, kind="scenery", r=16,h=64, ceil=true },
--  gutted_torso2  = { id=76, kind="scenery", r=16,h=64, ceil=true },
--  gutted_torso3  = { id=77, kind="scenery", r=16,h=64, ceil=true },
--  gutted_torso4  = { id=78, kind="scenery", r=16,h=64, ceil=true },

--  hang_arm_pair  = { id=59, kind="scenery", r=20,h=84, ceil=true, pass=true },
--  hang_leg_pair  = { id=60, kind="scenery", r=20,h=68, ceil=true, pass=true },
--  hang_leg_gone  = { id=61, kind="scenery", r=20,h=52, ceil=true, pass=true },  
--  hang_leg       = { id=62, kind="scenery", r=20,h=52, ceil=true, pass=true },
--  hang_twitching = { id=63, kind="scenery", r=20,h=68, ceil=true, pass=true },

  HELL_MARBLE3 =
  {
    theme_probs = { HELL=70 },
    mat_pri = 6,

    wall  = "MARBLE3",
    floor = "DEM1_6",
    ceil  = "FLOOR7_2",

    lift = "SUPPORT3",
    lift_floor = "CEIL5_2",

    step = "MARBLE1",
    pic_wd  = "SP_DUDE1",

    scenery = { green_pillar=5, green_column=5, green_column_hrt=3, red_torch=10, green_torch=10, blue_torch=10, impaled_human=3, impaled_twitch=3, skull_pole=2, skull_kebab=2, dead_player=2, gibbed_player=1, gibs=1, skull_cairn=2, evil_eye=2, hang_arm_pair=2, hang_leg_pair=2, hang_leg_gone=1, hang_leg=1, gutted_victim1=2, gutted_victim2=2, gutted_torso1=2, gutted_torso2=2, gutted_torso3=2, gutted_torso4=2, hang_twitching=2 },

    bad_liquid = "lava",
    good_liquid = "water",

    sc_fabs = { pillar_MARBFAC4=30, secret_enclosure_4_Marbface=40, other=50 },
  },

  HELL_GRAY =
  {
    theme_probs = { HELL=70 },
    mat_pri = 6,

    wall  = "MARBGRAY",
    floor = "DEM1_6",
    ceil  = "FLOOR7_2",

    lift = "SKSPINE1",
    lift_floor = "FLAT5_6",

    step = "STEP5",
    pic_wd  = "SP_DUDE1",

    scenery = { green_pillar=5, green_column=5, green_column_hrt=3, red_torch=10, green_torch=10, blue_torch=10, impaled_human=3, impaled_twitch=3, skull_pole=2, skull_kebab=2, dead_player=2, gibbed_player=1, gibs=1, skull_cairn=2, evil_eye=2, hang_arm_pair=2, hang_leg_pair=2, hang_leg_gone=1, hang_leg=1, gutted_victim1=2, gutted_victim2=2, gutted_torso1=2, gutted_torso2=2, gutted_torso3=2, gutted_torso4=2, hang_twitching=2 },

    bad_liquid = "lava",
    good_liquid = "blood",

    sc_fabs = { pillar_MARBFAC4=30, secret_enclosure_4_Marbface=40, other=50 },
  },

  HELL_GRAY2 =
  {
    theme_probs = { HELL=70 },
    mat_pri = 6,

    wall  = "MARBGRAY",
    floor = "DEM1_5",
    ceil  = "FLOOR7_2",

    lift = "SUPPORT3",
    lift_floor = "CEIL5_2",

    step = "STEP5",
    pic_wd  = "SP_DUDE1",

    scenery = { green_pillar=5, green_column=5, green_column_hrt=3, red_torch=10, green_torch=10, blue_torch=10, impaled_human=3, impaled_twitch=3, skull_pole=2, skull_kebab=2, dead_player=2, gibbed_player=1, gibs=1, skull_cairn=2, evil_eye=2, hang_arm_pair=2, hang_leg_pair=2, hang_leg_gone=1, hang_leg=1, gutted_victim1=2, gutted_victim2=2, gutted_torso1=2, gutted_torso2=2, gutted_torso3=2, gutted_torso4=2, hang_twitching=2 },

    bad_liquid = "lava",
    good_liquid = "blood",

    sc_fabs = { pillar_MARBFAC4=30, secret_enclosure_4_Marbface=40, other=50 },
  },

  HELL_WODMET =
  {
    theme_probs = { HELL=40 },
    mat_pri = 6,

    wall  = "WOODMET1",
    floor = "FLAT5_1",
    ceil  = "FLAT5_2",

    lift = "SUPPORT3",
    lift_floor = "CEIL5_2",

    step = "WOOD1",
    pic_wd  = "MARBFAC3",

    scenery = { candelabra=5, green_pillar=5, green_column=5, green_column_hrt=3, red_torch=10, green_torch=10, blue_torch=10, impaled_human=3, impaled_twitch=3, skull_pole=2, skull_kebab=2, dead_player=2, gibbed_player=1, gibs=1, skull_cairn=2, evil_eye=2, hang_arm_pair=2, hang_leg_pair=2, hang_leg_gone=1, hang_leg=1, gutted_victim1=2, gutted_victim2=2, gutted_torso1=2, gutted_torso2=2, gutted_torso3=2, gutted_torso4=2, hang_twitching=2 },

    bad_liquid = "blood",
    good_liquid = "water",

    sc_fabs = { pillar_MARBFAC4=20, secret_enclosure_4_Marbface=30, other=80 },
  },

  HELL_WODMET2 =
  {
    theme_probs = { HELL=40 },
    mat_pri = 6,

    wall  = "WOODMET1",
    floor = "FLAT5_2",
    ceil  = "FLAT5_1",

    lift = "SUPPORT3",
    lift_floor = "CEIL5_2",

    step = "WOOD1",
    pic_wd  = "MARBFACE",

    scenery = { red_pillar=3, red_column=3, green_pillar=3, green_column=3, green_column_hrt=1, red_torch=10, green_torch=10, blue_torch=10, red_torch_sm=5, green_torch_sm=5, blue_torch_sm=5, impaled_human=3, impaled_twitch=3, skull_pole=2, skull_kebab=2, dead_player=2, gibbed_player=1, gibs=1, skull_cairn=2, evil_eye=2, hang_arm_pair=2, hang_leg_pair=2, hang_leg_gone=1, hang_leg=1, gutted_victim1=2, gutted_victim2=2, gutted_torso1=2, gutted_torso2=2, gutted_torso3=2, gutted_torso4=2, hang_twitching=2 },

    bad_liquid = "blood",
    good_liquid = "water",

    sc_fabs = { pillar_MARBFAC4=20, secret_enclosure_4_Marbface=30, other=80 },
  },

  HELL_STUCCO =
  {
    theme_probs = { HELL=35 },
    mat_pri = 2,

    wall  = "STUCCO3",
    floor = "FLAT8",
    ceil  = "CRATOP2",
    step = "STEP2",

    lift = "SUPPORT3",
    lift_floor = "CEIL5_2",

    sc_fabs = { pillar_PANBLUE=20, pillar_PANRED=20, pillar_4_Panblue=20, pillar_4_Panred=20, other=70 },
    scenery = { candelabra=5, burning_barrel=2, red_torch=10, red_torch_sm=5, green_torch=10, green_torch_sm=5, blue_torch=10, blue_torch_sm=5, dead_player=3, gibbed_player=2, gibs=1, impaled_human=3, impaled_twitch=2, skull_kebab=3, skull_pole=2, skull_cairn=2, evil_eye=2, skull_rock=1, hang_arm_pair=2, hang_leg_pair=2, hang_leg_gone=1, hang_leg=1, gutted_victim1=2, gutted_victim2=2, gutted_torso1=2, gutted_torso2=2, gutted_torso3=2, gutted_torso4=2, hang_twitching=2 },

    wall_fabs = { solid_STUCCO2=40, other=60 },
  },

  HELL_D2WOOD1 =
  {
    theme_probs = { HELL=35 },
    mat_pri = 2,

    wall  = "WOODVERT",
    floor = "FLAT5_2",
    ceil  = "CEIL1_1",
    step = "STEP2",

    lift = "SUPPORT3",
    lift_floor = "CEIL5_2",

    scenery = { candelabra=5, burning_barrel=2, red_torch=10, red_torch_sm=5, green_torch=10, green_torch_sm=5, blue_torch=10, blue_torch_sm=5, dead_player=3, gibbed_player=2, gibs=1, impaled_human=3, impaled_twitch=2, skull_kebab=3, skull_pole=2, skull_cairn=2, evil_eye=2, skull_rock=1, hang_arm_pair=2, hang_leg_pair=2, hang_leg_gone=1, hang_leg=1, gutted_victim1=2, gutted_victim2=2, gutted_torso1=2, gutted_torso2=2, gutted_torso3=2, gutted_torso4=2, hang_twitching=2 },

  },

  HELL_D2WOOD2 =
  {
    theme_probs = { HELL=35 },
    mat_pri = 2,

    wall  = "WOOD12",
    floor = "FLAT5_1",
    ceil  = "CEIL1_1",
    step = "STEP2",

    lift = "SUPPORT3",
    lift_floor = "CEIL5_2",

    scenery = { candelabra=5, burning_barrel=2, red_torch=10, red_torch_sm=5, green_torch=10, green_torch_sm=5, blue_torch=10, blue_torch_sm=5, dead_player=3, gibbed_player=2, gibs=1, impaled_human=3, impaled_twitch=2, skull_kebab=3, skull_pole=2, skull_cairn=2, evil_eye=2, skull_rock=1, hang_arm_pair=2, hang_leg_pair=2, hang_leg_gone=1, hang_leg=1, gutted_victim1=2, gutted_victim2=2, gutted_torso1=2, gutted_torso2=2, gutted_torso3=2, gutted_torso4=2, hang_twitching=2 },

  },

  HELL_D2WOOD3 =
  {
    theme_probs = { HELL=35 },
    mat_pri = 2,

    wall  = "WOOD9",
    floor = "FLAT5_2",
    ceil  = "CEIL1_1",
    step = "STEP2",

    lift = "SUPPORT3",
    lift_floor = "CEIL5_2",

    scenery = { candelabra=5, burning_barrel=2, red_torch=10, red_torch_sm=5, green_torch=10, green_torch_sm=5, blue_torch=10, blue_torch_sm=5, dead_player=3, gibbed_player=2, gibs=1, impaled_human=3, impaled_twitch=2, skull_kebab=3, skull_pole=2, skull_cairn=2, evil_eye=2, skull_rock=1, hang_arm_pair=2, hang_leg_pair=2, hang_leg_gone=1, hang_leg=1, gutted_victim1=2, gutted_victim2=2, gutted_torso1=2, gutted_torso2=2, gutted_torso3=2, gutted_torso4=2, hang_twitching=2 },

  },

  ---- CAVE ----------------
  
  CAVE_ASH =
  {
    theme_probs = { CAVE=30 },
    mat_pri = 2,

    wall  = "ASHWALL2",
    floor = "FLOOR6_2",
    ceil  = "FLOOR6_2",
    step = "ASHWALL2",

    arch  = "arch_russian_WOOD",
    scenery = { burning_barrel=1, red_torch=15, red_torch_sm=7, green_torch=15, green_torch_sm=7, blue_torch=15, blue_torch_sm=7, dead_player=2, gibbed_player=1, gibs=1, impaled_human=3, impaled_twitch=2, skull_kebab=1, skull_pole=1, hang_arm_pair=2, hang_leg_pair=2, hang_leg_gone=1, hang_leg=1, gutted_victim1=2, gutted_victim2=2, gutted_torso1=2, gutted_torso2=2, gutted_torso3=2, gutted_torso4=2, hang_twitching=2 },

    sc_fabs = { stalagmite_MED=40, other=10 },
  },

  CAVE_ASH2 =
  {
    theme_probs = { CAVE=30 },
    mat_pri = 2,

    wall  = "ASHWALL3",
    floor = "FLAT10",
    ceil  = "RROCK03",
    step = "ASHWALL3",

    arch  = "arch_russian_WOOD",
    scenery = { burning_barrel=1, red_torch=15, red_torch_sm=7, green_torch=15, green_torch_sm=7, blue_torch=15, blue_torch_sm=7, dead_player=2, gibbed_player=1, gibs=1, impaled_human=3, impaled_twitch=2, skull_kebab=1, skull_pole=1, hang_arm_pair=2, hang_leg_pair=2, hang_leg_gone=1, hang_leg=1, gutted_victim1=2, gutted_victim2=2, gutted_torso1=2, gutted_torso2=2, gutted_torso3=2, gutted_torso4=2, hang_twitching=2 },

    sc_fabs = { stalagmite_MED=40, other=10 },
  },

  CAVE_ASH3 =
  {
    theme_probs = { CAVE=30 },
    mat_pri = 2,

    wall  = "ASHWALL4",
    floor = "FLAT10",
    ceil  = "FLAT10",
    step = "ASHWALL4",

    arch  = "arch_russian_WOOD",
    scenery = { burning_barrel=1, red_torch=15, red_torch_sm=7, green_torch=15, green_torch_sm=7, blue_torch=15, blue_torch_sm=7, dead_player=2, gibbed_player=1, gibs=1, impaled_human=3, impaled_twitch=2, skull_kebab=1, skull_pole=1, hang_arm_pair=2, hang_leg_pair=2, hang_leg_gone=1, hang_leg=1, gutted_victim1=2, gutted_victim2=2, gutted_torso1=2, gutted_torso2=2, gutted_torso3=2, gutted_torso4=2, hang_twitching=2 },

    sc_fabs = { stalagmite_MED=40, other=10 },
  },

  CAVE_ZIMMER =
  {
    theme_probs = { CAVE=10 },
    mat_pri = 2,

    wall  = "ZIMMER4",
    floor = "RROCK04",
    ceil  = "RROCK03",

    arch  = "arch_hole",
    scenery = { burning_barrel=1, red_torch=15, red_torch_sm=7, green_torch=15, green_torch_sm=7, blue_torch=15, blue_torch_sm=7, dead_player=2, gibbed_player=1, gibs=1, impaled_human=3, impaled_twitch=2, skull_kebab=1, skull_pole=1, hang_arm_pair=2, hang_leg_pair=2, hang_leg_gone=1, hang_leg=1, gutted_victim1=2, gutted_victim2=2, gutted_torso1=2, gutted_torso2=2, gutted_torso3=2, gutted_torso4=2, hang_twitching=2 },

    sc_fabs = { stalagmite_MED=40, other=10 },
  },

  CAVE_ROCK =
  {
    theme_probs = { CAVE=30 },
    mat_pri = 2,

    wall  = "ROCK3",
    floor = "RROCK13",
    ceil  = "RROCK13",

    arch  = "arch_russian_WOOD",
    scenery = { burning_barrel=1, red_torch=15, red_torch_sm=7, green_torch=15, green_torch_sm=7, blue_torch=15, blue_torch_sm=7, dead_player=2, gibbed_player=1, gibs=1, impaled_human=3, impaled_twitch=2, skull_kebab=1, skull_pole=1, hang_arm_pair=2, hang_leg_pair=2, hang_leg_gone=1, hang_leg=1, gutted_victim1=2, gutted_victim2=2, gutted_torso1=2, gutted_torso2=2, gutted_torso3=2, gutted_torso4=2, hang_twitching=2 },

    sc_fabs = { stalagmite_MED=40, other=10 },
  },

  CAVE_ROCK2 =
  {
    theme_probs = { CAVE=30 },
    mat_pri = 2,

    wall  = "ROCK5",
    floor = "RROCK16",
    ceil  = "RROCK09",

    arch  = "arch_russian_WOOD",
    scenery = { burning_barrel=1, red_torch=15, red_torch_sm=7, green_torch=15, green_torch_sm=7, blue_torch=15, blue_torch_sm=7, dead_player=2, gibbed_player=1, gibs=1, impaled_human=3, impaled_twitch=2, skull_kebab=1, skull_pole=1, hang_arm_pair=2, hang_leg_pair=2, hang_leg_gone=1, hang_leg=1, gutted_victim1=2, gutted_victim2=2, gutted_torso1=2, gutted_torso2=2, gutted_torso3=2, gutted_torso4=2, hang_twitching=2 },

    sc_fabs = { stalagmite_MED=40, secret_enclosure_4_Spdude=35, other=10 },
  },

  ----- NATURE -----------------

  NAT_GRASS =
  {
    theme_probs = { NATURE=50 },
    outdoor = true,
    mat_pri = 2,

    wall = "ZIMMER7",
    step = "ZIMMER7",

    floor = "RROCK20",
    ceil  = "RROCK20",

    lift = "SUPPORT3",
    lift_floor = "CEIL5_2",

    scenery = { brown_stub=10, burnt_tree=12, big_tree=7, dead_player=2, gibbed_player=1 },

    bad_liquid = "nukage",

  },

  NAT_GRASS2 =
  {
    theme_probs = { NATURE=50 },
    outdoor = true,
    mat_pri = 2,

    wall = "ZIMMER1",
    step = "ZIMMER1",

    floor = "RROCK19",
    ceil  = "RROCK20",

    lift = "SUPPORT3",
    lift_floor = "CEIL5_2",

    scenery = { brown_stub=10, burnt_tree=12, big_tree=7, dead_player=2, gibbed_player=1 },

    bad_liquid = "nukage",

  },

  NAT_GRASS3 =
  {
    theme_probs = { NATURE=50 },
    outdoor = true,
    mat_pri = 2,

    wall = "ZIMMER2",
    step = "ZIMMER2",

    floor = "GRASS1",
    ceil  = "RROCK20",

    lift = "SUPPORT3",
    lift_floor = "CEIL5_2",

    scenery = { brown_stub=10, burnt_tree=12, big_tree=7, dead_player=2, gibbed_player=1 },

    bad_liquid = "nukage",

  },

  NAT_DEDGRASS1 =
  {
    theme_probs = { NATURE=40 },
    outdoor = true,
    mat_pri = 2,

    wall = "ZIMMER3",
    step = "ZIMMER3",

    floor = "RROCK18",
    ceil  = "RROCK17",

    lift = "SUPPORT2",
    lift_floor = "FLAT23",

    scenery = { brown_stub=10, burnt_tree=12, big_tree=7, dead_player=2, gibbed_player=1 },

    bad_liquid = "nukage",

  },

  NAT_DEDGRASS2 =
  {
    theme_probs = { NATURE=40 },
    outdoor = true,
    mat_pri = 2,

    wall = "ZIMMER4",
    step = "ZIMMER4",

    floor = "RROCK17",
    ceil  = "RROCK18",

    lift = "SUPPORT2",
    lift_floor = "FLAT23",

    scenery = { brown_stub=10, burnt_tree=12, big_tree=7, dead_player=2, gibbed_player=1 },

    bad_liquid = "nukage",

  },

  NAT_SWAMP =
  {
    theme_probs = { NATURE=70 },
    outdoor = true,
    mat_pri = 2,

    wall = "ZIMMER8",
    step = "ZIMMER2",

    floor = "GRASS2",
    ceil  = "MFLR8_3",

    lift = "SUPPORT3",
    lift_floor = "CEIL5_2",

    scenery = { brown_stub=10, burnt_tree=12, big_tree=7, dead_player=2, gibbed_player=1 },

    bad_liquid = "nukage",
  },

  NAT_TANROCK7 =
  {
    theme_probs = { NATURE=30 },
    outdoor = true,
    mat_pri = 3,

    wall = "TANROCK7",
    void = "ZIMMER4",
    step = "TANROCK7",
    lift = "SUPPORT3",
    piller = "ASHWALL7",

    floor = "RROCK15",
    ceil  = "RROCK15",

    scenery = { brown_stub=12, burnt_tree=10, big_tree=7, dead_player=2, gibbed_player=1 },
    bad_liquid = "slime",
  },

  NAT_TANROCK8 =
  {
    theme_probs = { NATURE=20 },
    outdoor = true,
    mat_pri = 3,

    wall = "TANROCK8",
    void = "TANROCK8",
    step = "TANROCK8",
    lift = "SUPPORT3",

    floor = "RROCK17",
    ceil  = "RROCK17",

    scenery = { brown_stub=10, burnt_tree=10, big_tree=7, dead_player=2, gibbed_player=1 },
    bad_liquid = "slime",
  },

  NAT_MUDDY =
  {
    theme_probs = { NATURE=35 },
    outdoor = true,
    mat_pri = 2,

    wall = "ASHWALL4",
    void = "ASHWALL4",
    step = "STEP3",

    floor = "FLAT10",
    ceil  = "FLAT10",

    scenery = { brown_stub=10, burnt_tree=10, big_tree=7, dead_player=2, gibbed_player=1 },

    bad_liquid = "slime",
  },

  NAT_SPROCK =
  {
    theme_probs = { NATURE=50 } ,
    outdoor = true,
    mat_pri = 3,

    wall  = "SP_ROCK1",
    floor = "MFLR8_3",
    ceil  = "MFLR8_3",

--  void = "BROWNPIP",
    step = "SP_ROCK1",
    lift = "SUPPORT3",
--    pillar = "BROWN1",  -- was "BRONZE2" (not in doom 1)

    lift_floor = "CEIL5_2",

    scenery = { brown_stub=15, burnt_tree=20, big_tree=10, dead_player=2, gibbed_player=1, gibs=1, 		skull_pole=1, skull_kebab=1 },
    good_liquid = "water",
    bad_liquid = "lava",

    door_probs = { out_diff=75, combo_diff=10, normal=5 }
  },


  ---- Wolf3D Secret Levels ----

  WOLF_CELLS =
  {
    mat_pri = 5,

    wall = "ZZWOLF9",
    void = "ZZWOLF9",
    step = "STEP4",

    floor = "FLAT5_4",
    ceil  = "FLAT14",
    scenery = { candelabra=5, red_torch=10, red_torch_sm=5, green_torch=10, green_torch_sm=5, blue_torch=10, blue_torch_sm=5, dead_player=1, gibbed_player=1, gibs=1, impaled_human=3, impaled_twitch=2, skull_kebab=3, skull_pole=2, skull_cairn=2, evil_eye=2, skull_rock=1, hang_twitching=2, },

    theme_probs = { WOLF=50 },
  },

  WOLF_BRICK =
  {
    mat_pri = 6,

    wall = "ZZWOLF11",
    void = "ZZWOLF11",
    -- decorate =  { ZZWOLF12, ZZWOLF13 }
    step = "STEP4",

    scenery = { candelabra=5, red_torch=10, red_torch_sm=5, green_torch=10, green_torch_sm=5, blue_torch=10, blue_torch_sm=5, dead_player=1, gibbed_player=1, gibs=1 },
    floor = "FLAT5_4",
    ceil  = "FLAT5_3",

    theme_probs = { WOLF=60 },
  },

  WOLF_STONE =
  {
    mat_pri = 4,

    wall = "ZZWOLF1",
    void = "ZZWOLF1",
    -- decorate =  { ZZWOLF2, ZZWOLF3, ZZWOLF4 }

    step = "STEP4",
    floor = "FLAT5_4",
    ceil  = "RROCK03",
    scenery = { candelabra=5, red_torch=10, red_torch_sm=5, green_torch=10, green_torch_sm=5, blue_torch=10, blue_torch_sm=5, dead_player=1, gibbed_player=1, gibs=1 },

    theme_probs = { WOLF=70 },
  },

  WOLF_WOOD =
  {
    mat_pri = 4,

    wall = "ZZWOLF5",
    void = "ZZWOLF5",
    -- decorate =  { ZZWOLF6, ZZWOLF7 }

    step = "STEP2",
    ceil  = "FLAT5_1",
    floor = "FLAT5_2",
    scenery = { candelabra=5, red_torch=10, red_torch_sm=5, green_torch=10, green_torch_sm=5, blue_torch=10, blue_torch_sm=5, dead_player=1, gibbed_player=1, gibs=1 },

    theme_probs = { WOLF=30 },
  },
}

D2_EXITS =
{
  METAL =
  {
    mat_pri = 8,

    wall = "METAL1",
    void = "METAL5",

    floor = "FLOOR5_1",
    ceil  = "TLITE6_4",

    hole_tex = "LITE3",

    sign = "EXITSIGN",
    sign_ceil="CEIL5_2",

    switch =
    {
      prefab="SWITCH_NICHE_TINY_DEEP",
      add_mode="wall",
      skin =
      {
        switch_w="SW1COMP", switch_h=32,
        frame_w="LITEBLU4", frame_f="FLAT14", frame_c="FLAT14",

        x_offset=16, y_offset=72, kind=11, tag=0,
      }
    },

    door = { wall="EXITDOOR", w=64, h=72,
             frame_ceil="TLITE6_6", frame_floor="FLOOR5_1" },
  },

  REDBRICK =
  {
    mat_pri = 8,

    wall = "BRICK11",
    void = "BRICK11",
    step = "WOOD1",

    floor = "FLAT5_2",
    ceil  = "FLOOR6_2",

    sign = "EXITSIGN",
    sign_ceil="CEIL5_2",

    switch =
    {
      prefab="SWITCH_PILLAR",
      skin =
      {
        switch_w="SW1WOOD", side_w="WOOD1",
        x_offset=0, y_offset=0, kind=11, tag=0,
      }
    },

    door = { wall="EXITDOOR", w=64, h=72,
             frame_ceil="TLITE6_6", frame_floor="FLAT5_2" },
  },

  SLOPPY =
  {
    small_exit = true,
    mat_pri = 1,

    wall = "SKINMET2",
    void = "SLOPPY1",
    step = "SKINMET2",

    floor = "FWATER1",
    ceil  = "SFLR6_4",

    liquid_prob = 0,

    sign = "EXITSIGN",
    sign_ceil="CEIL5_2",

    switch =
    {
      prefab="SWITCH_FLUSH",
      add_mode="wall",
      skin =
      {
        switch_w="SW1SKULL", wall="SLOPPY1",
        left_w="SK_LEFT", right_w="SK_RIGHT",
        kind=11, tag=0,
      }
    },

    door = { wall="EXITDOOR", w=64, h=72,
             frame_ceil="FLAT5_5", frame_floor="CEIL5_2" },
  },
}

D2_HALLWAYS =
{
  PANEL =
  {
    mat_pri = 0,

    wall = "PANEL2",
    void = "PANEL2",
    step = "STEP2",
    pillar = "PANRED",

    floor = "FLAT5_5",
    ceil  = "RROCK09",

    theme_probs = { URBAN=70 },
    trim_mode = "guillotine",
  },

  PANEL2 =
  {
    mat_pri = 0,

    wall = "PANEL3",
    void = "PANEL3",
    step = "STEP2",
    pillar = "PANBLACK",

    floor = "FLAT5_5",
    ceil  = "RROCK09",

    theme_probs = { URBAN=70 },
    trim_mode = "guillotine",
  },

  PANEL3 =
  {
    mat_pri = 0,

    wall = "PANCASE2",
    void = "PANCASE2",
    step = "STEP2",
    pillar = "PANBLUE",  -- PANEL5

    floor = "FLAT5_5",
    ceil  = "RROCK09",

    theme_probs = { URBAN=50 },
    trim_mode = "guillotine",
  },

  PANEL4 =
  {
    mat_pri = 0,

    wall = "PANEL9",
    void = "PANEL9",
    step = "STEP2",
    pillar = "PANRED",  -- PANEL5

    floor = "FLAT5_5",
    ceil  = "RROCK09",

    theme_probs = { URBAN=70 },
    trim_mode = "guillotine",
  },

  MOD =
  {
    mat_pri = 0,

    wall = "MODWALL1",
    void = "MODWALL1",
    step = "STEP3",
    pillar = "MODWALL2",  -- PANEL5

    floor = "MFLR8_2",
    ceil  = "CEIL5_1",

    theme_probs = { URBAN=40 },
    trim_mode = "guillotine",
  },

  STUCCO =
  {
    mat_pri = 0,

    wall = "STUCCO",
    void = "STUCCO",
    step = "STEP2",
    pillar = "STUCCO",  -- PANEL5

    floor = "FLAT8",
    ceil  = "CRATOP2",

    theme_probs = { URBAN=20,HELL=10 },
    trim_mode = "guillotine",
  },

  BRICK =
  {
    mat_pri = 0,

    wall = "BIGBRIK1",
    void = "BIGBRIK1",
    step = "STEP6",
    pillar = "STONE6",

    floor = "FLOOR5_4",
    ceil  = "FLAT1_1",

    theme_probs = { URBAN=70,NATURE=10,HELL=10 },
    trim_mode = "guillotine",
  },

  BRICK2 =
  {
    mat_pri = 0,

    wall = "BIGBRIK2",
    void = "BIGBRIK2",
    step = "STEP4",
    pillar = "STONE4",

    floor = "FLOOR0_3",
    ceil  = "FLAT5_4",

    theme_probs = { URBAN=70,NATURE=10,HELL=10 },
    trim_mode = "guillotine",
  },

  BSTONE =
  {
    theme_probs = { URBAN=20,NATURE=50,CAVE=30 },
    mat_pri = 0,

    wall = "BSTONE1",
    floor = "FLAT5",
    ceil  = "RROCK11",

    step = "STEP6",
    pillar = "BSTONE1",

    trim_mode = "guillotine",
  },

  BSTONE2 =
  {
    theme_probs = { URBAN=20,NATURE=50,CAVE=30 },
    mat_pri = 0,

    wall = "BSTONE2",
    floor = "FLAT5",
    ceil  = "RROCK12",

    step = "STEP6",
    pillar = "BSTONE1",

    trim_mode = "guillotine",
  },

  WOOD =
  {
    mat_pri = 0,

    wall = "WOODMET1",
    void = "WOODMET1",
    step = "STEP5",
    pillar = "WOODMET2",

    floor = "FLAT5_2",
    ceil  = "MFLR8_2",

    theme_probs = { URBAN=30,HELL=30 },
    trim_mode = "guillotine",
  },

  WOOD2 =
  {
    mat_pri = 0,

    wall = "WOOD1",
    void = "WOOD1",
    step = "STEP6",
    pillar = "WOOD3",

    floor = "FLAT5_1",
    ceil  = "FLAT5_2",

    theme_probs = { URBAN=30,HELL=30 },
    trim_mode = "guillotine",
  },

  METAL =
  {
    mat_pri = 0,

    wall = "METAL2",
    void = "METAL2",
    step = "STEP6",
    pillar = "SW1SATYR",

    floor = "FLAT5_5",
    ceil  = "CEIL5_1",

    theme_probs = { INDUSTRIAL=70,TECH=30 },
    trim_mode = "guillotine",
  },

  METAL2 =
  {
    mat_pri = 0,

    wall = "METAL5",
    void = "METAL5",
    step = "STEP6",
    pillar = "SW1SATYR",

    floor = "FLAT5_5",
    ceil  = "CEIL5_1",

    theme_probs = { INDUSTRIAL=70,TECH=30 },
    trim_mode = "guillotine",
  },

  TEKGREN =
  {
    mat_pri = 0,

    wall = "TEKGREN2",
    floor = "FLOOR3_3",
    ceil  = "GRNLITE1",

    step = "STEP6",
    pillar = "TEKGREN3",  -- was: "BRONZE2"

    well_lit = true,

    theme_probs = { TECH=80,INDUSTRIAL=40 },
    trim_mode = "guillotine",

    wall_fabs = { solid_TEKGREN5=30, other=50 },
  },

  PIPES =
  {
    mat_pri = 0,

    wall = "PIPEWAL2",
    void = "PIPEWAL1",
    step = "STEP4",
    pillar = "STONE4",

    floor = "FLAT5_4",
    ceil  = "FLAT5_4",

    theme_probs = { INDUSTRIAL=70 },
    trim_mode = "guillotine",
  },

  MARBLE =
  {
    mat_pri = 0,

    wall = "MARBLE1",
    void = "MARBLE1",
    step = "MARBLE1",
    pillar = "MARBGRAY",

    floor = "DEM1_6",
    ceil  = "FLOOR7_2",

    theme_probs = { HELL=70 },
    trim_mode = "guillotine",
  },

  MARBLE2 =
  {
    mat_pri = 0,

    wall = "MARBLE2",
    void = "MARBLE2",
    step = "MARBLE2",
    pillar = "MARBGRAY",

    floor = "DEM1_6",
    ceil  = "FLOOR7_2",

    theme_probs = { HELL=70 },
    trim_mode = "guillotine",
  },

  MARBLE3 =
  {
    mat_pri = 0,

    wall = "MARBLE3",
    void = "MARBLE3",
    step = "MARBLE3",
    pillar = "MARBGRAY",

    floor = "DEM1_6",
    ceil  = "FLOOR7_2",

    theme_probs = { HELL=70 },
    trim_mode = "guillotine",
  },

  SLOP =
  {
    mat_pri = 0,

    wall = "SLOPPY1",
    void = "SLOPPY1",
    step = "BFALL1",
    pillar = "SP_FACE2",

    floor = "BLOOD1",
    ceil  = "FLOOR1_6",

    theme_probs = { HELL=70 },
    trim_mode = "guillotine",
  },

  CRACKLE =
  {
    mat_pri = 0,

    wall = "CRACKLE2",
    void = "CRACKLE2",
    step = "ASHWALL2",
    pillar = "SP_FACE2",

    floor = "RROCK03",
    ceil  = "RROCK03",

    theme_probs = { HELL=70 },
    trim_mode = "guillotine",
  },

  CRACKLE2 =
  {
    mat_pri = 0,

    wall = "CRACKLE4",
    void = "CRACKLE4",
    step = "ASHWALL2",
    pillar = "SP_FACE2",

    floor = "RROCK03",
    ceil  = "RROCK03",

    theme_probs = { HELL=70 },
    trim_mode = "guillotine",
  },

  ICKY =
  {
    mat_pri = 0,

    wall = "ICKWALL3",
    void = "ICKWALL3",
    step = "STEP4",
    pillar = "ICKWALL1",

    floor = "FLOOR0_3",
    ceil  = "FLAT19",

    theme_probs = { INDUSTRIAL=70,TECH=30,HELL=10 },
    trim_mode = "guillotine",
  },
}

D2_MATS =
{
  ARCH =
  {
    wall  = "METAL",
    void  = "METAL1",
    floor = "SLIME14",
    ceil  = "SLIME14",
  },
}

D2_OVERHANGS =
{
  METAL =
  {
    ceil = "CEIL5_1",
    upper = "METAL6",
    thin = "METAL",
  },

  MARBLE =
  {
    thin = "MARBLE1",
    upper = "MARBLE3",
    ceil = "SLIME13",
  },

  PANEL =
  {
    thin = "PANBORD2",
    thick = "PANBORD1",
    upper = "PANCASE2",
    ceil = "CEIL3_1",
  },

  STONE =
  {
    thin = "STONE4",
    upper = "STONE4",
    ceil = "FLAT5_4",
  },

  STONE2 =
  {
    thin = "STONE6",
    upper = "STONE6",
    ceil = "FLAT5_5",
  },

}

D2_DOORS =
{
  d_thin1  = { wall="SPCDOOR1", w=64, h=112 },
  d_thin2  = { wall="SPCDOOR2", w=64, h=112 },
  d_thin3  = { wall="SPCDOOR3", w=64, h=112 },

  d_weird  = { wall="SPCDOOR4", w=64, h=112 },
}

D2_CRATES =
{
  MODWALL =
  {
    wall = "MODWALL3", h=64, floor = "FLAT19"
  },
  
  PIPES =
  {
    wall = "PIPES", h=64, floor = "CEIL3_2", can_rotate=true
  },

  SILVER2 =
  {
    wall = "SILVER2", h=64, floor = "FLAT23",
    can_rotate=true, rot_x_offset=0
  },

  SILVER3 =
  {
    wall = "SILVER3", h=128, floor = "FLAT23", can_rotate=true
  },

  TVS =
  {
    wall = "SPACEW3", h=64, floor = "CEIL5_1"
  },
}

D2_RAILS =
{
  r_1 = { wall="MIDBARS3", w=128, h=72  },
  r_2 = { wall="MIDGRATE", w=128, h=128 },
}

D2_LIGHTS =
{
  green1 = { floor="GRNLITE1", side="TEKGREN2" },
}

D2_LIQUIDS =
{
--###  slime = { floor="SLIME01", wall="BLODRIP1", sec_kind=7 }  -- 5% damage
}

D2_SCENERY =
{
}

D2_SCENERY_PREFABS =
{
  billboard_NAZI =
  {
    prefab = "BILLBOARD",
--  environment = "outdoor",
    add_mode = "extend",

    min_height = 160,

    skin =
    {
      pic_w = "ZZWOLF2", pic_back = "ZZWOLF1",
      pic_f = "FLAT5_4",  pic_h = 128,

      corn_w = "ZZWOLF5", corn_f = "FLAT5_1",
      corn_h = 112,

      step_w = "ZZWOLF5", step_f = "FLAT5_1",
    },

    theme_probs = { WOLF=5 },
  },

  billboard_stilts_FLAGGY =
  {
    prefab = "BILLBOARD_ON_STILTS",
    environment = "outdoor",
    add_mode = "island",
    min_height = 160,

    skin =
    {
      pic_w  = "ZZWOLF12", pic_offset_h = 64,
      beam_w = "WOOD1", beam_f = "FLAT5_2",
    },

    theme_probs = { NATURE=2 },
  },

  pond_small_GRASS =
  {
    prefab = "POND_SMALL",
    environment = "outdoor",
    theme_probs = { NATURE=90 },
    skin = 
    {
      pond_w="ZIMMER4", pond_f="RROCK18",
      outer_w="BROWNHUG", liquid_f="FWATER1",
      kind=0
    },
  },

  rock_pieces_GRNROCK =
  {
    prefab = "ROCK_PIECES",
    environment = "outdoor",
    theme_probs = { NATURE=2 },
    skin = { rock_w="ROCK2", rock_f="GRNROCK", rock_h=16 },
  },

  comp_tall_STATION1 =
  {
    prefab = "COMPUTER_TALL",
    theme_probs = { TECH=20, INDUSTRIAL=20 },
    skin   = { comp_w="COMPSTA1", comp_f="FLAT23", side_w="SHAWN2" },
  },
 
  comp_tall_STATION2 =
  {
    prefab = "COMPUTER_TALL",
    theme_probs = { TECH=20, INDUSTRIAL=20 },
    skin   = { comp_w="COMPSTA2", comp_f="FLAT23", side_w="SHAWN2" },
  },
 
  comp_thin_STATION1 =
  {
    prefab = "COMPUTER_TALL_THIN",
    theme_probs = { TECH=20, INDUSTRIAL=20 },
    skin   = { comp_w="COMPSTA1", comp_f="FLAT23", side_w="SHAWN2" },
  },
 
  comp_thin_STATION2 =
  {
    prefab = "COMPUTER_TALL_THIN",
    theme_probs = { TECH=20, INDUSTRIAL=20 },
    skin   = { comp_w="COMPSTA2", comp_f="FLAT23", side_w="SHAWN2" },
  },
 
  pillar_SPDUDE4 =
  {
    prefab = "PILLAR", add_mode = "island",
    environment = "indoor",
    theme_probs = { HELL=20, CAVE=5 },
    skin = { wall="SP_DUDE4" },
  },

  comp_desk_EW8 =
  {
    prefab = "COMPUTER_DESK",
    theme_probs = { TECH=20, INDUSTRIAL=20 },
    add_mode = "extend",
    skin   = { comp_f="CONS1_5", side_w="SHAWN2" },
    force_dir = 2,
  },

  comp_desk_EW2 =
  {
    prefab = "COMPUTER_DESK",
    theme_probs = { TECH=20, INDUSTRIAL=20 },
    add_mode = "extend",
    skin   = { comp_f="CONS1_1", side_w="SHAWN2" },
    force_dir = 8,
  },

  comp_desk_NS6 =
  {
    prefab = "COMPUTER_DESK",
    theme_probs = { TECH=20, INDUSTRIAL=20 },
    add_mode = "extend",
    skin   = { comp_f="CONS1_7", side_w="SHAWN2" },
    force_dir = 4,
  },

  comp_desk_USHAPE1 =
  {
    prefab = "COMPUTER_DESK_U_SHAPE",
    theme_probs = { TECH=20, INDUSTRIAL=20 },
    add_mode = "island",
    skin   =
    {
      comp_Nf="CONS1_1", comp_Wf="CONS1_7",
      comp_Sf="CONS1_5",
      comp_cf="COMP01", side_w ="SHAWN2"
    },

--  pickup_specialness = 60,
    force_dir = 2,
  },

  bookcase_WIDE =
  {
    theme_probs = { URBAN=20, HELL=2 },
    prefab = "BOOKCASE_WIDE",
    skin   = { book_w="PANBOOK", book_f="FLAT5_2", side_w="PANCASE1" },
  },



--  drinks_bar_WOOD_POTION =
--  {
--    prefab = "DRINKS_BAR",
--    environment = "indoor",
--    min_height = 64,

--    skin = { bar_w = "PANBORD1", bar_f = "FLAT5_2",
--             drink_t = "potion",
--           },

--    prob = 2,
--  },

  crate_WOOD3 =
  {
    prefab = "CRATE_TWO_SIDED",

    skin =
    {
      crate_h = 62,
      crate_w = "WOOD3", crate_w2 = "WOOD3",
      crate_f = "CEIL1_1",
      x_offset = 128,
    }
  },

  crate_WOODSKULL =
  {
    prefab = "CRATE",

    skin =
    {
      crate_h = 62,
      crate_w = "WOOD4",
      crate_f = "CEIL1_1",
    }
  },

secret_enclosure_11_crate_woodskull =
  {
    prefab = "ENCLOSURE_SECRET11",

    theme_probs = { CAVE=10, HELL=10, URBAN=5 },
    
    min_height = 132,
    
    skin = { crate_h = 62, crate_f="CEIL1_1", crate_w="WOOD4", door_kind=0, tag=0, kind=121,
		 pickup = "shells" },
    
   prob = 3,
  },

  crate_WOODMET1 =
  {
    prefab = "CRATE_TWO_SIDED",
    theme_probs = { CAVE=10, HELL=10, URBAN=5 },

    skin =
    {
      crate_h = 64,
      crate_w = "WOODMET1", crate_w2 = "WOODMET3",
      crate_f = "CEIL5_2",
      x_offset = 0,
    }
  },

  crate_rotate_WOOD3 =
  {
    prefab = "CRATE_ROTATE",
    theme_probs = { CAVE=10, HELL=10, URBAN=5 },

    skin =
    {
      crate_h = 62,
      crate_w = "WOOD3",
      crate_f = "CEIL1_1",
    }
  },

  crate_rot22_WOODMET1 =
  {
    prefab = "CRATE_ROTATE",
    theme_probs = { CAVE=10, HELL=10, URBAN=5 },

    skin =
    {
      crate_h = 64,
      crate_w = "WOODMET1",
      crate_f = "CEIL5_2",
    }
  },

  crate_big_WOOD10 =
  {
    prefab = "CRATE_BIG",
    theme_probs = { CAVE=10, HELL=10, URBAN=10 },
    min_height = 144,

    skin =
    {
      crate_h = 128,
      crate_w = "WOOD10",
      crate_f = "FLAT5_2"
    }
  },

secret_enclosure_14_crate_big =
  {
    prefab = "ENCLOSURE_SECRET14",      
    min_height = 196,    
    skin = { crate_f="FLAT5_2", crate_w="WOOD10", door_kind=0, tag=0, kind=130,
		 pickup = "shells" },
    
   prob = 3,
  },

secret_enclosure_17_crate_big =
  {
    prefab = "ENCLOSURE_SECRET17",    
    theme_probs = { CAVE=10, HELL=10, URBAN=10 },
    min_height = 196,    
    skin = { crate_h = 128, crate_f="FLAT5_2", crate_w="WOOD10", door_kind=0, tag=0, kind=121,
		 pickup = "shells" },
    
   prob = 3,
  },

secret_enclosure_15_crate_big =
  {
    prefab = "ENCLOSURE_SECRET15",      
    theme_probs = { CAVE=10, HELL=10, URBAN=10, INDUSTRIAL=5 },
    environment = "outdoor",
    min_height = 128,
    max_height = 128,    
    skin = { door_w="WOOD10", door_kind=0, tag=0, kind=109,
		 pickup = "shells" },
    
   prob = 3,
  },

  crate_TV =
  {
    prefab = "CRATE",
    environment = "indoor",
    theme_probs = { TECH=20, INDUSTRIAL=10 },

    skin =
    {
      crate_h = 64,
      crate_w = "SPACEW3",
      crate_f = "CEIL5_1"
    }
  },

secret_enclosure_11_crate_tv =
  {
    prefab = "ENCLOSURE_SECRET11",
    environment = "indoor",
    theme_probs = { TECH=20, INDUSTRIAL=10 },
    
    min_height = 132,
    
    skin = { crate_h = 64, crate_f="CEIL5_1", crate_w="SPACEW3", door_kind=0, tag=0, kind=121,
		 pickup = "shells" },
    
   prob = 2,
  },

  crate_rotnar_SILVER =
  {
    prefab = "CRATE_ROTATE_NARROW",
    add_mode = "island",
    environment = "indoor",
    theme_probs = { TECH=20, INDUSTRIAL=10 },

    skin =
    {
      crate_h = 64,
      crate_w = "SILVER2",
      crate_f = "FLAT23"
    }
  },

  pillar_MARBFAC4 =
  {
    prefab = "PILLAR", add_mode = "island",
    environment = "indoor",
    skin = { wall="MARBFAC4" },
  },

  pillar_PANBLUE =
  {
    prefab = "PILLAR", add_mode = "island",
    environment = "indoor",
    skin = { wall="PANBLUE" },
  },
 
  pillar_PANRED =
  {
    prefab = "PILLAR", add_mode = "island",
    environment = "indoor",
    skin = { wall="PANRED" },
  },
 
  pillar_PANEL5 =
  {
    prefab = "PILLAR", add_mode = "island",
    environment = "indoor",
    skin = { wall="PANEL5" },
  },

 pillar_4_Panred =
  {
    	prefab = "ENCLOSURE_SECRET4", add_mode = "island",
    theme_probs = { URBAN=50, HELL=5 },
	environment = "indoor",
    	skin = { track_x="LITE5", track_w="DOORTRAK", door_h=128, door_w="PANRED",
             door_kind=0, tag=0, kind=109, x_offset = 16, pickup = "bullets" },     
    
  },
 pillar_4_Panblue =
  {
    	prefab = "ENCLOSURE_SECRET4", add_mode = "island",
    theme_probs = { URBAN=50, HELL=5 },
	environment = "indoor",
    	skin = { track_x="LITE5", track_w="DOORTRAK", door_h=128, door_w="PANBLUE",
             door_kind=0, tag=0, kind=109, x_offset = 16, pickup = "bullets" },     
   
  },
 pillar_4_Panel5 =
  {
    	prefab = "ENCLOSURE_SECRET4", add_mode = "island",
    theme_probs = { URBAN=50, HELL=5 },
	environment = "indoor",
    	skin = { track_x="LITE5", track_w="DOORTRAK", door_h=128, door_w="PANEL5",
             door_kind=0, tag=0, kind=109, x_offset = 16, pickup = "bullets" },     
    
  },


computer1_TALL_enclosure_drop =
  {
    prefab = "ENCLOSURE_COMPUTER_TALL",
    environment = "indoor",
    theme_probs = { TECH=20, INDUSTRIAL=10 },
    min_height = 156,
    skin   = { comp_w="COMPSTA1", comp_f="FLAT23", side_w="SHAWN2", 
               door_kind=0, tag=0, kind=121 },
  

  prob = 3,
},

computer2_TALL_enclosure_drop =
  {
    prefab = "ENCLOSURE_COMPUTER_TALL",
    environment = "indoor",
    theme_probs = { TECH=20, INDUSTRIAL=10 },
    min_height = 156,
    skin   = { comp_w="COMPSTA2", comp_f="FLAT23", side_w="SHAWN2", 
               door_kind=0, tag=0, kind=121 },
  

  prob = 3,
},



bookcase_WIDE_enclosure_drop =
  {
    prefab = "ENCLOSURE_BOOKCASE_WIDE",
    environment = "indoor",
    theme_probs = { URBAN=20, HELL=5 },
    min_height = 196,
    skin   = { book_w="PANBOOK", book_f="FLAT5_2", side_w="PANCASE1", 
               door_kind=0, tag=0, kind=121 },
  

  prob = 3,
},

bookcase_WIDE_enclosure_raise =
  {
    prefab = "ENCLOSURE_BOOKCASE_WIDE_RAISE",
    environment = "indoor",
    theme_probs = { URBAN=20, HELL=5 },
    min_height = 128,
    max_height = 128,
    skin   = { book_w="PANBOOK", book_f="FLAT5_2", side_w="PANCASE1", 
               door_kind=0, tag=0, kind=109 },
  

  prob = 3,
},
	


  cage_small_METAL =
  {
    prefab = "CAGE_SMALL",
    add_mode = "island",
    min_height = 144,
    is_cage = true,

    skin =
    {
      cage_w = "METAL",
      cage_f = "CEIL5_2",

      rail_w = "MIDBARS3",
    }
  },

  cage_medium_METAL =
  {
    prefab = "CAGE_MEDIUM",
    add_mode = "island",
    min_height = 168,
    is_cage = true,

    skin =
    {
      cage_w = "METAL",
      cage_f = "CEIL5_2",

      rail_w = "MIDBARS3",
    },

    prob = 1,
    force_dir = 2, -- optimisation
  },

  crate_WOODMET2 =
  {
    prefab = "CRATE_TWO_SIDED",
    theme_probs = { URBAN=20, HELL=20, CAVE=10, NATURE=10 },

    skin =
    {
      crate_h = 64,
      crate_w = "WOODMET1", crate_w2 = "WOODMET4",
      crate_f = "CEIL5_2",
      x_offset = 0,
    }
  },

  crate_WOODMET3 =
  {
    prefab = "CRATE_TWO_SIDED",
    theme_probs = { URBAN=20, HELL=20, CAVE=10, NATURE=10 },

    skin =
    {
      crate_h = 64,
      crate_w = "WOODMET4", crate_w2 = "WOODMET3",
      crate_f = "CEIL5_2",
      x_offset = 0,
    }
  },

}


D2_FEATURE_PREFABS =
{
  overhang3_METAL6 =
  {
    prefab = "OVERHANG_3",
    environment = "outdoor",
    add_mode = "island",
    min_height = 128,
    max_height = 320,

    skin =
    {
      beam_w = "METAL",
      hang_u = "METAL6",
      hang_c = "CEIL5_1",
    },

    pickup_specialness = 35,
    theme_probs = { URBAN=30 },
  },

  billboard_stilts4_WREATH =
  {
    prefab = "BILLBOARD_STILTS_HUGE",
    environment = "outdoor",
    add_mode = "island",
    min_height = 160,

    skin =
    {
      pic_w  = "ZZWOLF13", pic_offset_h = 128,
      beam_w = "WOOD1", beam_f = "FLAT5_2",
    },

    theme_probs = { NATURE=3 },
    pickup_specialness = 61,
    force_dir = 2, -- optimisation
  },

  statue_tech1 =
  {
    prefab = "STATUE_TECH_1",
    environment = "indoor",
    min_height = 176,
    max_height = 248,

    skin =
    {
      wall="COMPWERD", floor="FLAT14", ceil="FLOOR4_8",
      step_w="STEP1", carpet_f="FLOOR1_1",
      
      comp_w="SPACEW3", comp2_w="COMPTALL", span_w="COMPSPAN",
      comp_f="CEIL5_1", lite_c="TLITE6_5",

      lamp_t="lamp"
    },
    
    theme_probs = { TECH=80, INDUSTRIAL=20 },
    force_dir = 2, -- optimisation
  },

  statue_tech2 =
  {
    prefab = "STATUE_TECH_2",
    environment = "indoor",
    min_height = 160,
    max_height = 256,

    skin =
    {
      wall="METAL", floor="FLAT23", ceil="FLAT23",
      outer_w="STEP4",

      carpet_f="FLAT14", lite_c="TLITE6_5",

      tv_w="SPACEW3", tv_f="CEIL5_1",
      span_w="COMPSPAN", span_f="FLAT4",
    },

    theme_probs = { TECH=80, INDUSTRIAL=20 },
    force_dir = 2, -- optimisation
  },

  machine_pump1 =
  {
    prefab = "MACHINE_PUMP",
    environment = "indoor",
    add_mode = "island",
    theme_probs = { INDUSTRIAL=80, TECH=20 },

    min_height = 192,
    max_height = 240,

    skin =
    {
      ceil="FLAT1",

      metal3_w="METAL3", metal_f="CEIL5_1",
      metal4_w="METAL4", metal_c="CEIL5_1",
      metal5_w="METAL5",

      pump_w="SPACEW4", pump_c="FLOOR3_3",
      beam_w="DOORSTOP",

      kind=48 -- scroll left
    },

  },

  pillar_double_TEKLITE =
  {
    prefab = "PILLAR_DOUBLE_TECH_LARGE",
    environment = "indoor",
    add_mode = "island",
    min_height = 160,
    theme_probs = { TECH=90, INDUSTRIAL=10 },

    skin =
    {
      outer_f ="FLOOR0_3", outer_w ="STEP4",   outer_lt =160,
      inner_f ="FLOOR0_2", inner_w ="STEP5",   inner_lt =160,
      shine_f ="RROCK03",  shine_w ="METAL6",  shine_lt =160,
      pillar_f="FLOOR7_1", pillar_w="TEKLITE", pillar_lt=240,
      shine_side="METAL2", light_w ="LITEBLU4", kind=8,
    },
  },

  statue_tech_jr_BLUE_METAL =
  {
    prefab = "STATUE_TECH_JR",
    environment = "indoor",
    add_mode = "island",
    min_height = 160,
    max_height = 480,
    theme_probs = { TECH=70 },

    skin =
    {
      outer_f ="CEIL5_1",  outer_w ="METAL5",   outer_lt =176,
      tech_f  ="FLAT14",   tech_w  ="TEKWALL4", tech_lt  =255,
      tech_c  ="FLAT14",   beam_w  ="SUPPORT3",
      lite_f  ="FLAT14",   lite_w  ="LITEBLU4",
      shine_f ="RROCK03",  shine_w ="METAL6",   shine_lt =144,
      shine_side="METAL2", kind=3,
    },
  },

  pond_medium_GRASS =
  {
    prefab = "POND_MEDIUM",
    environment = "outdoor",
    skin = 
    {
      pond_w="BROWNHUG", pond_w2="ZIMMER2",
      pond_f="RROCK18",  pond_f2="RROCK19",
      outer_w="ZIMMER2", liquid_f="FWATER1",
      kind=0
    },
    theme_probs = { NATURE=100 },
  },
  
  pond_large_GRASS =
  {
    prefab = "POND_LARGE",
    environment = "outdoor",
    theme_probs = { NATURE=170 },
    skin = 
    {
      pond_w="ZIMMER2", pond_f="RROCK19",
      outer_w="BROWNHUG", liquid_f="FWATER1",
      kind=0
    },
  },

  four_sided_pic_ADOLF =
  {
    prefab = "WALL_PIC_FOUR_SIDED",
    environment = "outdoor",
    add_mode = "island",
    min_height = 192,

    skin = { pic_w="ZZWOLF7" },
    theme_probs = { WOLF=40, URBAN=5 },
    force_dir = 2, -- optimisation
  },

-- Test here --

  four_sided_pic_BARON =
  {
    prefab = "WALL_PIC_FOUR_SIDED",
    environment = "outdoor",
    add_mode = "island",
    min_height = 192,

    skin = { pic_w="MARBFAC3" },
    theme_probs = { HELL=50, URBAN=15 },
    force_dir = 2, -- optimisation
  },

  four_sided_pic_DEMON =
  {
    prefab = "WALL_PIC_FOUR_SIDED",
    environment = "outdoor",
    add_mode = "island",
    min_height = 192,

    skin = { pic_w="MARBFACE" },
    theme_probs = { HELL=50, URBAN=15 },
    force_dir = 2, -- optimisation
  },

  four_sided_pic_UAC =
  {
    prefab = "WALL_PIC_FOUR_SIDED",
    environment = "outdoor",
    add_mode = "island",
    min_height = 192,

    skin = { pic_w="SHAWN1" },
    theme_probs = { TECH=50, URBAN=5 },
    force_dir = 2, -- optimisation
  },

  four_sided_pic_VILE =
  {
    prefab = "WALL_PIC_FOUR_SIDED",
    environment = "outdoor",
    add_mode = "island",
    min_height = 192,

    skin = { pic_w="MARBFAC2" },
    theme_probs = { HELL=20, URBAN=15 },
    force_dir = 2, -- optimisation
  },

-- End test --

  skylight_mega_METALWOOD =
  {
    prefab = "SKYLIGHT_MEGA_2",
    environment = "indoor",
    add_mode = "island",
    min_height = 96,

    skin =
    { 
      sky_c = "F_SKY1",
      frame_w = "METAL", frame_c = "CEIL5_2",
      beam_w = "WOOD12", beam_c = "FLAT5_2",
    },

    prob = 10,
  },

  comp_desk_USHAPE2 =
  {
    prefab = "COMPUTER_DESK_HUGE",
    add_mode = "island",
    theme_probs = { TECH=40, INDUSTRIAL=10 },

    skin   =
    {
      comp_Nf="CONS1_1", comp_Wf="CONS1_7",
      comp_Sf="CONS1_5",
      comp_cf="COMP01", side_w ="SHAWN2"
    },
    pickup_specialness = 60,
    force_dir = 2,
  },

  cage_large_METAL =
  {
    prefab = "CAGE_LARGE",
    add_mode = "island",
    min_height = 176,
    is_cage = true,

    skin =
    {
      cage_w = "METAL",
      cage_f = "CEIL5_2",

      rail_w = "MIDBARS3",
    },

    prob = 1,
    force_dir = 2, -- optimisation
  },

  cage_large_liq_NUKAGE =
  {
    prefab = "CAGE_LARGE_W_LIQUID",
    add_mode = "island",
    min_height = 256,
    is_cage = true,

    skin =
    {
      liquid_f = "NUKAGE1",

      cage_w = "SLADWALL",
      cage_f = "CEIL5_2",
      cage_sign_w = "SLADPOIS",

      rail_w = "MIDBARS3",
    },

    prob = 4,
    force_dir = 2, -- optimisation
  },

  cage_medium_liq_BLOOD =
  {
    prefab = "CAGE_MEDIUM_W_LIQUID",
    add_mode = "island",
    min_height = 160,
    is_cage = true,

    skin =
    {
      liquid_f = "BLOOD1",

      cage_w = "GSTFONT1",
      cage_f = "FLOOR7_2",

      rail_w = "MIDBARS3",
    },

    prob = 2,
    force_dir = 2, -- optimisation
  },

  cage_medium_liq_LAVA =
  {
    prefab = "CAGE_MEDIUM_W_LIQUID",
    add_mode = "island",
    min_height = 160,
    is_cage = true,

    skin =
    {
      liquid_f = "LAVA1",

      cage_w = "BRNPOIS",
      cage_f = "CEIL5_2",

      rail_w = "MIDBARS3",
    },

    prob = 2,
    force_dir = 2, -- optimisation
  },
}


D2_FEATURE_PREFABS =
{
  overhang3_METAL6 =
  {
    prefab = "OVERHANG_3",
    environment = "outdoor",
    add_mode = "island",
    min_height = 128,
    max_height = 320,

    skin =
    {
      beam_w = "METAL",
      hang_u = "METAL6",
      hang_c = "CEIL5_1",
    },

    pickup_specialness = 35,
    theme_probs = { URBAN=30 },
  },

  billboard_stilts4_WREATH =
  {
    prefab = "BILLBOARD_STILTS_HUGE",
    environment = "outdoor",
    add_mode = "island",
    min_height = 160,

    skin =
    {
      pic_w  = "ZZWOLF13", pic_offset_h = 128,
      beam_w = "WOOD1", beam_f = "FLAT5_2",
    },

    theme_probs = { WOLF=3 },
    pickup_specialness = 61,
    force_dir = 2, -- optimisation
  },

  statue_tech1 =
  {
    prefab = "STATUE_TECH_1",
    environment = "indoor",
    min_height = 176,
    max_height = 248,

    skin =
    {
      wall="COMPWERD", floor="FLAT14", ceil="FLOOR4_8",
      step_w="STEP1", carpet_f="FLOOR1_1",
      
      comp_w="SPACEW3", comp2_w="COMPTALL", span_w="COMPSPAN",
      comp_f="CEIL5_1", lite_c="TLITE6_5",

      lamp_t="lamp"
    },
    
    theme_probs = { TECH=80, INDUSTRIAL=20 },
    force_dir = 2, -- optimisation
  },

  statue_tech2 =
  {
    prefab = "STATUE_TECH_2",
    environment = "indoor",
    min_height = 160,
    max_height = 256,

    skin =
    {
      wall="METAL", floor="FLAT23", ceil="FLAT23",
      outer_w="STEP4",

      carpet_f="FLAT14", lite_c="TLITE6_5",

      tv_w="SPACEW3", tv_f="CEIL5_1",
      span_w="COMPSPAN", span_f="FLAT4",
    },

    theme_probs = { TECH=80, INDUSTRIAL=20 },
    force_dir = 2, -- optimisation
  },

  machine_pump1 =
  {
    prefab = "MACHINE_PUMP",
    environment = "indoor",
    add_mode = "island",
    theme_probs = { INDUSTRIAL=80, TECH=20 },

    min_height = 192,
    max_height = 240,

    skin =
    {
      ceil="FLAT1",

      metal3_w="METAL3", metal_f="CEIL5_1",
      metal4_w="METAL4", metal_c="CEIL5_1",
      metal5_w="METAL5",

      pump_w="SPACEW4", pump_c="FLOOR3_3",
      beam_w="DOORSTOP",

      kind=48 -- scroll left
    },

  },

  pillar_double_TEKLITE =
  {
    prefab = "PILLAR_DOUBLE_TECH_LARGE",
    environment = "indoor",
    add_mode = "island",
    min_height = 160,
    theme_probs = { TECH=90, INDUSTRIAL=10 },

    skin =
    {
      outer_f ="FLOOR0_3", outer_w ="STEP4",   outer_lt =160,
      inner_f ="FLOOR0_2", inner_w ="STEP5",   inner_lt =160,
      shine_f ="RROCK03",  shine_w ="METAL6",  shine_lt =160,
      pillar_f="FLOOR7_1", pillar_w="TEKLITE", pillar_lt=240,
      shine_side="METAL2", light_w ="LITEBLU4", kind=8,
    },
  },

  statue_tech_jr_BLUE_METAL =
  {
    prefab = "STATUE_TECH_JR",
    environment = "indoor",
    add_mode = "island",
    min_height = 160,
    max_height = 480,
    theme_probs = { TECH=70 },

    skin =
    {
      outer_f ="CEIL5_1",  outer_w ="METAL5",   outer_lt =176,
      tech_f  ="FLAT14",   tech_w  ="TEKWALL4", tech_lt  =255,
      tech_c  ="FLAT14",   beam_w  ="SUPPORT3",
      lite_f  ="FLAT14",   lite_w  ="LITEBLU4",
      shine_f ="RROCK03",  shine_w ="METAL6",   shine_lt =144,
      shine_side="METAL2", kind=3,
    },
  },

  pond_medium_GRASS =
  {
    prefab = "POND_MEDIUM",
    environment = "outdoor",
    skin = 
    {
      pond_w="BROWNHUG", pond_w2="ZIMMER2",
      pond_f="RROCK18",  pond_f2="RROCK19",
      outer_w="ZIMMER2", liquid_f="FWATER1",
      kind=0
    },
    theme_probs = { NATURE=100 },
  },
  
  pond_large_GRASS =
  {
    prefab = "POND_LARGE",
    environment = "outdoor",
    theme_probs = { NATURE=170 },
    skin = 
    {
      pond_w="ZIMMER2", pond_f="RROCK19",
      outer_w="BROWNHUG", liquid_f="FWATER1",
      kind=0
    },
  },

  four_sided_pic_ADOLF =
  {
    prefab = "WALL_PIC_FOUR_SIDED",
    environment = "outdoor",
    add_mode = "island",
    min_height = 192,

    skin = { pic_w="ZZWOLF7" },
    theme_probs = { WOLF=40 },
    force_dir = 2, -- optimisation
  },

  skylight_mega_METALWOOD =
  {
    prefab = "SKYLIGHT_MEGA_2",
    environment = "indoor",
    add_mode = "island",
    min_height = 96,

    skin =
    { 
      sky_c = "F_SKY1",
      frame_w = "METAL", frame_c = "CEIL5_2",
      beam_w = "WOOD12", beam_c = "FLAT5_2",
    },

    prob = 10,
  },

  comp_desk_USHAPE2 =
  {
    prefab = "COMPUTER_DESK_HUGE",
    add_mode = "island",
    skin   =
    {
      comp_Nf="CONS1_1", comp_Wf="CONS1_7",
      comp_Sf="CONS1_5",
      comp_cf="COMP01", side_w ="SILVER1"
    },
    pickup_specialness = 60,
    force_dir = 2,
  },

  cage_large_METAL =
  {
    prefab = "CAGE_LARGE",
    add_mode = "island",
    min_height = 176,
    is_cage = true,

    skin =
    {
      cage_w = "METAL",
      cage_f = "CEIL5_2",

      rail_w = "MIDBARS3",
    },

    prob = 1,
    force_dir = 2, -- optimisation
  },

  cage_large_liq_NUKAGE =
  {
    prefab = "CAGE_LARGE_W_LIQUID",
    add_mode = "island",
    min_height = 240,
    is_cage = true,

    skin =
    {
      liquid_f = "NUKAGE1",

      cage_w = "SLADWALL",
      cage_f = "CEIL5_2",
      cage_sign_w = "SLADPOIS",

      rail_w = "MIDBARS3",
    },

    prob = 4,
    force_dir = 2, -- optimisation
  },

  cage_large_liq_NUKAGE_short =
  {
    prefab = "CAGE_LARGE_W_LIQUID_SHORT",
    add_mode = "island",
    min_height = 176,
    is_cage = true,

    skin =
    {
      liquid_f = "NUKAGE1",

      cage_w = "SLADWALL",
      cage_f = "CEIL5_2",
      cage_sign_w = "SLADPOIS",

      rail_w = "MIDBARS3",
    },

    prob = 3,
    force_dir = 2, -- optimisation
  },

  cage_medium_liq_BLOOD =
  {
    prefab = "CAGE_MEDIUM_W_LIQUID",
    add_mode = "island",
    min_height = 176,               
    is_cage = true,

    skin =
    {
      liquid_f = "BLOOD1",

      cage_w = "GSTFONT1",
      cage_f = "FLOOR7_2",

      rail_w = "MIDBARS3",
    },

    prob = 2,
    force_dir = 2, -- optimisation
  },

  cage_medium_liq_LAVA =
  {
    prefab = "CAGE_MEDIUM_W_LIQUID",
    add_mode = "island",
    min_height = 176,              
    is_cage = true,

    skin =
    {
      liquid_f = "LAVA1",

      cage_w = "BRNPOIS",
      cage_f = "CEIL5_2",

      rail_w = "MIDBARS3",
    },

    prob = 2,
    force_dir = 2, -- optimisation
  },
 
cage_medium_liq_WATER =          
  {
    prefab = "CAGE_MEDIUM_W_LIQUID_POSTS",
    add_mode = "island",
    min_height = 176,              
    is_cage = true,

    skin =
    {
      liquid_f = "FWATER1",

      cage_w = "FIREMAG1",
      cage_f = "FWATER1",

      rail_w = "MIDBARS3",
    },

    prob = 2,
    force_dir = 2, -- optimisation
  },

cage_medium_liq_SLIME =            
  {
    prefab = "CAGE_MEDIUM_W_LIQUID_POSTS",    
    add_mode = "island",
    min_height = 176,              
    is_cage = true,

    skin =
    {
      liquid_f = "NUKAGE1",

      cage_w = "SFALL1",
      cage_f = "NUKAGE1",

      rail_w = "MIDBARS3",
    },

    prob = 2,
    force_dir = 2, -- optimisation
  },

hangman_post =                       

  {
    prefab = "HANGMAN",
    environment = "indoor",
    min_height = 104,
    max_height = 240,    
    skin =
    {
      crate_g = "WOOD1",
      crate_w = "WOOD1",
      crate_f = "FLOOR7_1",
      scenery = "hang_twitching"

    },
    prob = 2, 
},

}

D2_WALL_PREFABS =
{
  solid_STUCCO2 =
  {
    prefab = "SOLID", skin = { wall="STUCCO2" },
  },
  
  solid_TEKGREN3 =
  {
    prefab = "SOLID", skin = { wall="TEKGREN3" },
  },
  
  solid_TEKGREN4 =
  {
    prefab = "SOLID", skin = { wall="TEKGREN4" },
  },
  
  solid_TEKGREN5 =
  {
    prefab = "SOLID", skin = { wall="TEKGREN5" },
  },
  
  solid_PANEL8 =
  {
    prefab = "SOLID", skin = { wall="PANEL8" },
  },
  
  solid_PANEL9 =
  {
    prefab = "SOLID", skin = { wall="PANEL9" },
  },

 
  wall_pic_TV =
  {
    prefab = "WALL_PIC",
    min_height = 160,
    skin = { pic_w="SPACEW3", lite_w="LITE3", pic_h=128 },
    theme_probs = { TECH=90, INDUSTRIAL=30 },
  },

  wall_pic_SLOP1 =
  {
    prefab = "WALL_PIC",
    min_height = 160,
    skin = { pic_w="SLOPPY1", lite_w="METAL", pic_h=128 },
    theme_probs = { HELL=40 },
  },

  wall_pic_SLOP2 =
  {
    prefab = "WALL_PIC",
    min_height = 160,
    skin = { pic_w="SP_FACE2", lite_w="METAL", pic_h=128 },
    theme_probs = { HELL=30 },
  },


  wall_pic_2S_EAGLE =
  {
    prefab = "WALL_PIC_SHALLOW",
    min_height = 160,
    skin = { pic_w="ZZWOLF6", lite_w="LITE5", pic_h=128 },

    theme_probs = { WOLF=8 }, 
  },

  wall_pic_SPDUDE7 =
  {
    prefab = "WALL_PIC",
    min_height = 160,
    theme_probs = { HELL=40, CAVE=5 },
    skin = { pic_w="SP_DUDE7", lite_w="METAL", pic_h=128 },
  },

  wall_pic_SPDUDE8 =
  {
    prefab = "WALL_PIC",
    min_height = 160,
    theme_probs = { HELL=40, CAVE=5 },
    skin = { pic_w="SP_DUDE8", lite_w="METAL", pic_h=128 },
  },

  cage_niche_MIDGRATE =
  {
    prefab = "CAGE_NICHE",
---  environment = "indoor",
    add_mode = "wall",
    is_cage = true,

    min_height = 160,

    skin =
    {
      rail_w = "MIDGRATE",
      rail_h = 128,
    },

    prob = 2,
  },
}

D2_DOOR_PREFABS =
{
  spacey =
  {
    w=64, h=112, prefab="DOOR_LIT_NARROW",

    skin =
    {
      door_w="SPCDOOR3", door_c="FLAT23",
      lite_w="LITE5", step_w="STEP1",
      frame_f="FLAT1", frame_c="TLITE6_6",
      track_w="DOORTRAK",
      door_h=112,
      door_kind=1, tag=0,
    },

    theme_probs = { TECH=60,INDUSTRIAL=5 },
  },

  wolfy =
  {
    w=128, h=128, prefab="DOOR_WOLFY",

    skin =
    {
      door_w="ZDOORF1", door_c="FLAT23",
      back_w="ZDOORB1", trace_w="ZZWOLF10",
      door_h=128,
      door_kind=1, tag=0,
    },

    theme_probs = { WOLF=50 },
  },

  techbronze1 =
  {
    w=128, h=112, prefab="DOOR_LIT",

    skin =
    {
      door_w="TEKBRON1", door_c="CRATOP2",
      lite_w="LITE5", step_w="STEP4",
      frame_f="SLIME15", frame_c="TLITE6_6",
      track_w="METAL2",
      door_h=112,
      door_kind=1, tag=0,
    },

    theme_probs = { INDUSTRIAL=20,TECH=90,URBAN=10 },
  },

  techbronze2 =
  {
    w=128, h=112, prefab="DOOR_LIT",

    skin =
    {
      door_w="TEKBRON2", door_c="CRATOP2",
      lite_w="LITE5", step_w="STEP4",
      frame_f="SLIME14", frame_c="TLITE6_6",
      track_w="METAL2",
      door_h=112,
      door_kind=1, tag=0,
    },

    theme_probs = { INDUSTRIAL=20,TECH=90,URBAN=10 },
  },

  woodlion =
  {
    w=128, h=112, prefab="DOOR",

    skin =
    {
      door_w="WOODMET2", door_c="CEIL5_2",
      lite_w="LITE5", step_w="STEP4",
      frame_f="FLAT1", frame_c="TLITE6_6",
      track_w="METAL",
      door_h=112,
      door_kind=1, tag=0,
    },

    theme_probs = { URBAN=35,NATURE=15,HELL=50 },
  },

}

D2_MISC_PREFABS =
{
  fence_wire_STD =
  {
    prefab = "FENCE_RAIL",
    skin = { rail_w="MIDBARS3" },
  },
  
  exit_hole_SKY =
  {
    prefab = "EXIT_HOLE_ROUND",
    add_mode = "island",

    skin =
    {
      hole_f="F_SKY1",
      walk_kind = 52  -- exit_W1
    },

--FIXME  HOLE.is_cage = true  -- don't place items/monsters here
  },

  end_switch_667 =
  {
    prefab = "DOOM2_667_END_SWITCH",
    add_mode = "island",

    skin =
    {
      switch_w="SW1SKIN", switch_f="SFLR6_4",
      kind=9, tag=667,
    }
  },
}

D2_ROOMS =
{
  PLANT =
  {
    sc_fabs =
    {
      crate_TV = 50,
      comp_desk_EW8 = 30,
      comp_desk_EW2 = 30,
      comp_desk_NS6 = 30,
      comp_desk_USHAPE1 = 20,
      other = 30
    },

    wall_fabs =
    {
      wall_pic_TV = 30, 
      other = 100
    },
  },

  COMPUTER =
  {
    pf_count = { 2,4 },

    sc_fabs =
    {
      comp_tall_STATION1 = 10, comp_tall_STATION2 = 10,
      comp_thin_STATION1 = 30, comp_thin_STATION2 = 30,

      other = 50
    },

    wall_fabs =
    {
      wall_pic_TV = 30, 
      other = 100
    },
  },

  TORTURE =
  {
    space_range = { 60, 90 },

    sc_count = { 6,16 },

    scenery =
    {
      impaled_human  = 40, impaled_twitch = 40,
      gutted_victim1 = 40, gutted_victim2 = 40,
      gutted_torso1  = 40, gutted_torso2  = 40,
      gutted_torso3  = 40, gutted_torso4  = 40,

      hang_arm_pair  = 40, hang_leg_pair  = 40,
      hang_leg_gone  = 40, hang_leg       = 40,
      hang_twitching = 40,

---   pool_blood_1  = 10, pool_blood_2  = 10, pool_brains = 10,

      other = 50
    },

    sc_fabs =
    {
      pillar_SPDUDE5=30, other=50
    },

    wall_fabs =
    {
      cage_niche_MIDGRATE = 50,
      wall_pic_SPDUDE1 = 20, wall_pic_SPDUDE2 = 20,
      wall_pic_SPDUDE7 = 30, wall_pic_SPDUDE8 = 30,

      other = 50
    },
  },

  PRISON =
  {
    space_range = { 40, 80 },

    sc_fabs =
    {
      cage_pillar_METAL=50, other=10
    },

    wall_fabs =
    {
      cage_niche_MIDGRATE = 50, other = 10
    },
  },

  WAREHOUSE2 =
  {
    space_range = { 80, 99 },

    pf_count = { 5,10 },

    -- crate it up baby!
    sc_fabs =
    {
      crate_WOOD3 = 50,
      crate_WOODMET1 = 40,
      crate_WOODSKULL = 30,
      crate_big_WOOD10 = 25,
	secret_enclosure_17_crate_big=30,
	secret_enclosure_11_crate_woodskull=25,
	
      crate_rotate_WOOD3 = 10,
      crate_rot22_WOODMET1 = 15,

      other = 20
    },
  },

  -- TODO: check in-game level names for ideas
}

D2_THEMES =
{
}

------------------------------------------------------------

D2_QUESTS =
{
  key =
  {
    k_blue=50, k_red=50, k_yellow=50
  },
  key2 =
  {
    kc_blue=50, kc_red=50, kc_yellow=50
  },

  switch =
  {
    sw_blue=50,     sw_hot=30,
    sw_vine=10,     sw_gray=20,
    sw_metl=50,     sw_metl_2=25,     
    
    sw_brick_wht_D2=20,sw_compspan_D2=20,
    sw_brick_red_D2=20,sw_fireblue_D2=25,
    sw_bloodred_D2=25, sw_bloodgrn_D2=15,
    sw_skin_D2=40,  sw_wood_D2=30, 
    sw_stone_D2=20, sw_rock_D2=20,
    sw_cement9_D2=20,
  },

  weapon =
  {
    saw=10, super=65, launch=80, plasma=60, bfg=5
  },

  item =
  {
    blue_armor=60, invis=25, mega=25, backpack=30,
    berserk=15, goggle=3, invul=3, map=15, 
  },
}

D2_EPISODE_THEMES =
{
  { URBAN=4, INDUSTRIAL=4, TECH=9, NATURE=3, CAVE=1, HELL=0 },
  { URBAN=9, INDUSTRIAL=5, TECH=7, NATURE=5, CAVE=2, HELL=1 },
  { URBAN=3, INDUSTRIAL=2, TECH=5, NATURE=3, CAVE=6, HELL=9 },

  -- this entry used for a single episode or level
  { URBAN=5, INDUSTRIAL=5, TECH=5, NATURE=5, CAVE=4, HELL=5 },
}

D2_SECRET_KINDS =
{
  MAP31 = "wolfy",
  MAP32 = "wolfy",
}

D2_SECRET_EXITS =
{
  MAP15 = true,
  MAP31 = true,
}

D2_LEVEL_BOSSES =
{
  MAP30 = "cyber", --"boss_brain",
}

D2_LEVEL_BOSSES_INSANE =
{
  MAP30 = "cyber",
}

D2_SKY_INFO =
{
    { color="brown",  light=176 },
    { color="gray",   light=155 }, -- bright clouds + dark buildings
    { color="red",    light=192 },
}

D2_EPISODE_INFO =
{
  { start=1,  len=11 },
  { start=12, len=11 },  -- last two are MAP31, MAP32
  { start=21, len=10 },
}

function doom2_get_levels(episode)
  assert(GAME.sky_info)

  local level_list = {}

  local theme_probs = D2_EPISODE_THEMES[episode]
  if SETTINGS.length ~= "full" then
    theme_probs = D2_EPISODE_THEMES[4]
  end
  assert(theme_probs)

  local ep_start  = D2_EPISODE_INFO[episode].start
  local ep_length = D2_EPISODE_INFO[episode].len

  for map = 1,ep_length do
    local Level =
    {
      name = string.format("MAP%02d", ep_start + map-1),

      episode   = episode,
      ep_along  = map,
      ep_length = ep_length,

      theme_probs = theme_probs,

      -- allow TNT and Plutonia to override the sky stuff
      sky_info = GAME.sky_info[episode],

      toughness_factor = 1 + 1.5 * (map-1) / (ep_length-1),
    }

    -- fixup for secret levels
    if episode == 2 and map >= 10 then
      Level.name = string.format("MAP%02d", 21+map)
      Level.sky_info = D2_SKY_INFO[3]
      Level.theme_probs = { WOLF=10 }
      Level.toughness_factor = 1.2
    end
    Level.boss_kind          = D2_LEVEL_BOSSES[Level.name]
    Level.boss_kind_insane   = D2_LEVEL_BOSSES_INSANE[Level.name]
    Level.secret_kind        = D2_SECRET_KINDS[Level.name]
    Level.secret_exit        = D2_SECRET_EXITS[Level.name]


if SETTINGS.questlength == "long" then
	std_decide_quests(Level, D2_QUESTS, DM_QUEST_LEN_PROBS_LONG)
elseif SETTINGS.questlength == "short" then
	std_decide_quests(Level, D2_QUESTS, DM_QUEST_LEN_PROBS_SHORT)
else
   	std_decide_quests(Level, D2_QUESTS, DM_QUEST_LEN_PROBS)
end


    table.insert(level_list, Level)
  end

  return level_list
end


------------------------------------------------------------

GAME_FACTORIES["doom2"] = function()

  local T = doom_common_factory()

  T.episodes   = 3
  T.level_func = doom2_get_levels

  T.quests   = D2_QUESTS
  T.sky_info = D2_SKY_INFO

  T.themes   = copy_and_merge(T.themes,   D2_THEMES)
  T.rooms    = copy_and_merge(T.rooms,    D2_ROOMS)
  T.monsters = copy_and_merge(T.monsters, D2_MONSTERS)

  T.combos   = copy_and_merge(T.combos,   D2_COMBOS)
  T.hallways = copy_and_merge(T.hallways, D2_HALLWAYS)
  T.exits    = copy_and_merge(T.exits,    D2_EXITS)

  T.rails = D2_RAILS

  T.hangs   = copy_and_merge(T.hangs,   D2_OVERHANGS)
  T.crates  = copy_and_merge(T.crates,  D2_CRATES)
  T.mats    = copy_and_merge(T.mats,    D2_MATS)
  T.doors   = copy_and_merge(T.doors,   D2_DOORS)
  T.lights  = copy_and_merge(T.lights,  D2_LIGHTS)
  T.liquids = copy_and_merge(T.liquids, D2_LIQUIDS)

  T.sc_fabs   = copy_and_merge(T.sc_fabs,   D2_SCENERY_PREFABS)
  T.feat_fabs = copy_and_merge(T.feat_fabs, D2_FEATURE_PREFABS)
  T.wall_fabs = copy_and_merge(T.wall_fabs, D2_WALL_PREFABS)
  T.door_fabs = copy_and_merge(T.door_fabs, D2_DOOR_PREFABS)
  T.misc_fabs = copy_and_merge(T.misc_fabs, D2_MISC_PREFABS)

  return T
end

