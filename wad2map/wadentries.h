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
	wadentries.h

	Ted Mielczarek
	12/07/1999

  This file contains an enumeration of the different wad entry types.
 */

#ifndef __WADENTRIES_H_
#define __WADENTRIES_H_

typedef enum {
	W_THINGS		= 0,
	W_LINEDEFS	= 1,
	W_SIDEDEFS	= 2,
	W_VERTEXES	= 3,
	W_SEGS			= 4,
	W_SSECTORS	= 5,
	W_NODES			= 6,
	W_SECTORS		= 7,
	W_REJECT		= 8,
	W_BLOCKMAP	= 9,
	W_D1LEVEL,
	W_D2LEVEL,
	W_NOT_LEVEL_ENTRY
} levelentries;

extern const char WAD_ENTRY_NAMES[10][9];
#define NUM_LEVEL_ENTRIES 10

// lookup function
levelentries LookupLevelEntry(char *s);
bool LoadLevelData(CWadFile &wadFile, level_t *level, char *szMap);
void LevelExtents(level_t *level);
void InitLevel(level_t *l);
void CleanupLevel(level_t *l);
void DumpLevel(char *filename, level_t *l);

#endif /* __WADENTRIES_H_ */
