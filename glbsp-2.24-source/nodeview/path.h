//------------------------------------------------------------------------
//  PATH : storage for path points
//------------------------------------------------------------------------
//
//  GL-Node Viewer (C) 2004-2007 Andrew Apted
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

#ifndef __NODEVIEW_PATH_H__
#define __NODEVIEW_PATH_H__

class path_c
{
public:
  path_c();
  ~path_c();

  int point_num;
  int *points;  // pairs

private:
  static const int MAX_PTS = 1024;

public:
  static path_c * ReadFile(const char *filename);

  void GetPoint(int index, int *x, int *y)
  {
    *x = points[index*2 + 0];
    *y = points[index*2 + 1];
  }
};

#endif /* __NODEVIEW_PATH_H__ */
