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
	clip_ssectors.h

	Ted Mielczarek
	12-13-1999

	This file contains the prototypes for the ssector clipping code.
*/
#ifndef __CLIP_SSECTORS_H_
#define __CLIP_SSECTORS_H_

bool ClipSsectors(level_t *level, poly_t *polys);
void MakeWorldPoly(poly_t *thePoly, level_t *level);
bool RecurseNodes(node_t *node, poly_t *thePoly, level_t *level, poly_t *polys);

#endif /* __CLIP_SSECTORS_H_ */
