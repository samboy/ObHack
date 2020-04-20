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
	2dclip.h

	Ted Mielczarek
	12/10/1999

	This file contains prototypes for the functions in 2dclip.cpp, which
	are 2d clipping routines.
*/
#ifndef __2DCLIP_H_
#define __2DCLIP_H_

typedef enum {
	on_line,
	left_side,
	right_side
} side;

// dot product macro
#define DOT_PROD(a,b) ((a.x) * (b.x) + (a.y) * (b.y))

side PointLocation(point_t *p, line_t *l);
bool PointInPoly(point_t *p, poly_t *s);
bool IntersectPoint(line_t *l, point_t l2[2], point_t *result);
void LineFromPoints(line_t *l, point_t p[2]);
bool ClipPolyToLine(poly_t *poly, line_t *l, side keep);
void CheckPolys(poly_t *p, int n);
bool CheckPoly(poly_t *p);
bool PointsEqual(point_t *p1, point_t *p2);
void RemovePoint(poly_t *p, int n);
void printpoint(char *s, point_t *p);
void DumpPoly(FILE *f, poly_t *p);
side OppositeSide(side s);

#endif /* __2DCLIP_H_ */
