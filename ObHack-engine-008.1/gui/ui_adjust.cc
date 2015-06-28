//----------------------------------------------------------------
//  Adjustment screen
//----------------------------------------------------------------
//
//  Oblige Level Maker (C) 2006,2007 Andrew Apted
//  OhHack changes (C) 2007-2015 Sam Trenholme and Fritz
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//----------------------------------------------------------------

#include "headers.h"
#include "hdr_fltk.h"

#include "ui_adjust.h"
#include "ui_window.h"

#include "lib_util.h"

//
// Adjust Constructor
//
UI_Adjust::UI_Adjust(int x, int y, int w, int h, const char *label) :
    Fl_Group(x, y, w, h, label)
{
  end(); // cancel begin() in Fl_Group constructor

  box(FL_THIN_UP_BOX);
//  align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT | FL_ALIGN_TOP);



  int cy = y + 8;
  
  Fl_Box *heading = new Fl_Box(FL_FLAT_BOX, x+6, cy, 95, 24, "Adjustments");
  heading->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
  heading->labeltype(FL_NORMAL_LABEL);
  heading->labelfont(FL_HELVETICA_BOLD);
  add(heading);

  
  maxsize = new Fl_Choice(x+ 320, cy, 130, 24, "Prog/Exp. Max Level Size: ");
  maxsize->align(FL_ALIGN_LEFT);
  maxsize->add("Regular|Large|Huge|Gigantic");
  maxsize->value(2);
  
  add(maxsize);

   
  cy += 32;   // 28
 
  size = new Fl_Choice(x+ 96, cy, 130, 24, "Level Size: ");
  size->align(FL_ALIGN_LEFT);
  size->add("Tiny|Small|Regular|Large|Huge|Gigantic|Progressive|Expansion");
  size->value(2);
  size->callback(size_callback, this);

  add(size);



//enclosure = new Fl_Check_Button(x+320, cy, 130, 24, "Enclosures: ");
  enclosure = new Fl_Choice(x+320, cy, 130, 24, "Enclosures: ");
  enclosure->align(FL_ALIGN_LEFT);
  enclosure->add("On|Off");
  enclosure->value(0);

  add(enclosure);


  health = new Fl_Choice(x+550, cy, 130, 24, "Health: ");
  health->align(FL_ALIGN_LEFT);
  health->add("None|Rare|Less|Normal|More");
  health->value(3);

  add(health);

  
    
  cy += 32;   // 28
  
  questlength = new Fl_Choice(x+96, cy, 130, 24, "Quest Len: ");
  questlength->align(FL_ALIGN_LEFT);
  questlength->add("Shorter|Normal|Longer");
  questlength->value(1);

  add(questlength);



  roomsize = new Fl_Choice(x+320, cy, 130, 24, "Room Size: ");
  roomsize->align(FL_ALIGN_LEFT);
  roomsize->add("Smaller|Normal|Medium|Large|Random"); 
  roomsize->value(1);

  add(roomsize);
  
  
  ammo = new Fl_Choice(x+550, cy, 130, 24, "Ammo: ");
  ammo->align(FL_ALIGN_LEFT);
  ammo->add("None|Rare|Less|Normal|More");
  ammo->value(3);
  
  add(ammo);
  
  

  cy += 32;

  mons = new Fl_Choice(x+ 96, cy, 130, 24, "Monsters: ");
  mons->align(FL_ALIGN_LEFT);
  mons->add("Rare|Scarce|Plenty|Hordes|Swarms|Infested|Insane|Insane+Weapons");
  mons->value(2);

  add(mons);
  
  lighting = new Fl_Choice(x+320, cy, 130, 24, "Rm Lighting: ");
  lighting->align(FL_ALIGN_LEFT);
  lighting->add("None|Low|Medium|High|Higher|Random"); 
  lighting->value(0);

  add(lighting);


  switches = new Fl_Choice(x+550, cy, 130, 24, "Switches: ");
  switches->align(FL_ALIGN_LEFT);
  switches->add("Keys only|Keys + Switches|Switches only"); 
  switches->value(1);

  add(switches);
  
  

  cy += 32;
  
  puzzles = new Fl_Choice(x+ 96, cy, 130, 24, "Puzzles: ");
  puzzles->align(FL_ALIGN_LEFT);
  puzzles->add("Few|Some|Heaps");
  puzzles->value(1);

  add(puzzles);

  steep = new Fl_Choice(x+ 320, cy, 130, 24, "Steepness: ");
  steep->align(FL_ALIGN_LEFT);
  steep->add("Flat|A little|Some|Steep|Random");
  steep->value(2);

  add(steep);

  keytype = new Fl_Choice(x+550, cy, 130, 24, "Key Type: ");
  keytype->align(FL_ALIGN_LEFT);
  keytype->add("Skull Keys|Key Cards|Skulls or Cards"); 
  keytype->value(0);

  add(keytype);
 

  cy += 32;
  
  outdoors = new Fl_Choice(x+96, cy, 130, 24, "Outdoors: ");
  outdoors->align(FL_ALIGN_LEFT);
  outdoors->add("Indoors|Rare|Some|More|Lots|Outdoors"); 
  outdoors->value(2);

  add(outdoors);

  
  hallways = new Fl_Choice(x+320, cy, 130, 24, "Hallways: ");
  hallways->align(FL_ALIGN_LEFT);
  hallways->add("None|Few|Normal|Random"); 
  hallways->value(2);

  add(hallways);	


  iweapon = new Fl_Choice(x+550, cy, 130, 24, "Start weapon: ");
  iweapon->align(FL_ALIGN_LEFT);
  iweapon->add("Pistol|Shotgun|Chaingun|Launcher"); 
  iweapon->value(0);

  add(iweapon);	

  cy += 32;
  
  stairs = new Fl_Choice(x+96, cy, 130, 24, "Stairs: ");
  stairs->align(FL_ALIGN_LEFT);
  stairs->add("Lifts + stairs|Mostly stairs");
  stairs->value(0);

  add(stairs);

  secrets = new Fl_Choice(x+550, cy, 130, 24, "Secrets: ");
  secrets->align(FL_ALIGN_LEFT);
  secrets->add("None|Very Rare|Rare|Uncommon|Common");
  secrets->value(4);

  add(secrets);

  resizable(0);  // don't resize our children
}


//
// Adjust Destructor
//
UI_Adjust::~UI_Adjust()
{
}

void UI_Adjust::Locked(bool value)
{
  if (value)
  {
    size ->deactivate();
    maxsize ->deactivate();
    steep->deactivate();
    health->deactivate();
    ammo ->deactivate();
    mons ->deactivate();
    puzzles->deactivate();
    outdoors->deactivate();
    iweapon->deactivate();
    switches->deactivate();
    keytype->deactivate();
    roomsize->deactivate();
    lighting->deactivate();
    enclosure->deactivate();
    questlength->deactivate();
    hallways->deactivate();
    stairs->deactivate();
    secrets->deactivate();
  }
  else
  {
    size ->activate();
    maxsize ->activate();
    steep ->activate();
    health->activate();
    ammo ->activate();
    mons ->activate();
    puzzles->activate();
    outdoors->activate();
    iweapon->activate();
    switches->activate();
    keytype->activate();
    roomsize->activate();
    lighting->activate();
    enclosure->activate();
    questlength->activate();
    hallways->activate();
    stairs->activate();
    secrets->activate();

size_callback(this, this);

  }
}

void UI_Adjust::size_callback(Fl_Widget *w, void *data)
{
  UI_Adjust *that = (UI_Adjust *)data;

  if (main_win)
  {
    main_win->adjust_box->UpdateSizeLabel(that->get_Size());
  }
}


void UI_Adjust::UpdateLabels(const char *game, const char *mode)
{
 mn_val = mons->value(); 
 en_val = enclosure->value();

if (strcmp(mode,"dm")==0 || strcmp(mode,"dmne")==0 || strcmp(mode,"ctf")==0)
  {
    if (mn_val == 5 || mn_val == 6)  mn_val = 4;
    mons->label("Players: ");
    mons->clear();
    mons->add("Rare|Scarce|Plenty|Hordes|Swarms|Infested");
    mons->value(mn_val);
    
    enclosure->value(1);
    
    puzzles->label("Weapons: ");
  }
  else
  {
    mons->label("Monsters: ");
    mons->clear();
    mons->add("Rare|Scarce|Plenty|Hordes|Swarms|Infested|Insane|Insane+Weapons");
    mons->value(mn_val);
    
//    enclosure->value(0);

    if (strcmp(game, "wolf3d") == 0 || strcmp(game, "spear") == 0)
      puzzles->label("Bosses: ");
    else
      puzzles->label("Puzzles: ");
  }

if (strcmp(game, "heretic") == 0 || strcmp(game, "hexen") == 0
    || strcmp(game, "blasphemer") == 0)
{
      enclosure->value(1);
      enclosure->deactivate();
}
else
      enclosure->activate();


  SYS_ASSERT(main_win);

  main_win->adjust_box->redraw();
}

void UI_Adjust::UpdateGamesLabels(const char *game, const char *length)
{

iw_val = iweapon->value();
kt_val = keytype->value(); 
sz_val = size->value();
mn_val = mons->value();
 
if (strcmp(game, "hexen")==0 )
  { 
   	iweapon->clear();
    	iweapon->add("None|Basic|Hardcore");
    	iweapon->value(0);
	iweapon->deactivate();
	keytype->clear(); 
	keytype->add("Hexen");
	keytype->value(0);
	keytype->deactivate();

	mons->clear();
    	if (mn_val == 6)  mn_val = 5;
	mons->add("Rare|Scarce|Plenty|Hordes|Swarms|Infested|Insane");
    	mons->value(mn_val);	
	
  }
 
else
 if (strcmp(game, "heretic")==0 || strcmp(game, "blasphemer") == 0)
  { 
	iweapon->activate();
    	iweapon->clear();
    	iweapon->add("Elven Wand|Crossbow|Dragon Claw|Phoenix Rod");
    	iweapon->value(iw_val);
	keytype->clear(); 
	keytype->add("Heretic Keys");
	keytype->value(0);
	keytype->deactivate();

	mons->clear();    	
	mons->add("Rare|Scarce|Plenty|Hordes|Swarms|Infested|Insane|Insane+Weapons");
    	mons->value(mn_val);

  }
    
  else
  { 
	iweapon->activate();
    	iweapon->clear();
    	iweapon->add("Pistol|Shotgun|Chaingun|Launcher"); 
    	iweapon->value(iw_val);
	
	keytype->clear(); 
	keytype->add("Skull Keys|Key Cards|Skulls or Cards");
	keytype->value(kt_val);
	keytype->activate();
	
	mons->clear();
    	mons->add("Rare|Scarce|Plenty|Hordes|Swarms|Infested|Insane|Insane+Weapons");
    	mons->value(mn_val);
  
  }

if (strcmp(game, "doom1")==0 || strcmp(game, "doom1c") == 0 || 
	strcmp(game, "heretic") == 0 || strcmp(game, "blasphemer") == 0)
  { 
	if (strcmp(length, "single")==0)
	  { 
	   	
		size->clear();
 	  	if (sz_val == 6 || sz_val == 7)  sz_val = 2;
		size->add("Tiny|Small|Regular|Large|Huge|Gigantic");   		
		size->value(sz_val);
		maxsize ->deactivate();
	  }
	else
   	{
		
		size->clear();
   		if (sz_val == 7)  sz_val = 6;
		size->add("Tiny|Small|Regular|Large|Huge|Gigantic|Progressive");   		
		size->value(sz_val);
		
		//if (sz_val == 6 || sz_val == 7)			
		//	maxsize ->activate();			
		//else			
		//	maxsize ->deactivate();	
  	}
  }
else
  { 
   	if (strcmp(length, "single")==0)
	  { 
	   	
		size->clear();
 	  	if (sz_val == 6 || sz_val == 7)  sz_val = 2;
		size->add("Tiny|Small|Regular|Large|Huge|Gigantic");   		
		size->value(sz_val);
		maxsize ->deactivate();
	  }
	else
   	{
		
		size->clear();   		
		size->add("Tiny|Small|Regular|Large|Huge|Gigantic|Progressive|Expansion");  		
		size->value(sz_val);
		
		//if (sz_val == 6 || sz_val == 7)			
		//	maxsize ->activate();			
		//else			
		//	maxsize ->deactivate();		 	
  	}
  }
 

  SYS_ASSERT(main_win);

  main_win->adjust_box->redraw();
}

void UI_Adjust::UpdateSizeLabel(const char *size)
{

len_val = questlength->value();

{
	if (strcmp(size,"progressive")==0 || strcmp(size,"expansion")==0 )  
    	
		maxsize ->activate();

  	else

      	maxsize ->deactivate();

  SYS_ASSERT(main_win);

  main_win->adjust_box->redraw();
}

{
if (strcmp(size,"tiny")==0 || strcmp(size,"small")==0 )  
  	{  	
		questlength->clear();
 		if (len_val == 2 )  len_val = 1;
		questlength->add("Shorter|Normal");   		
		questlength->value(len_val);
	}
  else
	{
     		questlength->clear(); 	  	
		questlength->add("Shorter|Normal|Longer");   		
		questlength->value(len_val);
	}
  
  SYS_ASSERT(main_win);

  main_win->adjust_box->redraw();

  }
}

//----------------------------------------------------------------

const char * UI_Adjust::maxsize_syms[4] =
{
  "regular", "large", "huge", "gigantic"
};

const char * UI_Adjust::adjust_syms[5] =
{
  "none", "rare", "less", "normal", "more"
};

const char * UI_Adjust::adjust2_syms[5] =  // Ammo
{
  "none", "rare", "less", "normal", "more"
};

const char * UI_Adjust::adjust3_syms[3] =  // Puzzles
{
  "less", "normal", "more"
};

const char * UI_Adjust::size_syms[8] =
{
  "tiny", "small", "regular", "large", "huge", "gigantic", "progressive", "expansion" 
};

const char * UI_Adjust::mons_syms[8] =
{
  "rare", "less", "normal", "more", "swarms", "infested", "insane", "insanew"
};

const char * UI_Adjust::steep_syms[5] =
{
  "flat", "little", "some", "steep", "random"
};

const char * UI_Adjust::outdoors_syms[6] =
{
  "indoors", "rare", "some", "more", "lots", "outdoors"
};

const char * UI_Adjust::iweapon_syms[4] = 
{
  "none", "basic", "hardcore2",  "hardcore"
};

const char * UI_Adjust::stairs_syms[2] =
{
  "lifts", "stairs"
};

const char * UI_Adjust::switches_syms[3] =
{
  "keys", "both", "switches"
};

const char * UI_Adjust::keytype_syms[3] =
{
  "skulls", "keycards", "both"
};

const char * UI_Adjust::roomsize_syms[5] =
{
  "smaller", "normal", "medium", "large", "random"
};

const char * UI_Adjust::lighting_syms[6] =
{
  "none", "dim", "normal", "bright", "brighter", "random"
};

const char * UI_Adjust::enclosure_syms[2] =
{
  "true", "false"
};

const char * UI_Adjust::questlength_syms[3] =
{
  "short", "normal", "long"
};

const char * UI_Adjust::hallways_syms[4] =
{
  "none", "few", "normal", "random"
};

const char * UI_Adjust::secrets_syms[5] = 
{
  "none", "veryrare", "rare", "uncommon", "common"
};


//----------------------------------------------------------------

const char *UI_Adjust::get_maxSize()
{
  return maxsize_syms[maxsize->value()];
}

const char *UI_Adjust::get_Health()
{
  return adjust_syms[health->value()];
}

const char *UI_Adjust::get_Ammo()
{
  return adjust2_syms[ammo->value()];
}

const char *UI_Adjust::get_Monsters()
{
  return mons_syms[mons->value()];
}

const char *UI_Adjust::get_Traps()
{
  return adjust3_syms[1];  // TODO
}

const char *UI_Adjust::get_Puzzles()
{
  return adjust3_syms[puzzles->value()];
}

const char *UI_Adjust::get_Size()
{
  return size_syms[size->value()];
}

const char *UI_Adjust::get_Steep()
{
  return steep_syms[steep->value()];
}

const char *UI_Adjust::get_Outdoors()
{
  return outdoors_syms[outdoors->value()];
}

const char *UI_Adjust::get_Iweapon()
{
  return iweapon_syms[iweapon->value()];
}

const char *UI_Adjust::get_Switches()
{
  return switches_syms[switches->value()];
}

const char *UI_Adjust::get_KeyType()
{
  return keytype_syms[keytype->value()];
}

const char *UI_Adjust::get_RoomSize()
{
  return roomsize_syms[roomsize->value()];
}

const char *UI_Adjust::get_Lighting()
{
  return lighting_syms[lighting->value()];
}

const char *UI_Adjust::get_Enclosure()
{
  return enclosure_syms[enclosure->value()];
}

const char *UI_Adjust::get_QuestLength()
{
  return questlength_syms[questlength->value()];
}

const char *UI_Adjust::get_Hallways()
{
  return hallways_syms[hallways->value()];
}

const char *UI_Adjust::get_Stairs()
{
  return stairs_syms[stairs->value()];
}

const char *UI_Adjust::get_Secrets()
{
  return secrets_syms[secrets->value()];
}


//----------------------------------------------------------------
int UI_Adjust::Find2Sym(const char *str)
{
  for (int i=0; adjust2_syms[i]; i++)
    if (StrCaseCmp(str, adjust2_syms[i]) == 0)
      return i;

  return -1; // Unknown
}

int UI_Adjust::Find3Sym(const char *str)
{
  for (int i=0; adjust3_syms[i]; i++)
    if (StrCaseCmp(str, adjust3_syms[i]) == 0)
      return i;

  return -1; // Unknown
}

int UI_Adjust::FindSym(const char *str)
{
  for (int i=0; adjust_syms[i]; i++)
    if (StrCaseCmp(str, adjust_syms[i]) == 0)
      return i;

  return -1; // Unknown
}

bool UI_Adjust::set_maxSize(const char *str)
{
  for (int i=0; maxsize_syms[i]; i++) {
    if (StrCaseCmp(str, maxsize_syms[i]) == 0)
    {
      maxsize->value(i); return true;
    }
  }

  return false;
}


bool UI_Adjust::set_Health(const char *str)
{
  int i = FindSym(str);

  if (i >= 0) { health->value(i); return true; }

  return false;
}

bool UI_Adjust::set_Ammo(const char *str)
{
  int i = Find2Sym(str);

  if (i >= 0) { ammo->value(i); return true; }

  return false;
}

bool UI_Adjust::set_Monsters(const char *str)
{
  for (int i=0; mons_syms[i]; i++) {
    if (StrCaseCmp(str, mons_syms[i]) == 0)
    {
      mons->value(i); return true;
    }
  }

  return false;
}

bool UI_Adjust::set_Puzzles(const char *str)
{
  int i = Find3Sym(str);

  if (i >= 0) { puzzles->value(i); return true; }

  return false;
}

bool UI_Adjust::set_Traps(const char *str)
{
  // TODO !!! set_Traps
  return false;
}

bool UI_Adjust::set_Size(const char *str)
{
  for (int i=0; size_syms[i]; i++) {
    if (StrCaseCmp(str, size_syms[i]) == 0)
    {      
	size->value(i); return true;      
    }
}
  return false;
}

bool UI_Adjust::set_Steep(const char *str)
{
  for (int i=0; steep_syms[i]; i++)
    if (StrCaseCmp(str, steep_syms[i]) == 0)
    {
      steep->value(i); return true;
    }

  return false;
}

bool UI_Adjust::set_Outdoors(const char *str)
{
  for (int i=0; outdoors_syms[i]; i++) {
    if (StrCaseCmp(str, outdoors_syms[i]) == 0)
    {
      outdoors->value(i); return true;
    }
  }
  return false;
}

bool UI_Adjust::set_Iweapon(const char *str)
{
  for (int i=0; iweapon_syms[i]; i++) {
    if (StrCaseCmp(str, iweapon_syms[i]) == 0)
    {
      iweapon->value(i); return true;
    }
  }

  return false;
}

bool UI_Adjust::set_Switches(const char *str)
{
  for (int i=0; switches_syms[i]; i++) {
    if (StrCaseCmp(str, switches_syms[i]) == 0)
    {
      switches->value(i); return true;
    }
  }

  return false;
}

bool UI_Adjust::set_KeyType(const char *str)
{
  for (int i=0; keytype_syms[i]; i++) {
    if (StrCaseCmp(str, keytype_syms[i]) == 0)
    {
      keytype->value(i); return true;
    }
  }

  return false;
}

bool UI_Adjust::set_RoomSize(const char *str)
{
  for (int i=0; roomsize_syms[i]; i++) {
    if (StrCaseCmp(str, roomsize_syms[i]) == 0)
    {
      roomsize->value(i); return true;
    }
  }

  return false;
}

bool UI_Adjust::set_Lighting(const char *str)
{
  for (int i=0; lighting_syms[i]; i++) {
    if (StrCaseCmp(str, lighting_syms[i]) == 0)
    {
      lighting->value(i); return true;
    }
  }

  return false;
}

bool UI_Adjust::set_Enclosure(const char *str)
{
  for (int i=0; enclosure_syms[i]; i++) {
    if (StrCaseCmp(str, enclosure_syms[i]) == 0)
    {
      enclosure->value(i); return true;
    }
  }

  return false;
}

bool UI_Adjust::set_QuestLength(const char *str)
{
  for (int i=0; questlength_syms[i]; i++) {
    if (StrCaseCmp(str, questlength_syms[i]) == 0)
    {
      questlength->value(i); return true;
    }
  }

  return false;
}

bool UI_Adjust::set_Hallways(const char *str)
{
  for (int i=0; hallways_syms[i]; i++) {
    if (StrCaseCmp(str, hallways_syms[i]) == 0)
    {
      hallways->value(i); return true;
    }
  }

  return false;
}

bool UI_Adjust::set_Stairs(const char *str)
{
  for (int i=0; stairs_syms[i]; i++) {
    if (StrCaseCmp(str, stairs_syms[i]) == 0)
    {
      stairs->value(i); return true;
    }
  }

  return false;
}

bool UI_Adjust::set_Secrets(const char *str)
{
  for (int i=0; secrets_syms[i]; i++) {
    if (StrCaseCmp(str, secrets_syms[i]) == 0)
    {
      secrets->value(i); return true;
    }
  }

  return false;
}

