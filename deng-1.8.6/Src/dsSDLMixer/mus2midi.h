/* DE1: $Id: mus2midi.h,v 1.1 2004/08/08 19:09:19 skyjake Exp $
 * Copyright (C) 2004 Jaakko Ker�nen <jaakko.keranen@iki.fi>
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
 * mus2midi.h: MUS to MIDI conversion
 */

#ifndef __DOOMSDAY_SDLMIXER_MUS2MIDI_H__
#define __DOOMSDAY_SDLMIXER_MUS2MIDI_H__

void convertMusToMidi(unsigned char *data, unsigned int length,
					  const char *outFile);

#endif
