//------------------------------------------------------------------------
//  Adjustment screen
//------------------------------------------------------------------------
//
//  Oblige Level Maker (C) 2006,2007 Andrew Apted
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
//------------------------------------------------------------------------

#ifndef __UI_ADJUST_H__
#define __UI_ADJUST_H__

class UI_Adjust : public Fl_Group
{
private:
  Fl_Choice *health;   // How much health the map has
  Fl_Choice *ammo;     // How much ammo the map has
  Fl_Choice *mons;     // How many monsters the map has
  Fl_Choice *puzzles;
  Fl_Choice *size;     // How big the map is
  Fl_Choice *steep;    // How much up and down the map will have
  Fl_Choice *outdoors; // How much of the map will be outdoors 
  Fl_Choice *iweapon;  // The inital weapon
  Fl_Choice *switches; // Whether to have key quests or switch quests

public:
  UI_Adjust(int x, int y, int w, int h, const char *label = NULL);
  virtual ~UI_Adjust();

public:

  void Locked(bool value);
  void UpdateLabels(const char *game, const char *mode);

  const char *get_Size();
  const char *get_Steep();
  const char *get_Puzzles();
  const char *get_Traps();

  const char *get_Monsters();
  const char *get_Health();
  const char *get_Ammo();
  const char *get_Outdoors();
  const char *get_Iweapon();
  const char *get_Switches();

  bool set_Size(const char *str);
  bool set_Steep(const char *str);
  bool set_Puzzles(const char *str);
  bool set_Traps(const char *str);

  bool set_Monsters(const char *str);
  bool set_Health(const char *str);
  bool set_Ammo(const char *str);
  bool set_Outdoors(const char *str);
  bool set_Iweapon(const char *str);
  bool set_Switches(const char *str);

private:
  static const char *adjust_syms[4];
  static const char *adjust3_syms[3];
  static const char *mons_syms[5];
  static const char *size_syms[6];
  static const char *steep_syms[4];
  static const char *outdoors_syms[6];
  static const char *iweapon_syms[3];
  static const char *switches_syms[3];

  int FindSym(const char *str);
  int Find3Sym(const char *str);
};

#endif /* __UI_ADJUST_H__ */
