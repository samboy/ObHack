----------------------------------------------------------------
-- PLANNER : Single Player
----------------------------------------------------------------
--
--  Oblige Level Maker (C) 2006,2007 Andrew Apted
--  Changes (C) 2007-2020 Sam Trenholme
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


function show_quests(quests)

  if not quests then
    if PLAN.deathmatch then
      con.printf("Deathmatch Quest: frag fest!\n")
      return
    end

    con.printf("Quests:\n")

    quests = PLAN.quests
  end

  for zzz,Q in ipairs(quests) do
    con.printf("  %s %s : len:%d kind:%s (%s)%s%s\n",
        (Q.mode and string.upper(Q.mode)) or sel(Q.parent, "SUB", "MAIN"),
        (Q.level and string.format("%d.%d", Q.level, Q.sub_level)) or "",
        Q.want_len, Q.kind, tostring(Q.item),
        Q.is_secret and " SECRET" or "",
        Q.force_key and (" force_key:" .. Q.force_key) or ""
    )
  end

  con.printf("\nEND SHOW QUESTS\n");
end


function show_path(x)

  local function show_cell(c)
    if (c == nil) then
      con.printf("    |")
    else
      local kind, L, R = " ", " ", " "

          if c.dm_player then kind = "P"
      elseif c.dm_weapon then kind = "W"
      elseif c.scenic    then kind = "C"
      elseif c.is_depot  then kind = "D"
      elseif c == c.quest.first then kind = "S"
      elseif c ~= c.quest.last then
            if c.quest.is_secret then kind = "z"
        elseif c.hallway then kind = "h"
        elseif c.quest.parent then kind = "q"
        else kind = "p"
        end
      elseif c.quest.kind == "exit" then kind = "E"
      elseif c.quest.kind == "boss" then kind = "B"
      elseif c.quest.kind == "item" or
             c.quest.kind == "weapon" then kind = "W"
      elseif c.quest.kind == "switch" or
             c.quest.kind == "key" then kind = "K"
      elseif c.quest.kind == "gate" or
             c.quest.kind == "back" then kind = "G"
      else kind = "?"
      end
          if c.exit_dir == 2 then R = "v"
      elseif c.exit_dir == 8 then R = "^"
      elseif c.exit_dir == 4 then R = "<"
      elseif c.exit_dir == 6 then R = ">"
      end

      if c == c.quest.path[2] then
            if c.entry_dir == 2 then L = "v"
        elseif c.entry_dir == 8 then L = "^"
        elseif c.entry_dir == 4 then L = "<"
        elseif c.entry_dir == 6 then L = ">"
        end
      end
      if R == "<" or L == ">" then L,R = R,L end

      con.printf("%s", L .. kind .. c.quest.level .. R .. "|")
    end
  end

  local function divider(len)
    for i = len,1,-1 do
      con.printf("----+")
    end
    con.printf("\n")
  end

  -- BEGIN show_path --

  if x ~= nil then 
	show_cell(x) 
	return
  end

  divider(PLAN.w)

  for y = PLAN.h,1,-1 do
    for x = 1,PLAN.w do
      show_cell(PLAN.cells[x][y])
    end
    con.printf("\n")
    divider(PLAN.w)
  end
  con.printf("\nEND SHOW PATH\n")
end


function show_chunks()

  local function show_cell(c,ky)

    local function chk(kx)
      if not c or not c.chunks then return " " end

      local K = c.chunks[kx][ky]
      assert(K)

      if not K.kind then return "!" end

      if K.kind == "empty" then return " " end
--[[
      if K.stair_dir == 2 then return "v" end
      if K.stair_dir == 8 then return "^" end
      if K.stair_dir == 4 then return "<" end
      if K.stair_dir == 6 then return ">" end
--]]
      if K.kind == "void"   then return "x" end
      if K.kind == "room"   then return "5" end
      if K.kind == "liquid" then return "~" end

      if K.kind == "closet" then return "C" end
      if K.kind == "cage"   then return "G" end
      if K.kind == "vista"  then return "V" end

      if K.kind == "player" then return "P" end
      if K.kind == "quest"  then return "T" end
      if K.kind == "exit"   then return "E" end

      if K.link then
-- if K.link.build == c then return "/" end
-- if K.link.src.floor_h == K.link.dest.floor_h then return "/" end

        if K.link == c.link[2] then return "2" end
        if K.link == c.link[8] then return "8" end
        if K.link == c.link[4] then return "4" end
        if K.link == c.link[6] then return "6" end
      end

      return "?"
    end

    for x = 1,3 do
      con.printf("%s", chk(x))
    end
    con.printf("|")
  end

  local function divider(len)
    for i = len,1,-1 do
      for x = 1,3 do
        con.printf("-")
      end
      con.printf("+")
    end
    con.printf("\n")
  end

  -- BEGIN show_cell --

  divider(PLAN.w)

  for y = PLAN.h,1,-1 do
    for row = 3,1,-1 do
      for x = 1,PLAN.w do
        show_cell(PLAN.cells[x][y], row)
      end
      con.printf("\n")
    end
    divider(PLAN.w)
  end
  con.printf("\nEND SHOW_CHUNKS\n")
end

function show_cell_blocks(c)

  local function chk(B)
    if not B then return "!" end
    if B.walk then return tostring(B.walk) end
    if B.solid then return "#" end
    if B.fragments then return "%" end
    if B.f_tex then return "/" end
    if B.has_blocker then return "B" end

    if not B.chunk then return "?" end
    if B.chunk.kind == "vista" then return "V" end
    if B.chunk.kind == "void"  then return "x" end

    return "." -- unused
  end

  con.printf("CELL BLOCKS @ (%d,%d)\n", c.x, c.y)

  for y = c.by2,c.by1,-1 do
    for x = c.bx1,c.bx2 do
      con.printf("%s", chk(PLAN.blocks[x][y]))
    end
    con.printf("\nEND SHOW_CELL_BLOCKS\n")
  end
end


function random_cell()
  return rand_irange(1, PLAN.w), rand_irange(1, PLAN.h)
end

function empty_loc()  ---### UNUSED
  for loop = 1,999 do
    local x,y = random_cell()
    if not PLAN.cells[x][y] then return x, y end
  end
end


function link_other(link, cell)
  if link.cells[1] == cell then return link.cells[2] end
  if link.cells[2] == cell then return link.cells[1] end
  return nil
end

function links_in_cell(c)
  local count = 0
  for dir = 2,8,2 do
    if c.link[dir] then count = count + 1 end
  end
  return count
end


function get_base_plan(level, plan_size, cell_size)

  local cw = plan_size
  local ch = plan_size

  local Plan =
  {
    level = level,

    w = cw,
    h = ch,

    blk_w = BORDER_BLK*2 + cw * (cell_size+1) + 1,
    blk_h = BORDER_BLK*2 + ch * (cell_size+1) + 1,

    cells = array_2D(cw, ch),
    quests = {},

    all_cells  = {},
    all_depots = {},
    all_links  = {},
    all_things = {},

    f_min = 5*64,
    f_max = 5*64,

    used_items = {},
    things = {},

    free_tag = 10,
    mark = 10,
    floor_code = 1,

    cell_base_coords = function (x, y)
      local bx = BORDER_BLK + 2 + (x-1) * (cell_size+1)
      local by = BORDER_BLK + 2 + (y-1) * (cell_size+1)
      return bx,by, bx+cell_size-1, by+cell_size-1
    end,
  }

  Plan.blocks = array_2D(Plan.blk_w, Plan.blk_h)

  return Plan
end
 
function allocate_tag()
  local result = PLAN.free_tag
  PLAN.free_tag = PLAN.free_tag + 1

  return result
end

function allocate_mark()
  local result = PLAN.mark
  PLAN.mark = PLAN.mark + 1

  return result
end

function allocate_floor_code()
  local result = PLAN.floor_code
  PLAN.floor_code = PLAN.floor_code + 1

  return result
end


function std_decide_quests(Level, QUEST_TAB, LEN_PROBS)

  local function prob_tab_to_list(prob_tab)
    local tab = copy_table(prob_tab)
    local list = {}
    while not table_empty(tab) do
      local name = rand_key_by_probs(tab)
      table.insert(list, name)
      tab[name] = nil
    end
    return list
  end

  local ky_list = prob_tab_to_list(QUEST_TAB.key)
  local sw_list = prob_tab_to_list(QUEST_TAB.switch)
  local wp_list = {}
  if SETTINGS.mode == "spdm" and QUEST_TAB.weapon_spdm then
    wp_list = prob_tab_to_list(QUEST_TAB.weapon_spdm)
  else
    wp_list = prob_tab_to_list(QUEST_TAB.weapon)
  end
  local it_list = prob_tab_to_list(QUEST_TAB.item)


  -- decide how many keys, switches, weapons & items
  -- Some values below were modified

  local TOT_MINIMUMS = { tiny = 1, small = 3, regular = 4, large = 5, huge = 8
  , progressive = 1  }
  local TOT_MAXIMUMS = { tiny = 2, small = 4, regular = 6, large = 8, huge = 12
, progressive = 2 }
  --- These next two thingys only used for "tiny" and "small"
  local TOT_KEYS = { tiny = 0, small = 2, regular = 2, large = 3, huge = 3, progressive= 1 }
  local TOT_SWITCH = { tiny = 0, small = 2, regular = 1, large = 2, huge = 3, progressive = 0 }
  local TTT_MIN = { less = 0, normal = 1, more = 2 }
  local TTT_MAX = { less = 0, normal = 2, more = 3 }

  local tot_min = TOT_MINIMUMS[SETTINGS.size]
  local tot_max = TOT_MAXIMUMS[SETTINGS.size]
  local as_if = 0

  if SETTINGS.size == "progressive" then
	if Level.ep_along <= 1 then
		tot_min = 1
		tot_max = 1
		as_if = 1
	elseif Level.ep_along <= 2 then
		tot_min = 1
		tot_max = 2	
		as_if = 1
	elseif Level.ep_along <= 3 then
		tot_min = 2
		tot_max = 2
		as_if = 2
	elseif Level.ep_along <= 4 then
		tot_min = 2
		tot_max = 4
		as_if = 2
	elseif Level.ep_along <= 5 then
		tot_min = 3
		tot_max = 6
	elseif Level.ep_along <= 6 then
		tot_min = 4
		tot_max = 7
	elseif Level.ep_along <= 7 then
		tot_min = 5
		tot_max = 9
	elseif Level.ep_along <= 8 then
		tot_min = 7
		tot_max = 11
	else
		tot_min = 8
		tot_max = 12
	end
  end

  assert(tot_min and tot_max)
  assert(tot_min <= tot_max)

  assert(#ky_list + #sw_list + #wp_list + #it_list >= tot_min)


  local RATIO_MINIMUMS = { less=0.0, normal=0.4, more=1.0 }
  local RATIO_MAXIMUMS = { less=0.6, normal=1.2, more=2.5 }

  local ratio_min = RATIO_MINIMUMS[SETTINGS.traps]
  local ratio_max = RATIO_MAXIMUMS[SETTINGS.traps]

  assert(ratio_min and ratio_max)
  assert(ratio_min <= ratio_max)

  local keys, switches, weapons, items
  local total, ratio

  local tsthings

  --- local ky_min = 1 -- sel(SETTINGS.traps == "less", 0, 1) --- Commented out since it's not needed

  for loop = 1,999 do


  if SETTINGS.size == "tiny" or SETTINGS.size == "small" or as_if > 0 then
    tsthings = 0
    weapons  = rand_irange(0,      #wp_list)
    items    = rand_irange(0,      #it_list)
    if weapons == 0 and items == 0 then weapons = 1 end --- Make sure we have at least one weapon or item
    if as_if == 0 then
	keys = 1
	switches = 0
    else
	keys = as_if - 1
	switches = 0
    end
  else
    tsthings = 1
    keys     = rand_irange(0,      #ky_list)
    switches = rand_irange(0,      #sw_list)

    weapons  = rand_irange(1,      #wp_list)
    if weapons == 0 then weapons = 1 end

    items    = rand_irange(1,      #it_list)
    if items == 0 then items = 1 end
  end

    total    = keys + switches + weapons + items
    ratio    = (keys + switches) / (weapons + items)

--- Hack to fix a problem with "Few" mode under Puzzles with Small levels
--- If this is not here, then Small levels will never have keys or switches

   ---if SETTINGS.traps ~= "normal" and rand_irange(1,100) <= 75 then
   ---  keys = rand_irange(TTT_MIN[SETTINGS.traps],TTT_MAX[SETTINGS.traps])
   ---end
 
    if (tot_min <= total and total <= tot_max) and
       ((ratio_min <= ratio and ratio <= ratio_max) or loop >= 900)
    then break; end
  end
 
--- This makes sure the correct number of total items and stuff appears in a level, and in the log file
--- Before, there were often too many items especially tiny or small levels
    if (total > tot_max) or (total < tot_min) then

	if SETTINGS.size ~= "small" then
		weapons = rand_irange(tsthings,tot_min)
	end
      if SETTINGS.game == "doom2" or SETTINGS.game == "freedoom" and weapons > 5 then weapons = 5 end
      if SETTINGS.game == "tnt" or SETTINGS.game == "plutonia" and weapons > 5 then weapons = 5 end
      if SETTINGS.game == "doom" or SETTINGS.game == "heretic" and weapons > 4 then weapons = 4 end

      items = rand_irange(tsthings,(tot_max - weapons))
      if SETTINGS.game == "doom2" or SETTINGS.game == "freedoom" and items > 6 then items = 6 end
      if SETTINGS.game == "tnt" or SETTINGS.game == "plutonia" and items > 6 then items = 6 end
      if SETTINGS.game == "doom" and items > 5 then items = 5 end
      if SETTINGS.game == "heretic" and items > 7 then items = 7 end

    --- Make sure we have at least one weapon or item
    if SETTINGS.size == "tiny" or SETTINGS.size == "small" and weapons == 0 and items == 0 then weapons = 1 end
    if SETTINGS.size == "regular" or SETTINGS.size == "large" or SETTINGS.size == "huge" and items == 0 then
      items = 1 
      --- weapons = weapons - 1 
    end

      keys = rand_irange(0, (tot_max - weapons - items))
      if keys > 3 then keys = 3 end

      switches = rand_irange(0,(tot_max - weapons - items - keys))
      if SETTINGS.game == "doom2" or SETTINGS.game == "freedoom" and switches > 5 then switches = 5 end
      if SETTINGS.game == "tnt" or SETTINGS.game == "plutonia" and switches > 5 then switches = 5 end
      if SETTINGS.game == "doom" and switches > 6 then switches = 6 end
      if SETTINGS.game == "heretic" and switches > 3 then switches = 3 end
    end

    --- Make sure "puzzles" affects things in tiny maps
    if SETTINGS.size == "tiny" then
	keys = 0
        switches = 0
    end
    if SETTINGS.size == "tiny" and SETTINGS.traps == "more" then
       if rand_irange(1,100) <= 60 then
	 keys = 1
       else
         switches = 1
       end
       if rand_irange(1,100) <= 50 then
	 weapons = 1
	 items = 0
       else
         items = 1
         weapons = 0
       end
    end 
    if SETTINGS.size == "tiny" and SETTINGS.traps == "normal" then
       if rand_irange(1,100) <= 40 then
         if rand_irange(1,100) <= 60 then
	   keys = 1
         else
           switches = 1
         end
         if rand_irange(1,100) <= 50 then
	   weapons = 1
	   items = 0
         else
           items = 1
	   weapons = 0
         end
       end
    end 

   if SETTINGS.size == "tiny" and weapons >= 1 then
	weapons = 1
	items = 0
   else
	items = 1
	weapons = 0
   end
   if SETTINGS.size == "tiny" and switches == 0 and keys == 0 then
	if rand_irange(1,100) <= 40 then
		weapons = weapons + 1
	else
		items = items + 1
	end
   end

	if SETTINGS.size == "small" then
		-- In small maps, we heave either 3 (puzzles + weapons + items)
                -- or 4 (puzzles + weapons + items); the number of puzzles 
		-- depends on what the user requested in the pull-down menu
		-- (This is called "traps" here for historical reasons)
		local vvn = 0 --- Keys + Switches
		if SETTINGS.traps == "less" then
			vvn = rand_irange(0,1) -- 0 or 1 puzzles
		elseif SETTINGS.traps == "normal" then
			vvn = rand_irange(1,2) -- 1 or 2 puzzles
		else 
			vvn = 2 -- 2 puzzles
		end
		if vvn == 0 then -- no puzzles
			keys = 0	
			switches = 0
		elseif vvn == 1 then -- 1 puzzle
			if rand_irange(1,100) <= 60 then
				keys = 1
				swtiches = 0
			else
				keys = 0
				switches = 1
			end
		elseif vvn == 2 then -- 2 puzzles
			local vvq = 0
			vvq = rand_irange(1,100)
			if vvq <= 45 then
				keys = 2
				switches = 0
			elseif vvq <= 75 then
				keys = 1
				switches = 1
			else	
				keys = 0
				switches = 2
			end
		end
		-- Now add items and weapons
		-- Small levels always have at least one item or weapon
		if rand_irange(1,100) <= 40 then 
			weapons = 1
			items = 0
		else
			weapons = 0
			items = 1
		end
		-- If we have 1 or 0 puzzles, add another weapon/item
		if vvn < 2 then
			if rand_irange(1,100) <= 40 then
				weapons = weapons + 1
			else
				items = items + 1
			end
		end
		-- If we 0 puzzles, add another weapon/item
		if vvn < 1 then
			if rand_irange(1,100) <= 40 then
				weapons = weapons + 1
			else
				items = items + 1
			end
		end
		-- Sometimes we have an extra weapon/item
		if rand_irange(1,100) <= 32 then
			if rand_irange(1,100) <= 40 then
				weapons = weapons + 1
			else
				items = items + 1
			end
		end		
		con.printf("Key Weapons %d Items %d\n",weapons,items)
	end

--- Combined single player and deathmatch maps
   if SETTINGS.mode == "spdm" then
     if keys + switches < 3 then	
	keys = keys + switches
	switches = 0
     else
	switches = (keys + switches) - 3
	keys = 3
     end
     weapons = weapons + items + switches
     if SETTINGS.game == "doom2" or SETTINGS.game == "freedoom" and weapons > 5 then weapons = 5 end
     if SETTINGS.game == "tnt" or SETTINGS.game == "plutonia" and weapons > 5 then weapons = 5 end
     if SETTINGS.game == "doom" or SETTINGS.game == "heretic" and weapons > 4 then weapons = 4 end
     items = 0
     switches = 0
   end

   if SETTINGS.switches == "keys" then -- Remove switches from levels 
	-- (useful for maps which are mostly SP but can also be used for DM) 
     if keys + switches < 3 then	
	keys = keys + switches
     else
	keys = 3
     end
     switches = 0
   end

   if SETTINGS.switches == "switches" then -- Remove keys from levels
     if keys + switches < #sw_list then
	switches = keys + switches
     else
	switches = #sw_list
     end
     keys = 0
   end

--- Make sure we have at least one quest in levels without exits
--- (E6M3, etc)
   if Level.no_exit and weapons < 1 then weapons = 1 end

  con.printf("Count: Keys %d, Switches %d, Weapons %d, Items %d\n",
      keys, switches, weapons, items)

  -- build the quest list

  Level.quests = {}

  local function add_quest(kind, item)
    local len_probs = non_nil(LEN_PROBS[kind])
    local Quest =
    {
      kind = kind,
      item = item,
      want_len = 1 + rand_index_by_probs(len_probs),
      along = Level.ep_along
    }
    -- Chance of a quest being secret
    if (item == "secret") or
       (kind == "weapon" and rand_odds(2)) or
       (kind == "item"   and rand_odds(10))
    then
      if SETTINGS.mode ~= "spdm" then
        Quest.is_secret = true
      end
    end

    table.insert(Level.quests, Quest)
    return Quest
  end

  -- In "spdm" mode all quest objects are weapons
  if SETTINGS.mode == "spdm" then
    weapons = items + weapons + switches
    switches = 0
    items = 0
    if weapons < keys then
      weapons = keys
    end
    if weapons < 1 then
      weapons = 1
    end
  end

--- This is a fix to make sure levels have variety in the minimum and maximum number of keys, items, etc..
--- Before, it only had "tot_max" and thus only used the maximum value.. ie. all "Regular" levels had 6 (instead of 3-6)
    for i = 1,rand_irange(tot_min,tot_max) do
      if (i <= keys)     then add_quest("key",    ky_list[i]) end
      if (i <= switches) then add_quest("switch", sw_list[i]) end
      if (i <= weapons)  then add_quest("weapon", wp_list[i]) end
      if (i <= items)    then add_quest("item",   it_list[i]) end
    end

  if Level.secret_exit then
    add_quest("exit", "secret")
  end

---  Disabled because this doesn't work; we'll wait for real arenas
---  if Level.boss_kind then
---    local Q = add_quest("exit", Level.boss_kind)
---    Q.kind = "boss" -- hackish
---  else
---  Please keep the following; (almost) every level needs an exit
  if not Level.no_exit then
    add_quest("exit", "normal")
  end
---  end

--- Make sure we have at least one secret quest per level
  iis = 0
  iid = 0
  while iis < 1 and iid < 1000 and SETTINGS.mode ~= "spdm" do
	iis = 0
  	for iia, iib in ipairs(Level.quests) do	
		if iib.is_secret == true then
			iis = iis + 1
		end
  	end
	if iis == 0 then
		for iia, iib in ipairs(Level.quests) do
			if iib.kind == "weapon" and rand_odds(10) then
				iib.is_secret = true
			end
			if iib.kind == "item" and rand_odds(10) then
				iib.is_secret = true
			end
		end
	end
	iid = iid + 1
   end
	
  return quest_list
end


function create_cell(x, y, quest, along, combo, is_depot)
  if quest.kind then
    con.printf("Creating cell at %d %d with quest %s\n",x,y,quest.kind)
  else
    con.printf("Creating cell at %d %d\n",x,y)
  end
  local CELL =
  {
    x=x, y=y,
    
    quest = quest,
    along = along,
    combo = combo,

    floor_h = 128, ceil_h = 256, -- dummy values

    link = {}, border = {}, corner = {},
    closet = {}, nudges = {}, vistas = {},
    reclaim = {},

    is_depot = is_depot,
    liquid = quest.liquid,

    monsters = {}
  }

  if is_depot then
    CELL.no_nudge = true
  end

  CELL.bx1, CELL.by1, CELL.bx2, CELL.by2 = PLAN.cell_base_coords(x, y)

  CELL.bw = CELL.bx2 - CELL.bx1 + 1
  CELL.bh = CELL.by2 - CELL.by1 + 1

  PLAN.cells[x][y] = CELL

  if is_depot then
    table.insert(PLAN.all_depots, CELL)
  else
    table.insert(PLAN.all_cells, CELL)
  end

  return CELL
end


function create_link(c, other, dir)
  local LINK =
  {
    cells = { c, other },
    kind = "arch",  -- updated later
    build = c,    -- updated later
    long = sel(GAME.caps.blocky_doors, 1, 3),
    deep = 1,
  }

  c.link[dir] = LINK
  other.link[10-dir] = LINK

  table.insert(PLAN.all_links, LINK)

  return LINK
end

function shuffle_build_sites()

  local function count_builds(c, external)
    local count = 0
    
    for side = 2,8,2 do
      local L = c.link[side]
      if L then
        if (L.build == c) == (not external) then
          count = count + 1
        end
      end
    end
    
    return count
  end

  -- shuffle_build_sites --
  
  for zzz,link in ipairs(PLAN.all_links) do

    if link.is_exit or link.is_secret or link.kind == "vista" then
      -- do not change this link
    else
      local c1 = link.cells[1]
      local c2 = link.cells[2]

      local SL = links_in_cell(c1)
      local DL = links_in_cell(c2)

      local chance = 50

          if DL > SL then chance = 33
      elseif SL > DL then chance = 66
      end

      if c1.hallway and not c2.hallway then chance =  5 end
      if c2.hallway and not c1.hallway then chance = 95 end

      link.build = rand_sel(chance, c2, c1)
    end
  end

  -- make sure cells are never devoid of build sites.
  -- Although this happens quite rarely, it can make the
  -- stair building algorithm fail.
  for loop = 1,4 do
    local modified = false

    for zzz,c in ipairs(PLAN.all_cells) do
      if count_builds(c, true) == 4 then
con.debugf("EXTERNALS @ cell (%d,%d) total=4\n", c.x,c.y)
        for tries = 1,4 do
          local dir = math.random(1,4) * 2
          local L = c.link[dir]

          if L.is_exit or L.kind == "vista" then
            -- do not change this link
          else
con.debugf("  CHANGING SIDE %d\n", dir)
            L.build = c
            modified = true
            break -- out of 'try' loop
          end
        end
      end
    end

    if not modified then break end

    con.ticker()
  end
end

function get_door_chance(c, other)

  local probs =
    c.room_type.door_probs or
    other.room_type.door_probs or
    c.combo.door_probs or
    c.quest.theme.door_probs or
    GAME.door_probs

  assert(probs)

  if c.combo.outdoor ~= other.combo.outdoor then
    return non_nil(probs.out_diff)

  elseif c.combo ~= other.combo then
    return non_nil(probs.combo_diff)

  else
    return non_nil(probs.normal)
  end
end

function get_window_chance(c, other)

  local probs =
    c.room_type.window_probs or
    other.room_type.door_probs or
    c.combo.window_probs or
    c.quest.theme.window_probs or
    GAME.window_probs

  assert(probs)

  if c.combo.outdoor ~= other.combo.outdoor then
    return non_nil(probs.out_diff)

  elseif c.combo ~= other.combo then
    return non_nil(probs.combo_diff)

  else
    return non_nil(probs.normal)
  end
end

-- FIXME: get_fence_chance(c, other) ???

function compute_height_minmax()

  local function merge_neighbour(c, other)
    c.f_min = math.min(c.f_min, other.floor_h)
    c.f_max = math.max(c.f_max, other.floor_h)
    c.c_min = math.min(c.c_min, other.ceil_h)
    c.c_max = math.max(c.c_max, other.ceil_h)
  end

  local function minmax(c)
    c.f_min = c.floor_h
    c.f_max = c.floor_h
    c.c_min = c.ceil_h
    c.c_max = c.ceil_h

    for dir = 2,8,2 do
      if c.link[dir] then
        local link = c.link[dir]
        if link.build ~= c then
          merge_neighbour(c, link_other(link,c))
        end
      end
    end
  end

  for zzz,c in ipairs(PLAN.all_cells) do
    minmax(c)
  end
end


function resize_rooms()

  local function try_nudge_cell(c, side, pass)

    -- There are three passes:
    --   1: nudge against empty cells
    --   2: nudge against another valid cell
    --   3: nudge against the map's edge

    if c.no_nudge then return end 

    if rand_odds(25) then return end

    local dx,dy = dir_to_delta(side)
    local ax,ay = dir_to_across(side)

    local ox,oy = c.x + dx, c.y + dy

    local other = neighbour_by_side(c, side)

    if other and other.no_nudge then return end

    -- already moved this edge?
    if c.nudges[side] then return end

    -- direction: +1 = outwards, -1 inwards
    local dir

    if not other then
      if valid_cell(ox, oy) then
        if pass ~= 1 then return end

        -- empty cells on the map can only be nudged in one direction
        -- (vertical or horizontal) in a checker-board pattern.  This
        -- prevents a problem of a corner needing TWO mini-borders.

        if ((ox + oy) % 2) == math.abs(dy) then return end
      else
        if pass ~= 3 then return end
      end

      -- further requirements:
      -- (a) current cell is indoor
      -- (b) neighbours of current are all indoor or empty
      -- (c) neighbours of other   are all indoor or empty

      if c.combo.outdoor then return end

      for dmul = 0,1 do for amul = -1,1,2 do
        local nx = c.x + dx*dmul + ax*amul
        local ny = c.y + dy*dmul + ay*amul

        local n = valid_cell(nx, ny) and PLAN.cells[nx][ny]

        if n and n.combo.outdoor then return end
      end end

      if c.hallway and rand_odds(66) then dir = -1 end

    else
      if pass ~= 2 then return end

      -- cannot move the border if the cells aren't aligned
      if (side == 2) or (side == 8) then
        if not (c.bx1 == other.bx1 and c.bx2 == other.bx2) then return end
      else 
        if not (c.by1 == other.by1 and c.by2 == other.by2) then return end
      end

      if (c.hallway ~= other.hallway) and rand_odds(90) then
        dir = sel(c.hallway, -1, 1)

      else
        local SL = links_in_cell(c)
        local DL = links_in_cell(other)

        if (SL ~= DL) and rand_odds(90) then
          dir = sel(SL < DL, -1, 1)
        end
      end
    end

    dir = dir or rand_sel(66, 1, -1)

    if (dir < 0 and c.no_shrink) or
       (dir > 0 and other and other.no_shrink)
    then return end

    local deep = rand_index_by_probs { 10, 30, 90 }
    local mv_x = math.abs(dx) * deep
    local mv_y = math.abs(dy) * deep

    assert(deep <= BORDER_BLK)

    -- don't make the shrinking cell too small
    local shrinker = sel(dir < 0, c, other)
    if shrinker then
      local new_w, new_h = shrinker.bw - mv_x, shrinker.bh - mv_y
      local min_size = GAME.cell_min_size

      if new_w < min_size or new_h < min_size then return end
    end

    c.nudges[side] = true
    if other then
      other.nudges[10-side] = true
    end

    dx = dx * mv_x * dir
    dy = dy * mv_y * dir

-- con.debugf("~~~~~~~ NUDGING (%d,%d) side:%d  by %d/%d\n", c.x,c.y,side,dx,dy)

    if (side == 2) or (side == 4) then
      c.bx1 = c.bx1 + dx
      c.by1 = c.by1 + dy
    else
      c.bx2 = c.bx2 + dx
      c.by2 = c.by2 + dy
    end

    c.bw = c.bx2 - c.bx1 + 1
    c.bh = c.by2 - c.by1 + 1

    if other then
      if (side == 2) or (side == 4) then
        other.bx2 = other.bx2 + dx
        other.by2 = other.by2 + dy
      else
        other.bx1 = other.bx1 + dx
        other.by1 = other.by1 + dy
      end

      other.bw = other.bx2 - other.bx1 + 1
      other.bh = other.by2 - other.by1 + 1
    end
  end

  --- resize_rooms ---

  local visit_list = {}

  for zzz,c in ipairs(PLAN.all_cells) do
    for side = 2,8,2 do
      table.insert(visit_list, { c=c, side=side })
    end
  end

  for pass = 1,3 do
    rand_shuffle(visit_list)
    for zzz,v in ipairs(visit_list) do
      try_nudge_cell(v.c, v.side, pass)
    end
  end

for zzz,cell in ipairs(PLAN.all_cells) do
con.debugf("CELL @ (%d,%d) has coords [%d,%d]..[%d,%d]\n",
cell.x, cell.y, cell.bx1, cell.by1, cell.bx2, cell.by2)
end

end


function create_corners()

  local SUB_TO_DIR = { { 1, 3 }, { 7, 9 } }
  
  local function find_corners(x, y)

    -- this table is indexed by a coordinate string, hence
    -- we can find the shared corners by looking them up.
    local shared_corners = {}

    for sub_x = 0,1 do for sub_y = 0,1 do
      local cx = x + sub_x
      local cy = y + sub_y
      local c_dir = SUB_TO_DIR[2-sub_y][2-sub_x]

      local c = valid_cell(cx,cy) and PLAN.cells[cx][cy]

      if c and not c.is_depot then
        local bx, by = corner_coords(c_dir, c.bx1, c.by1, c.bx2, c.by2)
        local dx, dy = dir_to_delta(c_dir)

        bx = bx+dx
        by = by+dy

        local b_name = string.format("%d:%d", bx, by)

        if not shared_corners[b_name] then

          shared_corners[b_name] =
          {
            bx=bx, by=by, cells={}, borders={}
          }
        end

        c.corner[c_dir] = shared_corners[b_name]
      end
    end end

    -- figure out which cells are touching which corners

     for _,b_name in ipairs(sorted_table_keys(shared_corners)) do
      local CN = shared_corners[b_name]
      for sub_x = 0,1 do for sub_y = 0,1 do
        local cx = x + sub_x
        local cy = y + sub_y
        local c = valid_cell(cx,cy) and PLAN.cells[cx][cy]

        if c and not c.is_depot and
           (CN.bx >= c.bx1-1) and (CN.by >= c.by1-1) and
           (CN.bx <= c.bx2+1) and (CN.by <= c.by2+1)
        then 
          table.insert(CN.cells, c)
        end
      end end

    end
  end

  --- create_corners ---

  for x = 0, PLAN.w do -- NOTE: goes outside the plan
    for y = 0, PLAN.h do
      find_corners(x, y)
    end
  end
end

function create_borders()

  local function get_corner_dirs(side)
        if side == 2 then return 1,3
    elseif side == 8 then return 7,9
    elseif side == 4 then return 1,7
    elseif side == 6 then return 3,9
    end
  end

  local function add_border(c, side, D, other)

    if c.border[side] then return end

    assert(D.x2 >= D.x1)
    assert(D.y2 >= D.y1)

    c.border[side] = D
    D.cells = { c }

    if D.x1 < D.x2 then
      D.long = D.x2 - D.x1 + 1
    else
      D.long = D.y2 - D.y1 + 1
    end

    if other then
      other.border[10-side] = D
      table.insert(D.cells, other)
    end
  end

--[[
Scenarios:

A.  l_cell: nil, other: OK
--> BORDER: no change
--> MINI: none

B.  l_cell: nil, other: OK
--> BORDER: limited by other's corner
--> MINI: stuff between my corner and other's corner

C.  l_cell: OK, other: XX
--> BORDER: limited by l_cell's corner
--> MINI: stuff between my corner and l_cell's corner
--]]

  local function find_borders(c)

    assert(c.bx2 >= c.bx1)
    assert(c.by2 >= c.by1)

    for side = 2,8,2 do

      local other = neighbour_by_side(c, side)

      local dx,dy = dir_to_delta(side)

      local cx1,cy1, cx2,cy2 = side_coords(side, c.bx1,c.by1, c.bx2,c.by2)

      cx1, cy1 = cx1+dx, cy1+dy
      cx2, cy2 = cx2+dx, cy2+dy

      local l_dir, h_dir = get_corner_dirs(side)
      local l_cell = neighbour_by_side(c, l_dir)
      local h_cell = neighbour_by_side(c, h_dir)

      if side == 2 or side == 8 then

        local l_x = cx1-1
        local h_x = cx2+1

        if other then l_x = other.bx1-1
        elseif l_cell then l_x = l_cell.bx2+1
        end

        if other then h_x = other.bx2+1
        elseif h_cell then h_x = h_cell.bx1-1
        end

        if l_x-1 >= cx1 then
          add_border(c, l_dir, { x1=cx1, y1=cy1, x2=l_x-1, y2=cy1, side=side }, l_cell)
        end
        if l_x+1 > cx1 then
          cx1 = l_x+1
        end

        if h_x+1 <= cx2 then
          add_border(c, h_dir, { x1=h_x+1, y1=cy1, x2=cx2, y2=cy1, side=side }, h_cell)
        end
        if h_x-1 < cx2 then
          cx2 = h_x-1
        end

      else -- side==4 or side==6

        local l_y = cy1-1
        local h_y = cy2+1

        if other then l_y = other.by1-1
        elseif l_cell then l_y = l_cell.by2+1
        end

        if other then h_y = other.by2+1
        elseif h_cell then h_y = h_cell.by1-1
        end

        if l_y-1 >= cy1 then
          add_border(c, l_dir, { x1=cx1, y1=cy1, x2=cx1, y2=l_y-1, side=side }, l_cell)
        end
        if l_y+1 > cy1 then
          cy1 = l_y+1
        end

        if h_y+1 <= cy2 then
          add_border(c, h_dir, { x1=cx1, y1=h_y+1, x2=cx1, y2=cy2, side=side }, h_cell)
        end
        if h_y-1 < cy2 then
          cy2 = h_y-1
        end
      end

      add_border(c, side, { x1=cx1, y1=cy1, x2=cx2, y2=cy2, side=side }, other)

    end
  end

  ---| create_borders |---

  for zzz,c in ipairs(PLAN.all_cells) do
    find_borders(c)
  end

end

function match_borders_and_corners()

  local function try_add_border(c, E, D)
    
    if D.y1 == E.by and D.y2 == E.by then

      if D.x1 == E.bx+1 then E.borders[6] = D end
      if D.x2 == E.bx-1 then E.borders[4] = D end
      
    elseif D.x1 == E.bx and D.x2 == E.bx then

      if D.y1 == E.by+1 then E.borders[8] = D end
      if D.y2 == E.by-1 then E.borders[2] = D end
    end
  end

  for zzz,c in ipairs(PLAN.all_cells) do
    for cnum = 1,9,2 do
      local E = c.corner[cnum]
      if E then
        for side = 1,9 do
          local D = c.border[side]
          if D then try_add_border(c, E, D) end
        end
      end
    end
  end
end


----------------------------------------------------------------

function plan_sp_level(level, is_coop, recursion_depth)

  PLAN = get_base_plan(level, GAME.plan_size, GAME.cell_size)

  PLAN.coop = is_coop

  local p = PLAN


  local function travel_cost(cells, cx, cy, nx, ny)
    if cells[nx][ny] then return -1 end -- impassible
    return 5
  end

  local function valid_and_empty(cx, cy)
    return valid_cell(cx, cy) and not PLAN.cells[cx][cy]
  end

  local FB_BACK_PROBS = { 20, 90, 70, 50, 30, 10 }

  local function branch_spot_score(c, Q)
    -- make sure we have somewhere to go
    if not (valid_and_empty(c.x-1,c.y) or valid_and_empty(c.x+1,c.y) or
            valid_and_empty(c.x,c.y-1) or valid_and_empty(c.x,c.y+1)) then
      return 0
    end

    -- never branch off secret quests (except in emergencies)
    if c.quest.is_secret then
      if Q.is_secret then return 0.01 end
      return 0.00001
    end

    -- never branch off exit/quest rooms (except in emergencies)
    if c.is_exit or c == c.quest.last or
       (c.is_start and links_in_cell(c) >= 3)
    then
      return 0.00001
    end

    -- sub quests always connect to their parent
    if Q.parent then
      if Q.parent == c.quest then return 90 end
      if Q.parent == c.quest.parent then return 60 end
      return 0.2
    end

    -- first main quest always joins the initial room
    if Q.level == 1 then return 100 end

    -- usually we fork off the previous quest, but
    -- give a chance for other quests
    local quest_d = Q.level - c.quest.level
    assert(quest_d >= 1)

    -- how much backtracking (avoid forking off key room)
    -- Need to handle a Sub branching off a Sub...
    local where = c
    while where.quest.parent do
      where = where.quest.path[1]
    end
    local back_d = #where.quest.path - where.along

    -- doesn't matter when branching off non-parent ancestor
    if quest_d >= 2 then back_d = 1 end

    if back_d < 1 then return 0.001 end

    if back_d > #FB_BACK_PROBS then
       back_d = #FB_BACK_PROBS
    end

    -- less chance for main quest branching off a Sub
    if c.quest.parent then quest_d = quest_d + 1.4 end

    return FB_BACK_PROBS[back_d] / quest_d / quest_d
  end

  local function find_branch_spot(Q)
    local b_cells = {}  
    local b_probs = {}

--con.debugf(Q.parent and "SUB-Q: " or "QUEST: ", Q.level, "\n")
    for x = 1,PLAN.w do for y = 1,PLAN.h do
      local c = PLAN.cells[x][y]
      if c and not c.is_depot then
        local prob = branch_spot_score(c, Q)

        if prob > 0 then
--con.debugf("  ",c.x, ",", c.y, " prob= ",prob,"\n")
          table.insert(b_cells, c)
          table.insert(b_probs, prob)
        end
      end
    end end

    if #b_cells == 0 then
      show_path()
      return false
      ---error("Unable to find branch spot for quest " .. Q.level)
    end

    assert(#b_cells == #b_probs)

    return b_cells[rand_index_by_probs(b_probs)]
  end

  local MATCH_SCORES =
  {
    100, 70, 20, 2
  }

  local function where_now(x, y, path_dirs)
   
     
    local function dir_score(dir)
      local dx, dy = dir_to_delta(dir)

      if not valid_and_empty(x+dx, y+dy) then return 0 end

      local matches = 0
      if path_dirs[#path_dirs]   == dir then matches = matches+1 end
      if path_dirs[#path_dirs-1] == dir then matches = matches+1 end
      if path_dirs[#path_dirs-2] == dir then matches = matches+1 end

      return MATCH_SCORES[1 + matches]
    end

    local poss_dirs = { 0,0,0,0, 0,0,0,0 }

    poss_dirs[2] = dir_score(2)
    poss_dirs[4] = dir_score(4)
    poss_dirs[6] = dir_score(6)
    poss_dirs[8] = dir_score(8)

    local dir = rand_index_by_probs(poss_dirs)

    con.printf("Calling where_now at %d %d\n",x,y)
    if dir then
      assert(poss_dirs[dir] > 0)
      local dx, dy = dir_to_delta(dir)
      con.printf("where_now delta is %d %d\n",dx,dy)
      return x+dx, y+dy, dir
    end
  end

  local function liquid_for_quest(Q)
    if rand_odds(50) then
      return nil
    end

    local L = p.liquid

    while Q.combo.bad_liquid == L.name do
      if Q.combo.good_liquid then
        return find_liquid(Q.combo.good_liquid)
      end
      L = choose_liquid()
    end

    if Q.combo.good_liquid and dual_odds(Q.parent, 33, 66) then
      return find_liquid(Q.combo.good_liquid)
    end

    if Q.parent then
      return Q.parent.liquid
    end

    return L
  end

  local HALL_LEN_PROBS = { 100, 80, 50, 25,  6,  1,  0 }

  local function make_hallways(Q)

    local function hall_lighting(start,idx,finish)
      local level = 128
      while (level > 80) and (idx > start) and (idx < finish) do
        level = level - 16
        start = start + 1
        finish = finish - 1
      end
      return level
    end

    if #Q.path < 3 then return end

    if Q.combo.outdoor and Q.first.combo.outdoor then return end

    local h_probs =
      Q.combo.hallway_probs or
      Q.theme.hallway_probs or
      GAME.hallway_probs

    if not h_probs then return end

    -- longer quests are more likely to add hallways
    local chance = h_probs[math.min(#h_probs, #Q.path-2)]
    if not rand_odds(chance) then return end

    local start  = 2
    local finish = #Q.path - 1

    local st_movable = true

    if Q.first.hallway then
      st_movable = false
    end

    -- don't leave an outdoor gap when branching off an indoor area
    if Q.combo.outdoor and not Q.first.combo.outdoor then
      st_movable = false
    end

--[[
    then
      while start < finish do
        local length = finish - start + 1
        if rand_odds(HALL_LEN_PROBS[math.min(length, 7)]) then
          break;
        end
          start = start + 1
      end
    end
--]]
    while finish > start do
      local length = finish - start + 1
      if rand_odds(HALL_LEN_PROBS[math.min(length, 7)]) then
        break;
      end

      if st_movable and rand_odds(33) then
        start = start + 1
      else
        finish = finish - 1
      end
    end

    local combo
    if start == 2 and Q.first.hallway then
      -- extend the hallway in the previous quest
      combo = Q.first.combo
    elseif not GAME.hallways then
      combo = Q.first.combo
    else
      combo = get_rand_hallway(Q.theme)
      if not combo then return end
    end
    assert(combo)

    con.debugf("HALLWAY: start=%d len=%d QLEN:%d\n", start, finish-start+1, #Q.path)

    for idx = start,finish do
      local c = Q.path[idx]
      c.hallway = true
      c.combo = combo
      c.room_type = non_nil(GAME.rooms["HALLWAY"])
      if combo.well_lit then
        c.light = 176
      else
        c.light = hall_lighting(start,idx,finish)
      end
    end

    Q.has_hallway = true
  end
  
  local function specialize_rooms(Q)

    local cells = {}
    local probs = {}

    for i = 2,#Q.path do
      local c      = Q.path[i]
      local c_prev = Q.path[i+1]
      local c_next = Q.path[i-1]

      if not c.hallway then
        c.room_type = get_rand_roomtype(Q.theme)
con.debugf("ROOM %d QUEST %d.%d ---> %s\n",
c.along, Q.level, Q.sub_level, c.room_type.name)

--[[ KEEP ???
        local prob = 10

        if not c_prev then prob = 40 end
        if not c_next then prob = 70 end
        if c_prev and c_prev.hallway then prob = prob+50 end
        if c_next and c_next.hallway then prob = prob+20 end

        table.insert(cells, c)
        table.insert(probs, prob)
--]]
      end
    end

--[[ KEEP ???
    while #cells > 0 do

      local idx = rand_index_by_probs(probs)
      local c   = cells[idx]

      c.room_type = get_rand_roomtype(Q.theme)

con.debugf("ROOM %d QUEST %d.%d ---> %s\n",
c.along, Q.level, Q.sub_level, c.room_type.name)

--      if rand_odds(70) then break end

      table.remove(cells, idx)
      table.remove(probs, idx)
    end
--]]

    -- use PLAIN type of every other cell
    for zzz, c in ipairs(Q.path) do
      if not c.room_type then
        c.room_type = non_nil(GAME.rooms["PLAIN"])
      end
    end
  end

  local function make_quest_path(Q)

    assert(Q.combo)

    -- decide liquid
    if GAME.caps.liquids then
      Q.liquid = liquid_for_quest(Q)
    end

    -- add very first room somewhere in lower-left quarter of map
    if not Q.parent and Q.level == 1 then
      local x = rand_irange(1, int(PLAN.w / 2))
      local y = rand_irange(1, int(PLAN.h / 2))

      con.printf("Create cell line 1374\n") 
      local c = create_cell(x, y, Q, 1, Q.combo)

      c.is_start = true
      c.no_shrink = true
      c.no_monsters = true
---#  if GAME.wolf_format then c.no_monsters=true end
    end


    local cur = find_branch_spot(Q)
    if cur == false then
	con.printf("WARNING: Unable to find branch spot!\n");
	return false
    end

    con.printf("BRANCH SPOT @ (%d,%d)\n", cur.x, cur.y)

    table.insert(Q.path, cur)

    local along = 2
    local path_dirs = {}

    -- adjust wanted length based on size adjustment
    local want_len = Q.want_len
    --- Some values changed here, makes some levels bigger but should prevent some bugs
    if want_len >= 2 and SETTINGS.size == "tiny" then
      want_len = int(want_len * 0.85 - con.random())
    elseif want_len >= 3 and SETTINGS.size == "small" then
      want_len = int(want_len * 0.85 - con.random())
    elseif want_len >= 4 and SETTINGS.size == "medium" then -- Was "Small"
      want_len = int(want_len * 0.85 - con.random())
    elseif SETTINGS.size == "large" then -- The Oblige "large" size
      want_len = int(want_len * 1.35 + con.random())
    -- The old "huge" was too big; it took 30 minutes to make a 
    -- megawad, and the frame rate was pretty laggy
    elseif SETTINGS.size == "huge" then
      want_len = int(want_len * 1.35 + con.random())
    end

  if SETTINGS.size == "progressive" then
	con.printf("Q.along is %d\n",Q.along)
	want_len_adjust = 0
	if Q.along <= 1 then
		want_len_adjust = 0.85
	elseif Q.along <= 2 then
		want_len_adjust = 0.87
	elseif Q.along <= 3 then
		want_len_adjust = 0.9
	elseif Q.along <= 4 then
		want_len_adjust = 0.95
	elseif Q.along <= 5 then
		want_len_adjust = 0
	elseif Q.along <= 6 then
		want_len_adjust = 0
	elseif Q.along <= 7 then
		want_len_adjust = 1.1
	elseif Q.along <= 8 then
		want_len_adjust = 1.2
	else
		want_len_adjust = 1.35
	end
  end

    if want_len_adjust ~= 0 and want_len_adjust ~= nil then
        if want_len_adjust < 1 then
            if want_len < 5 then want_len = 5 end
		want_len = int(want_len * want_len_adjust - con.random())
	else
		want_len = int(want_len * want_len_adjust + con.random())
	end
    end

    if want_len == 1 then want_len = 2 end

    -- Keep tiny levels tiny
    if SETTINGS.size == "tiny" and want_len > 3 then
	want_len = 3
    end
    -- Make huge levels bigger
    if SETTINGS.size == "huge" and want_len < 9 then
	want_len = want_len + 1
    end

    -- secrets don't work well going outdoor-->outdoor
    -- But we keep them outdoors in all-outdoor maps
    if SETTINGS.outdoors ~= "outdoors" and 
       Q.is_secret and cur.combo.outdoor and Q.combo.outdoor then
      Q.combo = get_rand_indoor_combo(Q.theme)
con.printf("\nADJUSTED SECRET COMBO NEAR CELL (%d,%d)\n", cur.x,cur.y)
    end

    while along <= want_len do

      -- figure out where to go next
      local nx, ny, dir = where_now(cur.x, cur.y, path_dirs)

      if not nx then 
        con.printf("Warning: where_now failed at %d %d\n",cur.x,cur.y)
	break 
      end


      ---con.printf("Create cell line 1418\n") 
      local nextc = create_cell(nx, ny, Q, along, Q.combo)

      nextc.entry_dir = 10 - dir
      if not cur.exit_dir then cur.exit_dir = dir end

      create_link(cur, nextc, dir)

      table.insert(Q.path, nextc)
      table.insert(path_dirs, dir)

      cur = nextc
      along = along + 1
    end

    Q.first = Q.path[1]
    Q.last  = Q.path[#Q.path]

    Q.last.no_shrink = true

    make_hallways(Q)

    if GAME.shack_prob and Q.combo.outdoor and not Q.has_hallway then
      -- Experimental: start cell is a building
      if #Q.path >= 3 and Q == PLAN.quests[1] and rand_odds(GAME.shack_prob) then
        Q.first.combo = get_rand_indoor_combo(Q.theme)
con.printf("\nCHANGED INITIAL ROOM @ (%d,%d)\n", Q.first.x,Q.first.y)
      end

      -- Experimental: quest cell is a building
      if #Q.path >= 4 and dual_odds(Q.parent, GAME.shack_prob/4, GAME.shack_prob) then
con.printf("\nCHANGED QUEST ROOM @ (%d,%d)\n", Q.last.x,Q.last.y)
        Q.last.combo = get_rand_indoor_combo(Q.theme)
      end
    end

    specialize_rooms(Q)

    -- FIXME: assign depot spot __now__
    return true
  end


  local function decide_links()

    for zzz,link in ipairs(PLAN.all_links) do
      local c1 = link.cells[1]
      local c2 = link.cells[2]

      if (not c1.quest.is_secret) ~= (not c2.quest.is_secret) then
        -- secret quests need a secret door
        link.kind = "door"
        link.is_secret = true

      elseif c1.quest.level == c2.quest.level then

        local c = link.build
        local other = link_other(link, c)

        local door_chance = get_door_chance(c, other)

        if rand_odds(door_chance) then link.kind = "door" end

      else -- need a locked door

        local lock_level = math.max(c1.quest.level, c2.quest.level) - 1
        assert(lock_level >= 1 and lock_level < #PLAN.quests)

        for zzz,Q in ipairs(PLAN.quests) do
          if Q.level == lock_level and Q.sub_level == 0 then

            link.quest = Q -- !!!! FIXME: SHITTY WAY TO MARK A LOCK
            link.kind  = "door"
            break;
          end
        end

        assert(link.quest)
      end
    end

    -- for Wolfenstein3D, first room should have a door
    if GAME.caps.sealed_start then
      local c = PLAN.quests[1].first

      for side=2,8,2 do
        local link = c.link[side]
        if link and link.kind == "arch" then
          link.kind = "door"
        end
      end
    end
  end


  local function select_floor_heights()

    local function start_height()
      return 64 * rand_index_by_probs { 5, 40,80, 90, 70,30, 10 }
    end

    local function quest_heights(Q)

      local diff_probs = Q.combo.diff_probs or
          Q.theme.diff_probs or GAME.diff_probs

      local bump_probs = Q.combo.bump_probs or
          Q.theme.bump_probs or GAME.bump_probs

      assert(diff_probs)
      assert(bump_probs)

      -- determine overall slope of quest (up/down/level)
      local slope
      local sl_min,sl_max = -64,64

      if Q.path[1].floor_h <= (MIN_FLOOR+128) then
        sl_min, sl_max = 16,96
      elseif Q.path[1].floor_h >= (MAX_CEIL-192) then
        sl_min, sl_max = -96,-16
      end


      repeat
        slope = rand_key_by_probs(diff_probs)
        if rand_odds(50) then slope = -slope end
      until (sl_min <= slope) and (slope <= sl_max)

      --- Lets put some limits to how much the rooms can differ by height
      --- this is getting complaints on Doomworld
      if SETTINGS.steep == "flat" then
	doomworld_max_dh = 0
	doomworld_mult_factor = 0
      elseif SETTINGS.steep == "little" then
	doomworld_max_dh = 32
	doomworld_mult_factor = .5
      elseif SETTINGS.steep == "some" then
	doomworld_max_dh = 44 --- Maximum allowed height change
 	doomworld_mult_factor = .7 --- The bigger, the steeper
      elseif SETTINGS.steep == "steep" then	
        doomworld_max_dh = 48000  --- Maximum allowed change in height
        doomworld_mult_factor = 1 --- 1 is normal; .5 is flatter, 2 steeper
      end
      doomworld_min_dh = 0      --- Minimum allowed change in height
      slope = slope * doomworld_mult_factor 
      if slope < -doomworld_max_dh then slope = -doomworld_max_dh end
      if slope > doomworld_max_dh then slope = doomworld_max_dh end
      if slope > -doomworld_min_dh and slope < doomworld_min_dh then
        if slope < 0 then
		slope = -doomworld_min_dh
	else
		slope = doomworld_min_dh
	end
      end

      if vv_global_initial_height == -12345 then
        vv_global_initial_height = Q.path[1].floor_h
      end

      --- Minimize problems with sudden floor height changes
      if SETTINGS.steep ~= "steep" then --- ROD compatibility
         for idx = 1, #Q.path do
           if not Q.path[idx].visited then
	     Q.path[idx].floor_h = vv_global_initial_height
             Q.path[idx].visited = true
           end
         end
      end

      con.printf("QUEST> start:%d  slope:%d\n", Q.path[1].floor_h, slope)

      -- now traverse path and choose floor heights
      for idx = 2,#Q.path do
        local c = Q.path[idx]
        local prev = Q.path[idx-1]

        local change = math.abs(slope)

        if c.hallway and prev.hallway then
          if change > 128 then change = 64
          elseif change > 16 then change = change / 2
          end
        end

        if slope < 0 then change = -change end

        c.floor_h = prev.floor_h + change

        -- every journey has a few bumps along the way...
        local bump

        if not (c.hallway and prev.hallway) then
          bump = rand_key_by_probs(bump_probs)
          bump = bump * doomworld_mult_factor
	  if bump < doomworld_min_dh then bump = doomworld_min_dh end
	  if bump > doomworld_max_dh then bump = doomworld_max_dh end
          if rand_odds(50) then bump = -bump end
          c.floor_h = c.floor_h + bump --- We're not in Kansas anymore
        end

        c.floor_h = math.max(c.floor_h, MIN_FLOOR)
        c.floor_h = math.min(c.floor_h, MAX_CEIL-128)

        --- Make sure we have no cracks in the floor
        if SETTINGS.steep ~= "steep" and (c.floor_h % 8) ~= 0 then
           con.printf("Adjusting floor current value %d ",c.floor_h);
	   local upordown = 0
           if (c.floor_h % 8) >= 4 then
              upordown = 8
           end
           c.floor_h = c.floor_h - (c.floor_h % 8)
           c.floor_h = c.floor_h + upordown
           con.printf("new value %d\n",c.floor_h);
        end

--c.floor_h = rand_irange(MIN_FLOOR, MAX_CEIL-384)
        --- DEBUG
        --- con.printf("Prev: %s\n",table_to_str(prev))
        --- con.printf("C: %s\n",table_to_str(c))
        --- con.printf(".. idx: %d floor:%d prev floor: %d bump:%d\n",
        ---   idx, c.floor_h, prev.floor_h, bump or 0)
      end
    end

    local function scenic_floor(c)

      -- Method: examine neighbour cells (not including other scenic
      -- cells) to determine minimum and maximum floor range.  Then
      -- use start_height() to randomly select a height in that
      -- range (with some leeway).

      local f_min = MAX_CEIL
      local f_max = MIN_FLOOR

      for dir = 2,8,2 do
        local n = neighbour_by_side(c, dir)
        if n and n.combo.outdoor and not n.scenic then
          f_min = math.min(f_min, n.floor_h)
          f_max = math.max(f_max, n.floor_h)
        end
      end

      if f_min > f_max then
        con.debugf("SCENIC AT (%d,%d) has no outdoor neighbours\n", c.x, c.y)
        c.floor_h = start_height()
        return
      end

      f_min = f_min - 64
      f_max = f_max + 32 -- may get a fence too

      for loop = 1,10 do
        c.floor_h = start_height()
        if (f_min <= c.floor_h) and (c.floor_h <= f_max) then
          return
        end
      end
    end

    ---| select_floor_heights |---

    if not GAME.caps.heights then return end

    if not PLAN.quests[1] then return false end
    if not PLAN.quests[1].path[1] then return false end
    if not PLAN.quests[1].path[1].floor_h then return false end

    PLAN.quests[1].path[1].floor_h = start_height()

    vv_global_initial_height = -12345
    for zzz,Q in ipairs(PLAN.quests) do
      quest_heights(Q)
    end

    -- do scenic cells
    for zzz,c in ipairs(PLAN.all_cells) do
      if c.scenic then
        scenic_floor(c);
      end
    end
  end

  local function select_ceiling_heights()

    if not GAME.caps.heights then return end

    local function initial_height(c)

      if c.is_exit then
        c.ceil_h = c.floor_h + (c.combo.exit_h or 128)
      else
        local height_list =
          c.room_type.room_heights or
          c.combo.room_heights or
          c.quest.theme.room_heights or
          GAME.room_heights

        assert(height_list)

        c.ceil_h = c.floor_h + rand_key_by_probs(height_list)
      end

      c.ceil_h = math.min(c.ceil_h, MAX_CEIL)
      c.ceil_h = math.max(c.ceil_h, c.f_max + 80)
    end

    local function raise_the_rooves()

      local function merge_sky(c, dir)
        local other = neighbour_by_side(c, dir)
        if other then
          -- FIXME: when border is 100% solid (no windows/doors/fences)
          --        then we don't need to merge sky heights.

          if c.combo.outdoor then
            if c.sky_h < other.sky_h then
               c.sky_h = other.sky_h
               return true;
            end
          else
            -- indoor rooms only need a rudimentary sky_h
            -- (this prevents spreading the same value to every cell)

            if c.sky_h < other.ceil_h then
               c.sky_h = other.ceil_h
               return true;
            end
          end
        end
      end

      local function merge_link(c, dir)

        if c.is_exit then return end

        local other = neighbour_by_side(c, dir)
        if not other then return end

        local need = sel(c.combo.outdoor, 96, 64)

        if c.ceil_h < other.floor_h + need then
           c.ceil_h = other.floor_h + need
           return true
        end
      end

      --- raise_the_rooves ---

      for zzz,c in ipairs(PLAN.all_cells) do
        for dir = 2,8,2 do
          if c.link[dir] then
            merge_link(c, dir)
          end
        end
      end

      for zzz,c in ipairs(PLAN.all_cells) do
        c.sky_h = c.ceil_h
      end

      repeat
        local changed = false
        for zzz,c in ipairs(PLAN.all_cells) do
          for dir = 2,8,2 do
            if merge_sky(c, dir) then changed = true end
          end
        end
      until not changed

      for zzz,c in ipairs(PLAN.all_cells) do
        if c.combo.outdoor then
          c.ceil_h = math.max(c.ceil_h, c.sky_h)
        end
      end
    end

    --- select_ceiling_heights ---

    for zzz,c in ipairs(PLAN.all_cells) do
      initial_height(c)
    end

    raise_the_rooves()

  end

  local function assign_floor_codes()
    if GAME.caps.heights then return end -- not needed (yet??)

    local function should_connect(c, other, link)
      if link.kind == "arch" then return true end

      if link.kind ~= "door" then return false end

      if c.quest.level ~= other.quest.level then return false end

      if not link.floor_connx then
        link.floor_connx = dual_odds(c.combo == other.combo, 33, 11)
      end

      return link.floor_connx
    end

    local function grow(seeds)
      local new_seeds = { }

      for zzz,c in ipairs(seeds) do
        assert(c.floor_code)
        for _,yyy in ipairs(sorted_table_keys(c.link)) do
          local L = c.link[yyy]
          local other = link_other(L,c)

          if not other.floor_code and should_connect(c, other, L) then
            other.floor_code = c.floor_code
            table.insert(new_seeds, other)
          end
        end
      end

      return new_seeds
    end

    -- standard flood-fill
    
    local seeds = { PLAN.quests[1].first }

    seeds[1].floor_code = allocate_floor_code()

    repeat
      seeds = grow(seeds)

      if #seeds == 0 then
        -- grown as far as possible, so find new seeding spot
        for zzz,c in ipairs(PLAN.all_cells) do
          if not c.floor_code then
            c.floor_code = allocate_floor_code()
            table.insert(seeds, c)
            break
          end
        end
      end
    until #seeds == 0
  end

  
  local function shuffle_quests()
    
    local function sequence_score(qlist)
      -- higher (worse) score when the same type of quest
      -- appears multiple times in a row.  Also checks for
      -- how many sub-quests per quest.

      local score = { 0, 0, 0, 0 }

      local repeats = 0
      local subs = 0

      -- Note that we go ONE PAST the end
      for i = 1, #qlist+1 do

        if (qlist[i-1] and qlist[i-1].kind) == (qlist[i] and qlist[i].kind) then
          repeats = math.min(4, repeats + 1)
        else
          if repeats > 0 then score[repeats] = score[repeats] + 1 end
          repeats = 1
        end

        if qlist[i] and qlist[i].mode == "sub" then
          subs = math.min(4, subs + 1)
        else
          if subs > 0 then score[subs] = score[subs] + 1.8 end
          subs = 0
        end
      end

      return score[4]*100 + score[3]*40 + score[2]*10 
    end

    local function shuffle_main_quests(qlist)

      local MODE_PRI = { ["begin"]=0, ["main"]=1, ["end"]=3, ["sub"]=4 }

      -- put main quests into basic order

      for zzz,Q in ipairs(qlist) do
        Q.main_pri = non_nil(MODE_PRI[Q.mode]) + con.random()/2

        if Q.kind == "boss" and Q.mode == "end" then
          Q,main_pri = Q.main_pri - 1
        end
      end

      table.sort(qlist,
        function (A,B) return A.main_pri < B.main_pri end)

      -- FIXME: break up long sequence of same kind of main quest

con.debugf("\n*** shuffle_main_quests ***\n")
con.debugf("qlist now:\n%s\n\n", table_to_str(qlist,2))
    end

    local function sub_join_score(main_Q, sub_Q)
      
      local score = 90

      if sub_Q.kind == "weapon" then
        score = score / (main_Q.level) ^ 2

      elseif sub_Q.kind == "exit" and sub_Q.item == "secret" then
        score = score / (5 - math.max(main_Q.level, 4)) ^ 2
      end

      score = score / (main_Q.num_children + 2) ^ 2

      -- FIXME: take into account children of same type

      return score
    end

    local function assign_sub_quests(qlist)

      local sub_list = {}

-- FIXME: no big need to remove subs ...

      for i = #qlist,1,-1 do
        if qlist[i].mode == "sub" then
          table.insert(sub_list, table.remove(qlist, i))
        end
      end

      local num_main = #qlist
      if(num_main <= 0) then return false end
      assert(num_main > 0)

      for i = 1,num_main do
        qlist[i].level = i
        qlist[i].sub_level = 0
        qlist[i].num_children = 0
      end

      local probs = {}

      while #sub_list > 0 do
        local sub = table.remove(sub_list, 1)

        for i = 1,num_main do
          probs[i] = sub_join_score(qlist[i], sub)
        end

        local main_idx = rand_index_by_probs(probs)

        -- ??? FIXME: add an offset based on sub.prefer_pos

        local main_Q = non_nil(qlist[main_idx])

        main_Q.num_children = main_Q.num_children + 1

        sub.level = main_Q.level
        sub.sub_level = main_Q.num_children
        sub.parent = main_Q

        -- add sub quest to end of qlist.  The will be put into
        -- their proper place by a final sort of the list.

        table.insert(qlist, sub)
      end


      table.sort(qlist,
        function (A,B)
          return (A.level*100 + A.sub_level) < (B.level*100 + B.sub_level)
        end)
    end

    ---- shuffle_quests ----
    
    assert(PLAN.level)
    assert(PLAN.level.quests)
    assert(# PLAN.level.quests >= 1)

    PLAN.quests = PLAN.level.quests

    -- setup important fields in Quest class
    for zzz,Q in ipairs(PLAN.quests) do
      if not Q.mode then
        if Q.kind == "exit" and Q.item ~= "secret" then
          Q.mode = "end"
        elseif Q.kind == "boss" then
          Q.mode = "end"
        elseif Q.kind == "key" or Q.kind == "switch" then
          Q.mode = "main"
        else
          Q.mode = "sub"
        end
      end

      Q.tag = allocate_tag()
      Q.path = {}
    end

    shuffle_main_quests(PLAN.quests)

    assign_sub_quests(PLAN.quests)

    con.ticker();
  end

  local function plot_quests()

    -- plot secret quests _after_ normal quests, otherwise
    -- the secret quests can block off all possible branch
    -- spots for normal quests (which cannot connect to a
    -- secret quest).
  
    for pass = 1,2 do
      for zzz,Q in ipairs(PLAN.quests) do
        if pass == sel(Q.is_secret,2,1) then
          if make_quest_path(Q) == false then
		return false
	  end
        end
      end
    end

    con.ticker();
    return true
  end

  local function decide_themes()

    local T1 = get_rand_theme()
    local T2 = get_rand_theme()

    if T1 == T2 then T2 = get_rand_theme() end

    --- Both themes have indoors if we only want indoors
    if SETTINGS.outdoors == "indoors" or SETTINGS.outdoors == "rare" then
      for vvo = 1,50 do
        if T1.no_indoors then 
		T1 = get_rand_theme() 
        end
        if T2.no_indoors then 
		T2 = get_rand_theme() 
        end
      end
    end
 
    --- The initial theme will have outdoors at all outdoor settings
    --- except "indoors", "rare" and "some"
    if SETTINGS.outdoors == "more" or SETTINGS.outdoors == "lots" or
       SETTINGS.outdoors == "outdoors" then
      for vvo = 1,50 do
        if not T1.has_outdoors then 
		T1 = get_rand_theme() 
		con.printf("Trying another theme\n");
		con.printf("%s\n",table_to_str(T1)); --- DEBUG
        end
        --- Both themes will have outdoors at an outdoor setting of
        --- "outdoors"
        if SETTINGS.outdoors == "outdoors" and not T2.has_outdoors then
		T2 = get_rand_theme()
        end
      end
    end


--T1 = GAME.themes["CAVE"]
--T2 = GAME.themes["CAVE"]

    -- choose change-over point
    local mid_q = int(#PLAN.quests / 2 + con.random())

    if #PLAN.quests >= 4 then
      mid_q = mid_q + (rand_index_by_probs { 1,3,1 }) - 2
    end
    if #PLAN.quests >= 6 then
      mid_q = mid_q + (rand_index_by_probs { 1,6,1 }) - 2
    end

    --- Let's ensure that the initial room is outdoors at higher
    --- outdoor settings
    if mid_q == 1 and (SETTINGS.outdoors == "more" or
       SETTINGS.outdoors == "lots" or SETTINGS.outdoors == "outdoors") then
	mid_q = 2
    end 

con.debugf("CHANGE_OVER = %d (total:%d)\n", mid_q, #PLAN.quests)

    for i = 1,#PLAN.quests do
      
      local Q = PLAN.quests[i]

      Q.theme = sel(i >= mid_q, T2, T1)

      --- If we only want indoors, we only get indoors
      if SETTINGS.outdoors == "indoors" or 
         (SETTINGS.outdoors == "rare" and num_outdoors_quests
          and num_outdoors_quests > 2) then
	Q.combo = get_rand_indoor_combo(Q.theme)
      else
        Q.combo = get_rand_combo(Q.theme)
	if Q.combo.outdoor then
		if num_outdoors_quests then
			num_outdoors_quests = num_outdoors_quests + 1
		else
			num_outdoors_quests = 1
		end
        end
      end

      --- Player almost always starts outdoors if outdoors is set to "more"
      --- or higher
      if SETTINGS.outdoors == "more" or SETTINGS.outdoors == "lots" or 
         SETTINGS.outdoors == "outdoors" then
        for vvo = 1,50 do
          if i == 1 and not Q.combo.outdoor then
            con.printf("DEBUG: outdoorland initial combo %d %s\n",mid_q,
                       table_to_str(Q.theme))
            Q.combo = get_rand_combo(Q.theme)
          end
        end
      end
      --- In case of having an indoors combo, there is a certain chance
      --- we will make the combo outdoors 
      outdoorland = 0
      if SETTINGS.outdoors == "lots" then
        outdoorland = 45
      elseif SETTINGS.outdoors == "outdoors" then
        outdoorland = 99 
      end
      if outdoorland > 0 and Q.theme.has_outdoors then
        while not Q.combo.outdoor and rand_irange(1,100) < outdoorland do
          con.printf("DEBUG: outdoorland combo\n")
	  Q.combo = get_rand_combo(Q.theme)
        end
      end
        

con.debugf("QUEST %d.%d theme:%s combo:%s\n", Q.level, Q.sub_level,
Q.theme.name, Q.combo.name)
    end
  end

  local function peak_toughness(Q)
    local peak = 140 + 5 * #Q.path

    peak = peak + 20 * Q.sub_level
    peak = peak * (Q.level ^ 0.7) * (1 + rand_skew()/5)

    peak = peak * GAME.toughness_factor
    peak = peak * (PLAN.level.toughness_factor or 1)

    if Q.is_secret then
      peak = math.max(0, peak / 2 - 40)
    end

    if PLAN.coop and SETTINGS.mode ~= "spdm" then
      peak = peak * PLAN.coop_toughness
    end

    return peak
  end

  local function setup_exit_rooms()

    local function setup_one_exit(c)

      if not GAME.caps.elevator_exits then
        if c.quest.is_secret and GAME.exits["BLOODY"] then
          c.combo = GAME.exits["BLOODY"] --FIXME
        else
          c.combo = get_rand_exit_combo()
        end
      end

      c.is_exit = true
      c.no_shrink = true
      c.no_monsters = true
      c.light = 176

      c.small_exit = c.combo.small_exit or rand_odds(25)

      for dir = 2,8,2 do
        if c.link[dir] then
          local link = c.link[dir]
          if link.kind == "arch" or link.kind == "door" then
            link.kind = "door"
            link.build = c
            link.is_exit = true
            link.long = sel(GAME.caps.blocky_doors, 1,
                 sel(c.combo.front_mark or c.small_exit, 3, 2))
          end
        end
      end
    end

    for zzz,c in ipairs(PLAN.all_cells) do
      if c.quest.kind == "exit" and c == c.quest.last then
        setup_one_exit(c)
      end
    end
  end
  
  local function add_scenic_cells()
    -- these cells improve the outdoor environment.
    -- When a outdoor->indoor transition occurs and a
    -- nearby cell is empty, it looks bad (as if the
    -- building has a paper front and no side).

    local function test_flat_front(x, y)
      local empties = {}
      local innies  = {}
      local outies  = {}
      local scenics = 0

      for dx = 0,1 do
        for dy = 0,1 do
          local c = PLAN.cells[x+dx][y+dy]
          if not c then
            table.insert(empties, { x=x+dx, y=y+dy })
          elseif c.scenic == "solid" then
            table.insert(innies, c)
          elseif c.scenic == "outdoor" then
            scenics = scenics + 1
          elseif c.combo.outdoor then
            table.insert(outies, c)
          else
            table.insert(innies, c)
          end
        end
      end

      if #empties ~= 1 or scenics > 1 or #outies < 1 then return end

      if #outies == 1 and #innies == 2 and 
         (outies[1].x ~= empties[1].x) and
         (outies[1].y ~= empties[1].y)
      then return end

      con.printf("Create cell line 2107\n") 
      local c = create_cell(empties[1].x, empties[1].y,
        outies[1].quest, outies[1].along, outies[1].combo)

      c.scenic = "outdoor"
      c.room_type = non_nil(GAME.rooms["SCENIC"])

      -- Experimental "SOLID SCENIC" cells
      if #innies >= 1 and rand_odds(66) and
         ((empties[1].x == innies[1].x) or
          (empties[1].y == innies[1].y))
      then
        c.scenic = "solid"
        c.combo = innies[1].combo
        if innies[1].hallway then c.combo = innies[1].quest.combo end

        con.debugf("SOLID-")
      end

      con.debugf("SCENIC CREATED AT (%d,%d)\n", c.x, c.y)
    end

    --- add_scenic_cells ---

    for loop = 1,3 do
      for x = 1, PLAN.w-1 do
        for y = 1, PLAN.h-1 do
          test_flat_front(x, y)
        end
      end
    end

  end

  local function add_bridges()
    --[[
    for zzz,c in ipairs(PLAN.all_cells) do
      for dir = 2,8,2 do
        local pdir = rotate_cw90(dir)
        if c.link[dir].switch and
        if c.link[dir] and c.link[10-dir] and
           not c.link[pdir] and not c.link[10-pdir]
      end
    end
    --]]
  end

  local function add_vistas()

    local function prelim_check(a, b, dir)

      if b.is_exit or b.hallway or b.is_depot then return false end

      if b.scenic == "solid" then return false end

      -- ensure last cell has enough room for quest item
      if b == b.quest.last then return false end

      if a.small_exit or a.scenic or a.is_depot then return false end

      if (a.is_start and links_in_cell(a) >= 2) then return false end
      if (b.is_start and links_in_cell(b) >= 2) then return false end

      if a.f_min  < (b.f_max + 24) then return false end
      if b.ceil_h < (a.f_max + 96) then return false end

      if a.combo.outdoor and b.combo.outdoor and a.ceil_h ~= b.ceil_h then return false end
      if a.combo.outdoor and not b.combo.outdoor and a.ceil_h <= b.ceil_h then return false end
      if b.combo.outdoor and not a.combo.outdoor and b.ceil_h <= a.ceil_h then return false end

      -- do not allow two vistas/falloffs in a room unless they
      -- are opposite each other
      if b.vistas[rotate_cw90(dir)] or
         b.vistas[rotate_ccw90(dir)]
      then return false end

      return true
    end

    local function quest_compare(a, b)

      local aq = a.quest.parent or a.quest
      local bq = b.quest.parent or b.quest

      if aq.level < bq.level then return -1 end
      if aq.level > bq.level then return  1 end

      return 0
    end
    
    local function can_make_falloff(a, b, dir)

      if b.scenic then return false end

      if b.quest.is_secret and a.quest ~= b.quest then return false end

      if b.quest.kind == "exit" and a.quest ~= b.quest then return false end

      if a.f_min < (b.f_max + 64) then return false end

      return true
    end

    local function can_make_vista(a, b, dir)

      if a.combo == b.combo then return false end

      if a.combo.outdoor and rand_odds(50) then return false end

      if not b.combo.outdoor and rand_odds(60) then return false end

      return true
    end

    -- add_vistas --

    for zzz,c in ipairs(PLAN.all_cells) do
      for dir = 2,8,2 do
        local nb = neighbour_by_side(c, dir)

        if nb and not c.link[dir] and rand_odds(100) and --FIXME
           prelim_check(c, nb, dir)
        then
          local V = can_make_vista(c, nb, dir)
          local F = can_make_falloff(c, nb, dir)
          local q_cmp = quest_compare(c, nb)

          if q_cmp < 0 then F = false end

          -- without this check, falloffs will be rarely made
          if F and V and rand_odds(33) then V = false end

          if F or V then
            local L = create_link(c, nb, dir)
            L.kind = sel(V, "vista", "falloff")

            if V and F and dual_odds(nb.combo.outdoor, 40, 75) then
              L.fall_over = true
            end

            if V then
              L.build = c
              L.vista_src  = c
              L.vista_dest = nb
            end

            -- record the vista in the other cell
            nb.vistas[10-dir] = true

            con.debugf("%s @ (%d,%d) dir:%d %s\n", string.upper(L.kind),
                       c.x, c.y, dir, sel(L.fall_over, "FALL-OVER", "-"))
          end
        end
      end
    end
  end

  local function add_windows()
    
    local function can_make_window(a, b, dir)

      local link = a.link[dir]

      if b.is_depot or b.is_bridge then return false end

      if (a.is_exit or b.is_exit) and rand_odds(90) then return false end

      if link and link.kind == "vista" then return false end

      local cc = math.min(a.ceil_h, b.ceil_h) - 32
      local ff = math.max(a.f_max,  b.f_max)  + 32

      if (cc - ff) < 32 then return false end

      if a.combo.outdoor and b.combo.outdoor and a.ceil_h ~= b.ceil_h then return false end

--!!      if a.combo.outdoor and not b.combo.outdoor and b.ceil_h > b.ceil_h + 32 then return false end
--!!      if b.combo.outdoor and not a.combo.outdoor and a.ceil_h > a.ceil_h + 32 then return false end

      local window_chance = get_window_chance(a, b)

      return rand_odds(window_chance)
    end

    for zzz,c in ipairs(PLAN.all_cells) do
      for side = 6,9 do
        local other = neighbour_by_side(c, side)

        if c.border[side] and other and can_make_window(c, other, side) then
con.debugf("WINDOW @ (%d,%d):%d\n", c.x,c.y,side)
          c.border[side].window = true
        end
      end
    end
  end


  local function add_surprises()

    -- the chance we'll use the 1st/2nd/3rd/etc location
    local LOC_PROBS = { 100, 60, 40, 25, 10 }

    local sm_prob = 36
    local bg_prob = 60

    --- if SETTINGS.traps == "less" then sm_prob, bg_prob = 15, 25 end
    --- if SETTINGS.traps == "more" then sm_prob, bg_prob = 60, 80 end

    local function add_closet(Q)

      if not GAME.caps.closets then return end

      local locs  = {}
      local SIDES = { 2,4,6,8 }

      for idx,c in ipairs(Q.path) do
        rand_shuffle(SIDES)
        for zzz,side in ipairs(SIDES) do
          if idx >= 2 and not c.link[side]
--!!! FIXME    and not c.vista[side] and c.vista_from ~= side
          then
            table.insert(locs, {c=c, side=side})
            break; -- only one location per cell
          end
        end
      end

      if #locs < 1 then return end

      local r = con.random() * 100
      local use_all = false

      if r < 3 then
        use_all = true -- Ouchies!
      elseif r < 10 then
        -- begin at first room (no change needed)
      elseif r < 50 then
        reverse_array(locs) -- begin at last room
      else
        rand_shuffle(locs)
      end

      local SURPRISE =
      {
        trigger_cell = Q.last,
        door_tag = allocate_tag(),
        toughness = peak_toughness(Q) * 1.4,
        places = {}
      }

      for idx,L in ipairs(locs) do
        if use_all or (idx <= #LOC_PROBS and rand_odds(LOC_PROBS[idx])) then
          table.insert(SURPRISE.places,
            { c = L.c, side = L.side, tag = allocate_tag(),
              mon_set = { easy={}, medium={}, hard={} }, spots = {} })
          L.c.closet[L.side] = true
          con.debugf("CLOSET @ (%d,%d)\n", L.c.x, L.c.y)
        end
      end

      Q.closet = SURPRISE
    end


    local function choose_depot_target(Q, num, spread)
      if #Q.path < 2 then return Q.path[1] end

      local idx

          if spread == "last"   then idx = #Q.path
      elseif spread == "behind" then idx = #Q.path - 1
      elseif spread == "first"  then idx = 2
      elseif spread == "linear" then idx = #Q.path - (num-1)
      else -- "random"
        idx = #Q.path - rand_irange(0,10)
      end

      while idx < 2 do
        idx = idx + (#Q.path - 1)
        assert(idx <= #Q.path)
      end

      con.debugf("..Depot target %d @ (%d,%d) tag: %d\n", num,
         Q.path[idx].x, Q.path[idx].y, PLAN.free_tag+1);

      return Q.path[idx]
    end

    local function add_depot(Q)

      if not GAME.caps.depots then return end
      assert(GAME.depot_info)
      assert(GAME.depot_info.teleport_kind)

      local function valid_depot_spot(x, y)
        if PLAN.cells[x][y] then return false end

        -- check for overlap (FIXME: pre-allocate)
        local bx1,by1, bx2,by2 = PLAN.cell_base_coords(x, y)

        for dx = -1,1 do for dy = -1,1 do
          local c = valid_cell(x+dx, y+dy) and PLAN.cells[x+dx][y+dy]
          if c then
            local ox1 = math.max(c.bx1-1, bx1)
            local oy1 = math.max(c.by1-1, by1)
            local ox2 = math.max(c.bx2+1, bx2)
            local oy2 = math.max(c.by2+1, by2)

            if ox1 <= ox2 and oy1 <= oy2 then
              error("DEPOT OVERLAP!")  --!!!
              return false
            end
          end
        end end

        return true
      end

      local pos_x, pos_y
      local best_score = -999

      local start = PLAN.quests[1].first

      -- find place on map to build the depot (furthest from start pos)
      for x = 1,PLAN.w do for y = 1,PLAN.h do
        if not PLAN.cells[x][y] then
          local score = dist(x, y, start.x, start.y)
          if score > best_score then
            best_score = score
            pos_x, pos_y = x, y
          end
        end
      end end

      if not pos_x then return end

      con.debugf("DEPOT @ (%d,%d)\n", pos_x, pos_y)

      local spread = rand_key_by_probs { linear=3, random=3, last=5, behind=5, first=1 }

      con.printf("Create cell line 2447\n") 
      local CELL = create_cell(pos_x, pos_y, Q, 1, Q.first.combo, "depot")

      local SURPRISE =
      {
        trigger_cell = Q.last,
        depot_cell = CELL,
        spread = spread,
        toughness = peak_toughness(Q) * 1.2,
        door_tag = allocate_tag(),
        places = {}
      }

      for num = 1,4 do
        table.insert(SURPRISE.places,
          { c = choose_depot_target(Q,num,spread), tag = allocate_tag(),
            mon_set = { easy={}, medium={}, hard={} }, spots = {} })
      end

      Q.depot = SURPRISE
    end

    local function try_add_surprise(Q)
      if Q.kind == "exit" then return end

      if dual_odds(Q.parent, sm_prob, bg_prob) then
        if rand_odds(70) then
          add_closet(Q)
        else
          add_depot(Q)
        end
      end
    end

    --- add_surprises ---

    for zzz,Q in ipairs(PLAN.quests) do
      try_add_surprise(Q)
    end
  end


  local function toughen_it_up()

    local function toughen_quest(Q)
      
      local peak = peak_toughness(Q)
      local skip = 0

      if SETTINGS.mons == "rare" then peak = peak/3.6 end
      if SETTINGS.mons == "less" then peak = peak/1.8 end
      if SETTINGS.mons == "more" then peak = peak*1.8 end
      if SETTINGS.mons == "swarms" then peak = peak*3.6 end
      -- More monsters if both single player and deathmatch
      if SETTINGS.mode == "spdm2" then peak = peak * 2.1 end

      -- go backwards from quest cell to start cell
      for i = #Q.path,1,-1 do
        local cell = Q.path[i]
        if not cell.toughness then
          if skip > 0 or cell.is_exit or cell == PLAN.quests[1].first then
            cell.toughness = (1 + rand_skew()) * peak / 3.5
            skip = skip - 1
          else
            cell.toughness = peak
            peak = peak * 0.75
            skip = rand_index_by_probs({ 10, 70, 70, 20 }) - 1
            if skip == 0 and Q.level == 1 then skip = 1 end
          end
        end
      end

---??  for j = 1,#Q.path do
---??    con.printf("%d%s",
---??      Q.path[j].toughness or -789,
---??      sel(j < #Q.path, ",", "\n"))
---??  end
    end

    -- toughen_it_up --

    for zzz,Q in ipairs(PLAN.quests) do
      toughen_quest(Q)
    end
  end


  ---=== plan_sp_level ===---

  p.hmodels = initial_hmodels()

  if GAME.caps.liquids then
    p.liquid = choose_liquid()

    if (p.liquid) then
      con.printf("LIQUID: %s\n", p.liquid.name)
    end
  end

  con.printf("\n")

  if not PLAN.level or not PLAN.level.quests or (#PLAN.level.quests < 1 )then
	con.printf("WARNING: Level %s has no quests, huh? Remaking!\n",
                   level.name);
        if recursion_depth < 1024 then
	  return plan_sp_level(level,is_coop,recursion_depth + 1)
        else 
	  con.printf("Recursion depth exceeded\n")
        end
  end

  shuffle_quests()
  decide_themes()

  show_quests()

  if not plot_quests() then 
	con.printf("WARNING: Level %s plot_quest() failed remaking\n",
                   level.name);
        if recursion_depth < 1024 then
	  return plan_sp_level(level,is_coop,recursion_depth + 1)
        else 
	  con.printf("Recursion depth exceeded\n")
        end
  end

  decide_links()
  
  setup_exit_rooms()
  
  shuffle_build_sites()
  add_scenic_cells()

  con.ticker();

  select_floor_heights()
  compute_height_minmax()

  select_ceiling_heights()
  compute_height_minmax()

  assign_floor_codes()

  resize_rooms()

  if PLAN.coop then
    PLAN.coop_toughness = rand_range(1.5, 2.1)
    con.debugf("coop_toughness = %d\n", PLAN.coop_toughness);
  end

  toughen_it_up()

  add_vistas()

-- FIXME add_surprises()

  create_corners()
  create_borders()
  match_borders_and_corners()

  add_windows()

  --- Make sure we have an exit; if not, then redraw the entire level
  --- Also, if there is supposed to be a secret exit, make sure we have
  --- two exits
  local vvx, vvy, vvg, vvr, vvm
  vvg = 0 --- number of exits
  vvr = 0 --- number of rooms
  for vvx = 1,PLAN.w do
	for vvy = 1,PLAN.h do
		if PLAN.cells[vvx][vvy] then
                        if not PLAN.cells[vvx][vvy].scenic then
			  if PLAN.cells[vvx][vvy].quest.kind == "exit" then
      			    if PLAN.cells[vvx][vvy] == PLAN.cells[vvx][vvy].quest.last then
				show_path(PLAN.cells[vvx][vvy])
				con.printf(" Exit at %d %d\n",vvx,vvy)
				vvg = vvg + 1
                          end
			  end
			  vvr = vvr + 1
 			end
		end
	end
  end
  con.printf("Level exits %d rooms %d\n",vvg,vvr)	
  if level.no_exit and vvg ~= 0 then
	con.printf("WARNING: Level %s should not have an exit, remaking!\n",
                   level.name);
        if recursion_depth < 1024 then
	  return plan_sp_level(level,is_coop,recursion_depth + 1)
        else 
	  con.printf("Recursion depth exceeded\n")
        end
  end
  if vvg == 0 and not level.no_exit then
	con.printf("WARNING: Level %s has no exit; remaking!\n",level.name)
        if recursion_depth < 1024 then
	  return plan_sp_level(level,is_coop,recursion_depth + 1)
        else 
	  con.printf("Recursion depth exceeded\n")
        end
  end
  if level.secret_exit and vvg < 2 then
	con.printf("WARNING: Level %s has no secret exit; remaking!\n",level.name)
        if recursion_depth < 1024 then
	  return plan_sp_level(level,is_coop,recursion_depth + 1)
        else 
	  con.printf("Recursion depth exceeded\n")
        end
  end
  vvm = 6 --- Minimum number of cells (rooms) --- Changed from 5 to 6 to prevent missing items in Tiny/Small levels
  if SETTINGS.size == "tiny" then vvm = 4 end --- Changed from 2 to 4 to prevent "empty levels" and missing items
  if SETTINGS.size == "progressive" then vvm = 3 + level.ep_along end 
  if vvr < vvm then
        -- Remake levels that are too small
	con.printf("WARNING: Level %s has only %d rooms; remaking!\n",level.name,vvr)
        if recursion_depth < 1024 then
          -- So we don't slow things down, we make one of the quests
          -- a little longer, so that we're less likely to not have enough
          -- rooms 
	  local vvz = #level.quests
	  local vvy = rand_irange(1,vvz)
          if level.quests[vvy] ~= nil then
	  	level.quests[vvy].want_len = level.quests[vvy].want_len + 1
	  end
	  return plan_sp_level(level,is_coop,recursion_depth + 1)
        else 
	  con.printf("Recursion depth exceeded\n")
        end
  end
  


  return p
end --- plan_sp_level 

