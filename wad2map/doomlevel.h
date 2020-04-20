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
	doomlevel.h

  Ted Mielczarek
  12/07/1999

  Contains struct definitions for doom level data.
*/
#ifndef __DOOMLEVEL_H_
#define __DOOMLEVEL_H_

typedef struct linedef_s {
	short int from_vertex;
	short int to_vertex;
	short int attributes;
	short int type;
	short int sector_trigger;
	short int sidedefs[2];
} linedef_t;

typedef struct sidedef_s {
	short int	u_offset;	
	short int	v_offset;
	char	uppertxt[8];
	char	lowertxt[8];
	char	walltxt[8];
	short int	sector;
} sidedef_t;

typedef struct vertex_s {
	short int x;
	short int y;
} vertex_t;

typedef struct segment_s {
	short int from_vertex;
	short int to_vertex;
	short int angle;
	short int linedef;
	short int side;
	short int distance;
} segment_t;

typedef struct ssector_s {
	short int numsegs;
	short int startseg;
} ssector_t;

typedef struct node_s {
	short int x;
	short int y;
	short int dx;
	short int dy;

	short int left_y_upper;
	short int left_y_lower;
	short int left_x_upper;
	short int left_x_lower;

	short int right_y_upper;
	short int right_y_lower;
	short int right_x_upper;
	short int right_x_lower;

	unsigned short int right_child;
	unsigned short int left_child;
} node_t;

typedef struct sector_s {
	short int floor_alt;
	short int ceiling_alt;
	char floortxt[8];
	char ceiltxt[8];
	short int brightness;
	short int special;
	short int trigger;
} sector_t;

typedef struct thing_s {
	short x;
	short y;
	short angle;
	short thingnum;
	short options;
} thing_t;

// This is just to contain all the level data nicely
typedef struct level_s {
	linedef_t *linedefs;
	long n_linedefs;

	sidedef_t *sidedefs;
	long n_sidedefs;

	vertex_t *vertices;
	long n_vertices;

	segment_t *segs;
	long n_segs;

	ssector_t *ssectors;
	long n_ssectors;

	node_t *nodes;
	long n_nodes;

	sector_t *sectors;
	long n_sectors;

	thing_t *things;
	long n_things;

	short l_width, l_height, x_center, y_center;

} level_t;

#endif /* __DOOMLEVEL_H_ */
