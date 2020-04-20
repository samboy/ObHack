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
// WadFile.h: interface for the CWadFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WADFILE_H__852EB12B_ACEE_11D3_910E_0000E82F44A6__INCLUDED_)
#define AFX_WADFILE_H__852EB12B_ACEE_11D3_910E_0000E82F44A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// This is defined for windows
#ifndef ZeroMemory
#define ZeroMemory(x,y) memset(x,0,y)
#endif

// Wad Header struct
typedef struct s_wadheader
{
	char id[4];		// wad id, either IWAD or PWAD
	long numlumps;	// number of entries
	long dirpos;	// offset to start of directory
} wadheader_t;

// Wad Directory Entry struct
typedef struct s_waddirentry
{
	long offset;	// offset from start of wad, in bytes
	long size;		// size, in bytes
	char name[8];	// name, padded with zeroes
} waddirentry_t;

// wad types
#define IWAD_ID "IWAD"
#define PWAD_ID "PWAD"

enum wadtypes {
	NO_WAD,
	IWAD,
	PWAD
};

class CWadFile  
{
public:
	bool SeekFirst(char *szEntry);
	wadtypes WadType(void);
	void Close(void);
	long GetEntrySize();
	bool GetEntryData(void *pData);
	bool SeekPrevious(char *szEntry);
	bool SeekNext(char *szEntry);
	bool SeekTo(char *szEntry);
	bool IsOpen();
	bool Open(char *szFile);
	CWadFile(char *szFile);
	CWadFile();
	virtual ~CWadFile();

private:
	bool isOpen;
	FILE *wadfile;
	wadheader_t header;
	waddirentry_t *directory;
	wadtypes theWadType;
	long currentEntry;
};

#endif // !defined(AFX_WADFILE_H__852EB12B_ACEE_11D3_910E_0000E82F44A6__INCLUDED_)
