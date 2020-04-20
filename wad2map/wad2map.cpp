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
	wad2map.cpp

	Main entry point
*/
#include "StdAfx.h"
#include "defs.h"
#include "types.h"
#include "doomlevel.h"
#include "WadFile.h"
#include "convert.h"
#include "globals.h"
#include "things.h"

// Local function prototypes
int GetCommandlineOptions(int argc, char **argv);
void usage(void);
void License(void);

// Global variables
char wadfilename[MAX_PATH] = "\0",
		entityoptfilename[MAX_PATH] = DEFAULTENTITYFILE,
		textureoptfilename[MAX_PATH] = DEFAULTTEXTUREFILE;
char mapname[9] = "\0";
bool convert_all = false,
		do_textures = false;

// Function definitions
int main(int argc, char **argv)
{
	CWadFile theWad;
	int i;

	License();

	if(argc < 2)
		usage();

	// Check commandline options
	i = GetCommandlineOptions(argc,argv);

	// open wadfile and proceed
	if(!theWad.Open(argv[i])) {
		printf("Could not open %s for input!\n",argv[i]);
		exit(1);
	}

	// get thing/texture conversion data
	LoadThingConvertFile(entityoptfilename);

	// do all conversion
	DoConversion(theWad);
	// close up
	theWad.Close();

	printf("Exiting...\n");

	return(0);
}

int GetCommandlineOptions(int argc, char **argv)
{
	int i;

		// check commandline options
	for(i=1;i<argc;i++) {
		// check for "convert all" option
		if(!strcmp(argv[i],"-a")) {
			convert_all = true;
		}
		// check for "do textures" option
		else if(!strcmp(argv[i],"-dt")) {
			do_textures = true;
		}
		// check for map name
		else if(!strcmp(argv[i],"-m")) {
			i++;
			if(i == argc)
				usage();
			strcpy(mapname,argv[i]);
		}
		// check for entity conversion options file
		else if(!strcmp(argv[i],"-e")) {
			i++;
			if(i == argc)
				usage();
			strcpy(entityoptfilename,argv[i]);
		}
		// check for texture conversion options files
		else if(!strcmp(argv[i],"-t")) {
			i++;
			if(i == argc)
				usage();
			strcpy(textureoptfilename,argv[i]);
		}
		else // unknown option
			if(i < argc-1)
				usage();
	}

	if(i == (argc + 1))
		usage();

	return(i - 1);
}

void usage(void)
{
	printf("Usage: wad2map [options] wadfile\n");
	printf("options:\n\n");
	printf("-m mapname\n");
	printf("Convert this map.  If used with -a,\n");
	printf("starts with this map and converts all\n");
	printf("maps following it.  If not specified,\n");
	printf("converts the first map found.\n\n");
	printf("-a\n");
	printf("Convert all maps in the wad.\n\n");
	printf("-e file\n");
	printf("Read entity conversion data from this\n");
	printf("file.  Default is %s\n\n",DEFAULTENTITYFILE);
	printf("-t file\n");
	printf("Read texture conversion data from this\n");
	printf("file.  Default is %s (not functional)\n\n",DEFAULTTEXTUREFILE);
	printf("-dt\n");
	printf("Replace textures with Quake textures.\n");
	printf("Do not use this option if you intend to\n");
	printf("use converted doom textures. (not functional)\n\n");

	exit(1);
}

void License(void)
{
	printf("Wad2Map version 1.0, Copyright (C) 2000 Ted Mielczarek\n"
		"Wad2Map comes with ABSOLUTELY NO WARRANTY; for details see GPL.txt\n"
		"This is free software, and you are welcome to redistribute it\n"
		"under certain conditions; see GPL.txt for details.\n\n");
}