/*
	Wad2Map v1.0
	(c) 2000 Ted Mielczarek
	
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    You can contact the author of this program at tam4@lehigh.edu
*/
/*
	globals.h

	Ted Mielczarek
	1-13-2000

	This file contains extern definitions for the global variables
	in wad2map.cpp
*/
#ifndef __GLOBALS_H_
#define __GLOBALS_H_

extern char wadfilename[MAX_PATH];

extern char entityoptfilename[MAX_PATH];
#define DEFAULTENTITYFILE "entities.list"

extern char textureoptfilename[MAX_PATH];
#define DEFAULTTEXTUREFILE "textures.list"

extern char mapname[9];
extern bool convert_all;
extern bool do_textures;

#endif /* __GLOBALS_H_ */
