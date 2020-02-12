//----------------------------------------------------------------
//  Adjustment screen
//----------------------------------------------------------------
//
//  Oblige Level Maker (C) 2006,2007 Andrew Apted
//  OhHack changes (C) 2007-2009 Sam Trenholme
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

  Fl_Box *heading = new Fl_Box(FL_FLAT_BOX, x+6, cy, 160, 24, "Adjustments");
  heading->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
  heading->labeltype(FL_NORMAL_LABEL);
  heading->labelfont(FL_HELVETICA_BOLD);

  add(heading);

  cy += 28;

  size = new Fl_Choice(x+ 96, cy, 130, 24, "Level Size: ");
  size->align(FL_ALIGN_LEFT);
  size->add("Tiny|Small|Regular|Large|Huge|Progressive");
  size->value(1);

  add(size);

  steep = new Fl_Choice(x+ 320, cy, 130, 24, "Steepness: ");
  steep->align(FL_ALIGN_LEFT);
  steep->add("Flat|A little|Some|Steep");
  steep->value(2);

  add(steep);

  cy += 32;

  health = new Fl_Choice(x+320, cy, 130, 24, "Health: ");
  health->align(FL_ALIGN_LEFT);
  health->add("None|Less|Enough|More");
  health->value(2);

  add(health);

  mons = new Fl_Choice(x+ 96, cy, 130, 24, "Monsters: ");
  mons->align(FL_ALIGN_LEFT);
  mons->add("Rare|Scarce|Plenty|Hordes|Swarms");
  mons->value(2);

  add(mons);

  cy += 32;

  ammo = new Fl_Choice(x+320, cy, 130, 24, "Ammo: ");
  ammo->align(FL_ALIGN_LEFT);
  ammo->add("Less|Enough|More");
  ammo->value(1);
  
  add(ammo);

  puzzles = new Fl_Choice(x+ 96, cy, 130, 24, "Puzzles: ");
  puzzles->align(FL_ALIGN_LEFT);
  puzzles->add("Few|Some|Heaps");
  puzzles->value(2);

  add(puzzles);

  cy += 32;

  outdoors = new Fl_Choice(x+96, cy, 130, 24, "Outdoors: ");
  outdoors->align(FL_ALIGN_LEFT);
  outdoors->add("Indoors|Rare|Some|More|Lots|Outdoors"); 
  outdoors->value(3);

  add(outdoors);

  iweapon = new Fl_Choice(x+320, cy, 130, 24, "Start weapon: ");
  iweapon->align(FL_ALIGN_LEFT);
  iweapon->add("None|Basic|Hardcore"); 
  iweapon->value(0);

  add(iweapon);
	
  cy += 32;
  switches = new Fl_Choice(x+96, cy, 130, 24, "Switches: ");
  switches->align(FL_ALIGN_LEFT);
  switches->add("Keys only|Keys + switches|Switches only"); 
  switches->value(0);

  add(switches);

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
    steep->deactivate();
    health->deactivate();
    ammo ->deactivate();
    mons ->deactivate();
    puzzles->deactivate();
    outdoors->deactivate();
    iweapon->deactivate();
    switches->deactivate();
  }
  else
  {
    size ->activate();
    steep ->activate();
    health->activate();
    ammo ->activate();
    mons ->activate();
    puzzles->activate();
    outdoors->activate();
    iweapon->activate();
    switches->activate();
  }
}

void UI_Adjust::UpdateLabels(const char *game, const char *mode)
{
  if (strcmp(mode,"dm")==0 || strcmp(mode,"dmne")==0 || strcmp(mode,"ctf")==0)
  {
    mons->label("Players: ");
    puzzles->label("Weapons: ");
  }
  else
  {
    mons->label("Monsters: ");

    if (strcmp(game, "wolf3d") == 0 || strcmp(game, "spear") == 0)
      puzzles->label("Bosses: ");
    else
      puzzles->label("Puzzles: ");
  }

  SYS_ASSERT(main_win);

  main_win->adjust_box->redraw();
}

//----------------------------------------------------------------

const char * UI_Adjust::adjust_syms[4] =
{
  "rare", "less", "normal", "more"
};

const char * UI_Adjust::adjust3_syms[3] =
{
  "less", "normal", "more"
};

const char * UI_Adjust::size_syms[6] =
{
  "tiny", "small", "regular", "large", "huge", "progressive"
};

const char * UI_Adjust::mons_syms[5] =
{
  "rare", "less", "normal", "more", "swarms"
};

const char * UI_Adjust::steep_syms[4] =
{
  "flat", "little", "some", "steep"
};

const char * UI_Adjust::outdoors_syms[6] =
{
  "indoors", "rare", "some", "more", "lots", "outdoors"
};

const char * UI_Adjust::iweapon_syms[3] = 
{
  "none", "basic", "hardcore"
};

const char * UI_Adjust::switches_syms[3] =
{
  "keys", "both", "switches"
};

const char *UI_Adjust::get_Health()
{
  return adjust_syms[health->value()];
}

const char *UI_Adjust::get_Ammo()
{
  return adjust3_syms[ammo->value()];
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

//----------------------------------------------------------------

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

bool UI_Adjust::set_Health(const char *str)
{
  int i = FindSym(str);

  if (i >= 0) { health->value(i); return true; }

  return false;
}

bool UI_Adjust::set_Ammo(const char *str)
{
  int i = Find3Sym(str);

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
  for (int i=0; outdoors_syms[i]; i++)
    if (StrCaseCmp(str, outdoors_syms[i]) == 0)
    {
      outdoors->value(i); return true;
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
