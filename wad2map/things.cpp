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
	things.cpp

	Ted Mielczarek
	1-11-2000

	This file contains routines for converting things from a wadfile
	to a .map file.
*/

#include "StdAfx.h"
#include <errno.h>
#include "defs.h"
#include "types.h"
#include "doomlevel.h"
#include "2dclip.h"
#include "things.h"
#include "progress.h"

// Globals
thingconvert_t things[MAX_DOOM_THINGS];
int numthings = 0;
specialthing_t specialthings[] = {
	{'*', MiscModel}
};
int numspecialthings = sizeof(specialthings) / sizeof(specialthing_t);

// This function is only used if the thing convert file cannot be loaded
void SetThingConvertDefaults(void)
{
	memset(things,0,sizeof(things));
	// just initialize this one for quick testing
	things[0].d_thing = 1;
	strcpy(things[0].q_entity,"info_player_start");
	numthings++;
}

void LoadThingConvertFile(char *szFile)
{
	FILE *f;
	char strIn[1024], qThing[256],*s,*ptr;
	long dThing;
	int i;

	f = fopen(szFile,"r");
	if(f == NULL) {
		fprintf(stderr,"Could not open thing convert list %s, using defaults.\n",szFile);
		SetThingConvertDefaults();
		return;
	}

	printf("Loading thing conversion options from %s\n",szFile);

	// initialize numthings
	numthings = 0;
	i = 0;

	while(!feof(f)) {
		fgets(strIn,1024,f);
		if(feof(f))
			break;

		i++;
		// look for thing number
		s = strtok(strIn,WHITESPACECHARS);
		// nothing on line
		if(s == NULL)
			continue;

		// just a comment
		if(*s == ';')
			continue;

		dThing = strtol(s,&ptr,0);
		if(*ptr != '\0' || errno == ERANGE) {
			fprintf(stderr,"LoadThingConvertFile: Bad thing number on line %d\n",i);
			continue;
		}

		// look for entity name
		s = strtok(NULL,WHITESPACECHARS);

		// skip things with nothing to convert to
		// blank line
		if(s == NULL)
			continue;
		// just a comment
		else if(*s == ';')
			continue;

		strcpy(qThing,s);

		// set values
		things[numthings].d_thing = short(dThing);
		strcpy(things[numthings].q_entity,qThing);
		numthings++;
	}

	fclose(f);
}

bool ConvertThings(FILE *f, level_t *l, poly_t *ss)
{
	int i,c,z,st;
	thing_t *t = l->things;
	char szName[256];

	printf("Converting things: ");
	InitProgress(20,'*',true);
	DrawProgress(l->n_things,0);

	c = 0;
	for(i=0; i<l->n_things; i++, t++) {
		if(LookupThing(t->thingnum,szName)) {
			// get  z coordinate
			z = GetThingZ(l,t,ss);
			// see if it's a "special thing"
			st = LookupSpecialThing(szName[0]);
			// output thing
			fprintf(f,"// entity %d\n",c++);
			fprintf(f,"{\n");
			// handle "special things"
			if(st != -1)
				specialthings[st].stp(f,szName+1,t,z);
			else {
				fprintf(f,"\"classname\" \"%s\"\n",szName);
				fprintf(f,"\"origin\" \"%d %d %d\"\n",t->x,t->y,z);
				fprintf(f,"\"angle\" \"%d\"\n",t->angle);
			}
			fprintf(f,"}\n\n");
		}
		DrawProgress(l->n_things,i);
	}
	DrawProgress(l->n_things,i);
	printf("\n");

	return(true);
}

bool LookupThing(short d_thing, char *q_entity)
{
	int i;

	// lookup d_thing number in things list
	for(i=0;i<numthings;i++) {
		if(d_thing == things[i].d_thing) {
			// found
			strcpy(q_entity,things[i].q_entity);
			return(true);
		}
	}
	// not found
	return(false);
}

int LookupSpecialThing(char c)
{
	int i;

	for(i=0;i<numspecialthings;i++)
		if(specialthings[i].c == c)
			return(i);

	return(-1);
}

int GetThingZ(level_t *l, thing_t *t, poly_t *ss)
{
	int i;
	point_t p;

	// coords of thing
	p.x = t->x;
	p.y = t->y;

	for(i=0; i<l->n_ssectors; i++) {
		if(PointInPoly(&p,&ss[i]))
			return(l->sectors[ss[i].sector].floor_alt + 8);
	}

	return(0);
}

//--------------------------------------------------
// "Special Things" procedures
//--------------------------------------------------
bool MiscModel(FILE *f, char *szModel, thing_t *t, int z)
{
	if(*szModel == '\0')
		return(false);

	fprintf(f,"\"classname\" \"misc_model\"\n");
	fprintf(f,"\"model\" \"%s\"\n",szModel);
	fprintf(f,"\"origin\" \"%d %d %d\"\n",t->x,t->y,z);
	return(true);
}
