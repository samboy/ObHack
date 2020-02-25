#!/usr/bin/python

# Wad2PDF is a program that converts Doom levels into PDF files.
# (C) 2005-2008 Jussi Pakkanen
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

import os, sys, time
import pdflogic, wad
from thingdics import *

config = pdflogic.config

def createdefaultconfig():
    global config
    config['papersize'] = papersizedic['A4'] 
    config['drawthinggraphics'] = True
    config['drawthingcrosses'] = False
    config['drawsubsectors'] = True
    config['compresslevels'] = True
    config['useblockmap'] = True
    config['mergelevels'] = False
    config['levelnames'] = None
    config['textoffset'] = 30 # Used in aligning console texts.
    config['lighting'] = False
    config['lightvalue'] = 0.4

def filterlevels(wad):
    """Remove all levels not wanted by the user."""
    if not config.has_key('levels'):
        return
    filtered = []
    for level in wad.levels:
        if config['levels'].has_key(level.header.name):
            filtered.append(level)
    wad.levels = filtered
    

def mergearray(target, source, levels=False):
    """Adds and overwrites graphics from the source to target arrays."""
    for sgra in source:
        overwritten = 0
        for i in range(len(target)):
            tgra = target[i]

            # If the lump exists, overwrite it.
            if levels: # Are we dealing with levels?
                tname = tgra.header.name
                sname = sgra.header.name
            else:
                tname = tgra.name
                sname = sgra.name
            if tname == sname:
                overwritten = 1
                target[i] = sgra
                break

        # If graphic was not overwritten, append it.
        if overwritten == 0:
            target.append(sgra)


def mergewad(target, source):
    """Joins graphics, levels, palettes etc from the source to target.
    Does not do a perfect join: sounds, texture definitions etc are
    ignored."""

    # Only display levels from the lastest wad file.
    if source.levels is not None:
        if config['mergelevels']:
            mergearray(target.levels, source.levels, True)
            target.levels.sort(wad.levelsorter)
        else:
            target.levels = source.levels

    if source.playpal is not None:
        target.playpal = source.playpal

    # Careful! Since this program does not save anything, no potential
    # lossage.
    #target.fname = os.path.basename(source.fname)

    mergearray(target.sprites, source.sprites)
    mergearray(target.flats, source.flats)

def loadlevelnamefile(fname):
    """Load level names from the specified file. The format of one line is:
    MAPNAME The name of the level"""
    ifile = file(fname)
    lnames = {}
    for line in ifile:
        line = line.strip()
        if len(line) == 0:
            continue
        arr = line.split(' ', 1)
        if len(arr) != 2:
            print 'Malformed level name line:', line
            sys.exit(1)
        lnames[arr[0]] = arr[1]
    config['levelnames'] = lnames


def parseparameters(params):
    global config
    files = []
    if len(params) == 0:
        return files
    i = -1
    landscape = False
    while i < len(params)-1:
        i += 1
        par = params[i]
        # Parameters start with a hyphen. Wad files don't. Period.
        if par[0] != '-':
            files.append(par)
            continue

        # Check for parameters.
        if par == '--landscape':
            landscape = True
            continue

        if par == '--papersize':
            i += 1
            psize = params[i].upper()
            if papersizedic.has_key(psize):
                config['papersize'] = papersizedic[psize]
                continue
            # A custom paper size in the form '100X100'.
            parr = psize.split('X')
            if len(parr) != 2:
                print 'Unparseable paper size', psize
                sys.exit(1)
            try:
                ps = (int(parr[0]), int(parr[1]))
            except ValueError:
                print 'Unparseable paper size', psize
                sys.exit(1)
            if ps[0] <= 0 or ps[1] <= 0:
                print 'Paper sizes must be bigger than zero.'
                sys.exit(1)
            config['papersize'] = ps
            continue
            
        if par == '-o':
            i += 1
            config['outfilename'] = params[i]
            continue

        if par == '--lighting':
            config['lighting'] = True
            continue

        if par =='--lightvalue':
            i+=1
            lval = float(params[i])
            if lval < 0.0 or lval > 1.0:
                raise Exception('Light value %.1f is not between one and zero.' % lval)
            config['lightvalue'] = lval
            continue
            

        # Only process the levels in the next parameter:
        # --levels MAP01,MAP02,MAP03
        if par == '--levels':
            i = i+1
            larr = params[i].split(',')
            ldic = {}
            for l in larr:
                ldic[l] = True
            config['levels'] = ldic
            continue

        if par == '--levelnamefile':
            i+=1
            loadlevelnamefile(params[i])
            continue

        if par == '--nocompression': # A 'secret' switch. Shh!
            config['compresslevels'] = False
            continue
        
        if par == '--mergelevels':
            config['mergelevels'] = True
            continue

        if par == '--noblockmap':
            config['useblockmap'] = False
            continue

        if par == '--nosubsectors':
            config['drawsubsectors'] = False
            continue

        if par == '--nothings':
            config['drawthinggraphics'] = False
            config['drawthingcrosses'] = False
            continue

        if par == '--thingcrosses':
            config['drawthinggraphics'] = False
            config['drawthingcrosses'] = True
            continue

        if par == '--title':
            i = i+1
            config['title'] = params[i]
            continue

        if par == '--author':
            i = i+1
            config['author'] = params[i]
            continue

        if par == '--creator':
            i = i+1
            config['creator'] = params[i]
            continue

        if par == '--keywords':
            i = i+1
            config['keywords'] = params[i]
            continue

        if par == '--subject':
            i = i+1
            config['subject'] = params[i]
            continue

        print 'Unknown parameter', par
        print 'Exiting'
        sys.exit(1)

    # Doing landscape? Then swap length and height.
    if landscape:
        temp = config['papersize']
        config['papersize'] = (temp[1], temp[0])
        
    return files

if __name__ == '__main__':
    starttime = time.time()
    print 'Wad2PDF v 1.7 (C) 2008 Jussi Pakkanen'
    print ''
    print 'Wad2PDF comes with ABSOLUTELY NO WARRANTY.'
    print 'This is free software, and you are welcome to redistribute it'
    print 'under the GPL. See included file LICENSE for further info.'
    print ''
    
    if len(sys.argv) == 1:
        print 'No parameters defined. Usage'
        print sys.argv[0], '<IWAD file> <optional wads> <additional switches>'
        sys.exit(1)
    createdefaultconfig()
    wfiles = parseparameters(sys.argv[1:])
    #print 'Loading WAD files.'

    w = wad.wad()
    firstwad = 1
    for fname in wfiles:
        print 'Loading', fname + '.'
        newwad = wad.wad()
        newwad.load(fname)
        if firstwad == 1:
            firstwad = 0
            if newwad.type != 'IWAD':
                print 'First argument', fname, 'is not an IWAD file. Exiting.'
                sys.exit(1)
        mergewad(w, newwad)

    filterlevels(w)
    if len(w.levels) == 0:
        print 'No levels to process. Check your \'--levels\' parameters.'
        sys.exit(1)
    
    #print '' # Empty line. Looks mighty fine.

    # Get the mappings between thing numbers and their sprites.
    iwadbase = os.path.basename(wfiles[0]).lower()
    try:
        spritemapper = thingdicmapper[iwadbase]
        title = gamemapper[iwadbase]
    except KeyError:
        print 'Your IWAD file', wfiles[0], 'is not supported.'
        sys.exit(1)

    # Then the level names.
    levelbase = os.path.basename(wfiles[-1]).lower()
    if config['levelnames'] is None:
        try:
            levelnames = levelnamemapper[levelbase]
        except KeyError:
            levelnames = {}
        config['levelnames'] = levelnames

    # Add some minor stuff to config.
    if not config.has_key('outfilename'):
        config['outfilename'] = wfiles[-1][:-3] + 'pdf'
    if not config.has_key('creator'):
        config['creator'] = 'Some Doom level editor'
    if not config.has_key('title'):
        try:
            config['title'] = gamemapper[levelbase]
        except KeyError:
            config['title'] = levelbase

    outfilename = config['outfilename']
    if outfilename[-4:].lower() != '.pdf':
        outfilename = outfilename + '.pdf'

    #print outfilename
    pdflogic.createpdf(w, outfilename, spritemapper)

    # Done, print out the total duration.
    duration = int(time.time() - starttime)
    if duration < 60:
        print '\nFinished in %d seconds.' % duration
    else:
        print '\nFinished in %d minutes, %d seconds.' % \
              (duration/60,
               duration%60)
        
