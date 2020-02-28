/* DE1: $Id: con_decl.h,v 1.5 2004/05/31 15:04:41 skyjake Exp $
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
 * con_decl.h: Console Utility Macros
 */

#ifndef __DOOMSDAY_CONSOLE_DECL_H__
#define __DOOMSDAY_CONSOLE_DECL_H__

#include "con_main.h"

/*
 * Macros for creating new console commands.
 */
#define C_CMD(name, fn, help) \
	{ ccmd_t _c = { name, CCmd##fn, help }; Con_AddCommand(&_c); }

// A handy helper for declaring console commands.
#define D_CMD(x) int CCmd##x(int argc, char **argv)

/*
 * Macros for creating new console variables.
 */
#define C_VAR(name, ptr, type, flags, min, max, help)			\
	{ cvar_t _v = { name, flags, type, ptr, min, max, help };	\
		Con_AddVariable(&_v); }

#define C_VAR_BYTE(name, ptr, flags, min, max, help)	\
	C_VAR(name, ptr, CVT_BYTE, flags, min, max, help)

#define C_VAR_INT(name, ptr, flags, min, max, help)		\
	C_VAR(name, ptr, CVT_INT, flags, min, max, help)

#define C_VAR_FLOAT(name, ptr, flags, min, max, help) \
	C_VAR(name, ptr, CVT_FLOAT, flags, min, max, help)

#define C_VAR_CHARPTR(name, ptr, flags, min, max, help) \
	C_VAR(name, ptr, CVT_CHARPTR, flags, min, max, help)

#endif
