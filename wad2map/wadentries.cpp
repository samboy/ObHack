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
	wadentries.cpp

	Ted Mielczarek
	12/09/1999

	This file contains an index of doom level wad entries and
	a function to look them up into the enum defined in wadentries.h
*/

#include "StdAfx.h"
#include "defs.h"
#include "WadFile.h"
#include "doomlevel.h"
#include "wadentries.h"

// table of level entries
const char WAD_ENTRY_NAMES[10][9] =
{
	"THINGS",
	"LINEDEFS",
	"SIDEDEFS",
	"VERTEXES",
	"SEGS",
	"SSECTORS",
	"NODES",
	"SECTORS",
	"REJECT",
	"BLOCKMAP"
};

levelentries LookupLevelEntry(char *s)
{
	int i;

	if(strlen(s) == 4)
		if(s[0]=='E' && isdigit(s[1]) && s[2]=='M' && isdigit(s[3]))
			return(W_D1LEVEL);

	if(strlen(s) == 5)
		if(!strncmp(s,"MAP",3) && isdigit(s[3]) && isdigit(s[4]))
			return(W_D2LEVEL);

	for(i=0;i<NUM_LEVEL_ENTRIES;i++)
		if(!strncmp(s,WAD_ENTRY_NAMES[i],8))
			return(levelentries(i));

	return(W_NOT_LEVEL_ENTRY);
}

bool LoadLevelData(CWadFile &wadFile, level_t *level, char *szMap)
{
	char szTmp[9];
	levelentries le;
	int c = 0;

	if(!wadFile.SeekTo(szMap))
		return(false);

	do {
		if(!wadFile.SeekNext(szTmp))
			return(false);

		le = LookupLevelEntry(szTmp);
		switch(le) {
		case W_VERTEXES:
			level->n_vertices = wadFile.GetEntrySize() / sizeof(vertex_t);
			level->vertices = new vertex_t[level->n_vertices];
			wadFile.GetEntryData(level->vertices);
			c++;
			break;
		case W_LINEDEFS:
			level->n_linedefs = wadFile.GetEntrySize() / sizeof(linedef_t);
			level->linedefs = new linedef_t[level->n_linedefs];
			wadFile.GetEntryData(level->linedefs);
			c++;
			break;
		case W_SIDEDEFS:
			level->n_sidedefs = wadFile.GetEntrySize() / sizeof(sidedef_t);
			level->sidedefs = new sidedef_t[level->n_sidedefs];
			wadFile.GetEntryData(level->sidedefs);
			c++;
			break;
		case W_SECTORS:
			level->n_sectors = wadFile.GetEntrySize() / sizeof(sector_t);
			level->sectors = new sector_t[level->n_sectors];
			wadFile.GetEntryData(level->sectors);
			c++;
			break;
		case W_SEGS:
			level->n_segs = wadFile.GetEntrySize() / sizeof(segment_t);
			level->segs = new segment_t[level->n_segs];
			wadFile.GetEntryData(level->segs);
			c++;
			break;
		case W_SSECTORS:
			level->n_ssectors = wadFile.GetEntrySize() / sizeof(ssector_t);
			level->ssectors = new ssector_t[level->n_ssectors];
			wadFile.GetEntryData(level->ssectors);
			c++;
			break;
		case W_NODES:
			level->n_nodes = wadFile.GetEntrySize() / sizeof(node_t);
			level->nodes = new node_t[level->n_nodes];
			wadFile.GetEntryData(level->nodes);
			c++;
			break;
		case W_THINGS:
			level->n_things = wadFile.GetEntrySize() / sizeof(thing_t);
			level->things = new thing_t[level->n_things];
			wadFile.GetEntryData(level->things);
			c++;
			break;
		default:
			break;
		}
	} while(c < 8);

	return(true);
}

void LevelExtents(level_t *level)
{
	int i;
	short xmin = short(0x7FFF);
	short xmax = short(0x8000);
	short ymin = short(0x7FFF);
	short ymax = short(0x8000);

	// get max/min x/y
	for(i=0;i<level->n_vertices;i++) {
		xmin = min(xmin,level->vertices[i].x);
		xmax = max(xmax,level->vertices[i].x);
		ymin = min(ymin,level->vertices[i].y);
		ymax = max(ymax,level->vertices[i].y);
	}

	// calc height, width, x/y center
	level->l_width = xmax - xmin;
	level->l_height = ymax - ymin;
	level->x_center = xmin + level->l_width / 2;
	level->y_center = ymin + level->l_height / 2;
}

void InitLevel(level_t *l)
{
	memset(l,0,sizeof(level_t));
}

void CleanupLevel(level_t *l)
{
	if(l->linedefs != NULL)
		delete[] l->linedefs;
	if(l->nodes != NULL)
		delete[] l->nodes;
	if(l->sectors != NULL)
		delete[] l->sectors;
	if(l->segs != NULL)
		delete[] l->segs;
	if(l->sidedefs != NULL)
		delete[] l->sidedefs;
	if(l->ssectors != NULL)
		delete[] l->ssectors;
	if(l->vertices != NULL)
		delete[] l->vertices;
	if(l->things != NULL)
		delete[] l->things;

	memset(l,0,sizeof(level_t));
}

void DumpLevel(char *filename, level_t *l)
{
	FILE *f = fopen(filename,"w");
	int i;

	if(f == NULL)
		return;

	fprintf(f,"Level Dump\n----------\n");

	fprintf(f,"NODES\n-----\n");
	for(i=0;i<l->n_nodes;i++) {
		fprintf(f,"Node %d:\n",i);
		fprintf(f,"x = %d\n"
		"y = %d\n"
		"dx = %d\n"
		"dy = %d\n"
		"left_y_upper = %d\n"
		"left_y_lower = %d\n"
		"left_x_upper = %d\n"
		"left_x_lower = %d\n"
		"right_y_upper = %d\n"
		"right_y_lower = %d\n"
		"right_x_upper = %d\n"
		"right_x_lower = %d\n"
		"left_child = %d\n"
		"right_child = %d\n\n",
		l->nodes[i].x,l->nodes[i].y,
		l->nodes[i].dx,l->nodes[i].dy,
		l->nodes[i].left_y_upper,
		l->nodes[i].left_y_lower,
		l->nodes[i].left_x_upper,
		l->nodes[i].left_x_lower,
		l->nodes[i].right_y_upper,
		l->nodes[i].right_y_lower,
		l->nodes[i].right_x_upper,
		l->nodes[i].right_x_lower,
		l->nodes[i].left_child,
		l->nodes[i].right_child);
	}

	fprintf(f,"SSECTORS\n--------\n");
	for(i=0;i<l->n_ssectors;i++) {
		fprintf(f,"SSector %d:\n",i);
		fprintf(f,
			"numsegs = %d\n"
			"startseg = %d\n\n",
			l->ssectors[i].numsegs,
			l->ssectors[i].startseg);
	}

	fprintf(f,"SEGS\n----\n");
	for(i=0;i<l->n_segs;i++) {
		fprintf(f,"Seg %d:\n",i);
		fprintf(f,
			"from_vertex = %d\n"
			"to_vertex = %d\n"
			"angle = %d\n"
			"linedef = %d\n"
			"side = %d\n"
			"distance = %d\n",
			l->segs[i].from_vertex,
			l->segs[i].to_vertex,
			l->segs[i].angle,
			l->segs[i].linedef,
			l->segs[i].side,
			l->segs[i].distance);
	}

	fclose(f);
}
