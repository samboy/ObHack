//------------------------------------------------------------------------
//  Build screen
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

#ifndef __UI_BUILD_H__
#define __UI_BUILD_H__

class UI_Build : public Fl_Group
{
private:
  Fl_Box *status;
  Fl_Progress *progress;

  char  prog_msg[20];
  int   prog_pass;
  int   prog_num_pass;
  float prog_limit;

  Fl_Button *build;
  Fl_Button *stop;
  Fl_Button *quit;

public:
  UI_MiniMap *mini_map;

public:
  UI_Build(int x, int y, int w, int h, const char *label = NULL);
  virtual ~UI_Build();

public:
  void ProgInit(int num_pass);
  void ProgBegin(int pass, float limit);
  void ProgUpdate(float val);
  void ProgFinish();
  void ProgStatus(const char *msg);
  void ProgSetButton(bool abort);

  void Locked(bool value);

private:
  static void build_callback(Fl_Widget *, void*);
  static void stop_callback(Fl_Widget *, void*);
  static void quit_callback(Fl_Widget *, void*);
};

#endif /* __UI_BUILD_H__ */
