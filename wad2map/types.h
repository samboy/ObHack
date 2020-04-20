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
	types.h

	Ted Mielczarek
	12/10/1999

	This file contains data types for the program.
*/
#ifndef __TYPES_H_
#define __TYPES_H_

// we can use double or int
#ifdef USE_FLOATING_POINT
typedef double coord;
#define CSPEC "%lf"
#else
typedef int coord;
#define CSPEC "%d"
#endif

typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned long dword;

// point
typedef struct point_s {
	coord x,y;
} point_t;

// 3d point (used for dumping maps)
typedef struct point3d_s {
	coord x,y,z;
} point3d_t;

// point-normal form of a line
typedef struct line_s {
	point_t n;	// normal vector
	point_t p;	// point
} line_t;

// is this enough?
#define MAX_POLY_VERTS 256

typedef struct poly_s {
	point_t p[MAX_POLY_VERTS];			// poly vertices
	int num_verts;									// vertex count
	short sidedef[MAX_POLY_VERTS];	// to keep track of sidedefs/lines
	short sector;										// sector this is a part of (-1 for none)
} poly_t;

#endif /* __TYPES_H_ */
