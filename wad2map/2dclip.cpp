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
	2dclip.cpp

	Ted Mielczarek
	12/10/1999

	This file contains the 2d clipping routines for forming ssectors.
*/

#include <StdAfx.h>
#include <math.h>
#include "types.h"
#include "2dclip.h"

// find out which side of a line a point is on
side PointLocation(point_t *p, line_t *l)
{
	coord lofq;
	point_t v;

	// get a vector from line to point
	v.x = p->x - l->p.x;
	v.y = p->y - l->p.y;

	lofq = DOT_PROD(v,l->n);

	if(lofq < 0)
		return(left_side);

	if(lofq > 0)
		return(right_side);
	
	return(on_line);
}

/*
	PointInPoly

	Determine if the point p lies within the poly s
*/
bool PointInPoly(point_t *p, poly_t *s)
{
	line_t l;
	int i;

	for(i=0;i<s->num_verts-1;i++) {
		LineFromPoints(&l,s->p+i);
		if(PointLocation(p,&l) == left_side)
			return(false);
	}

	return(true);
}

bool IntersectPoint(line_t *l, point_t l2[2], point_t *result)
{
	point_t d;
	double t;

	// get direction vector for l2 (the line segment
	d.x = l2[1].x - l2[0].x;
	d.y = l2[1].y - l2[0].y;

	// are the lines parallel?
	if(DOT_PROD(l->n,d) == 0)
		return(false);

	t = double(DOT_PROD(l->n,l->p) - DOT_PROD(l->n,l2[0])) / double(DOT_PROD(l->n,d));

	if(t < 0 || t > 1) {
		// outside the line segment
		return(false);
	}

	// get intersect point
#ifdef USE_FLOATING_POINT
	result->x = l2[0].x + t*d.x;
 	result->y = l2[0].y + t*d.y;
#else
	// if using int, round correctly
	result->x = int(floor(l2[0].x + t*d.x + 0.5));
 	result->y = int(floor(l2[0].y + t*d.y + 0.5));
#endif

	return(true);
}

void LineFromPoints(line_t *l, point_t p[2])
{
	// copy point A p[0]
	memcpy(&l->p,&p[0],sizeof(point_t));

	// calc normal vector:
	// use negative inverse slope of direction vector
	l->n.x = p[1].y - p[0].y;
	l->n.y = -1*(p[1].x - p[0].x);
}

bool ClipPolyToLine(poly_t *poly, line_t *l, side keep)
{
	int i;
	poly_t newpoly;
	point_t pt, tmp[2];
	side from,to,drop;

	memset(&newpoly,0,sizeof(newpoly));
	drop = OppositeSide(keep);

	// check first point
	if(PointLocation(&poly->p[0],l) != drop)
		memcpy(&newpoly.p[newpoly.num_verts++],&poly->p[0],sizeof(point_t));

	// cycle thru poly points
	for(i=0;i<poly->num_verts-1;i++) {
		from = PointLocation(&poly->p[i],l);
		to = PointLocation(&poly->p[i+1],l);
		if(from != drop) {
			if(to != drop)
				// crosses in to in
				memcpy(&newpoly.p[newpoly.num_verts++],&poly->p[i+1],sizeof(point_t));
			else {
				// check for points on line...
				if(from != on_line) {
					// crosses in to out, save crossing
					if(IntersectPoint(l,&poly->p[i],&pt))
						memcpy(&newpoly.p[newpoly.num_verts++],&pt,sizeof(point_t));
				}
			}
		}
		else {
			if(to != drop) {
				if(to != on_line) {
					// crosses out to in, save intersect point and "to" point
					if(IntersectPoint(l,&poly->p[i],&pt))
						memcpy(&newpoly.p[newpoly.num_verts++],&pt,sizeof(point_t));
				}
				// out to in, or out to on line, save 'to'
				memcpy(&newpoly.p[newpoly.num_verts++],&poly->p[i+1],sizeof(point_t));
			}
			// out to out, save nothing
		}
	}

	// check last point to first point
	from = PointLocation(&poly->p[poly->num_verts-1],l);
	to = PointLocation(&poly->p[0],l);
	memcpy(tmp,&poly->p[poly->num_verts-1],sizeof(point_t)*2);
	memcpy(&tmp[1],&poly->p[0],sizeof(point_t)*2);
	if(from != drop) {
		if(to == drop) {
			// check for points on line...
			if(from != on_line) {
				// crosses in to out, save crossing
				if(IntersectPoint(l,tmp,&pt))
					memcpy(&newpoly.p[newpoly.num_verts++],&pt,sizeof(point_t));
			}
		}
	}
	else {
		if(to != drop) {
			if(to != on_line) {
				// crosses out to in, save intersect point
				if(IntersectPoint(l,tmp,&pt))
					memcpy(&newpoly.p[newpoly.num_verts++],&pt,sizeof(point_t));
			}
		}
		// out to out, save nothing
	}

	// check to see if all that's left is points on the line.  this could screw stuff up.
	from = on_line;
	for(i=0;i<newpoly.num_verts;i++) {
		to = PointLocation(&newpoly.p[i],l);
		if(to != on_line) {
			from = to;
			break;
		}
	}

	memset(poly,0,sizeof(poly_t));

	// if all points are on the line, don't copy it
	if(from != on_line)
		memcpy(poly,&newpoly,sizeof(newpoly));

	return(poly->num_verts > 2);
}

side OppositeSide(side s)
{
	if(s == right_side)
		return(left_side);
	
	if(s == left_side)
		return(right_side);

	return(s);
}

/*
	CheckPolys

	Check all polys for duplicate vertices.

	Parameters:
	p: Array of polys to check
	n: Number of polys in array
*/
void CheckPolys(poly_t *p, int n)
{
	int i,j,k;

	for(i=0;i<n;i++) {
		// degenerate poly...
		if(p[i].num_verts < 3) {
			memset(&p[i],0,sizeof(poly_t));
			continue;
		}
		for(j=0;j<p[i].num_verts-1;j++) {
			for(k=j;k<p[i].num_verts;k++) {
				if(j==k)
					continue;
				if(PointsEqual(&p[i].p[j], &p[i].p[k])) {
					// degenerate poly!
					if(p[i].num_verts <= 3) {
						memset(&p[i],0,sizeof(poly_t));
						break;
					}
					RemovePoint(&p[i],k);
				}
			}
		}
	}
}

/*
	CheckPoly

	Check a single poly for degeneracy. (Duplicate verts, < 3 verts, all verts colinear)
*/
bool CheckPoly(poly_t *p)
{
	int j,k;
	line_t l;
	bool isOk;

	// degenerate poly...
	if(p->num_verts < 3) {
		memset(p,0,sizeof(poly_t));
		return(false);
	}

	for(j=0;j<p->num_verts-1;j++) {
		for(k=j;k<p->num_verts;k++) {
			if(j==k)
				continue;
			if(PointsEqual(&p->p[j], &p->p[k])) {
				// degenerate poly!
				if(p->num_verts <= 3) {
					memset(p,0,sizeof(poly_t));
					return(false);
				}
				RemovePoint(p,k);
			}
		}
	}

	// check to see if all points are colinear
	LineFromPoints(&l,p->p);
	isOk = false;
	for(j=2;j<p->num_verts;j++) {
		if(PointLocation(p->p+j,&l) != on_line) {
			isOk = true;
			break;
		}
	}	

	return(isOk);
}

bool PointsEqual(point_t *p1, point_t *p2)
{
#ifdef USE_FLOATING_POINT
	if((fabs(p1->x - p2->x) < 0.1) && (fabs(p1->y - p2->y) < 0.1))
#else
	if(abs(p1->x - p2->x) < 3 && abs(p1->y - p2->y) < 3)
#endif
	//if(p1->x == p2->x && p1->y == p2->y)
		return(true);

	return(false);
}

void RemovePoint(poly_t *p, int n)
{
	int i,j;

	// number of verts after this
	i = p->num_verts - n - 1;
	
	// if any, move points back
	if(i > 0)
		for(j=0;j<i;j++)
			memcpy(&p->p[j+n],&p->p[j+n+1],sizeof(point_t));
	
	// zero out last vertex
	p->p[p->num_verts - 1].x = 0;
	p->p[p->num_verts - 1].y = 0;

	// one less point
	p->num_verts--;
}

/*
	printpoint

	Print a point to a string as (x, y)
*/
void printpoint(char *s, point_t *p)
{
	sprintf(s,"("CSPEC", "CSPEC")",p->x,p->y);
}

/*
	DumpPoly

	Dump all points in a poly to a file.
*/
void DumpPoly(FILE *f, poly_t *p)
{
	int i;
	char szTmp[256];

	for(i=0;i<p->num_verts;i++) {
		printpoint(szTmp,p->p+i);
		fprintf(f,szTmp);
		fprintf(f,", ");
	}
	fprintf(f,"\n");
}
