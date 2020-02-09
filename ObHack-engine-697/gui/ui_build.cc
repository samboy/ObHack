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

#include "headers.h"
#include "hdr_fltk.h"
#include "lib_util.h"

#include "main.h"
#include "ui_map.h"
#include "ui_build.h"
#include "ui_window.h"


#define PROGRESS_BG  fl_gray_ramp(FL_NUM_GRAY * 16 / 24)
#define PROGRESS_FG  fl_color_cube(3,3,0)
#define GLBSP_FG     fl_color_cube(1,4,2)

#define ABORT_COLOR  fl_color_cube(3,1,1)


/* extern */
void menu_do_about(Fl_Widget *w, void * data);


UI_Build::UI_Build(int x, int y, int w, int h, const char *label) :
    Fl_Group(x, y, w, h, label)
{
  end(); // cancel begin() in Fl_Group constructor
 
  box(FL_FLAT_BOX);
  color(MAIN_BG_COLOR, MAIN_BG_COLOR);


  int cy = y + 4;

  Fl_Box *sizer = new Fl_Box(FL_NO_BOX, x+12 , cy, x+120, 8, NULL);
  sizer->color(FL_RED, FL_RED);

  add(sizer);


  cy = y + h - 70;

  progress = new Fl_Progress(x+12, cy+8, 136, 20);
  progress->align(FL_ALIGN_INSIDE);
  progress->box(FL_FLAT_BOX);
  progress->color(PROGRESS_BG, PROGRESS_FG);
  progress->value(50);

  add(progress);

  progress->hide();


  cy = y + h - 40;

  status = new Fl_Box(FL_FLAT_BOX, x+12, cy, 136, 24, "Ready to go!");
  status->align(FL_ALIGN_INSIDE | FL_ALIGN_BOTTOM_LEFT);
  status->color(MAIN_BG_COLOR, MAIN_BG_COLOR);
  add(status);

  
  quit = new Fl_Button(x+w - 82, cy, 70, 30, "Quit");
  quit->callback(quit_callback, this);

  add(quit);

  Fl_Button *about = new Fl_Button(x+w - 82, cy-40, 70, 30, "About");
  about->callback(menu_do_about, this);

  add(about);

  build = new Fl_Button(x+w - 170, cy, 76, 30, "Build...");
  build->labelfont(FL_HELVETICA_BOLD);
  build->callback(build_callback, this);

  add(build);

  mini_map = new UI_MiniMap(x+w - 308, y + h - 94, 120, 90);

  add(mini_map);

  resizable(sizer);
}


UI_Build::~UI_Build()
{
}

void UI_Build::Locked(bool value)
{
  if (value)
  {
    quit->deactivate();
  }
  else
  {
    quit->activate();
  }
}

//----------------------------------------------------------------

void UI_Build::ProgInit(int num_pass)
{
  prog_num_pass = num_pass;

  progress->minimum(0.0);
  progress->maximum(100.0);

  progress->value(0.0);
}

void UI_Build::ProgBegin(int pass, float limit)
{
  prog_pass  = pass;
  prog_limit = limit;

  progress->color(PROGRESS_BG, (pass==1) ? PROGRESS_FG : GLBSP_FG);
  progress->show();
}

void UI_Build::ProgUpdate(float val)
{
  val = val / prog_limit;

  if (val < 0) val = 0;
  if (val > 1) val = 1;

  if (prog_num_pass == 1)
    val = val * 100.0;
  else if (prog_pass == 1)
    val = val * 75.0;
  else
    val = 75.0 + (val * 25.0);

  sprintf(prog_msg, "%d%%", int(val));

  progress->value(val);
  progress->label(prog_msg);

  Main_Ticker();
}

void UI_Build::ProgFinish()
{
  progress->hide();
}

void UI_Build::ProgStatus(const char *msg)
{
  status->label(msg);
}

void UI_Build::ProgSetButton(bool abort)
{
  if (abort)
  {
    build->callback(stop_callback, this);
    build->label("Abort");
    build->labelcolor(ABORT_COLOR);
  }
  else
  {
    build->label("Build...");
    build->labelcolor(FL_FOREGROUND_COLOR);
    build->callback(build_callback, this);
  }
}


//----------------------------------------------------------------
  
void UI_Build::build_callback(Fl_Widget *w, void *data)
{
  if (main_win->action == UI_MainWin::NONE)
  {
    main_win->action = UI_MainWin::BUILD;
  }
}

void UI_Build::stop_callback(Fl_Widget *w, void *data)
{
  if (main_win->action != UI_MainWin::QUIT)
  {
    main_win->action = UI_MainWin::ABORT;
  }
}

void UI_Build::quit_callback(Fl_Widget *w, void *data)
{
  main_win->action = UI_MainWin::QUIT;
}
