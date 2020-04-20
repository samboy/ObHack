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
// WadFile.cpp: implementation of the CWadFile class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "WadFile.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWadFile::CWadFile()
{
	isOpen = false;
	wadfile = NULL;
	ZeroMemory(&header,sizeof(header));
	directory = NULL;
	theWadType = NO_WAD;
	currentEntry = -1;
}

CWadFile::~CWadFile()
{
	if(isOpen)
		Close();
}

// Constructor with filename parameter
CWadFile::CWadFile(char *szFile)
{
	Open(szFile);
}

//------------------------------
// Open
//		Open a wad file with
//	the specified path/filename.
//  Return true for success, false
//	for failure.
//------------------------------
bool CWadFile::Open(char *szFile)
{
	if(isOpen)
		Close();

	ZeroMemory(&header,sizeof(header));

	wadfile = fopen(szFile,"rb");

	if(wadfile == NULL)
		return(false);

	if(fread(&header,sizeof(wadheader_t),1,wadfile) != 1) {
		fclose(wadfile);
		return(false);
	}

	// Check wad type
	if(!strncmp(header.id,IWAD_ID,4))
		// IWAD
		theWadType = IWAD;
	else if(!strncmp(header.id,PWAD_ID,4))
		// PWAD
		theWadType = PWAD;
	else {
		// not a valid wadfile
		fclose(wadfile);
		return(false);
	}

	if(header.numlumps <= 0) {
		// empty wad
		theWadType = NO_WAD;
		fclose(wadfile);
		return(false);
	}

	if(fseek(wadfile,header.dirpos,SEEK_SET) != 0) {
		// couldn't find directory
		theWadType = NO_WAD;
		fclose(wadfile);
		return(false);
	}

	// allocate memory for wad directory
	directory = new waddirentry_t[header.numlumps];

	if(directory == NULL) { // uh oh
		theWadType = NO_WAD;
		fclose(wadfile);
		return(false);
	}

	// attempt to read in directory
	if(fread(directory,sizeof(waddirentry_t),header.numlumps,wadfile)
		!= unsigned(header.numlumps)) {
		delete[] directory;
		theWadType = NO_WAD;
		fclose(wadfile);
		return(false);
	}

	// start at first entry
	currentEntry = 0;
	if(fseek(wadfile,directory[0].offset,SEEK_SET) != 0) {
		delete[] directory;
		theWadType = NO_WAD;
		fclose(wadfile);
		return(false);
	}

	// wadfile is open
	isOpen = true;

	return(true);
}

//------------------------------
// IsOpen
//		Return true if a wadfile
//	is open, false if not.
//------------------------------
bool CWadFile::IsOpen(void)
{
	return(isOpen);
}

//------------------------------
// SeekTo
//		Find the first entry in
//	the wadfile with this name.
//	Return true if found, false
//	if not.
//------------------------------
bool CWadFile::SeekTo(char *szEntry)
{
	int i;

	if(szEntry == NULL || szEntry[0] == '\0')
		return(false);

	for(i=0;i<header.numlumps;i++) {
		if(!strncmp(directory[i].name,szEntry,8)) {
			currentEntry = i;
			return(true);
		}
	}

	return(false);
}

//------------------------------
// SeekNext
//		Seek to the next entry
//	in the wadfile.  If szEntry
//	is not NULL, copy the entry
//	name into it.
//------------------------------
bool CWadFile::SeekNext(char *szEntry)
{
	// are we already at the end
	if(currentEntry + 1 == header.numlumps)
		return(false);

	currentEntry++;

	if(szEntry != NULL) {
		strncpy(szEntry,directory[currentEntry].name,8);
		szEntry[8] = '\0';
	}

	return(true);
}

//------------------------------
// SeekPrevious
//		Seek to the previous entry
//	in the wadfile.  If szEntry
//	is not NULL, copy the entry
//	name into it.
//------------------------------
bool CWadFile::SeekPrevious(char *szEntry)
{
	// are we already at the beginning
	if(currentEntry == 0)
		return(false);

	currentEntry--;

	if(szEntry != NULL) {
		strncpy(szEntry,directory[currentEntry].name,8);
		szEntry[8] = '\0';
	}

	return(true);
}

//------------------------------
// GetEntryData
//		Get the data associated
//	with the current entry and
//	store it in pData.  Returns
//	true on success, false on
//	failure.
//------------------------------
bool CWadFile::GetEntryData(void *pData)
{
	if(pData == NULL)
		return(false);

	// seek to entry
	if(fseek(wadfile,directory[currentEntry].offset,SEEK_SET) != 0)
		return(false);

	// read entry
	if(fread(pData,directory[currentEntry].size,1,wadfile) != 1)
		return(false);
	
	return(true);
}

//------------------------------
// GetEntrySize
//		Get the size of the current
//	entry, in bytes.
//------------------------------
long CWadFile::GetEntrySize(void)
{
	if(!isOpen)
		return(0);

	return(directory[currentEntry].size);
}

//------------------------------
// Close
//		Close the current wadfile.
//------------------------------
void CWadFile::Close()
{
	if(!isOpen)
		return;

	delete[] directory;
	directory = NULL;
	fclose(wadfile);
	wadfile = NULL;
	isOpen = false;
	theWadType = NO_WAD;
	currentEntry = -1;
	ZeroMemory(&header,sizeof(header));
}

wadtypes CWadFile::WadType()
{
	return(theWadType);
}

bool CWadFile::SeekFirst(char *szEntry)
{
	if(header.numlumps == 0)
		return(false);

	currentEntry = 0;
	if(szEntry != NULL) {
		strncpy(szEntry,directory[currentEntry].name,8);
		szEntry[8] = '\0';
	}
	return(true);
}
