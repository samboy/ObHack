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
	subtract_ssectors.h

	Ted Mielczarek
	12-21-1999

	This file contains prototypes for subtract_ssectors.cpp
*/
#ifndef __SUBTRACT_SSECTORS_H_
#define __SUBTRACT_SSECTORS_H_

// max polys we can have created for the world.  not enough?
#define MAX_POLYS_IN_LIST 1024

bool ClipWorldToPolys(poly_t *world, poly_t ss[], int n, poly_t **out, int &count);
bool Subtract(poly_t *sub);
bool CSGSubtract(poly_t *a, poly_t *inter);
bool PolyIntersect(poly_t *a, poly_t *b, poly_t *inter);
void InitList(void);
bool AddToList(poly_t *p);
void ClearList(void);
bool RemFromList(poly_t *p);
bool RemByIndex(int i);

#endif /* __SUBTRACT_SSECTORS_H_ */
