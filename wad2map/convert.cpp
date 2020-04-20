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
	convert.cpp

	Ted Mielczarek
	1-13-2000

	This file contains the main routines for running through the conversion process.
*/

#include "StdAfx.h"
#include "defs.h"
#include "WadFile.h"
#include "convert.h"
#include "types.h"
#include "doomlevel.h"
#include "wadentries.h"
#include "clip_ssectors.h"
#include "subtract_ssectors.h"
#include "dumpmap.h"
#include "globals.h"

void strupper(char *s);

bool DoConversion(CWadFile &wadFile)
{
	levelentries le = W_NOT_LEVEL_ENTRY;
	char szEntry[256];
	bool outOfEntries = false;
	// level data
	level_t level;
	poly_t *polys;
	poly_t *world;
	int nWorld;

	// no mapname specified, get first map
	if(mapname[0] == '\0') {
		wadFile.SeekFirst(szEntry);
		le = LookupLevelEntry(szEntry);
		while(le != W_D1LEVEL && le != W_D2LEVEL) {
			if(!wadFile.SeekNext(szEntry))
				break;
			le = LookupLevelEntry(szEntry);
		}
		if(le != W_D1LEVEL && le != W_D2LEVEL) {
			fprintf(stderr,"No level entries found.\n");
			return(false);
		}
		strcpy(mapname,szEntry);
	}
	else {
		strupper(mapname);
		if(!wadFile.SeekTo(mapname)) {
			fprintf(stderr,"Level %s not found.\n",mapname);
			return(false);
		}
	}


	// Conversion loop
	do {
		printf("\nConverting %s\n",mapname);

		if(!LoadLevelData(wadFile,&level,mapname)) {
			fprintf(stderr,"Could not load level data!");
			return(false);
		}

		LevelExtents(&level);

		polys = new poly_t[level.n_ssectors];
		// clip ssectors to node clipping lines
		ClipSsectors(&level,polys);
		// get world polys
		poly_t tmp;
		MakeWorldPoly(&tmp,&level);
		ClipWorldToPolys(&tmp,polys,level.n_ssectors,&world,nWorld);
		if(world == NULL)
			fprintf(stderr,"ClipWorldToPolys failed!\n");

		// output a .map
		DumpMap(mapname,&level,polys,world,nWorld);

		// clean up memory
		CleanupLevel(&level);
		if(polys != NULL) {
			delete[] polys;
			polys = NULL;
		}
		if(world != NULL) {
			delete[] world;
			world = NULL;
			nWorld = 0;
		}

		// find next level, if using "convert all"
		if(convert_all) {
			wadFile.SeekTo(mapname);
			do {
				if(!wadFile.SeekNext(szEntry)) {
					outOfEntries = true;
					break;
				}
				le = LookupLevelEntry(szEntry);
			} while(le != W_D1LEVEL && le != W_D2LEVEL);
			strcpy(mapname,szEntry);
		}

	} while((le == W_D1LEVEL || le == W_D2LEVEL) && convert_all && !outOfEntries);
	return(true);
}

void strupper(char *s)
{
	while(*s)
		*s++ = toupper(*s);
}
