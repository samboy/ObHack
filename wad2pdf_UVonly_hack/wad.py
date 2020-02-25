# -*- coding: latin1 -*-

# Wad2PDF is a program that converts Doom levels into PDF files.
# (C) 2005-8 Jussi Pakkanen
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

import struct
from math import sqrt
import os

headerstruct = '<4sii'
indexstruct = '<ii8s'

patchheaderstruct = '<HHhh'
patchoffsetstruct = '<l'

# Line noise magic.
doomthingstruct = '<hhhhh'
hexenthingstruct = '<6hHb5B'
doomlinedefstruct = '<4H3h'
hexenlinedefstruct = '<3H6B2h'
sidedefstruct = '<hh8s8s8sh'
vertexstruct = '<hh'
segstruct = '<6h'
ssectorstruct = '<HH'
nodestruct = '<14h'
sectorstruct = '<hh8s8shhh'
blockmapheaderstruct = '<hhHH'
texturestruct = '<8sHHHHHHH'
patchdescstruct = '<hhhhh'

# We only support level 5 GL nodes.
glvertstruct = '<hhhh'
glsegstruct = '<IIHHI'
glssectorstruct = '<II'
glnodestruct = nodestruct # The only identical element.
glmagicid = 'gNd5'

from thingdics import extragraphics

class lump:
    def __init__(self):
        self.data = ''
        self.name = ''

    def load(self, ifile, size, name):
        """Read lump from the file at the specified location."""
        self.data = ifile.read(size)
        self.name = name
        if len(self.data) != size:
            raise IOError('Lump size mismatch.')

    def save(self, ofile):
        """Write lump to a wad file. Returns a index tuple."""
        offset = ofile.tell()
        ofile.write(self.data)        
        return (offset, len(self.data), self.name)

    def writetofile(self, ofilename=None):
        """Writes the raw data out to an external file."""
        if ofilename is None:
            ofilename = self.name + '.lmp'
        ofile = file(ofilename, 'w')
        ofile.write(self.data)
        ofile.close()

    def readfromfile(self, ifilename):
        """Load contents of the given file to this lump."""
        ifile = file(ifilename, 'r')
        self.data = ifile.read()
        ifile.close()
              
class wad:
    def __init__(self):
        self.lumps = []
        self.type = 'PWAD'
        self.fname = ''
        self.music = []
        self.sfx = []
        self.patches = []
        self.sprites = []
        self.flats = []
        self.playpal = None
        self.levels = []
        self.extragraphics = []
        self.texture1 = None
        self.texture2 = None
        self.pnames = None

    def printlumplist(self, llist):
        for l in llist:
            print l.name

    def load(self, fname):
        """Load a WAD file from disk."""
        # Start with the header.
        global headerstruct
        ifile = file(fname, 'rb')
        he = ifile.read(struct.calcsize(headerstruct))
        (wtype, numlumps, ioffset) = struct.unpack(headerstruct, he)
        if wtype != 'IWAD' and wtype != 'PWAD':
            raise IOError('Not a wad file')
        self.type = wtype
        self.fname = fname

        # Then read the index.
        ifile.seek(ioffset)
        index = []
        for i in range(numlumps):
            idata = ifile.read(struct.calcsize(indexstruct))
            (loffset, lsize, lname) = struct.unpack(indexstruct, idata)
            lname = lname.split('\0')[0] # Makes string comparison work.
            ltuple = (loffset, lsize, lname)
            index.append(ltuple)

        #printindex(index)

        # Then read the lumps using the index.
        i = 0
        while i < len(index):
            ltuple = index[i]
            (loffset, lsize, lname) = ltuple
            ifile.seek(loffset)
            newlump = lump()
            newlump.load(ifile, lsize, lname)

            # If next index item is THINGS, we have a new level.
            if i < len(index)-1 and index[i+1][2] == 'THINGS':
                newlevel = level()
                i = newlevel.load(ifile, index, i)
                self.levels.append(newlevel)
                continue

            # Place the lump in an appropriate place.
            if lname[0:2] == 'D_': # Music
                self.music.append(newlump)
            elif lname[0:2] == 'DP' or \
                 lname[0:2] == 'DS': # Sound effects.
                self.sfx.append(newlump)
            elif lname == 'F_START' or \
                 lname == 'FF_START': # Flats
                i = self.loadseries(ifile, index, i, 'F_END', \
                                    'FF_END', self.flats)
            elif lname == 'P_START' or \
                 lname == 'PP_START': # Patches
                i = self.loadseries(ifile, index, i, 'P_END', 'PP_END',\
                                    self.patches)
            elif lname == 'S_START' or \
                 lname == 'SS_START': # Patches
                i = self.loadseries(ifile, index, i, 'S_END', 'SS_END',\
                                    self.sprites)
            elif lname == 'PLAYPAL':
                ppal = playpal()
                ppal.fromlump(newlump)
                self.playpal = ppal

            elif lname == 'TEXTURE1':
                tex1 = texture()
                tex1.fromlump(newlump)
                self.texture1 = tex1

            elif lname == 'TEXTURE2':
                tex2 = texture()
                tex2.fromlump(newlump)
                self.texture2 = tex2

            elif lname == 'PNAMES':
                pn = pnames()
                pn.fromlump(newlump)
                self.pnames = pn
                
            elif extragraphics.has_key(lname):
                self.extragraphics.append(newlump)
            else:
                self.lumps.append(newlump)
            i = i+1

        # The WAD is fully loaded. 
        ifile.close()

        # At this point patches etc are still lump objects. Convert
        # them to their native types
        for i in range(len(self.flats)):
            newflat = flat()
            newflat.fromlump(self.flats[i])
            self.flats[i] = newflat

        for i in range(len(self.patches)):
            newpatch = patch()
            newpatch.fromlump(self.patches[i])
            self.patches[i] = newpatch

        for i in range(len(self.sprites)):
            newsprite = patch()
            newsprite.fromlump(self.sprites[i])
            self.sprites[i] = newsprite

        for i in range(len(self.extragraphics)):
            newgraph = patch()
            newgraph.fromlump(self.extragraphics[i])
            self.extragraphics[i] = newgraph

        # Sort the levels according to their name.
        self.levels.sort(levelsorter)
        
        # Load external GL nodes.
        self.importgwa(fname)

    def importgwa(self, fname):
        """Loads GL nodes from an external GWA file, if it is newer
        than the current wad."""

        # Avoid recursive calls.
        if fname[-3:].lower() == 'gwa':
            return

        gwaname_lower = fname[:-3] + 'gwa'
        gwaname_upper = fname[:-3] + 'GWA'

        gwafile = wad()
        try:
            gwafile.load(gwaname_lower)
            gwaname = gwaname_lower
        except IOError:
            try:
                gwafile.load(gwaname_upper)
                gwaname = gwaname_upper
            except IOError:
                print 'No corresponding GWA file.'
                return

        fdate = os.stat(fname)[-2]
        gdate = os.stat(gwaname)[-2]

        # If GWA file is older, it is considered to be obsolete.
        if gdate < fdate:
            print 'Obsolete GWA data.'
            return

        # At this point we have a GWA file that has newer GL Node data
        # than the wad itself. Import it.
        for level in self.levels:
            glmark = 'GL_' + level.header.name

            # GWA files contain only plain lumps.
            i = 0
            while i < len(gwafile.lumps):
                lump = gwafile.lumps[i]
                if lump.name == glmark:
                    level.glheader = lump
                    i = i+1
                    level.glvert = gwafile.lumps[i]
                    i = i+1
                    level.glsegs = gwafile.lumps[i]
                    i = i+1
                    level.glssect = gwafile.lumps[i]
                    i = i+1
                    level.glnodes = gwafile.lumps[i]
                    i = i+1
                    level.glpvs = gwafile.lumps[i]
                    if gwafile.lumps[i].name != 'GL_PVS':
                        raise Exception('Malformed GL nodes in GWA file.')
                    break # This level is done
                i = i + 1
                


    def loadseries(self, ifile, index, i, stop1, stop2, array):
        """Read a sequence of lumps (patches, flats etc)."""
        i = i+1
        while i < len(index) and index[i][2] != stop1 and \
                  index[i][2] != stop2:
            ltuple = index[i]
            (loffset, lsize, lname) = ltuple
            #print i, lname
            if lsize == 0: # Skip weird markers.
                i = i+1
                continue
            ifile.seek(loffset)
            newlump = lump()
            newlump.load(ifile, lsize, lname)
            array.append(newlump)
            i = i+1
        return i

    def save(self, ofname=None):
        """Writes the data to the given file."""

        if ofname is not None:
            self.fname = ofname

        # First create a backup if necessary.
        try: # Why the hell is there not a standard file copy function?
            ifile = file(self.fname, 'r')
            data = ifile.read()
            ifile.close()
            bfname = self.fname + '~'
            ofile = file(bfname, 'w')
            ofile.write(data)
            ofile.close()
        except IOError:
            pass

        ofile = file(self.fname, 'w')
        # A fake header.
        ofile.write(struct.pack(headerstruct, 'TUNK', 0, 0))
        index = []

        # Start up with levels.
        for level in self.levels:
            index = index + level.save(ofile)
        
        # Write all basic lumps.
        for l in self.music:
            index.append(l.save(ofile))
        for l in self.sfx:
            index.append(l.save(ofile))
        for l in self.lumps:
            index.append(l.save(ofile))
        for l in self.extragraphics:
            index.append(l.save(ofile))

        # Patches etc.
        self.saveseries(ofile, index, 'P_START', 'P_END', self.patches)
        self.saveseries(ofile, index, 'S_START', 'S_END', self.sprites)
        self.saveseries(ofile, index, 'F_START', 'F_END', self.flats)

        if self.playpal is not None:
            index.append(self.playpal.save(ofile))
        if self.texture1 is not None:
            index.append(self.texture1.save(ofile))
        if self.texture2 is not None:
            index.append(self.texture2.save(ofile))
        if self.pnames is not None:
            index.append(self.pnames.save(ofile))

        # Then save the index.
        ioffset = ofile.tell()
        numlumps = len(index)
        for ind in index:
            ofile.write(struct.pack(indexstruct, ind[0], ind[1], ind[2]))

        # Write a proper header.
        ofile.seek(0)
        ofile.write(struct.pack(headerstruct, self.type, numlumps, ioffset))
        ofile.close()
                      
    def saveseries(self, ofile, index, starter, ender, array):
        """Save a bunch with array markers."""
        s = lump()
        s.name = starter
        index.append(s.save(ofile))
        for l in array:
            index.append(l.save(ofile))
        s.name = ender
        index.append(s.save(ofile))

class patch(lump):
    """A basic Doom graphic element."""
    def __init__(self):
        lump.__init__(self)
        self.width = 0
        self.height = 0
        self.loffset = 0
        self.toffset = 0
        self.offsets = []
        self.columnformat = True # False for flat data files. (Heretic)

    def load(self, ifile, size, name):
        lump.load(self, ifile, size, name)
        self.unpack()

    def fromlump(self, lump):
        self.name = lump.name
        self.data = lump.data
        self.unpack()

    def unpack(self):
        if len(self.data) == 320*200:
            # Heretic and Hexen have graphics that are NOT in the Doom
            # patch format. There is no reliable way of determining
            # what those are. Thank you Raven software, thank you so
            # much.
            self.width = 320
            self.height = 200
            self.columnformat = False
        else:
            self.unpackcolumn()
            self.columnformat = True
            

    def unpackcolumn(self):
        """Reveals structure in the binary mess. On some Heretic/Hexen
        graphics may throw a struct.error"""
        hsize = struct.calcsize(patchheaderstruct)
        (self.width, self.height, self.loffset, self.toffset) = \
                     struct.unpack(patchheaderstruct,\
                                   self.data[:hsize])
        self.offsets = []
        osize = struct.calcsize(patchoffsetstruct)
        for i in range(self.width):
            off = struct.unpack(patchoffsetstruct,\
                                self.data[hsize+i*osize:hsize+(i+1)*osize])[0]
            self.offsets.append(off)
        
    def getgraphic(self, transparentcolor=247):
        if self.columnformat: # Regular graphics?
            return self.getcolumngraphic(transparentcolor)

        # Expand the graphics. Abuse the flat class, since it knows
        # how to expand flat graphics files.
        expander = flat()
        expander.width = self.width
        expander.height = self.height
        expander.data = self.data
        return expander.getgraphic()

    def getcolumngraphic(self, transparentcolor):
        """Returns an array of arrays containing the indexed image."""
        result = []
        for i in range(self.height):
            row = [transparentcolor]*self.width
            result.append(row)

        # Iterate over every column
        for i in range(self.width):
            base = self.offsets[i]
            inc = 0
            while (struct.unpack('<B', self.data[base+inc])[0]) != 0xFF:
                j = struct.unpack('<B', self.data[base+inc])[0]
                inc = inc + 1
                count = struct.unpack('<B', self.data[base+inc])[0]
                inc = inc + 2 # Skip the garbage pixel.
                for c in range(count):
                    result[j][i] = struct.unpack('<B', self.data[base+inc])[0]
                    j = j+1
                    inc = inc+1
                inc = inc+1 # Skip other garbage pixel.
        return result
                    
class flat(lump):
    """A square floor graphic."""
    def __init__(self):
        lump.__init__(self)
        self.width = 0
        self.height = 0

    def load(self, ifile, size, name):
        lump.load(self, ifile, size, name)
        self.unpack()

    def fromlump(self, lump):
        """Take data from another lump and unpack it."""
        self.name = lump.name
        self.data = lump.data
        self.unpack()

    def unpack(self):
        """Sanity checks and unpacking."""
        # Heretic has a few 64*65 flats.
        if len(self.data) == 64*65:
            self.width = 64
            self.height = 65
            return
        # Hexen has flats sized 8192.
        if len(self.data) == 8192:
            self.width = 128
            self.height = 64
            return
        w = sqrt(len(self.data))
        w = int(w)
        if w*w != len(self.data):
            raise Exception('Flat %s is not square (%d bytes).' % (self.name, len(self.data)))
        self.width = w
        self.height = w

    def getgraphic(self):
        """Returns an array of arrays containing the indexed image."""
        result = []
        for j in range(self.height):
            row = []
            result.append(row)
            for i in range(self.width):
                ind = j*self.width + i
                val = struct.unpack('<B', self.data[ind])[0]
                row.append(val)
        return result

class playpal(lump):
    """A palette for all graphics."""
    def __init__(self):
        lump.__init__(self)

    def fromlump(self, lump):
        """Take data from another lump and unpack it."""
        self.name = lump.name
        self.data = lump.data
        self.unpack()
        
    def load(self, ifile, size, name):
        """Loads and unpacks the palette info including alpha."""
        lump.load(self, ifile, size, name)
        self.unpack()

    def unpack(self):
        """Transforms the binary data to editable form."""
        palsize = 256*3
        numpals = len(self.data) / palsize
        alphaind = 247 # This value is the same in every game
        if len(self.data) != numpals*palsize: # 
            raise Exception('Incorrect palette size %d.' % len(self.data))
        self.palettes = []
        for p in range(numpals):
            base = p*palsize
            cpal = []
            self.palettes.append(cpal)
            for i in range(256):
                ind = base + i*3
                (r, g, b) = struct.unpack('<BBB', self.data[ind:ind+3])
                if i == alphaind:
                    a = 0
                else:
                    a = 255
                tp = (r, g, b, a)
                cpal.append(tp)

class pnames(lump):
    def __init__(self):
        lump.__init__(self)

    def fromlump(self, lump):
        self.name = lump.name
        self.data = lump.data
        self.unpack()

    def unpack(self):
        pcount = struct.unpack('<l', self.data[0:4])[0]
        self.names = []
        for i in range(pcount):
            sta = 4 + i*8
            end = sta + 8
            name = struct.unpack('<8s', self.data[sta:end])[0]
            name = name.split('\0')[0]
            self.names.append(name.upper()) # UDS says these are case-insens.


class texture(lump):
    """Holds texture build info."""
    def __init__(self):
        lump.__init__(self)

    def fromlump(self, lump):
        """Take data from another lump and unpack it."""
        self.name = lump.name
        self.data = lump.data
        self.unpack()
        
    def unpack(self):
        numtextures = struct.unpack('<L', self.data[0:4])[0]
        texoffsets = []
        for i in range(numtextures):
            offset = struct.unpack('<L', self.data[(i+1)*4:(i+2)*4])[0]
            texoffsets.append(offset)

        self.definitions = []
        for offset in texoffsets:
            postart = offset+struct.calcsize(texturestruct)
            curdef = struct.unpack(texturestruct, \
                                   self.data[offset:postart])
            pdescs = []
            for i in range(curdef[-1]):
                sta = postart + i*struct.calcsize(patchdescstruct)
                end = sta + struct.calcsize(patchdescstruct)
                pdescs.append(struct.unpack(patchdescstruct,\
                                            self.data[sta:end]))
            curdef = list(curdef)
            curdef[0] = curdef[0].split('\0')[0]
            curdef[-1] = pdescs
            curdef = tuple(curdef)
            self.definitions.append(curdef)
                
            
            

class level:
    def __init__(self):
        self.header = None # This holds Fragglescript etc
        self.things = None
        self.linedefs = None
        self.sidedefs = None
        self.vertexes = None
        self.segs = None
        self.ssectors = None
        self.nodes = None
        self.sectors = None
        self.reject = None
        self.blockmap = None
        self.behavior = None

        # GL nodes, if the first one is None, these will not be
        # written to disk.
        self.glheader = None
        self.glvert = None
        self.glsegs = None
        self.glssect = None
        self.glnodes = None
        self.glpvs = None

    def load(self, ifile, index, i):
        """Loads a level at the current location.
        Returns the index number of the first item _not_
        belonging to this level."""
        (hoffset, hsize, hname) = index[i]
        newlump = lump()
        ifile.seek(hoffset)
        newlump.load(ifile, hsize, hname)
        self.header = newlump

        while i < len(index)-1:
            i = i+1
            (hoffset, hsize, hname) = index[i]
            ifile.seek(hoffset)
            newlump = lump()
            newlump.load(ifile, hsize, hname)
            if hname == 'THINGS':
                self.things = newlump
            elif hname == 'LINEDEFS':
                self.linedefs = newlump
            elif hname == 'SIDEDEFS':
                self.sidedefs = newlump
            elif hname == 'VERTEXES':
                self.vertexes = newlump
            elif hname == 'SEGS':
                self.segs = newlump
            elif hname == 'SSECTORS':
                self.ssectors = newlump
            elif hname == 'NODES':
                self.nodes = newlump
            elif hname == 'SECTORS':
                self.sectors = newlump
            elif hname == 'REJECT':
                self.reject = newlump
            elif hname == 'BLOCKMAP':
                self.blockmap = newlump
            elif hname == 'BEHAVIOR':
                self.behavior = newlump
            elif hname == 'GL_' + self.header.name:
                self.glheader = newlump
            elif hname == 'GL_VERT':
                self.glvert = newlump
            elif hname == 'GL_SEGS':
                self.glsegs = newlump
            elif hname == 'GL_SSECT':
                self.ssect = newlump
            elif hname == 'GL_NODES':
                self.glnodes = newlump
            elif hname == 'GL_PVS':
                self.glpvs = newlump
            else: # Reached the end. Return new index.
                return i
        return i

    def save(self, ofile):
        """Saves level to file. Returns an index array."""
        if self.header.name == '':
            return [] # Don't save empty levels.

        index = []
        index.append(self.header.save(ofile))
        index.append(self.things.save(ofile))
        index.append(self.linedefs.save(ofile))
        index.append(self.sidedefs.save(ofile))
        index.append(self.vertexes.save(ofile))
        index.append(self.segs.save(ofile))
        index.append(self.ssectors.save(ofile))
        index.append(self.nodes.save(ofile))
        index.append(self.sectors.save(ofile))
        index.append(self.reject.save(ofile))
        index.append(self.blockmap.save(ofile))

        if self.behavior is not None:
            index.append(self.behavior.save(ofile))

        if self.glvert is not None:
            index.append(self.glheader.save(ofile))
            index.append(self.glvert.save(ofile))
            index.append(self.glsegs.save(ofile))
            index.append(self.glssect.save(ofile))
            index.append(self.glnodes.save(ofile))
            index.append(self.glpvs.save(ofile))

        return index

    def expand(self, data, expander):
        """Unpacks an array of identical elements (like things etc).
        Accepts a lump or a string of data."""
        es = struct.calcsize(expander)
        result = []
        for i in range(len(data)/es):
            bb = struct.unpack(expander, data[i*es:(i+1)*es])
            result.append(bb)
        if len(data) != len(result)*es:
            raise Exception('Data size mismatch when unpacking.')
        return result

    def getvertices(self):
        global glmagicid
        midsize = len(glmagicid)
        if self.glvert.data[0:midsize] != glmagicid: # Version 5 nodes?
            print 'baz', self.glvert.data[0:midsize]
            raise Exception('GL segs not in 5.0 format. %s' %
                            self.header.name)
        return self.expand(self.vertexes.data, vertexstruct)
        

    def getlinedefs(self):
        if self.behavior is None:
            return self.expand(self.linedefs.data, doomlinedefstruct)
        return self.expand(self.linedefs.data, hexenlinedefstruct)

    def getthings(self):
        if self.behavior is None:
            return self.expand(self.things.data, doomthingstruct)
        return self.expand(self.things.data, hexenthingstruct)

    def getsegs(self):
        return self.expand(self.segs.data, segstruct)

    def getsectors(self):
        secs = self.expand(self.sectors.data, sectorstruct)
        result = []
        for s in secs:
            s = list(s)
            s[2] = s[2].split('\0')[0]
            s[3] = s[3].split('\0')[0]
            s = tuple(s)
            result.append(s)
        return result

    def getsidedefs(self):
        return self.expand(self.sidedefs.data, sidedefstruct)

    def getsubsectors(self):
        return self.expand(self.ssectors.data, ssectorstruct)

    def getglvertices(self):
        global glmagicid
        if self.glvert is None:
            raise Exception('Nonexistant GL vertices requested.')
        return self.expand(self.glvert.data[len(glmagicid):], glvertstruct)

    def getglsegs(self):
        if self.glsegs is None:
            raise Exception('Nonexistant GL segs requested.')
        return self.expand(self.glsegs.data, glsegstruct)

    def getglsubsectors(self):
        if self.glssect is None:
            raise Exception('Nonexistan GL subsectors requested.')
        return self.expand(self.glssect.data, glssectorstruct)


    def getblockmap(self):
        """Returns tuple ((xcoord, ycoord), [block lists]). Block list
        is an array of arrays. The first index is y, the second is x."""
        
        if self.blockmap is None:
            raise Exception('No blockmap in level %s.' % self.header.name)

        blockstart = '\x00\x00' # A list starts with zeros.
        blockend = '\xff\xff'   # 0xFFFF ends the block list.
        data = self.blockmap.data
        # Does blockmap exist?
        if len(data) == 0:
            return [[0, 0], [[]]]

        headersize = struct.calcsize(blockmapheaderstruct)
        header = data[0:headersize]
        (xcoord, ycoord, numcols, numrows) = \
                 struct.unpack(blockmapheaderstruct, header)
        #print 'cols', numcols, 'rows', numrows

        # Read block offsets.
        offsets = []
        for i in range(numcols*numrows):
            slicestart = headersize + i*2
            sliceend = slicestart+2
            coff = struct.unpack('<H', data[slicestart:sliceend])[0]
            coff *= 2 # Offsets are in shorts, not bytes.
            offsets.append(coff)

        # Now read in the blocks.
        blocks = []
        for y in range(numrows):
            currow = []
            blocks.append(currow)
            for x in range(numcols):
                curcol = [] # This holds the block list.
                currow.append(curcol)
                coff = offsets[y*numcols + x]

                # Consistency check.
                if data[coff:coff+2] != blockstart:
                    raise Exception('Blockmap is corrupted.')
                coff = coff+2
                while data[coff:coff+2] != blockend:
                    ldnum = struct.unpack('<H', data[coff:coff+2])[0]
                    curcol.append(ldnum)
                    coff += 2
                #print len(curcol)
        
        result = ((xcoord, ycoord), blocks)
        return result

def levelsorter(l1, l2):
    """Compares level names and returns -1, 0 or 1."""
    if l1.header.name == l2.header.name:
        return 0

    if l1.header.name < l2.header.name:
        return -1

    return 1
        
        
def printindex(index):
    ofile = file('d2ind.txt', 'w')        
    for ind in index:
        ofile.write(ind[2] + ' ' + str(ind[1]) + '\n')

def indexed2rgba(data, palette):
    """Converts an array of arrays indexed image buffer to an RGBA string."""

    # Sanity checks.
    height = len(data)
    width = len(data[0])

    for row in data:
        if len(row) != width:
            raise Exception('Image rows have different lengths.')

    image = []
    for row in data:
        for i in row:
            pal = palette[i]
            image.append(struct.pack('<BBBB', pal[0], pal[1], pal[2], pal[3]))
    image = ''.join(image)
    return (width, height, image)

def buildpatchdict(wadlist):
    """Builds a dictionary that maps a wall patch number (from TEXTURE1)
    to the corresponding patch graphic. The parameter is a sequence of wad
    files starting from the IWAD."""
    patchdict = {}
    pnamelump = None

    # Find the most recent PNAMES.
    for w in wadlist:
        if w.pnames is not None:
            pnamelump = w.pnames

    if pnames is None:
        raise Exception('No PNAMES lump found. Can not process textures.')


    # This is not very efficient, but it is only run once and takes <1
    # second.
    ind = -1
    for name in pnamelump.names:
        ind += 1
        curpatch = None
        for w in wadlist:
            for p in w.patches:
                if p.name == name:
                    curpatch = p
        if curpatch is None:
            raise Exception('Missing patch %s in PNAMES.' % name)


        patchdict[ind] = curpatch
                

    return patchdict

def buildtexture(texdef, patchdict, transpindex = 247):
    result = []
    for y in range(texdef[4]):
        result += [[0]*texdef[3]]

    for patchdef in texdef[-1]:
        xoff = patchdef[0]
        yoff = patchdef[1]
        pat = patchdict[patchdef[2]] # No caching -> sloooow.
        graphic = pat.getgraphic()
        pw = len(graphic[0])
        ph = len(graphic)
        for x in range(pw):
            for y in range(ph):
                pixel = graphic[y][x]
                if pixel == transpindex:
                    continue
                try:
                    result[y+yoff][x+xoff] = pixel
                except IndexError:
                    pass
    return result
