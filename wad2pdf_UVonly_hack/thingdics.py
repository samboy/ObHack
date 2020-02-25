# Dictionaries for mapping thing numbers to sprite names

# Wad2PDF is a program that converts Doom levels into PDF files.
# (C) 2005-8 Jussi Pakkanen
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


doomdic = { # From Matt Fell's Ultimate Doom specs
   0: None,      # There is one of these in Plutonia. Don't know why.
   1: 'PLAYA1',  #  Player 1 start (Player 1 start needed on ALL
   2: 'PLAYA1',  #  Player 2 start (Player starts 2-4 are needed in)
   3: 'PLAYA1',  #  Player 3 start (cooperative mode multiplayer games)
   4: 'PLAYA1',  #  Player 4 start
  11: 'PLAYF1',  #  Deathmatch start positions. Should have >= 4/level
  14: 'BFE2C0',  #  Teleport landing. Where players/monsters land when
3004: 'POSSA1',  ## FORMER HUMAN: regular pistol-shooting zombieman
  84: 'SSWVA1',  ## WOLFENSTEIN SS: guest appearance by Wolf3D blue guy
   9: 'SPOSA1',  ## FORMER HUMAN SERGEANT: black armor, shotgunners
  65: 'CPOSA1',  ## HEAVY WEAPON DUDE: red armor, chaingunners
3001: 'TROOF1',  ## IMP: brown, hurl fireballs
3002: 'SARGA1',  ## DEMON: pink, muscular bull-like chewers
  58: 'SARGA5',  ## SPECTRE: invisible version of the DEMON
3006: 'SKULC1',  ## LOST SOUL: flying flaming skulls, they really bite
3005: 'HEADA1',  ## CACODEMON: red one-eyed floating heads. Behold...
  69: 'BOS2G1',  ## HELL KNIGHT: grey-not-pink BARON, weaker
3003: 'BOSSG1',  ## BARON OF HELL: cloven hooved minotaur boss
  68: 'BSPIH1',  ## ARACHNOTRON: baby SPIDER, shoots green plasma
  71: 'PAINC1',  ## PAIN ELEMENTAL: shoots LOST SOULS, deserves its
  66: 'SKELJ1',  ## REVENANT: Fast skeletal dude shoots homing missles
  67: 'FATTA1',  ## MANCUBUS: Big, slow brown guy shoots barrage of
  64: 'VILEG1',  ## ARCH-VILE: Super-fire attack, ressurects the dead!
   7: 'SPIDA1D1',  ## SPIDER MASTERMIND: giant walking brain boss
  16: 'CYBRE1',  ## CYBER-DEMON: robo-boss, rocket launcher
  88: 'BBRNA0',  ## BOSS BRAIN: Horrifying visage of the ultimate demon
  89: None,      #  Boss Shooter: Shoots spinning skull-blocks
  87: None,      #  Spawn Spot: Where Todd McFarlane's guys appear
2005: 'CSAWA0',  #$ Chainsaw
2001: 'SHOTA0',  #$ Shotgun
  82: 'SGN2A0',  #$ Double-barreled shotgun
2002: 'MGUNA0',  #$ Chaingun, gatling gun, mini-gun, whatever
2003: 'LAUNA0',  #$ Rocket launcher
2004: 'PLASA0',  #$ Plasma gun
2006: 'BFUGA0',  #$ Bfg9000
2007: 'CLIPA0',  #$ Ammo clip
2008: 'SHELA0',  #$ Shotgun shells
2010: 'ROCKA0',  #$ A rocket
2047: 'CELLA0',  #$ Cell charge
2048: 'AMMOA0',  #$ Box of Ammo
2049: 'SBOXA0',  #$ Box of Shells
2046: 'BROKA0',  #$ Box of Rockets
  17: 'CELPA0',  #$ Cell charge pack
   8: 'BPAKA0',  #$ Backpack: doubles maximum ammo capacities
2011: 'STIMA0',  #$ Stimpak
2012: 'MEDIA0',  #$ Medikit
2014: 'BON1A0',  #! Health Potion +1% health
2015: 'BON2A0',  #! Spirit Armor +1% armor
2018: 'ARM1A0',  #$ Green armor 100%
2019: 'ARM2A0',  #$ Blue armor 200%
  83: 'MEGAA0',  #! Megasphere: 200% health, 200% armor
2013: 'SOULA0',  #! Soulsphere, Supercharge, +100% health
2022: 'PINVA0',  #! Invulnerability
2023: 'PSTRA0',  #! Berserk Strength and 100% health
2024: 'PINSA0',  #! Invisibility
2025: 'SUITA0',  #!)Radiation suit - see notes on ! above
2026: 'PMAPA0',  #! Computer map
2045: 'PVISA0',  #! Lite Amplification goggles
   5: 'BKEYB0',  #$ Blue keycard
  40: 'BSKUB0',  #$ Blue skullkey
  13: 'RKEYB0',  #$ Red keycard
  38: 'RSKUB0',  #$ Red skullkey
   6: 'YKEYB0',  #$ Yellow keycard
  39: 'YSKUB0',  #$ Yellow skullkey
2035: 'BAR1A0',  ## Barrel; not an obstacle after blown up 
  72: 'KEENA0',  ## A guest appearance by Billy
  48: 'ELECA0',  ## Tall, techno pillar
  30: 'COL1A0',  ## Tall green pillar
  32: 'COL3A0',  ## Tall red pillar
  31: 'COL2A0',  ## Short green pillar
  36: 'COL5A0',  ## Short green pillar with beating heart
  33: 'COL4A0',  ## Short red pillar
  37: 'COL6A0',  ## Short red pillar with skull
  47: 'SMITA0',  ## Stalagmite: small brown pointy stump
  43: 'TRE1A0',  ## Burnt tree: gray tree
  54: 'TRE2A0',  ## Large brown tree
2028: 'COLUA0',  ## Floor lamp
  85: 'TLMPA0',  ## Tall techno floor lamp
  86: 'TLP2A0',  ## Short techno floor lamp
  34: 'CANDA0',  #  Candle
  35: 'CBRAA0',  ## Candelabra
  44: 'TBLUA0',  ## Tall blue firestick
  45: 'TGRNA0',  ## Tall green firestick
  46: 'TREDA0',  ## Tall red firestick
  55: 'SMBTA0',  ## Short blue firestick
  56: 'SMGTA0',  ## Short green firestick
  57: 'SMRTA0',  ## Short red firestick
  70: 'FCANA0',  ## Burning barrel
  41: 'CEYEA0',  ## Evil Eye: floating eye in symbol, over candle
  42: 'FSKUA0',  ## Floating Skull: flaming skull-rock
  49: 'GOR1A0',  ## Hanging victim, twitching
  63: 'GOR1A0',  #  Hanging victim, twitching
  50: 'GOR2A0',  ## Hanging victim, arms out
  59: 'GOR2A0',  #  Hanging victim, arms out
  52: 'GOR4A0',  ## Hanging pair of legs
  60: 'GOR4A0',  #  Hanging pair of legs
  51: 'GOR3A0',  ## Hanging victim, 1-legged
  61: 'GOR3A0',  #  Hanging victim, 1-legged
  53: 'GOR5A0',  ## Hanging leg
  62: 'GOR5A0',  #  Hanging leg
  73: 'HDB1A0',  ## Hanging victim, guts removed
  74: 'HDB2A0',  ## Hanging victim, guts and brain removed
  75: 'HDB3A0',  ## Hanging torso, looking down
  76: 'HDB4A0',  ## Hanging torso, open skull
  77: 'HDB5A0',  ## Hanging torso, looking up
  78: 'HDB6A0',  ## Hanging torso, brain removed
  25: 'POL1A0',  ## Impaled human
  26: 'POL6A0',  ## Twitching impaled human
  27: 'POL4A0',  ## Skull on a pole
  28: 'POL2A0',  ## 5 skulls shish kebob
  29: 'POL3A0',  ## Pile of skulls and candles
  10: 'PLAYN0',  #  Bloody mess (an exploded player)
  12: 'PLAYN0',  #  Bloody mess, this thing is exactly the same as 10
  24: 'POL5A0',  #  Pool of blood and flesh
  79: 'POB1A0',  #  Pool of blood
  80: 'POB2A0',  #  Pool of blood
  81: 'BRS1A0',  #  Pool of brains
  15: 'PLAYL0',  #  Dead player
  18: 'POSSL0',  #  Dead former human
  19: 'SPOSL0',  #  Dead former sergeant
  20: 'TROOM0',  #  Dead imp
  21: 'SARGN0',  #  Dead demon
  22: 'HEADL0',  #  Dead cacodemon
  23: None       #  Dead lost soul, invisible
}

hereticdic = { # These were stolen from Wadauthor.
    0x001 : 'PLAYA1',    #  Player 1
    0x002 : 'PLAYA1',    #  Player 2
    0x003 : 'PLAYA1',    #  Player 3
    0x004 : 'PLAYA1',    #  Player 4
    0x005 : 'IMPXA1',    #  Gargoyle leader
    0x006 : 'HEADA1',    #  Ironlich
    0x007 : 'SRCRA1',    #  D'Sparil
    0x008 : 'BAGHA0',    #  Bag of holding
    0x009 : 'MNTRV1',    #  Maulotaur
    0x00a : 'AMG1A0',    #  Wand crystal (10)
    0x00b : 'PLAYF1',    #  Deathmatch
    0x00c : 'AMG2A0',    #  Wand crystal (50)
    0x00d : 'AMM1A0',    #  Mace spheres (20)
    0x00e : 'TELEG0',    #  Destination
    0x00f : 'WZRDA1',    #  Disciple of D'Sparil
    0x010 : 'AMM2A0',    #  Mace spheres (100)
    0x011 : 'SKH1A0',    #  Skull hang (70)
    0x012 : 'AMC1A0',    #  Crossbow bolts (5)
    0x013 : 'AMC2A0',    #  Crossbow quiver (20)
    0x014 : 'AMS1A0',    #  Hellstaff lesser runes (20)
    0x015 : 'AMS2A0',    #  Hellstaff greater runes (100)
    0x016 : 'AMP1A0',    #  Phoenix orb (1)
    0x017 : 'AMP2A0',    #  Phoenix orb (10)
    0x018 : 'SKH2A0',    #  Skull hang (60)
    0x019 : 'SKH3A0',    #  Skull hang (45)
    0x01a : 'SKH4A0',    #  Skull hang (35)
    0x01b : 'SRTCA0',    #  Serpent torch
    0x01c : 'CHDLB0',    #  Chandelier
    0x01d : 'SMPLA0',    #  Small pillar
    0x01e : 'EGGCA0',    #  Morph ovum
    0x01f : 'SHD2A0',    #  Enchanted shield
    0x020 : 'ARTISPHL',  #  Mystic urn
    0x021 : 'ARTITRCH',  #  Torch
    0x022 : 'ARTIFBMB',  #  Time bomb of the ancients
    0x023 : 'SPMPA0',    #  Map scroll
    0x024 : 'ARTIATLP',  #  Chaos device
    0x025 : 'STGSA0',    #  Stalagmite (small)
    0x026 : 'STGLA0',    #  Stalagmite (large)
    0x027 : 'STCSA0',    #  Stalactite (small)
    0x028 : 'STCLA0',	 #  Stalactite (large)
    0x029 : 'TELEA0',    #  Waterfall (continuous)
    0x02a : 'TELEA0',    #  Wind (continuous)
    0x02b : 'PPODK0',    #  Pod spawner
    0x02c : 'BARLA0',    #  Barrel
    0x02d : 'MUMMY1',    #  Nitrogolem
    0x02e : 'MUMMY5',    #  Nitrogolem ghost
    0x02f : 'BRPLA0',    #  Brown pillar
    0x030 : 'MOS1A0',    #  Moss (three)
    0x031 : 'MOS2A0',    #  Moss (one)
    0x032 : 'WTRHC0',    #  Wall torch
    0x033 : 'HCORA0',    #  Hanging corpse
    0x034 : 'TGLTG0',    #  Blue glitter
    0x035 : 'WBLSA0',    #  Dragon claw
    0x036 : 'AMB1A0',    #  Energy orb (10)
    0x037 : 'AMB2A0',    #  Energy orb (25)
    0x038 : 'SOR2I0',    #  D'Sparil teleport spot
    0x040 : 'KNIGA1',    #  Undead warrior
    0x041 : 'KNIGA5',    #  Undead warrior ghost
    0x042 : 'IMPXB1',    #  Gargoyle
    0x044 : 'MUMME1',    #  Golem
    0x045 : 'MUMME5',    #  Golem ghost
    0x046 : 'BEASA1',    #  Weredragon
    0x049 : 'AKYYA0',    #  Green key
    0x04a : 'TGLTB0',    #  Red glitter
    0x04b : 'ARTIINVS',  #  Invisibility
    0x04c : 'KFR1A0',    #  Fire brazier
    0x04f : 'BKYYA0',    #  Blue key
    0x050 : 'CKYYA0',    #  Yellow key
    0x051 : 'PTN1A0',    #  Crystal vial (10)
    0x052 : 'ARTIPTN2',  #  Quartz flask (25)
    0x053 : 'ARTISOAR',  #  Wings of wrath
    0x054 : 'ARTIINVU',  #  Ring of invulnerability
    0x055 : 'SHLDA0',    #  Silver shield
    0x056 : 'ARTIPWBK',  #  Tome of power
    0x057 : 'VLCOE0',    #  Volcano
    0x05a : 'CLNKA1',    #  Sabreclaw
    0x05c : 'SNKEA1',    #  Ophidian
    0x05e : 'KGZBA0',    #  Blue orb
    0x05f : 'KGZGA0',    #  Green orb
    0x060 : 'KGZYA0',    #  Yellow orb
    0x4b0 : 'TELEA0',    #  Scream
    0x4b1 : 'TELEA0',    #  Squish
    0x4b2 : 'TELEA0',    #  Water drops
    0x4b3 : 'TELEA0',    #  Slow footsteps
    0x4b4 : 'TELEA0',    #  Heartbeat
    0x4b5 : 'TELEA0',    #  Bells
    0x4b6 : 'TELEA0',    #  Growl
    0x4b7 : 'TELEA0',    #  Magic
    0x4b8 : 'TELEA0',    #  Laughter
    0x4b9 : 'TELEA0',    #  Running footsteps
    0x7d1 : 'WBOWA0',    #  Crossbow
    0x7d2 : 'WMCEA0',    #  Mace
    0x7d3 : 'WPHXA0',    #  Phoenix rod
    0x7d4 : 'WSKLA0',    #  Hellstaff
    0x7d5 : 'WGNTA0',    #  Gauntlets
    0x7f3 : 'PPODA0',    #  Pod
}

hexendic = { # This one also from Wadauthor. Thanks John Williston. :)
    0x001  : 'PLAYA1'  ,  # Player 1 *( number, -, -, -, - )
    0x002  : 'PLAYA1'  ,  # Player 2 *( number, -, -, -, - )
    0x003  : 'PLAYA1'  ,  # Player 3 *( number, -, -, -, - )
    0x004  : 'PLAYA1'  ,  # Player 4 *( number, -, -, -, - )
    0x005  : 'STTWA0'  ,  # Gargoyle statue w/skull
    0x006  : 'RCK1A0'  ,  # Rock w/moss (tiny)
    0x007  : 'RCK2A0'  ,  # Rock w/moss (small)
    0x009  : 'RCK3A0'  ,  # Rock w/moss (medium)
    0x00a  : 'WCSSA0'  ,  # Serpent staff
    0x00b  : 'PLAYF1'  ,  # Deathmatch *( number, -, -, -, - )
    0x00c  : 'WFR1A0'  ,  # Quietus blade
    0x00d  : 'WFR2A0'  ,  # Quietus guard
    0x00e  : 'TELEG0'  ,  # Destination
    0x00f  : 'RCK4A0'  ,  # Rock w/moss (large)
    0x010  : 'WFR3A0'  ,  # Quietus hilt
    0x011  : 'CDLRA0'  ,  # Chandelier w/flame
    0x012  : 'WCH1A0'  ,  # Wraithverge head
    0x013  : 'WCH2A0'  ,  # Wraithverge centerpiece
    0x014  : 'WCH3A0'  ,  # Wraithverge grip
    0x015  : 'WMS1A0'  ,  # Bloodscourge head
    0x016  : 'WMS2A0'  ,  # Bloodscourge centerpiece
    0x017  : 'WMS3A0'  ,  # Bloodscourge grip
    0x018  : 'TRE1A0'  ,  # Tree trunk (brown)
    0x019  : 'TRE1A0'  ,  # Tree trunk (brown, destructable)
    0x01a  : 'TRE2A0'  ,  # Tree (tall)
    0x01b  : 'TRE3A0'  ,  # Tree (cypress)
    0x01c  : 'STM1A0'  ,  # Tree stump (splintered)
    0x01d  : 'STM2A0'  ,  # Tree stump
    0x01e  : 'ARTIPORK',  # Porkalator
    0x01f  : 'DEMNA1'  ,  # Chaos serpent (fire)
    0x020  : 'ARTISPHL',  # Mystic urn
    0x021  : 'ARTITRCH',  # Torch
    0x022  : 'WRTHA1'  ,  # Reiver
    0x024  : 'ARTIATLP',  # Chaos device
    0x025  : 'STM3A0'  ,  # Stump w/moss (short)
    0x026  : 'STM4A0'  ,  # Stump w/moss (tall)
    0x027  : 'MSH1A0'  ,  # Mushroom (large, left)
    0x028  : 'MSH2A0'  ,  # Mushroom (large, right)
    0x029  : 'MSH3A0'  ,  # Mushroom (medium, left)
    0x02a  : 'MSH4A0'  ,  # Mushroom (small, right)
    0x02c  : 'MSH5A0'  ,  # Mushroom (small, light)
    0x02d  : 'MSH6A0'  ,  # Mushroom (small, forward)
    0x02e  : 'MSH7A0'  ,  # Mushroom (small, backward)
    0x02f  : 'MSH8A0'  ,  # Mushroom (small, morel)
    0x030  : 'SGMPA0'  ,  # Stalagmite/stalactite combo
    0x031  : 'SGM1A0'  ,  # Stalagmite (large)
    0x032  : 'SGM2A0'  ,  # Stalagmite (medium)
    0x033  : 'SGM3A0'  ,  # Stalagmite (small)
    0x034  : 'SLC1A0'  ,  # Stalactite (large)
    0x035  : 'WMCSA0'  ,  # Frost shards
    0x036  : 'WLTRA0'  ,  # Wall torch w/flame
    0x037  : 'WLTRI0'  ,  # Wall torch
    0x038  : 'SLC2A0'  ,  # Stalactite (medium)
    0x039  : 'SLC3A0'  ,  # Stalactite (small)
    0x03a  : 'MSS1A0'  ,  # Moss (three strands)
    0x03b  : 'MSS2A0'  ,  # Moss (one strand)
    0x03c  : 'TRE3A0'  ,  # Vine
    0x03d  : 'CPS1A0'  ,  # Corpse (impaled)
    0x03e  : 'CPS2A0'  ,  # Corpse (sleeping)
    0x03f  : 'TMS1A0'  ,  # Tombstone (R.I.P.)
    0x040  : 'TMS2A0'  ,  # Tombstone (Shane)
    0x041  : 'TMS3A0'  ,  # Tombstone (large cross)
    0x042  : 'TMS4A0'  ,  # Tombstone (Brian R.)
    0x043  : 'TMS5A0'  ,  # Tombstone (circular cross)
    0x044  : 'TMS6A0'  ,  # Tombstone (small cross on pedestal)
    0x045  : 'TMS7A0'  ,  # Tombstone (Brian P.)
    0x047  : 'CPS3A0'  ,  # Corpse (hung upside-down)
    0x048  : 'STT2A0'  ,  # Stone gargoyle (tall)
    0x049  : 'STT3A0'  ,  # Stone gargoyle (tall, frozen)
    0x04a  : 'STT4A0'  ,  # Stone gargoyle (short)
    0x04c  : 'STT5A0'  ,  # Stone gargoyle (short, frozen)
    0x04d  : 'BNR1A0'  ,  # Banner
    0x04e  : 'TRE4A0'  ,  # Tree w/leaves (brown, right)
    0x04f  : 'TRE5A0'  ,  # Tree w/leaves (brown, left)
    0x050  : 'TRE6A0'  ,  # Tree (gnarled)
    0x051  : 'PTN1A0'  ,  # Crystal vial (10)
    0x052  : 'PTN2A0'  ,  # Quartz flask (25)
    0x053  : 'SOARA0'  ,  # Wings of wrath
    0x054  : 'INVUA0'  ,  # Icon of the defender
    0x056  : 'ARTISUMN',  # Dark servant
    0x057  : 'TRE7A0'  ,  # Tree (gnarled, w/vine)
    0x058  : 'LOGGA0'  ,  # Log
    0x059  : 'ICT1A0'  ,  # Ice stalactite (large)
    0x05a  : 'ICT2A0'  ,  # Ice stalactite (medium)
    0x05b  : 'ICT3A0'  ,  # Ice stalactite (small)
    0x05c  : 'ICT4A0'  ,  # Ice stalactite (tiny)
    0x05d  : 'ICM1A0'  ,  # Ice stalagmite (large)
    0x05e  : 'ICM2A0'  ,  # Ice stalagmite (medium)
    0x05f  : 'ICM3A0'  ,  # Ice stalagmite (small)
    0x060  : 'ICM4A0'  ,  # Ice stalagmite (tiny)
    0x061  : 'RKBLA0'  ,  # Rock formation (large, brown)
    0x062  : 'RKBSA0'  ,  # Rock formation (small, brown)
    0x063  : 'RKBKA0'  ,  # Rock formation (small, gray)
    0x064  : 'RBL1A0'  ,  # Rubble (large)
    0x065  : 'RBL2A0'  ,  # Rubble (small)
    0x066  : 'RBL3A0'  ,  # Rubble (medium)
    0x067  : 'VASEA0'  ,  # Vase on pedestal
    0x068  : 'POT1A0'  ,  # Pot (tall, skinny)
    0x069  : 'POT2A0'  ,  # Pot (medium, skinny)
    0x06a  : 'POT3A0'  ,  # Pot (short, chipped)
    0x06b  : 'CENTC1'  ,  # Centaur
    0x06c  : 'CPS4A0'  ,  # Corpse (hung by neck)
    0x06d  : 'CPS5A0'  ,  # Corpse (bleeding, hung by neck)
    0x06e  : 'CPS6A0'  ,  # Corpse (chained to floor)
    0x06f  : 'BDPLA0'  ,  # Pool of blood
    0x071  : 'LEF1A0'  ,  # Blowing leaves
    0x072  : 'BISHA1'  ,  # Dark bishop
    0x073  : 'CENTF1'  ,  # Centaur leader
    0x074  : 'TWTRA0'  ,  # Brazier w/flame
    0x075  : 'TWTRI0'  ,  # Brazier
    0x076  : 'TLGLA0'  ,  # Magic step (sparkling)
    0x077  : 'CNDLA0'  ,  # Candles
    0x078  : 'SSPTD0'  ,  # Stalker leader
    0x079  : 'SSDVA0'  ,  # Stalker
    0x07a  : 'MAN1A0'  ,  # Blue mana
    0x07b  : 'WFHMA0'  ,  # Hammer of retribution
    0x07c  : 'MAN2A0'  ,  # Green mana
    0x08c  : 'TSMKA0'  ,  # Sparkling red smoke
    0x0fe  : 'DRAGA1'  ,  # Death wyvern *( tag, tag, tag, tag, tag )
    0x578  : 'TELEA0'  ,  # Stone
    0x579  : 'TELEA0'  ,  # Heavy
    0x57a  : 'TELEA0'  ,  # Metal
    0x57b  : 'TELEA0'  ,  # Creak
    0x57c  : 'TELEA0'  ,  # Silent
    0x57d  : 'TELEA0'  ,  # Lava
    0x57e  : 'TELEA0'  ,  # Water
    0x57f  : 'TELEA0'  ,  # Ice
    0x580  : 'TELEA0'  ,  # Earth crack
    0x581  : 'TELEA0'  ,  # Metal2
    0x582  : 'TELEA0'  ,  # Wind blowing
    0xbb8  : 'ICPRD0'  ,  # Polyobject anchor
    0xbb9  : 'SBFXH0'  ,  # Start spot
    0xbba  : 'SBFXC0'  ,  # Start spot w/crush
    0x1f40  : 'ARTIPSBG', # Flechette
    0x1f42  : 'ARTISPED', # Boots of speed
    0x1f43  : 'ARTIBMAN', # Krater of might
    0x1f44  : 'MAN3A0'  , # Combined mana
    0x1f45  : 'ARM1A0'  , # Mesh armor
    0x1f46  : 'ARM2A0'  , # Falcon shield
    0x1f47  : 'ARM3A0'  , # Platinum helmet
    0x1f48  : 'ARM4A0'  , # Amulet of warding
    0x1f49  : 'WCFMA0'  , # Firestorm
    0x1f4a  : 'WFAXA0'  , # Timon's axe
    0x1f54  : 'ICEYA1'  , # Wendigo
    0x1f5e  : 'KEY1A0'  , # Steel key
    0x1f5f  : 'KEY2A0'  , # Cave key
    0x1f60  : 'KEY3A0'  , # Axe key
    0x1f61  : 'KEY4A0'  , # Fire key
    0x1f62  : 'KEY5A0'  , # Emerald key
    0x1f63  : 'KEY6A0'  , # Dungeon key
    0x1f64  : 'KEY7A0'  , # Silver key
    0x1f65  : 'KEY8A0'  , # Rusted key
    0x1f66  : 'KEY9A0'  , # Horn key
    0x1f67  : 'KEYAA0'  , # Swamp key
    0x1f68  : 'WMLGF0'  , # Arc of death
    0x1f69  : 'ARTIBRAC', # Dragonskin bracers
    0x1f6a  : 'FBULA0'  , # Minotaur statue w/flame
    0x1f6b  : 'FBULH0'  , # Minotaur statue
    0x1f6c  : 'GAR1A0'  , # Wooden gargoyle on rocks (tall)
    0x1f6d  : 'GAR2A0'  , # Black/red gargoyle on rocks (tall)
    0x1f6e  : 'GAR3A0'  , # Red gargoyle on rocks (tall)
    0x1f6f  : 'GAR4A0'  , # Wooden gargoyle on pedestal (tall)
    0x1f70  : 'GAR5A0'  , # Metal gargoyle on pedestal (tall)
    0x1f71  : 'GAR6A0'  , # Black/red gargoyle (short)
    0x1f72  : 'GAR7A0'  , # Red gargoyle (short)
    0x1f73  : 'GAR8A0'  , # Wooden gargoyle (short)
    0x1f74  : 'GAR9A0'  , # Metal gargoyle (short)
    0x1f7c  : 'FSKLA0'  , # Fire skull
    0x1f7d  : 'BRTRA0'  , # Brazier w/flame (small)
    0x1f7e  : 'TRE1A0'  , # Tree (gray, destructable)
    0x1f7f  : 'CDLRD0'  , # Chandelier
    0x1f80  : 'SUITA0'  , # Suit of armor (destructable)
    0x1f81  : 'BBLLA0'  , # Bell
    0x1f82  : 'CANDA0'  , # Candle (blue)
    0x1f83  : 'IRONA0'  , # Iron maiden
    0x1f84  : 'XMASA0'  , # Tree (fir)
    0x1f85  : 'CDRNB0'  , # Cauldron (w/flame)
    0x1f86  : 'CDRNA0'  , # Cauldron
    0x1f87  : 'CHNSA0'  , # Chain (short)
    0x1f88  : 'CHNSB0'  , # Chain (long)
    0x1f89  : 'CHNSC0'  , # Chain w/heart on hook
    0x1f8a  : 'CHNSD0'  , # Chain w/large hook
    0x1f8b  : 'CHNSE0'  , # Chain w/small hook
    0x1f8c  : 'CHNSF0'  , # Chain w/spiked ball
    0x1f8d  : 'CHNSG0'  , # Chain w/skull on hook
    0x1f90  : 'DEM2A1'  , # Chaos serpent (gas)
    0x1fa4  : 'BARLA0'  , # Barrel
    0x1fa5  : 'SHB1A0'  , # Shrub (small)
    0x1fa6  : 'SHB2A0'  , # Shrub (large)
    0x1fa7  : 'BCKTA0'  , # Bucket (hanging)
    0x1fa8  : 'SHRMA0'  , # Mushroom (exploding)
    0x2008  : 'KEYBA0'  , # Castle key
    0x2134  : 'TST1A0'  , # Stein (tall)
    0x2135  : 'TST2A0'  , # Stein (short)
    0x2136  : 'TST3A0'  , # Candle w/spider's web
    0x2137  : 'TST4A0'  , # Candle (short)
    0x2138  : 'TST5A0'  , # Candle (tall)
    0x2139  : 'TST6A0'  , # Goblet (spilled)
    0x213a  : 'TST7A0'  , # Goblet (tall)
    0x213b  : 'TST8A0'  , # Goblet (short)
    0x213c  : 'TST9A0'  , # Goblet w/silver bands
    0x213d  : 'TST0A0'  , # Meat cleaver
    0x2329  : 'TELEC0'  , # Map spot *( tag, tag, tag, tag, tag )
    0x232a  : 'ARTISKLL', # Yorick's skull
    0x232b  : 'ARTIBGEM', # Heart of D'Sparil
    0x232c  : 'ARTIGEMR', # Ruby planet
    0x232d  : 'ARTIGEMG', # Emerald planet 1
    0x232e  : 'ARTIGEMB', # Sapphire planet 1
    0x232f  : 'ABK1A0'  , # Daemon codex
    0x2330  : 'ABK2A0'  , # Liber oscura
    0x2331  : 'ARTIGMG2', # Emerald planet 2
    0x2332  : 'ARTIGMB2', # Sapphire planet 2
    0x2333  : 'STWNA0'  , # Gargoyle statue
    0x2334  : 'GMPDA0'  , # Pedestal
    0x2335  : 'TELED0'  , # Map spot w/gravity
    0x2336  : 'ARTISKL2', # Flame mask
    0x2337  : 'ARTIFWEP', # Glaive seal
    0x2338  : 'ARTICWEP', # Holy relic
    0x2339  : 'ARTIMWEP', # Sigil of the Magus
    0x233a  : 'ARTIGEAR', # Clock gear
    0x233b  : 'ARTIGER2', # Clock gear (bronze)
    0x233c  : 'ARTIGER3', # Clock gear (bronze hub)
    0x233d  : 'ARTIGER4', # Clock gear (bronze ring)
    0x2710  : 'SPIRK0'  , # Spawn fog 
    0x2711  : 'FOGSA0'  , # Fog (small)
    0x2712  : 'FOGMA0'  , # Fog (medium) 
    0x2713  : 'FOGLA0'  , # Fog (large)
    0x271b  : 'WRTHE1'  , # Reiver leader
    0x272e  : 'ETTNA1'  , # Ettin
    0x2738  : 'ARTITELO', # Banishment device
    0x274c  : 'FDMNA1'  , # Fire gargoyle
    0x2760  : 'SORCA1'  , # Heresiarch
    0x276a  : 'TSPKC0'  , # Spike (down)
    0x276b  : 'TSPKA0'  , # Spike (up)
    0x2774  : 'PLAYA8'  , # Zedek (fighter boss)
    0x2775  : 'CLERA8'  , # Traductus (cleric boss)
    0x2776  : 'MAGEA8'  , # Menelkir (mage boss)
    0x277e  : 'ARTIBLST', # Disc of repulsion
    0x2788  : 'ARTIHRAD', # Mystic ambient incant
    0x27d8  : 'KORXA1'  , # Korax
    0x27f1  : 'ABATC3C7', # Spawn bat 
    0x2904  : 'FFSMA0'  , # Flame (small, timed) 
    0x2905  : 'FFSMC0'  , # Flame (small, continuous)
    0x2906  : 'FFLGA0'  , # Flame (large, timed) 
    0x2907  : 'FFLGF0'    # Flame (large, continuous)   
}

strifedic = { # From Yadex.
      22 : 'ROB2P0' , # "Crusader wreck"            
      24 : 'KLAXA0' , # "Siren"                     
      33 : 'TRE1A0' , # "Dead tree"                 
      44 : 'STATA0' , # "Statue"                    
      46 : 'LANTA0' , # "Lantern"                   
      48 : 'MONIA0' , # "Electrical column"         
      50 : 'LOGSA0' , # "Torch on a stand"          
      51 : 'TREEA0' , # "Palm tree"                 
      60 : 'BUSHA0' , # "Small shrub"               
      62 : 'SHRBA0' , # "Shrub"                     
      82 : 'BARWA0' , # "Wood barrel"               
      94 : 'BARTA0' , # "Barrel"                    
     112 : 'WTFTA0' , # "Fountain"                  
     165 : 'MUGGA0'   , # "Mug"                       
     194 : 'ANVLA0' , # "Anvil"                     
     202 : 'TREEB0' , # "Tree"                      
     215 : 'LOGGA0' , # "Wood in water"             
      23 : 'TELPA0' , # "Teleporter marker"         
      70 : 'BARLA0' , # "Flaming barrel?"           
     103 : 'DRIPC0' , # "Dripping water pt 1?"      
      53 : 'DRIPC0' , # "Dripping water pt 2?"      
     204 : 'NEALA1' , # "Holographic monk"          
     208 : 'HOGNA0' , # "Gun range target"          
      85 : 'RATTB2B8', # "Rat"                       8
     189 : 'STOLA0' , # "Three-Legged stool"        
     117 : 'CRABA0' , # "Medical device"            
    2011 : 'STMPA0' , # "Med patch"                 
    2012 : 'MDKTA0' , # "Medical kit"               
    2018 : 'ARM2A0' , # "Leather armor"             
    2019 : 'ARM1A0' , # "Metal armor"               
    2024 : 'SHD1A0' , # "Shadow armor"              
      34 : 'CNDLA0' , # "Candle"                    
      95 : 'LITSA0' , # "Grey FT lamp"              
     107 : 'TRCHA0' , # "Wall torch"                
     225 : 'SPDLA0' , # "Alien lamp"                
     106 : 'BRAZA0' , # "Brazier"                   
     105 : 'BOWLA0' , # "Bowl with fire"            
      58 : 'AGRDC1' , # "Beige Acolyte"     Should these be different?
     147 : 'AGRDC1' , # "Green Acolyte"     
     148 : 'AGRDC1' , # "Acolyte (red ?)"           
    3002 : 'AGRDC1' , # "Beige Acolyte"             
     143 : 'AGRDC1' , # "Brown Acolyte"             
     142 : 'AGRDC1' , # "Acolyte w/key"             
     146 : 'AGRDF8' , # "Aggressive Acolyte"        
     186 : 'SPIDJ4' , # "Stalker"                   
    3006 : 'SEWRC1' , # "Sentinel"                  
    3003 : 'PGRDA1' , # "Templar"                   
    3001 : 'ROB1A1' , # "Reaver"                    
    3005 : 'ROB2A2' , # "Crusader"                  
      16 : 'ROB3A1' , # "Inquisitor"                
      71 : 'PRGRH0' , # "Programmer?"               
     187 : 'MLDRA1' , # "Bishop?"                   
      76 : 'ALN1A0' , # "Oracle's specter"          
      12 : 'PRSTA0' , # "Loremaster"                
      26 : 'NESTA1' , # "Entity nest? (pod?)"       
     198 : 'PODDD0' , # "Entity pod? (nest?)"       
      27 : 'TURTA0' , # "Turret"                    
      72 : 'MRBDA0' , # "Bar keeper"                 # Brownish, sandy brown
      73 : 'MRBDA0' , # "Armourer"                   # Nat, nat
      74 : 'MRBDA0'   , # "Gerard"                     # Beige ?
     116 : 'MRBDA0' , # "Bowyer/Feris"               # Green, black
      65 : 'PEASA1' , # "Harris"                     # Red
     130 : 'PEASA1' , # "Peasant (beige)"            # Default (beige)
     132 : 'PEASA1' , # "Harris"                     # Red
     137 : 'PEASA1' , # "Peasant (brown)"            # Brown
     169 : 'PEASA1' , # "Spawned peasant"            # Red
     170 : 'PEASA1' , # "Peasant spawner"            # Red
     173 : 'PEASA1' , # "Peasant (green)"            # Green
     181 : 'PEASA1' , # "Governor Mourel"            # Cyan
    3004 : 'PEASA1' , # "Peasant (beige)"            # Default (beige)
     172 : 'PEASA1' , # "Richter"                    # Dark green
      66 : 'PEASA1' , # "Advisor"                    # Grey
      67 : 'PEASA1' , # "Person"                     # Brown
     134 : 'PEASA1' , # "Macil's advisor"            # Grey
     135 : 'PEASA1' , # "Advisor"                    # Grey
     136 : 'PEASA1' , # "Person"                     # Brown
     141 : 'BEGRD1' , # "MacGuffin/beggar"          
     199 : 'ORCLA1' , # "Oracle"                    
      64 : 'LEDRA1' , # "Macil (unkillable)"        
     200 : 'LEADA1' , # "Macil (killable)"          
       9 : 'HMN1A1' , # "Rebel"                     
     144 : 'HMN1A1' , # "Rebel (operator?)"         
     145 : 'HMN1A1' , # "Rebel"                     
     150 : 'HMN1A1' , # "Rebel"                     
       1 : 'PLAYA1' , # "Player 1 start"            
       2 : 'PLAYB1' , # "Player 2 start"            
       3 : 'PLAYC1' , # "Player 3 start"            
       4 : 'PLAYD1' , # "Player 4 start"            
      11 : 'PLAYF1' , # "Deathmatch start"          
      14 : 'TFOGA0' , # "Teleport exit"             
      69 : 'PLAYA5' , # "Level-change marker"       
     118 : 'PLAYE1' , # "Scoot spot 1"              
     119 : 'PLAYE2' , # "Scoot spot 2"              
     120 : 'PLAYE3' , # "Scoot spot 3"              
     121 : 'PLAYE4' , # "Scoot spot 4"              
     122 : 'PLAYE5' , # "Scoot spot 5"              
     123 : 'PLAYE6' , # "Scoot spot 6"              
     124 : 'PLAYE7' , # "Scoot spot 7"              
     125 : 'PLAYE8' , # "Scoot spot 8"              
    2001 : 'CBOWA0' , # "Cross bow"                 
    2002 : 'RIFLA0' , # "Assault gun"               
    2003 : 'MMSLA0' , # "Mini-missile launcher"     
    2005 : 'FLAMA0' , # "Flame thrower"             
     154 : 'GRNDA0' , # "Grenade launcher"          
    2004 : 'TRPDA0' , # "Mauler"                    
    2006 : 'RIFLA0' , # "Pulse rifle"               
      81 : 'SIGLE0' , # "Sigil (assembled)"         
    2007 : 'BLITA0' , # "Clip of bullets"           
    2048 : 'BBOXA0' , # "Ammo"                      
     115 : 'PQRLA0' , # "Poison bolts"              
     114 : 'XQRLA0' , # "Electric bolts"            
     152 : 'GRN1A0' , # "He-grenade rounds"         
     153 : 'GRN2A0' , # "Phosphorous grenades"      
    2010 : 'MSSLA0' , # "Rocket"                    
    2046 : 'ROKTA0' , # "Box of rockets"            
    2047 : 'BRY1A0' , # "Energy pod"                 #ok
      17 : 'CPACA0' , # "Energy pack"               
     138 : 'CREDA0' , # "10 gold"                   
      10 : 'BEACA0' , # "Teleporter beacon"         
     207 : 'TARGA0' , # "Targeter"                  
    2025 : 'MASKA0' , # "Environmental suit"        
    2026 : 'PMAPA0' , # "Map"                       
      59 : 'XPRKA0' , # "Degnin ore"                
     205 : 'RELCA0' , # "Chalice"                   
     220 : 'COUPA0' , # "The Front's coupling"      
     226 : 'COUPC0' , # "Junked coupling"           
      52 : 'OFICA0' , # "Officer's uniform"         
     113 : 'HERTA0' , # "Preserved hearts"          
     213 : 'TNK4A0' , # "Preserved spine"           
     229 : 'TNK6A0' , # "Preserved brain"           
     201 : 'ARMRA0' , # "Partial Acolyte"           
     209 : 'TNK1A0' , # "Tank of bodies 1"          
     210 : 'TNK2A0' , # "Tank of bodies 2"          
     211 : 'TNK3A0' , # "Tank of bodies 3"          
}

# Level names for the different games.

doomlevelnames = {
    'E1M1' : 'Hangar',
    'E1M2' : 'Nuclear Plant',
    'E1M3' : 'Toxin Refinery',
    'E1M4' : 'Command Control',
    'E1M5' : 'Phobos Lab',
    'E1M6' : 'Central Processing',
    'E1M7' : 'Computer Station',
    'E1M8' : 'Phobos Anomaly',
    'E1M9' : 'Military Base',
    'E2M1' : 'Deimos Anomaly',
    'E2M2' : 'Containment Area',
    'E2M3' : 'Refinery',
    'E2M4' : 'Deimos Lab',
    'E2M5' : 'Command Center',
    'E2M6' : 'Halls of the Damned',
    'E2M7' : 'Spawning Vats',
    'E2M8' : 'Tower of Babel',
    'E2M9' : 'Fortress of Mystery',
    'E3M1' : 'Hell Keep',
    'E3M2' : 'Slough of Despair',
    'E3M3' : 'Pandemonium',
    'E3M4' : 'House of Pain',
    'E3M5' : 'Unholy Cathedral',
    'E3M6' : 'Mt. Erebus',
    'E3M7' : 'Limbo',
    'E3M8' : 'Dis',
    'E3M9' : 'Warrens',
    'E4M1' : 'Hell Beneath',
    'E4M2' : 'Perfect Hatred',
    'E4M3' : 'Sever the Wicked',
    'E4M4' : 'Unruly Evil',
    'E4M5' : 'They Will Repent',
    'E4M6' : 'Against Thee Wickedly',
    'E4M7' : 'And Hell Followed',
    'E4M8' : 'Unto The Cruel',
    'E4M9' : 'Fear'
    }

doom2levelnames = {
    'MAP01' : 'Entryway',
    'MAP02' : 'Underhalls',
    'MAP03' : 'The Gantlet',
    'MAP04' : 'The Focus',
    'MAP05' : 'The Waste Tunnels',
    'MAP06' : 'The Crusher',
    'MAP07' : 'Dead Simple',
    'MAP08' : 'Tricks and Traps',
    'MAP09' : 'The Pit',
    'MAP10' : 'Refueling Base',
    'MAP11' : 'Circle of Death',
    'MAP12' : 'The Factory',
    'MAP13' : 'Downtown',
    'MAP14' : 'The Inmost Dens',
    'MAP15' : 'Industrial Zone',
    'MAP16' : 'Suburbs',
    'MAP17' : 'Tenements',
    'MAP18' : 'The Courtyard',
    'MAP19' : 'The Citadel',
    'MAP20' : 'Gotcha!',
    'MAP21' : 'Nirvana',
    'MAP22' : 'The Catacombs',
    'MAP23' : 'Barrels o\' Fun',
    'MAP24' : 'The Chasm',
    'MAP25' : 'Bloodfalls',
    'MAP26' : 'The Abandoned Mines',
    'MAP27' : 'Monster Condo',
    'MAP28' : 'The Spirit World',
    'MAP29' : 'The Living End',
    'MAP30' : 'Icon of Sin',
    'MAP31' : 'Wolfenstein',
    'MAP32' : 'Grosse'
    }

plutonialevelnames = {
    'MAP01' : 'Congo',
    'MAP02' : 'Well of Souls',
    'MAP03' : 'Aztec',
    'MAP04' : 'Caged',
    'MAP05' : 'Ghost Town',
    'MAP06' : 'Baron\'s Lair',
    'MAP07' : 'Caughtyard',
    'MAP08' : 'Realm',
    'MAP09' : 'Abattoire',
    'MAP10' : 'Onslaught',
    'MAP11' : 'Hunted',
    'MAP12' : 'Speed',
    'MAP13' : 'The Crypt',
    'MAP14' : 'Genesis',
    'MAP15' : 'The Twilight',
    'MAP16' : 'The Omen',
    'MAP17' : 'Compound',
    'MAP18' : 'Neurosphere',
    'MAP19' : 'NME',
    'MAP20' : 'The Death Domain',
    'MAP21' : 'Slayer',
    'MAP22' : 'Impossible Mission',
    'MAP23' : 'Tombstone',
    'MAP24' : 'The Final Frontier',
    'MAP25' : 'The Temple of Darkness',
    'MAP26' : 'Bunker',
    'MAP27' : 'Anti-Christ',
    'MAP28' : 'The Sewers',
    'MAP29' : 'Odyssey of Noises',
    'MAP30' : 'The Gateway to Hell',
    'MAP31' : 'Cyberden',
    'MAP32' : 'Go 2 It'
    }

tntlevelnames = {
    'MAP01' : 'System Control',
    'MAP02' : 'Human BBQ',
    'MAP03' : 'Power Control',
    'MAP04' : 'Wormhole',
    'MAP05' : 'Hanger',
    'MAP06' : 'Open Season',
    'MAP07' : 'Prison',
    'MAP08' : 'Metal',
    'MAP09' : 'Stronghold',
    'MAP10' : 'Redemption',
    'MAP11' : 'Storage Facility',
    'MAP12' : 'Crater',
    'MAP13' : 'Nukage Processing',
    'MAP14' : 'Steel Works',
    'MAP15' : 'Dead Zone',
    'MAP16' : 'Deepest Reaches',
    'MAP17' : 'Processing Area',
    'MAP18' : 'Mill',
    'MAP19' : 'Shipping/Respawning',
    'MAP20' : 'Central Processing',
    'MAP21' : 'Administration Center',
    'MAP22' : 'Habitat',
    'MAP23' : 'Lunar Mining Project',
    'MAP24' : 'Quarry',
    'MAP25' : 'Baron\'s Den',
    'MAP26' : 'Ballistyx',
    'MAP27' : 'Mount Pain',
    'MAP28' : 'Heck',
    'MAP29' : 'River Styx',
    'MAP30' : 'Last Call',
    'MAP31' : 'Pharaoh',
    'MAP32' : 'Caribbean'
    }

hereticlevelnames = {
    'E1M1' : 'The Docks',
    'E1M2' : 'The Dungeons',
    'E1M3' : 'The Gatehouse',
    'E1M4' : 'The Guard Tower',
    'E1M5' : 'The Citadel',
    'E1M6' : 'The Cathedral',
    'E1M7' : 'The Crypts',
    'E1M8' : 'Hell\'s Maw',
    'E1M9' : 'The Graveyard',
    'E2M1' : 'The Crater',
    'E2M2' : 'The Lava pits',
    'E2M3' : 'The River of Fire',
    'E2M4' : 'The Ice Grotto',
    'E2M5' : 'The Catacombs',
    'E2M6' : 'The Labyrinth',
    'E2M7' : 'The Great Hall',
    'E2M8' : 'The Portals of Chaos',
    'E2M9' : 'The Glacier',
    'E3M1' : 'The Storehouse',
    'E3M2' : 'The Cesspool',
    'E3M3' : 'The Confluence',
    'E3M4' : 'The Azure Fortress',
    'E3M5' : 'The Ophidian Lair',
    'E3M6' : 'The Halls of Fear',
    'E3M7' : 'The Chasm',
    'E3M8' : 'D\'Sparil\'s Keep',
    'E3M9' : 'The Aquifer',
    'E4M1' : 'The Catafalque',
    'E4M2' : 'Blockhouse',
    'E4M3' : 'Ambulatory',
    'E4M4' : 'Sepulcher',
    'E4M5' : 'Great Stair',
    'E4M6' : 'Halls of the Apostate',
    'E4M7' : 'Rampants of Perdition',
    'E4M8' : 'Shattered Bridge',
    'E4M9' : 'Mausoleum',
    'E5M1' : 'Ochre Cliffs',
    'E5M2' : 'Rapids',
    'E5M3' : 'Quay',
    'E5M4' : 'Courtyard',
    'E5M5' : 'Hydratyr',
    'E5M6' : 'Colonnade',
    'E5M7' : 'Foetid Manse',
    'E5M8' : 'Field of Judgement',
    'E5M9' : 'Skein of D\'Sparil'
    }

hexenlevelnames = {
    'MAP01' : 'Winnowing Hall',
    'MAP02' : 'Seven Portals',
    'MAP03' : 'Guardian of Ice',
    'MAP04' : 'Guardian of Fire',
    'MAP05' : 'Guardian of Steel',
    'MAP06' : 'Bright Crucible',
    'MAP07' : 'Shadow Wood',
    'MAP08' : 'Darkmere',
    'MAP09' : 'Caves of Circe',
    'MAP10' : 'Wastelands',
    'MAP11' : 'Sacred Grove',
    'MAP12' : 'Hypostyle',
    'MAP13' : 'Shadow Wood',
    'MAP14' : 'Swamp Demo',
    'MAP27' : 'Heresiarch\'s Seminary',
    'MAP28' : 'Dragon Chapel',
    'MAP29' : 'Nada',
    'MAP30' : 'Griffin Chapel',
    'MAP31' : 'Deathwind Chapel',
    'MAP32' : 'Orchard of Lamentations',
    'MAP33' : 'Silent Refectory',
    'MAP34' : 'Wolf Chapel',
    'MAP21' : 'Forsaken Outpost',
    'MAP22' : 'Castle of Grief',
    'MAP23' : 'Gibbet',
    'MAP24' : 'Effluvium',
    'MAP25' : 'Dungeons',
    'MAP26' : 'Desolate Garden',
    'MAP35' : 'Necropolis',
    'MAP36' : 'Zedek\'s Tomb',
    'MAP37' : 'Menelkir\'s Tomb',
    'MAP38' : 'Tradactus\' Tomb',
    'MAP39' : 'Vivarium',
    'MAP40' : 'Dark Crucible',
    'MAP41' : 'Maze',
    'MAP42' : 'Eric\'s Whirlwind O\' Death',
    'MAP43' : 'Maya',
    'MAP50' : 'The Badlands',
    'MAP51' : 'Caves of Ascension',
    'MAP52' : 'Lower Crypts',
    'MAP53' : 'The Hypostyle Hall',
    'MAP54' : 'The Sanctorium',
    'MAP55' : 'The Athenaeum',
    'MAP56' : 'The Cleric\'s Citadel',
    'MAP60' : 'Programmer Map',
    'MAP90' : 'BG0KEY',
    'MAP92' : 'Paul Map',
    'MAP93' : 'Paul Map2',
    'MAP95' : 'cjr@ravensoft.com',
    'MAP96' : 'Sound Development Map'
    }

strifelevelnames = { # From the Doom wiki.
    'MAP01' : 'Sanctuary',
    'MAP02' : 'Town',
    'MAP03' : 'Front Base',
    'MAP04' : 'Power Station',
    'MAP05' : 'Prison',
    'MAP06' : 'Sewers',
    'MAP07' : 'Castle',
    'MAP08' : 'Audience Chamber',
    'MAP09' : 'Castle: Programmer\'s Keep',
    'MAP10' : 'New Front Base',
    'MAP11' : 'Borderlands',
    'MAP12' : 'The Temple of the Oracle',
    'MAP13' : 'Catacombs',
    'MAP14' : 'Mines',
    'MAP15' : 'Fortress: Administration',
    'MAP16' : 'Fortress: Bishop\'s Tower',
    'MAP17' : 'Fortress: The Bailey',
    'MAP18' : 'Fortress: Stores',
    'MAP19' : 'Fortress: Security Complex',
    'MAP20' : 'Factory: Receiving',
    'MAP21' : 'Factory: Manufacturing',
    'MAP22' : 'Factory: Forge',
    'MAP23' : 'Order Commons',
    'MAP24' : 'Factory: Conversion Chapel',
    'MAP25' : 'Catacombs: Ruined Temple',
    'MAP26' : 'Proving Grounds',
    'MAP27' : 'The Lab',
    'MAP28' : 'Alien Ship',
    'MAP29' : 'Entity\'s Lair',
    'MAP30' : 'Abandoned Front Base',
    'MAP31' : 'Training Facility',
    'MAP32' : 'Sanctuary',
    'MAP33' : 'Town',
    'MAP34' : 'Movement Base',
}

extragraphics = {
    'HELP1' : True,
    'HELP2' : True,
    'TITLEPIC' : True,
    'TITLE' : True,
    'CREDIT' : True,
    'VICTORY2' : True,
    'E2END' :  True,
    'FINAL1':  True,
    'FINAL2':  True,
    'FINALE1': True,
    'FINALE2': True,
    'FINALE3': True,
    'INTERPIC':True,
    'PFUB1' :  True,
    'PFUB2' :  True,
    'END0'  :  True,
    'END1'  :  True,
    'END2'  :  True,
    'END3'  :  True,
    'END4'  :  True,
    'END5'  :  True,
    'END6'  :  True,

    'AMMNUM0' : True,
    'AMMNUM1' : True,
    'AMMNUM2' : True,
    'AMMNUM3' : True,
    'AMMNUM4' : True,
    'AMMNUM5' : True,
    'AMMNUM6' : True,
    'AMMNUM7' : True,
    'AMMNUM8' : True,
    'AMMNUM9' : True,
    'STMBARL' : True,
    'STMBARR' : True,
    'STABARL' : True,
    'STABARR' : True,
    'STCHAT'  : True,
    'STRSNUM0' : True,
    'STRSNUM1' : True,
    'STRSNUM2' : True,
    'STRSNUM3' : True,
    'STRSNUM4' : True,
    'STRSNUM5' : True,
    'STRSNUM6' : True,
    'STRSNUM7' : True,
    'STRSNUM8' : True,
    'STRSNUM9' : True,
    'STWEAP0' : True,
    'STWEAP1' : True,
    'STWEAP2' : True,
    'STWEAP3' : True,
    'STWEAP4' : True,
    'STWEAP5' : True,
    'STFRAG6' : True,
    'STBAR'   : True,
    'STGNUM0' : True,
    'STGNUM1' : True,
    'STGNUM2' : True,
    'STGNUM3' : True,
    'STGNUM4' : True,
    'STGNUM5' : True,
    'STGNUM6' : True,
    'STGNUM7' : True,
    'STGNUM8' : True,
    'STGNUM9' : True,
    'STTNUM0' : True,
    'STTNUM1' : True,
    'STTNUM2' : True,
    'STTNUM3' : True,
    'STTNUM4' : True,
    'STTNUM5' : True,
    'STTNUM6' : True,
    'STTNUM7' : True,
    'STTNUM8' : True,
    'STTNUM9' : True,
    'STTMINUS' : True,
    'STYSNUM0' : True,
    'STYSNUM1' : True,
    'STYSNUM2' : True,
    'STYSNUM3' : True,
    'STYSNUM4' : True,
    'STYSNUM5' : True,
    'STYSNUM6' : True,
    'STYSNUM7' : True,
    'STYSNUM8' : True,
    'STYSNUM9' : True,
    'STTPRCNT' : True,
    'STKEYS0'  : True,
    'STKEYS1'  : True,
    'STKEYS2'  : True,
    'STKEYS3'  : True,
    'STKEYS4'  : True,
    'STKEYS5'  : True,
    'STDISK'   : True,
    'STCDROM'  : True,
    'STARMS'   : True,

    'STCFN033' : True,
    'STCFN034' : True,
    'STCFN035' : True,
    'STCFN036' : True,
    'STCFN037' : True,
    'STCFN038' : True,
    'STCFN039' : True,
    'STCFN040' : True,
    'STCFN041' : True,
    'STCFN042' : True,
    'STCFN043' : True,
    'STCFN044' : True,
    'STCFN045' : True,
    'STCFN046' : True,
    'STCFN047' : True,
    'STCFN048' : True,
    'STCFN049' : True,
    'STCFN050' : True,
    'STCFN051' : True,
    'STCFN052' : True,
    'STCFN053' : True,
    'STCFN054' : True,
    'STCFN055' : True,
    'STCFN056' : True,
    'STCFN057' : True,
    'STCFN058' : True,
    'STCFN059' : True,
    'STCFN060' : True,
    'STCFN061' : True,
    'STCFN062' : True,
    'STCFN063' : True,
    'STCFN064' : True,
    'STCFN065' : True,
    'STCFN066' : True,
    'STCFN067' : True,
    'STCFN068' : True,
    'STCFN069' : True,
    'STCFN070' : True,
    'STCFN071' : True,
    'STCFN072' : True,
    'STCFN073' : True,
    'STCFN074' : True,
    'STCFN075' : True,
    'STCFN076' : True,
    'STCFN077' : True,
    'STCFN078' : True,
    'STCFN079' : True,
    'STCFN080' : True,
    'STCFN081' : True,
    'STCFN082' : True,
    'STCFN083' : True,
    'STCFN084' : True,
    'STCFN085' : True,
    'STCFN086' : True,
    'STCFN087' : True,
    'STCFN088' : True,
    'STCFN089' : True,
    'STCFN090' : True,
    'STCFN091' : True,
    'STCFN092' : True,
    'STCFN093' : True,
    'STCFN094' : True,
    'STCFN095' : True,
    'STCFN121' : True,
    'STFB0' : True,
    'STFB1' : True,
    'STFB2' : True,
    'STFB3' : True,
    'STPB0' : True,
    'STPB1' : True,
    'STPB2' : True,
    'STPB3' : True,
    'STFST00' : True,
    'STFST01' : True,
    'STFST02' : True,
    'STFST10' : True,
    'STFST11' : True,
    'STFST12' : True,
    'STFST20' : True,
    'STFST21' : True,
    'STFST22' : True,
    'STFST30' : True,
    'STFST31' : True,
    'STFST32' : True,
    'STFST40' : True,
    'STFST41' : True,
    'STFST42' : True,
    'STFTL00' : True,
    'STFTL10' : True,
    'STFTL20' : True,
    'STFTL30' : True,
    'STFTL40' : True,
    'STFTR00' : True,
    'STFTR10' : True,
    'STFTR20' : True,
    'STFTR30' : True,
    'STFTR40' : True,
    'STFOUCH0' : True,
    'STFOUCH1' : True,
    'STFOUCH2' : True,
    'STFOUCH3' : True,
    'STFOUCH4' : True,
    'STFEVL0'  : True,
    'STFEVL1'  : True,
    'STFEVL2'  : True,
    'STFEVL3'  : True,
    'STFEVL4'  : True,
    'STFKILL0' : True,
    'STFKILL1' : True,
    'STFKILL2' : True,
    'STFKILL3' : True,
    'STFKILL4' : True,
    'STFGOD0'  : True,
    'STFDEAD0' : True,
    'BRDR_TL'  : True,
    'BRDR_BL'  : True,
    'BRDR_TR'  : True,
    'BRDR_BR'  : True,
    'WIBONUS'  : True,
    'WISCORE'  : True,
    'WIMSTP0'  : True,
    'WIMSTP1'  : True,
    'WIMSTP2'  : True,
    'WIMSTP3'  : True,
    'WIMSTB0'  : True,
    'WIMSTB1'  : True,
    'WIMSTB2'  : True,
    'WIMSTB3'  : True,
    'WIMINUS'  : True,
    'WIMAP0'   : True,
    'WIMAP1'   : True,
    'WIMAP2'   : True,
    'WIA00900' : True,
    'WIA00901' : True,
    'WIA00902' : True,
    'WIA00800' : True,
    'WIA00801' : True,
    'WIA00802' : True,
    'WIA00700' : True,
    'WIA00701' : True,
    'WIA00702' : True,
    'WIA00600' : True,
    'WIA00601' : True,
    'WIA00602' : True,
    'WIA00500' : True,
    'WIA00501' : True,
    'WIA00502' : True,
    'WIA00400' : True,
    'WIA00401' : True,
    'WIA00402' : True,
    'WIA00300' : True,
    'WIA00301' : True,
    'WIA00302' : True,
    'WIA00200' : True,
    'WIA00201' : True,
    'WIA00202' : True,
    'WIA00100' : True,
    'WIA00101' : True,
    'WIA00102' : True,
    'WIA00000' : True,
    'WIA00001' : True,
    'WIA00002' : True,
    'WIA10000' : True,
    'WIA10100' : True,
    'WIA10200' : True,
    'WIA10300' : True,
    'WIA10400' : True,
    'WIA10500' : True,
    'WIA10600' : True,
    'WIA10700' : True,
    'WIA10701' : True,
    'WIA10702' : True,
    'WIA20000' : True,
    'WIA20001' : True,
    'WIA20002' : True,
    'WIA20100' : True,
    'WIA20101' : True,
    'WIA20102' : True,
    'WIA20200' : True,
    'WIA20201' : True,
    'WIA20202' : True,
    'WIA20300' : True,
    'WIA20301' : True,
    'WIA20302' : True,
    'WIA20400' : True,
    'WIA20401' : True,
    'WIA20402' : True,
    'WIA20500' : True,
    'WIA20501' : True,
    'WIA20502' : True,
    'WIURH0' : True,
    'WIURH1' : True,
    'WISPLAT': True,
    'WIOSTK' : True,
    'WIOSTI' : True,
    'WIF'    : True,
    'WIMSTT' : True,
    'WIOSTS' : True,
    'WIOSTF' : True,
    'WITIME' : True,
    'WIPAR'  : True,
    'WIMSTAR': True,
    'WIPCNT' : True,
    'WINUM0' : True,
    'WINUM1' : True,
    'WINUM2' : True,
    'WINUM3' : True,
    'WINUM4' : True,
    'WINUM5' : True,
    'WINUM6' : True,
    'WINUM7' : True,
    'WINUM8' : True,
    'WINUM9' : True,
    'WICOLON' : True,
    'WISUCKS' : True,
    'WIFRGS'  : True,
    'WILV00' : True,
    'WILV01' : True,
    'WILV02' : True,
    'WILV03' : True,
    'WILV04' : True,
    'WILV05' : True,
    'WILV06' : True,
    'WILV07' : True,
    'WILV08' : True,
    'WILV10' : True,
    'WILV11' : True,
    'WILV12' : True,
    'WILV13' : True,
    'WILV14' : True,
    'WILV15' : True,
    'WILV16' : True,
    'WILV17' : True,
    'WILV18' : True,
    'WILV20' : True,
    'WILV21' : True,
    'WILV22' : True,
    'WILV23' : True,
    'WILV24' : True,
    'WILV25' : True,
    'WILV26' : True,
    'WILV27' : True,
    'WILV28' : True,
    'WIP1' : True,
    'WIP2' : True,
    'WIP3' : True,
    'WIP4' : True,
    'WIBP1' : True,
    'WIBP2' : True,
    'WIBP3' : True,
    'WIBP4' : True,
    'WIKILRS'  : True,
    'WIVCTMS'  : True,
    'WISCRT2'  : True,
    'WIENTER'  : True,
    'M_DOOM'   : True,
    'M_RDTHIS' : True,
    'M_OPTION' : True,
    'M_QUITG'  : True,
    'M_NGAME'  : True,
    'M_SKULL1' : True,
    'M_SKULL2' : True,
    'M_THERMO' : True,
    'M_THERMR' : True,
    'M_THERML' : True,
    'M_THERMM' : True,
    'M_ENDGAM' : True,
    'M_PAUSE'  : True,
    'M_MESSG'  : True,
    'M_MSGON'  : True,
    'M_MSGOFF' : True,
    'M_EPISOD' : True,
    'M_EPI1'   : True,
    'M_EPI2'   : True,
    'M_EPI3'   : True,
    'M_HURT'   : True,
    'M_JKILL'  : True,
    'M_ROUGH'  : True,
    'M_SKILL'  : True,
    'M_NEWG'   : True,
    'M_ULTRA'  : True,
    'M_NMARE'  : True,
    'M_SVOL'   : True,
    'M_OPTTTL' : True,
    'M_SAVEG'  : True,
    'M_LOADG'  : True,
    'M_DISP'   : True,
    'M_MSENS'  : True,
    'M_GDHIGH' : True,
    'M_GDLOW'  : True,
    'M_DETAIL' : True,
    'M_DISOPT' : True,
    'M_SCRNSZ' : True,
    'M_SGTTL'  : True,
    'M_LGTTL'  : True,
    'M_SFXVOL' : True,
    'M_MUSVOL' : True,
    'M_LSLEFT' : True,
    'M_LSCNTR' : True,
    'M_LSRGHT' : True,

    }


# Map Iwad name to a correspoding game.

gamemapper = {'doom1.wad' : 'Doom',
              'doom.wad' : 'Ultimate Doom',
              'doom2.wad' : 'Doom II - Hell on Earth',
              'heretic.wad' : 'Heretic: Shadow of the Serpent Riders',
              'hexen.wad' : 'Hexen: Beyond Heretic',
              'tnt.wad' : 'TNT Evilution',
              'plutonia.wad' : 'The Plutonia Experiment',
              'strife1.wad' : 'Strife - Quest for the Sigil'
              }

levelnamemapper = {
    'doom1.wad' : doomlevelnames,
    'doom.wad' : doomlevelnames,
    'doom2.wad' : doom2levelnames,
    'heretic.wad' : hereticlevelnames,
    'hexen.wad' : hexenlevelnames,
    'tnt.wad' : tntlevelnames,
    'plutonia.wad' : plutonialevelnames,
    'strife1.wad' : strifelevelnames
    }

thingdicmapper = {
    'doom1.wad' : doomdic,
    'doom.wad' : doomdic,
    'doom2.wad' : doomdic,
    'heretic.wad' : hereticdic,
    'hexen.wad' : hexendic,
    'tnt.wad' : doomdic,
    'plutonia.wad' : doomdic,
    'strife1.wad' : strifedic
    }
    
papersizedic = {
    'A0' : (2384, 2835),
    'A1' : (1684, 2384),
    'A2' : (1190, 1684),
    'A3' : (842, 1190),
    'A4' : (595, 842),
    'A5' : (420, 595),
    'LETTER' : (612, 792),
    'LEGAL' : (612, 1008),
    'TABLOID' : (1224, 792)
    }
