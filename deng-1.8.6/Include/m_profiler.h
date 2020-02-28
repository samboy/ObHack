/* DE1: $Id: m_profiler.h,v 1.8 2004/05/31 15:04:41 skyjake Exp $
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
 * m_profiler.h: Utility Macros for Profiling
 */

#ifndef __DOOMSDAY_MISC_PROFILER_H__
#define __DOOMSDAY_MISC_PROFILER_H__

#if 0							   // Disabled

#include "dd_types.h"
#include "sys_timer.h"

/*
 * This header defines some handy macros for profiling. 
 * Define DD_PROFILE to active.
 */

typedef struct profiler_s {
	uint            totalTime;
	uint            startTime;
	uint            startCount;
} profiler_t;

#define BEGIN_PROF_TIMERS()	enum {

#ifdef DD_PROFILE				   // Profiling is enabled.
# define END_PROF_TIMERS()	,NUM_PROFS }; static profiler_t profiler_[NUM_PROFS];
# define BEGIN_PROF(x)		(profiler_[x].startCount++, profiler_[x].startTime = Sys_GetRealTime())
# define END_PROF(x)		(profiler_[x].totalTime += Sys_GetRealTime() - profiler_[x].startTime)
# define PRINT_PROF(x)		Con_Message(#x ": %i ms (%i starts) [%f ms]\n", \
								profiler_[x].totalTime, profiler_[x].startCount, \
								profiler_[x].startCount? profiler_[x].totalTime / \
								(float) profiler_[x].startCount : 0)
#else							// Profiling is disabled.
# define END_PROF_TIMERS()	,NUM_PROFS };
# define BEGIN_PROF(x)
# define END_PROF(x)
# define PRINT_PROF(x)
#endif							// DD_PROFILE

#endif

#endif
