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
	dumpmap.cpp

	Ted Mielczarek
	1-11-2000

	This file contains routines for exporting a .map file from all the polys
	generated from the doom level.
*/

#include "StdAfx.h"
#include "defs.h"
#include "types.h"
#include "doomlevel.h"
#include "things.h"
#include "dumpmap.h"
#include "progress.h"

#define LAMETEX "base_floor/diamond2c"

void DumpMap(char *mapname, level_t *l, poly_t *ss, poly_t *world, int nWorld)
{
	char filename[MAX_PATH],tex[9],shader[256];
	FILE *f;
	int i,j,c;
	short z_ceil,z_floor,z_max,z_min;
	point3d_t p[3];
	sector_t *sec;
	int nBrushes;

	// create filename, open file
	strcpy(filename,mapname);
	strcat(filename,".map");
	f = fopen(filename,"w");
	if(f == NULL)
		return;

	printf("Writing brushes to mapfile: ");
	// init progress meter
	InitProgress(20,'*',true);
	// 2 brushes for each ssector (floor/ceiling)
	nBrushes = 2 * l->n_ssectors + nWorld;

	// put out some kinda comment
	fprintf(f,"// This map generated by Wad2Map v%d.%d\n",MAJORVERSION,MINORVERSION);

	// find max/min ceiling/floor
	z_max = short(0x8000);
	z_min = short(0x7FFF);
	for(i=0;i<l->n_sectors;i++) {
		z_max = max(z_max,l->sectors[i].ceiling_alt);
		z_min = min(z_min,l->sectors[i].floor_alt);
	}
	// make sure floors/ceilings are at least 16 thick
	z_max += 16;
	z_min -= 16;

	// output brushes
	c = 0;
	// worldspawn ent
	fprintf(f,"{\n\"classname\"  \"worldspawn\"\n\"message\"  \"%s\"\n",mapname);
//------------------------------------------------------
//   Ssector Polys
//------------------------------------------------------
	for(i=0;i<l->n_ssectors;i++) {
		// degenerate/erased polys
		if(ss[i].num_verts < 3)
			continue;

		// get floor/ceiling height
		if(ss[i].sector != -1) {
			sec = &l->sectors[ss[i].sector];
			z_ceil = sec->ceiling_alt;
			z_floor = sec->floor_alt;
		}
		else {
			z_ceil = z_max - 16;;
			z_floor = z_min + 16;;
		}

		// output to map
		//** START FLOOR **
		fprintf(f,"// brush %d\n",c++);
		fprintf(f,"{\n");
		// output floor planes
		// clockwise plane for top floor plane
		p[0].x = 0;
		p[0].y = 0;
		p[1].x = 0;
		p[1].y = 1;
		p[2].x = 1;
		p[2].y = 1;
		p[0].z = p[1].z = p[2].z = z_floor;
		OutputPlane(f,p,LAMETEX);
		// counterclockwise plane for bottom floor plane
		p[0].x = 0;
		p[0].y = 0;
		p[1].x = 1;
		p[1].y = 0;
		p[2].x = 1;
		p[2].y = 1;
		p[0].z = p[1].z = p[2].z = z_min;
		OutputPlane(f,p,LAMETEX);
		// output sides
		for(j=0;j<ss[i].num_verts-1;j++) {
			p[0].x = ss[i].p[j+1].x;
			p[0].y = ss[i].p[j+1].y;
			p[0].z = 1;
			p[1].x = ss[i].p[j].x;
			p[1].y = ss[i].p[j].y;
			p[1].z = 1;
			p[2].x = ss[i].p[j].x;
			p[2].y = ss[i].p[j].y;
			p[2].z = 0;
			OutputPlane(f,p,LAMETEX);
		}
		// side from last to first
		p[0].x = ss[i].p[0].x;
		p[0].y = ss[i].p[0].y;
		p[0].z = 1;
		p[1].x = ss[i].p[ss[i].num_verts-1].x;
		p[1].y = ss[i].p[ss[i].num_verts-1].y;
		p[1].z = 1;
		p[2].x = p[1].x;
		p[2].y = p[1].y;
		p[2].z = 0;
		OutputPlane(f,p,LAMETEX);
		// close brush (floor)
		fprintf(f,"}\n");
		DrawProgress(nBrushes,c);
		//** END FLOOR **

		//** START CEILING **
		// start next brush (ceiling)
		fprintf(f,"// brush %d\n",c++);
		fprintf(f,"{\n");
		// output ceiling planes
		// clockwise plane for top ceiling plane
		p[0].x = 0;
		p[0].y = 0;
		p[1].x = 0;
		p[1].y = 1;
		p[2].x = 1;
		p[2].y = 1;
		p[0].z = p[1].z = p[2].z = z_max;
		OutputPlane(f,p,LAMETEX);
		// counterclockwise plane for bottom ceiling plane
		p[0].x = 0;
		p[0].y = 0;
		p[1].x = 1;
		p[1].y = 0;
		p[2].x = 1;
		p[2].y = 1;
		p[0].z = p[1].z = p[2].z = z_ceil;
		OutputPlane(f,p,LAMETEX);
		// output sides
		for(j=0;j<ss[i].num_verts-1;j++) {
			p[0].x = ss[i].p[j+1].x;
			p[0].y = ss[i].p[j+1].y;
			p[0].z = 1;
			p[1].x = ss[i].p[j].x;
			p[1].y = ss[i].p[j].y;
			p[1].z = 1;
			p[2].x = ss[i].p[j].x;
			p[2].y = ss[i].p[j].y;
			p[2].z = 0;
			OutputPlane(f,p,LAMETEX);
		}
		// side from last to first
		p[0].x = ss[i].p[0].x;
		p[0].y = ss[i].p[0].y;
		p[0].z = 1;
		p[1].x = ss[i].p[ss[i].num_verts-1].x;
		p[1].y = ss[i].p[ss[i].num_verts-1].y;
		p[1].z = 1;
		p[2].x = p[1].x;
		p[2].y = p[1].y;
		p[2].z = 0;
		OutputPlane(f,p,LAMETEX);

		// close ceiling brush
		fprintf(f,"}\n");
		DrawProgress(nBrushes,c);
		//** END CEILING **
	}

//------------------------------------------------------
//     World Polys
//------------------------------------------------------
	// Output world brushes
	for(i=0;i<nWorld;i++) {
		fprintf(f,"// brush %d\n",c++);
		fprintf(f,"{\n");
		// output top and bottom planes
		// clockwise plane for top
		p[0].x = 0;
		p[0].y = 0;
		p[1].x = 0;
		p[1].y = 1;
		p[2].x = 1;
		p[2].y = 1;
		p[0].z = p[1].z = p[2].z = z_max;
		OutputPlane(f,p,LAMETEX);
		// counterclockwise plane for bottom
		p[0].x = 0;
		p[0].y = 0;
		p[1].x = 1;
		p[1].y = 0;
		p[2].x = 1;
		p[2].y = 1;
		p[0].z = p[1].z = p[2].z = z_min;
		OutputPlane(f,p,LAMETEX);
		// output sides
		for(j=0;j<world[i].num_verts-1;j++) {
			p[0].x = world[i].p[j+1].x;
			p[0].y = world[i].p[j+1].y;
			p[0].z = 1;
			p[1].x = world[i].p[j].x;
			p[1].y = world[i].p[j].y;
			p[1].z = 1;
			p[2].x = world[i].p[j].x;
			p[2].y = world[i].p[j].y;
			p[2].z = 0;
			OutputPlane(f,p,LAMETEX);
		}
		// side from last to first
		p[0].x = world[i].p[0].x;
		p[0].y = world[i].p[0].y;
		p[0].z = 1;
		p[1].x = world[i].p[world[i].num_verts-1].x;
		p[1].y = world[i].p[world[i].num_verts-1].y;
		p[1].z = 1;
		p[2].x = p[1].x;
		p[2].y = p[1].y;
		p[2].z = 0;
		OutputPlane(f,p,LAMETEX);
		// close brush
		fprintf(f,"}\n");
		DrawProgress(nBrushes,c);
	}

//------------------------------------------------------
//    Closure Brushes (seal up the level)
//------------------------------------------------------
	OutputSealBrushes(f,l,z_max,z_min);

	fprintf(f,"}\n"); // close up worldspawn
	fprintf(f,"\n");

	printf("\n");
//------------------------------------------------------
//    Things
//------------------------------------------------------
	ConvertThings(f,l,ss);

	// End!
	printf("Finished writing mapfile\n");
	fclose(f);
}

void OutputSealBrushes(FILE *f, level_t *l, int z_max, int z_min)
{
	short xmax,ymax,xmin,ymin;

	// get dimensions
	xmax = l->x_center + l->l_width / 2;
	xmin = l->x_center - l->l_width / 2;
	ymax = l->y_center + l->l_height / 2;
	ymin = l->y_center - l->l_height / 2;

	fprintf(f,"// Seal brushes\n");
	// Top brush
	fprintf(f,"{\n");
	// clockwise plane for top
	WriteZPlane(f,z_max,true);
	// counterclockwise plane for bottom
	WriteZPlane(f,z_max-16,false);
	// right side
	WriteXPlane(f,xmax+16,true);
	// left side
	WriteXPlane(f,xmin-16,false);
	// front side
	WriteYPlane(f,ymax+16,true);
	// back side
	WriteYPlane(f,ymin-16,false);
	fprintf(f,"}\n");

	// Bottom brush
	fprintf(f,"{\n");
	// clockwise plane for top
	WriteZPlane(f,z_min,true);
	// counterclockwise plane for bottom
	WriteZPlane(f,z_min-16,false);
	// right side
	WriteXPlane(f,xmax+16,true);
	// left side
	WriteXPlane(f,xmin-16,false);
	// front side
	WriteYPlane(f,ymax+16,true);
	// back side
	WriteYPlane(f,ymin-16,false);
	fprintf(f,"}\n");

	// Right side brush
	fprintf(f,"{\n");
	// clockwise plane for top
	WriteZPlane(f,z_max-16,true);
	// counterclockwise plane for bottom
	WriteZPlane(f,z_min,false);
	// right side
	WriteXPlane(f,xmax+16,true);
	// left side
	WriteXPlane(f,xmax,false);
	// front side
	WriteYPlane(f,ymax+16,true);
	// back side
	WriteYPlane(f,ymin-16,false);
	fprintf(f,"}\n");
	
	// Left side brush
	fprintf(f,"{\n");
	// clockwise plane for top
	WriteZPlane(f,z_max-16,true);
	// counterclockwise plane for bottom
	WriteZPlane(f,z_min,false);
	// right side
	WriteXPlane(f,xmin,true);
	// left side
	WriteXPlane(f,xmin-16,false);
	// front side
	WriteYPlane(f,ymax+16,true);
	// back side
	WriteYPlane(f,ymin-16,false);
	fprintf(f,"}\n");

	// Front brush
	fprintf(f,"{\n");
	// clockwise plane for top
	WriteZPlane(f,z_max-16,true);
	// counterclockwise plane for bottom
	WriteZPlane(f,z_min,false);
	// right side
	WriteXPlane(f,xmax,true);
	// left side
	WriteXPlane(f,xmin,false);
	// front side
	WriteYPlane(f,ymax+16,true);
	// back side
	WriteYPlane(f,ymax,false);
	fprintf(f,"}\n");

	// Back brush
	fprintf(f,"{\n");
	// clockwise plane for top
	WriteZPlane(f,z_max-16,true);
	// counterclockwise plane for bottom
	WriteZPlane(f,z_min,false);
	// right side
	WriteXPlane(f,xmax,true);
	// left side
	WriteXPlane(f,xmin,false);
	// front side
	WriteYPlane(f,ymin,true);
	// back side
	WriteYPlane(f,ymin-16,false);
	fprintf(f,"}\n");
}

void WriteZPlane(FILE *f, int z, bool dir)
{
	point3d_t p[3];

	p[0].x = 0;
	p[0].y = 0;
	p[1].x = (dir)? 0 : 1;
	p[1].y = (dir)? 1 : 0;
	p[2].x = 1;
	p[2].y = 1;
	p[0].z = p[1].z = p[2].z = z;
	OutputPlane(f,p,LAMETEX);
}

void WriteXPlane(FILE *f, int x, bool dir)
{
	point3d_t p[3];

	p[0].x = x;
	p[0].y = 0;
	p[0].z = 0;
	p[1].x = x;
	p[1].y = (dir) ? 0 : 1;
	p[1].z = (dir) ? 1 : 0;
	p[2].x = x;
	p[2].y = 1;
	p[2].z = 1;
	OutputPlane(f,p,LAMETEX);
}

void WriteYPlane(FILE *f, int y, bool dir)
{
	point3d_t p[3];

	p[0].x = 0;
	p[0].y = y;
	p[0].z = 0;
	p[1].x = (dir) ? 1 : 0;
	p[1].y = y;
	p[1].z = (dir) ? 0 : 1;
	p[2].x = 1;
	p[2].y = y;
	p[2].z = 1;
	OutputPlane(f,p,LAMETEX);
}

void OutputPlane(FILE *f,point3d_t p[], char *tex)
{
	// output points
	fprintf(f,"( "CSPEC" "CSPEC" "CSPEC" ) ( "CSPEC" "CSPEC" "CSPEC" ) ( "CSPEC" "CSPEC" "CSPEC" ) ",
		p[0].x,p[0].y,p[0].z,p[1].x,p[1].y,p[1].z,p[2].x,p[2].y,p[2].z);
	// output texture
	fprintf(f,"%s ",tex);
	// output other data (x/y offset, rotation, x/y scale, ? ? ?
	fprintf(f,"%d %d %d %8.6f %8.6f %d %d %d\n",0,0,0,1.0,1.0,0,0,0);
}
