/* DE1: $Id: sys_file.h,v 1.10 2004/07/24 21:53:29 skyjake Exp $
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
 * sys_file.h: File Stream Abstraction Layer
 *
 * Data can be read from memory, virtual files or actual files.
 */

#ifndef __FILE_IO_H__
#define __FILE_IO_H__

#include <stdio.h>

#define deof(file) ((file)->flags.eof != 0)

typedef struct {
	struct DFILE_flags_s {
		unsigned char   open:1;
		unsigned char   file:1;
		unsigned char   eof:1;
	} flags;
	int             size;
	void           *data;
	char           *pos;
	unsigned int    lastModified;
} DFILE;

typedef enum filetype_e {
	FT_NORMAL,
	FT_DIRECTORY
} filetype_t;

typedef int     (*f_forall_func_t) (const char *fn, filetype_t type,
									void *parm);

void            F_InitDirec(void);
void            F_ShutdownDirec(void);
int             F_Access(const char *path);
DFILE          *F_Open(const char *path, const char *mode);
void            F_Close(DFILE * file);
int             F_Length(DFILE * file);
int             F_Read(void *dest, int count, DFILE * file);
int             F_GetC(DFILE * file);
int             F_Tell(DFILE * file);
int             F_Seek(DFILE * file, int offset, int whence);
void            F_Rewind(DFILE * file);
int             F_ForAll(const char *filespec, void *parm,
						 f_forall_func_t func);
unsigned int    F_LastModified(const char *fileName);

#endif
