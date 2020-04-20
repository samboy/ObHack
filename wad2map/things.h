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
	things.h

	Ted Mielczarek
	1-11-2000

	This file contains definitions for things.cpp
*/
#ifndef __THINGS_H_
#define __THINGS_H_

// thing conversion list
typedef struct thingconvert_s
{
	short d_thing;
	char q_entity[256];
} thingconvert_t;

typedef bool (*SPECIALTHINGPROC)(FILE *,char *, thing_t *, int);
typedef struct specialthing_s
{
	char c;
	SPECIALTHINGPROC stp;
} specialthing_t;

// number of unique things present in Doom
#define MAX_DOOM_THINGS 123

#define THING_SKILL_EASY	1
#define THING_SKILL_MED		(1<<1)
#define THING_SKILL_HARD	(1<<2)
#define THING_DEAF				(1<<3)
#define THING_MULTI_ONLY	(1<<4)

void SetThingConvertDefaults(void);
void LoadThingConvertFile(char *szFile);
bool ConvertThings(FILE *f, level_t *l, poly_t *ss);
bool LookupThing(short d_thing, char *q_entity);
int LookupSpecialThing(char c);
int GetThingZ(level_t *l, thing_t *t, poly_t *ss);
// Special Thing procs
bool MiscModel(FILE *f, char *szModel, thing_t *t, int z);
#endif /* __THINGS_H_ */
