/* DE1: $Id: con_config.c,v 1.9 2004/05/31 15:04:42 skyjake Exp $
 * Copyright (C) 2003, 2004 Jaakko Ker�nen <jaakko.keranen@iki.fi>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not: http://www.opensource.org/
 */

/*
 * con_config.c: Config Files
 */

// HEADER FILES ------------------------------------------------------------

#include <ctype.h>

#include "de_base.h"
#include "de_console.h"
#include "de_system.h"
#include "de_misc.h"

// MACROS ------------------------------------------------------------------

// TYPES -------------------------------------------------------------------

// EXTERNAL FUNCTION PROTOTYPES --------------------------------------------

// PUBLIC FUNCTION PROTOTYPES ----------------------------------------------

// PRIVATE FUNCTION PROTOTYPES ---------------------------------------------

// EXTERNAL DATA DECLARATIONS ----------------------------------------------

// PUBLIC DATA DEFINITIONS -------------------------------------------------

char    cfgFile[256];

// PRIVATE DATA DEFINITIONS ------------------------------------------------

// CODE --------------------------------------------------------------------

/*
 * Con_ParseCommands
 */
int Con_ParseCommands(char *fileName, int setdefault)
{
	DFILE  *file;
	char    buff[512];
	int     line = 1;

	// Is this supposed to be the default?
	if(setdefault)
		strcpy(cfgFile, fileName);

	// Open the file.
	if((file = F_Open(fileName, "rt")) == NULL)
		return false;

	VERBOSE(Con_Printf
			("Con_ParseCommands: %s (def:%i)\n", fileName, setdefault));

	// This file is filled with console commands.
	// Each line is a command.

	for(;;)
	{
		M_ReadLine(buff, 512, file);
		if(!M_IsComment(buff))
		{
			// Execute the commands silently.
			if(!Con_Execute(buff, setdefault ? true : false))
				Con_Message("%s(%d): error executing command\n" "  \"%s\"\n",
							fileName, line, buff);
		}
		if(deof(file))
			break;
		line++;
	}
	F_Close(file);
	return true;
}

/*
 * Con_WriteState
 *  Writes the state of the console (variables, bindings, aliases) into the
 *  given file, overwriting the previous contents.
 */
boolean Con_WriteState(const char *fileName)
{
	extern cvar_t *cvars;
	extern int numCVars;
	int     i;
	cvar_t *var;
	FILE   *file;

	VERBOSE(Con_Printf("Con_WriteState: %s\n", fileName));

	if((file = fopen(fileName, "wt")) == NULL)
	{
		Con_Message("Con_WriteState: Can't open %s for writing.\n", fileName);
		return false;
	}

	fprintf(file, "# %s / Doomsday Engine " DOOMSDAY_VERSION_TEXT "\n",
			gx.Get(DD_GAME_ID));
	fprintf(file,
			"# This configuration file is generated automatically. Each line is a\n");
	fprintf(file,
			"# console command. Lines beginning with # are comments. Use autoexec.cfg\n");
	fprintf(file, "# for your own startup commands.\n\n");

	fprintf(file, "#\n# CONSOLE VARIABLES\n#\n\n");

	// We'll write all the console variables that are flagged for archiving.        
	for(i = 0; i < numCVars; i++)
	{
		var = cvars + i;
		if(var->type == CVT_NULL || var->flags & CVF_NO_ARCHIVE)
			continue;

		// First print the comment (help text).
		M_WriteCommented(file, var->help);
		fprintf(file, "%s ", var->name);
		if(var->flags & CVF_PROTECTED)
			fprintf(file, "force ");
		if(var->type == CVT_BYTE)
			fprintf(file, "%d", *(byte *) var->ptr);
		if(var->type == CVT_INT)
			fprintf(file, "%d", *(int *) var->ptr);
		if(var->type == CVT_FLOAT)
			fprintf(file, "%s", TrimmedFloat(*(float *) var->ptr));
		if(var->type == CVT_CHARPTR)
		{
			fprintf(file, "\"");
			M_WriteTextEsc(file, *(char **) var->ptr);
			fprintf(file, "\"");
		}
		fprintf(file, "\n\n");
	}

	fprintf(file, "#\n# BINDINGS\n#\n\n");
	B_WriteToFile(file);

	fprintf(file, "\n#\n# ALIASES\n#\n\n");
	Con_WriteAliasesToFile(file);

	fclose(file);
	return true;
}

/*
 * Con_SaveDefaults
 *  Saves all bindings, aliases and archiveable console variables.
 *  The output file is a collection of console commands.
 */
void Con_SaveDefaults(void)
{
	Con_WriteState(cfgFile);
}

/*
 * CCmdWriteConsole
 */
int CCmdWriteConsole(int argc, char **argv)
{
	if(argc != 2)
	{
		Con_Message("Usage: %s (filename)\n", argv[0]);
		Con_Message("Saves console variables, bindings and aliases.\n");
		return true;
	}
	Con_Message("Writing to %s...\n", argv[1]);
	return !!Con_WriteState(argv[1]);
}
