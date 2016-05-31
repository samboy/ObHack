//----------------------------------------------------------------
//  Setup screen
//----------------------------------------------------------------
//
//  Oblige Level Maker (C) 2006,2007 Andrew Apted
//  ObHack changes (C) 2007-2016 Sam Trenholme and Fritz
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

#include "ui_setup.h"
#include "ui_window.h"

#include "lib_util.h"


//
// Setup Constructor
//
UI_Setup::UI_Setup(int x, int y, int w, int h, const char *label) :
    Fl_Group(x, y, w, h, label)
{
  end(); // cancel begin() in Fl_Group constructor
 
  box(FL_THIN_UP_BOX);
//  align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT | FL_ALIGN_TOP);

  int cy = y + 25;

  Fl_Box *heading = new Fl_Box(FL_FLAT_BOX, x+6, cy, 70, 24, "Settings");
  heading->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
  heading->labeltype(FL_NORMAL_LABEL);
  heading->labelfont(FL_HELVETICA_BOLD);

  add(heading);
  Fl_Box *heading2 = new Fl_Box(FL_FLAT_BOX, x+180, cy-8, 160, 0, "ObHack Level Generator");
  heading2->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
  heading2->labeltype(FL_NORMAL_LABEL);
  heading2->labelfont(FL_HELVETICA_BOLD_ITALIC);
  heading2->labelsize(28);
  heading2->labelcolor(120);
  add(heading2);

  cy += 28;
///seed = new Fl_Input(x+120, cy, 228, 24, "Random Seed: ");
  seed = new Fl_Input(x+232, cy, 228, 24, "Random Seed: ");
  seed->align(FL_ALIGN_LEFT);
  seed->maximum_size(20);
  seed->value("1");

  add(seed);

  bump = new Fl_Button(x+466, cy, 96, 24, "New Seed");
  bump->callback(bump_callback, this);

  add(bump);

  cy += 32;

  game = new Fl_Choice(x+182, cy, 150, 24, "Game: ");
  game->align(FL_ALIGN_LEFT);  
  game->add(
/// Games I can not test myself are disabled
///         "Wolf 3d|"
///         "Spear of Destiny|"
            "Doom 1|"
///         "Doom 1 Mr. Chris|"
            "Doom 2|"
            "TNT Evilution|"
            "Plutonia|"
            "FreeDoom 0.9|"
//          "Old FreeDoom|"
	    "Heretic|"
 	    "Blasphemer 2016-2"
///         "|Hexen"
            );
  game->value(4);
  game->callback(game_callback, this);
  

  add(game);

  length = new Fl_Choice(x +412, cy, 150, 24, "Length: ");
  length->align(FL_ALIGN_LEFT);
  length->add("Single Level|One Episode|Full Game");
  length->value(1);  
  length->callback(length_callback, this);

  add(length);

  cy += 32;

  port = new Fl_Choice(x+182, cy, 150, 24, "Port: ");
  port->align(FL_ALIGN_LEFT);
  port->add("Limit Removing"); //TODO: BOOM|EDGE|Legacy|JDoom|ZDoom
  port->value(0);

  add(port);

  mode = new Fl_Choice(x+412, cy, 150, 24, "Mode: ");
  mode->align(FL_ALIGN_LEFT);
  mode->add("Single Player|Co-op|Deathmatch|SP and DM|DM (no exit)|CTF");
  mode->value(0);
  mode->callback(mode_callback, this);

  add(mode);

  resizable(0);  // don't resize our children

  FreshSeed();

}


//
// Setup Destructor
//
UI_Setup::~UI_Setup()
{
}

void UI_Setup::SetSeed(u32_t new_val)
{
  char num_buf[40];

  sprintf(num_buf, "%04d", new_val % 10000);

  seed->value(num_buf);
}

void UI_Setup::FreshSeed()
{
  u32_t bump = TimeGetMillies();

  bump = IntHash(bump);
  
  SetSeed(bump);
}

void UI_Setup::BumpSeed()
{
  u32_t old_val = atoi(seed->value());

  u32_t bump = 90 + (IntHash(old_val) & 255);

  SetSeed(old_val + bump);
}

void UI_Setup::bump_callback(Fl_Widget *w, void *data)
{
  UI_Setup *that = (UI_Setup *)data;

  that->BumpSeed();
}

void UI_Setup::game_callback(Fl_Widget *w, void *data)
{
  UI_Setup *that = (UI_Setup *)data;

  // multiplayer is not supported in Wolf3d / SOD
  if (strcmp(that->get_Game(), "wolf3d") == 0 ||
      strcmp(that->get_Game(), "spear")  == 0)
  {
    that->mode->value(0);
    mode_callback(that, that);

    that->mode->deactivate();
  }
  else
    that->mode->activate();

if (strcmp(that->get_Game(), "hexen") == 0)
  {  	    
	if (strcmp(that->get_Length(),  "single") == 0)
	{
    	   that->length->value(1);
    	   length_callback(that, that);
	}    
  }


if (main_win)
  {
    main_win->adjust_box->UpdateLabels(that->get_Game(), that->get_Mode());
    main_win->adjust_box->set_Game(that->get_Game());
    main_win->adjust_box->UpdateGamesLabels(that->get_Game(), that->get_Length());

  }

}

void UI_Setup::mode_callback(Fl_Widget *w, void *data)
{
  UI_Setup *that = (UI_Setup *)data;

  if (main_win)
  {
    main_win->adjust_box->UpdateLabels(that->get_Game(), that->get_Mode());

  }
}

void UI_Setup::length_callback(Fl_Widget *w, void *data)
{
  UI_Setup *that = (UI_Setup *)data;

if (strcmp(that->get_Game(), "hexen") == 0)
  {     
	if (strcmp(that->get_Length(),  "single") == 0)
	{    	   
	   that->length->value(1);
    	   length_callback(that, that);
	}    
  }

  if (main_win)
  {
    main_win->adjust_box->UpdateGamesLabels(that->get_Game(), that->get_Length());       
  }
}


void UI_Setup::Locked(bool value)
{
  if (value)
  {
    seed->deactivate();
    bump->deactivate();

    game->deactivate();
    port->deactivate();
    mode->deactivate();
    length->deactivate();
  }
  else
  {
    seed->activate();
    bump->activate();

    game->activate();
    port->activate();
    mode->activate();
    length->activate();

    game_callback(this, this);
    mode_callback(this, this);
    length_callback(this, this);   
   
  }
}

//----------------------------------------------------------------

const char * UI_Setup::game_syms[] =
{
///  "wolf3d", 
///  "spear",
  "doom1", "doom2", "tnt", "plutonia", "freedoom", // "old",
  "heretic", "blasphemer"
///  ,"hexen"
  
};

const char * UI_Setup::port_syms[] =
{
  "nolimit" /// , "boom", "edge", "zdoom", etc..
};

const char * UI_Setup::mode_syms[] =
{
  "sp", "coop", "dm", "spdm", "dmne", "ctf"
};

const char * UI_Setup::length_syms[] =
{
  "single", "episode", "full"
};


const char *UI_Setup::get_Seed()
{
  return seed->value();
}

const char *UI_Setup::get_Game()
{
  return game_syms[game->value()];
}

const char *UI_Setup::get_Port()
{
  return port_syms[port->value()];
}

const char *UI_Setup::get_Mode()
{
  return mode_syms[mode->value()];
}

const char *UI_Setup::get_Length()
{
  return length_syms[length->value()];
}


//----------------------------------------------------------------

bool UI_Setup::set_Seed(const char *str)
{
  seed->value(str);

  return true;
}

bool UI_Setup::set_Game(const char *str)
{
  for (int i=0; game_syms[i]; i++)
  {
    if (StrCaseCmp(str, game_syms[i]) == 0)
    {
      game->value(i);
      game_callback(this, this);      
	return true;
    }
  }
  return false; // Unknown
}

bool UI_Setup::set_Port(const char *str)
{
  for (int i=0; port_syms[i]; i++)
  {
    if (StrCaseCmp(str, port_syms[i]) == 0)
    {
      port->value(i);
      return true;
    }
  }
  return false; // Unknown
}

bool UI_Setup::set_Mode(const char *str)
{
  for (int i=0; mode_syms[i]; i++)
  {
    if (StrCaseCmp(str, mode_syms[i]) == 0)
    {
      mode->value(i);

      mode_callback(this, this);
      game_callback(this, this);
      return true;
    }
  }
  return false; // Unknown
}

bool UI_Setup::set_Length(const char *str)
{
  for (int i=0; length_syms[i]; i++)
  {
    if (StrCaseCmp(str, length_syms[i]) == 0)
    {
      length->value(i);
      
	length_callback(this, this);	
	return true;
    }
  }
  return false; // Unknown
}

