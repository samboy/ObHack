/* DE1: $Id: de_system.h,v 1.8 2004/09/20 19:37:08 skyjake Exp $
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
 * de_system.h: Operating System Dependent Subsystems
 */

#ifndef __DOOMSDAY_SYSTEM__
#define __DOOMSDAY_SYSTEM__

#include "sys_system.h"
#include "sys_console.h"
#include "sys_direc.h"
#include "sys_file.h"
#include "sys_input.h"
#include "sys_network.h"
#include "sys_sock.h"
#include "sys_master.h"
#include "sys_timer.h"
#include "sys_mixer.h"
#include "sys_stwin.h"

#ifdef UNIX
#  include "Unix/sys_path.h"
#endif

#endif
