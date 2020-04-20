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
	progress.cpp

	Ted Mielczarek
	1-13-2000

	Defines routines for drawing an ascii progress bar.
*/

#include "StdAfx.h"
#include "progress.h"

int progLen = 10;
char fillChar = '*';
char clearBuf[256] = "\0";
bool doPercent = false;

void InitProgress(int len, char fill, bool drawPercent)
{
	int i,c;

	if(len > 255)
		len = 255;

	progLen = len;
	fillChar = fill;
	doPercent = drawPercent;

	clearBuf[0] = '\0';
	c = progLen+1;
	if(doPercent)
		c += 5;

	for(i=0;i<c;i++)
		strcat(clearBuf,"\b");

	// print empty progress bar
	printf("[");
	for(i=0;i<len;i++)
		printf(" ");
	printf("]   0%%");
}

void DrawProgress(long total, long count)
{
	int i, c;
	double d;

	d = double(count) / double(total);
	c = int(progLen * d);

	// clear last progress bar
	printf(clearBuf);

	// print progress bar
	for(i=0;i<progLen;i++)
		(i<c) ?
		printf("*") :
		printf(" ");

	if(doPercent)
		printf("] %3d%%",int(d*100));
	else
		printf("]");
}
