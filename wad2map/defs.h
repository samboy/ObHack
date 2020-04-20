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
	defs.h

	Ted Mielczarek
	1-13-2000

	Definitions of random stuff
*/
#ifndef __DEFS_H_
#define __DEFS_H_

#define MAJORVERSION 1
#define MINORVERSION 0

#ifndef max
#define max(x,y) ((x > y)?(x):(y))
#define min(x,y) ((x < y)?(x):(y))
#endif

#ifndef MAX_PATH
#define MAX_PATH 1024
#endif

#define WHITESPACECHARS " \t\r\n"

#ifndef OutputDebugString
#if DEBUG
#define OutputDebugString(x) fprintf(stderr,x)
#else
#define OutputDebugString
#endif /* DEBUG */
#endif /* OutputDebugString */

#endif /* __DEFS_H_ */
