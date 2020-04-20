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
	subtract_ssectors.cpp

	Ted Mielczarek
	12-21-1999

	This file contains routines to subtract the ssector polygons from the
	world polygon, creating the "wall" brushes.
*/
#include "StdAfx.h"
#include "defs.h"
#include "types.h"
#include "2dclip.h"
#include "subtract_ssectors.h"
#include "progress.h"

// Globals
poly_t *polyList[MAX_POLYS_IN_LIST];
int polyCount;

/*
	ClipWorldToPolys

	Parameters:
	world: Poly surrounding entire level
	ss:    List of polys to subtract from world
	n:     Count of polys in ss
	out:   Pointer to allocate list into to store returned polys
	count: Number of polys returned in out

	This function subtracts each poly in ss from world, and stores the results in
	out, and the number of polys created in count.
*/
bool ClipWorldToPolys(poly_t *world, poly_t ss[], int n, poly_t **out, int &count)
{
	int i,c;

	// MUST DO THIS FIRST!!
	InitList();

	// start out with world poly
	AddToList(world);

	printf("Subtracting ssectors from world: ");
	// init progress meter
	InitProgress(20,'*',true);
	//DrawProgress(n,0);

	// iterate through polys to subtract
	for(i=0;i<n;i++) {
		if(ss[i].num_verts > 2)
			// subtract this poly from every poly in the world list
			Subtract(&ss[i]);
		// draw progress meter
		DrawProgress(n,i);
	}
	DrawProgress(n,i);
	printf("\n");

	// make sure we didn't screw up
	if(polyCount > 0) {
		*out = new poly_t[polyCount];
		count = polyCount;
		c = 0;
		for(i=0;i < MAX_POLYS_IN_LIST && c < polyCount; i++)
			if(polyList[i] != NULL)
				memcpy(&(*out)[c++],polyList[i],sizeof(poly_t));
	}
	else // eek
		return(false);

	ClearList();

	// check all polys
	for(i=0;i<count;i++)
		if((*out)[i].num_verts < 3)
			OutputDebugString("Bad world brush\n");

	return(true);
}

bool Subtract(poly_t *sub)
{
	poly_t inter;
	int i;

	for(i=0;i<MAX_POLYS_IN_LIST; i++) {
		if(polyList[i] == NULL)
			continue;

		// do they intersect
		if(PolyIntersect(polyList[i],sub,&inter)) {
			if(CheckPoly(&inter)) {
				// cut intersection out of poly
				CSGSubtract(polyList[i],&inter);
				// remove old poly from list
				RemByIndex(i);
			}
		}
	}
			
	return(true);
}

bool CSGSubtract(poly_t *a, poly_t *inter)
{
	int i;
	poly_t save,tmp;
	line_t l;
	point_t p[2];

	memcpy(&tmp,a,sizeof(poly_t));
	for(i=0;i<inter->num_verts-1;i++) {
		LineFromPoints(&l,inter->p+i);
		memcpy(&save,&tmp,sizeof(poly_t));
		if(ClipPolyToLine(&save,&l,left_side)) {
			if(CheckPoly(&save))
				AddToList(&save);
			else
				OutputDebugString("Bad world brush\n");

			ClipPolyToLine(&tmp,&l,right_side);
		}
	}

	// do last vert->first vert
	memcpy(p,inter->p+inter->num_verts-1,sizeof(point_t));
	memcpy(p+1,inter->p,sizeof(point_t));
	LineFromPoints(&l,p);
	memcpy(&save,&tmp,sizeof(poly_t));
	if(ClipPolyToLine(&save,&l,left_side))
		if(CheckPoly(&save))
			AddToList(&save);
		else
			OutputDebugString("Bad world brush\n");

	return(true);
}

bool PolyIntersect(poly_t *a, poly_t *b, poly_t *inter)
{
	line_t l;
	int i;
	point_t p[2];

	memcpy(inter,a,sizeof(poly_t));
	// clip intersection poly (starts out as a) to each line in b
	for(i=0;i<b->num_verts-1;i++) {
		LineFromPoints(&l,b->p+i);
		ClipPolyToLine(inter,&l,right_side);
	}
		
	// get line from last vert to first vert
	memcpy(p,b->p+b->num_verts-1,sizeof(point_t));
	memcpy(p+1,b->p,sizeof(point_t));
	LineFromPoints(&l,p);
	ClipPolyToLine(inter,&l,right_side);

	if(inter->num_verts > 2)
		return(true);

	return(false);
}

void InitList(void)
{
	int i;

	for(i=0;i<MAX_POLYS_IN_LIST;i++)
		polyList[i] = NULL;

	polyCount = 0;
}

bool AddToList(poly_t *p)
{
	int i;

	// list is full, oops
	if(polyCount == MAX_POLYS_IN_LIST)
		return(false);

	for(i=0;i<MAX_POLYS_IN_LIST;i++) {
		if(polyList[i] == NULL) {
			polyList[i] = new poly_t;
			if(polyList[i] == NULL)
				// out of memory
				return(false);
			// just in case!
			p->sector = -1;
			memcpy(polyList[i],p,sizeof(poly_t));
			polyCount++;
			return(true);
		}
	}
	// no slots free, this shouldn't happen
	return(false);
}

void ClearList(void)
{
	int i;

	for(i=0;i<MAX_POLYS_IN_LIST;i++) {
		if(polyList[i] != NULL)
			delete polyList[i];
		polyList[i] = NULL;
	}
	polyCount = 0;
}

bool RemFromList(poly_t *p)
{
	int i;

	// list empty
	if(polyCount == 0)
		return(false);

	for(i=0;i<MAX_POLYS_IN_LIST;i++) {
		if(polyList[i] == p) {
			delete(polyList[i]);
			polyList[i] = NULL;
			polyCount--;
			return(true);
		}
	}

	return(false);
}

bool RemByIndex(int i)
{
	// list empty
	if(polyCount == 0)
		return(false);

	if(polyList[i] == NULL)
		return(false);

	delete(polyList[i]);
	polyList[i] = NULL;
	polyCount--;
	return(true);
}
