----------------------------------------------------------------
-- GAME DEF : FreeDOOM 0.5
----------------------------------------------------------------
--
--  Oblige Level Maker (C) 2006,2007 Andrew Apted
--  Changes (C) 2007 - 2015 Sam Trenholme
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

FD_MONSTER_LIST =
{
  ---| fairly good |---

  "gunner",
  "ss_dude",
  "zombie", "shooter", 
  "skull",  
  "pain",
  "demon",  "spectre", "caco", 
  "arach", "revenant", "mancubus",
  "vile",
  "cyber",
  "spider",
  "barrel"

  ---| crappy but playable |---

  -- "imp",
  -- "baron",  -- not yet coloured
  -- "knight",
  -- "keen"
}

FD_LIQUIDS =
{
  water = { floor="FWATER1", wall="WFALL1" },
}

FD_SKY_INFO =
{
  { color="brown",  light=192 },
  { color="black",  light=160 },
  { color="red",    light=192 },
}

FD_ROOMS =
{
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
      hang_twitching = 40,
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
}
----------------------------------------------------------------

GAME_FACTORIES["freedoom"] = function()

  -- the FreeDOOM IWAD contains both Doom 1 and Doom 2 textures

---!!!  local T = GAME_FACTORIES.doom1()
---!!!
---!!!  T.episodes   = 3
---!!!  T.level_func = doom2_get_levels
---!!!
---!!!  T.quests   = D2_QUESTS
---!!!
---!!!  T.combos   = copy_and_merge(T.combos,   D2_COMBOS)
---!!!  T.exits    = copy_and_merge(T.exits,    D2_EXITS)
---!!!  T.hallways = copy_and_merge(T.hallways, D2_HALLWAYS)
---!!!
---!!!  T.rails = copy_and_merge(T.rails, D2_RAILS)
---!!!
---!!!  T.hangs   = copy_and_merge(T.hangs,   D2_OVERHANGS)
---!!!  T.mats    = copy_and_merge(T.mats,    D2_MATS)
---!!!  T.crates  = copy_and_merge(T.crates,  D2_CRATES)
---!!!
---!!!  T.liquids = copy_and_merge(T.liquids, D2_LIQUIDS, FD_LIQUIDS)

  -- TEMPORARY HACK
  local T = GAME_FACTORIES.doom2()

  T.sky_info = FD_SKY_INFO
  T.rooms  = copy_and_merge(T.rooms, FD_ROOMS)  -- This is here until all the hanging sprites are done

  -- FreeDOOM is lacking many monster sprites

  T.monsters = {}
  
  for zzz,mon in ipairs(FD_MONSTER_LIST) do
    T.monsters[mon] = DM_MONSTERS[mon] or D2_MONSTERS[mon]
  end

  return T
end

