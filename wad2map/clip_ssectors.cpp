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
	clip_ssectors.cpp

	Ted Mielczarek
	12-13-1999

	This file clips the ssectors using each node division line traversing the node tree until
	a ssector is hit, and then clips the ssector to the bounding segs of the ssector.
*/
#include <StdAfx.h>
#include "defs.h"
#include "types.h"
#include "2dclip.h"
#include "doomlevel.h"
#include "WadFile.h"
#include "wadentries.h"
#include "clip_ssectors.h"
#include "progress.h"

int ssDone;

/*
	ClipSectors

	Take a doom level, and generate polygons of the ssectors.

	Parameters:
	level: Level data for the doom map.
	polys: An array of pointers to polys to fill.
*/
bool ClipSsectors(level_t *level, poly_t *polys)
{
	poly_t thePoly;

	MakeWorldPoly(&thePoly,level);

	printf("Creating ssectors: ");
	// draw a progress bar to be nice
	InitProgress(20,'*',true);
	//DrawProgress(level->n_ssectors,0);
	ssDone = 0;
	// walk bsp tree
	RecurseNodes(level->nodes + (level->n_nodes - 1),&thePoly,level,polys);

	printf("\n");
	// check all ssectors
	for(int i=0;i<level->n_ssectors;i++) {
		CheckPoly(polys+i);
		if(polys[i].num_verts < 3)
			OutputDebugString("Bad ssector\n");
	}

	return(true);
}

void MakeWorldPoly(poly_t *thePoly, level_t *level)
{
	// init thePoly to be a rectangle encompassing the entire level, with a 16 unit border
	memset(thePoly,0,sizeof(poly_t));
	thePoly->num_verts = 4;
	thePoly->p[0].x = level->x_center - level->l_width / 2 - 16;
	thePoly->p[0].y = level->y_center - level->l_height / 2 - 16;
	thePoly->p[1].x = level->x_center - level->l_width / 2 - 16;
	thePoly->p[1].y = level->y_center + level->l_height / 2 + 16;
	thePoly->p[2].x = level->x_center + level->l_width / 2 + 16;
	thePoly->p[2].y = level->y_center + level->l_height / 2 + 16;
	thePoly->p[3].x = level->x_center + level->l_width / 2 + 16;
	thePoly->p[3].y = level->y_center - level->l_height / 2 - 16;
}

/*
	RecurseNodes

	Traverse the bsp tree, using node division lines to clip away at a polygon until
	it hits a ssector, then use the segs bounding that ssector to clip the rest of it.

	Parameters:
	node: The current node of the bsp tree.
	thePoly: The current polygon being clipped.
	level: The doom level data.
	polys: The full set of polys being created for this level.
*/
bool RecurseNodes(node_t *node, poly_t *thePoly, level_t *level, poly_t *polys)
{
	poly_t newPoly;
	point_t p[2];
	line_t l;
	segment_t *s;
	int i;
	short ssnum;

	//***********
	// Left Child
	//***********
	// copy poly
	memcpy(&newPoly,thePoly,sizeof(poly_t));
	// clip it to the node split line and
	p[0].x = node->x;
	p[0].y = node->y;
	p[1].x = node->x + node->dx;
	p[1].y = node->y + node->dy;
	LineFromPoints(&l,p);
	ClipPolyToLine(&newPoly,&l,left_side);
	// is left node a ssector?
	if(node->left_child & 0x8000) {
		// clip it to the segs
		ssnum = node->left_child & 0x7FFF;
		for(i=0, s = &level->segs[level->ssectors[ssnum].startseg];
			i<level->ssectors[ssnum].numsegs; i++,s++) {
			// make clip line from seg
			p[0].x = level->vertices[s->from_vertex].x;
			p[0].y = level->vertices[s->from_vertex].y;
			p[1].x = level->vertices[s->to_vertex].x;
			p[1].y = level->vertices[s->to_vertex].y;
			LineFromPoints(&l,p);
			ClipPolyToLine(&newPoly,&l,right_side);
		}
		// set which sector this is part of
		if(level->ssectors[ssnum].numsegs > 0) {
			short segnum,linenum,sidenum;

			// could do this in one line, but it's ugly
			segnum = level->ssectors[ssnum].startseg;
			linenum = level->segs[segnum].linedef;
			sidenum = level->linedefs[linenum].sidedefs[level->segs[segnum].side];
			newPoly.sector = level->sidedefs[sidenum].sector;
		}
		else
			newPoly.sector = -1;
		// now add it to the list of polys
		memcpy(&polys[ssnum],&newPoly,sizeof(poly_t));
		ssDone++;
		// draw progress meter
		DrawProgress(level->n_ssectors,ssDone);
	}
	else {
		// otherwise, recurse
		RecurseNodes(&level->nodes[node->left_child],&newPoly,level,polys);
	}


	//***********
	// Right Child
	//***********
	// copy poly
	memcpy(&newPoly,thePoly,sizeof(poly_t));
	// clip it to the node split line
	p[0].x = node->x;
	p[0].y = node->y;
	p[1].x = node->x + node->dx;
	p[1].y = node->y + node->dy;
	LineFromPoints(&l,p);
	ClipPolyToLine(&newPoly,&l,right_side);
	// is left node a ssector?
	if(node->right_child & 0x8000) {
		// clip it to the segs
		ssnum = node->right_child & 0x7FFF;
		for(i=0, s = &level->segs[level->ssectors[ssnum].startseg];
			i<level->ssectors[ssnum].numsegs; i++,s++) {
			// make clip line from seg
			p[0].x = level->vertices[s->from_vertex].x;
			p[0].y = level->vertices[s->from_vertex].y;
			p[1].x = level->vertices[s->to_vertex].x;
			p[1].y = level->vertices[s->to_vertex].y;
			LineFromPoints(&l,p);
			ClipPolyToLine(&newPoly,&l,right_side);
		}
		// set which sector this is part of
		if(level->ssectors[ssnum].numsegs > 0) {
			short segnum,linenum,sidenum;

			// could do this in one line, but it's ugly
			segnum = level->ssectors[ssnum].startseg;
			linenum = level->segs[segnum].linedef;
			sidenum = level->linedefs[linenum].sidedefs[level->segs[segnum].side];
			newPoly.sector = level->sidedefs[sidenum].sector;
		}
		else
			newPoly.sector = -1;
		// now add it to the list of polys
		memcpy(&polys[ssnum],&newPoly,sizeof(poly_t));
		ssDone++;
		// draw progress meter
		DrawProgress(level->n_ssectors,ssDone);
	}
	else {
		// recurse
		RecurseNodes(&level->nodes[node->right_child],&newPoly,level,polys);
	}

	return(true);
}
