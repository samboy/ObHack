/* DE1: $Id: sys_mixer.c,v 1.4 2004/05/31 15:17:03 skyjake Exp $
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
 * sys_mixer.c: Volume Control
 */

// HEADER FILES ------------------------------------------------------------

#include "de_base.h"
#include "de_console.h"
#include "de_system.h"
#include "de_audio.h"
#include "de_misc.h"

// MACROS ------------------------------------------------------------------

// TYPES -------------------------------------------------------------------

// EXTERNAL FUNCTION PROTOTYPES --------------------------------------------

// PUBLIC FUNCTION PROTOTYPES ----------------------------------------------

// PRIVATE FUNCTION PROTOTYPES ---------------------------------------------

// EXTERNAL DATA DECLARATIONS ----------------------------------------------

// PUBLIC DATA DEFINITIONS -------------------------------------------------

// PRIVATE DATA DEFINITIONS ------------------------------------------------

static int initOk = 0;

// CODE --------------------------------------------------------------------

//===========================================================================
// Sys_InitMixer
//===========================================================================
int Sys_InitMixer(void)
{
	if(initOk || ArgCheck("-nomixer") || ArgCheck("-nomusic") || isDedicated)
		return true;

	// We're successful.
	initOk = true;
	return true;
}

//===========================================================================
// Sys_ShutdownMixer
//===========================================================================
void Sys_ShutdownMixer(void)
{
	if(!initOk)
		return;					// Can't uninitialize if not inited.
	initOk = false;
}

//===========================================================================
// Sys_Mixer4i
//===========================================================================
int Sys_Mixer4i(int device, int action, int control, int parm)
{
	if(!initOk)
		return MIX_ERROR;

	// There is currently no implementation for anything.
	return MIX_ERROR;
}

//===========================================================================
// Sys_Mixer3i
//===========================================================================
int Sys_Mixer3i(int device, int action, int control)
{
	return Sys_Mixer4i(device, action, control, 0);
}
