#!/usr/bin/python

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

from wad import *
from thingdics import *
import time, math, zlib, sys

pdf13header = "%PDF-1.3\n"
pdf14header = "%PDF-1.4\n"

objects = []

config = {}

catalog = """1 0 obj
  << /Type /Catalog
     /Pages %d 0 R
     /Outlines 2 0 R
  >>
endobj
"""

outlines = """2 0 obj
  << /Type /Outlines
     /First %d 0 R
     /Last  %d 0 R
     /Count %d
  >>
endobj
"""

# resource_templ = """
# 3 0 obj
#   << /ProcSet [/PDF /ImageC /ImageB]
#      /XObject << %s    >>
#      /Pattern << %s    >>
#   >>
# endobj
# """

patternresource_templ = """3 0 obj
  << /ProcSet [/PDF /ImageC]
     /XObject << %s    >>
  >>
endobj
"""

levelresource_templ = """%d 0 obj
  << /ProcSet [/PDF /ImageC /ImageB]
     /XObject << %s    >>
     /Pattern << %s    >>
     /ExtGState %s
  >>
endobj
"""

outline_templ = """%d 0 obj
  << /Title (%s)
     /Parent 2 0 R
%s     /Dest [%d 0 R /XYZ null null null]
  >>
endobj
"""

# Image prototype
spriteobj_templ = """%d 0 obj
<< /Type /XObject
   /Subtype /Image
   /Mask %d 0 R
   /Width %d
   /Height %d
   /ColorSpace /DeviceRGB
   /BitsPerComponent 8
   /Length %d
   /Filter /FlateDecode
   >>
stream
%s
endstream
endobj
"""

maskobj_templ = """%d 0 obj
<< /Type /XObject
   /Subtype /Image
   /ImageMask true
   /Width %d
   /Height %d
   /BitsPerComponent 1
   /Length %d
   /Filter /FlateDecode
   >>
stream
%s
endstream
endobj
"""

flatobj_templ = """%d 0 obj
<< /Type /XObject
   /Subtype /Image
   /Width %d
   /Height %d
   /ColorSpace /DeviceRGB
   /BitsPerComponent 8
   /Length %d
   /Filter /FlateDecode
   >>
stream
%s
endstream
endobj
"""

pattobj_templ = """%d 0 obj
  << /Type /Pattern
     /PatternType 1 %% Tiling pattern
     /PaintType 1 %% Colored
     /TilingType 1
     /BBox [0 0 %d %d]
     /XStep %d
     /YStep %d
     /Resources 3 0 R
     /Length %d
     /Matrix [%f 0 0 %f %f %f]
  >>
stream
%sendstream
endobj
"""


patternobj_templ = """%d 0 obj
  << /Type /Pattern
     /PatternType 1 %% Tiling pattern
     /PaintType 1 %% Colored
     /TilingType 1
     /BBox [0 0 %d %d]
     /XStep %d
     /YStep %d
     /Resources 3 0 R
     /Length %d
  >>
stream
%sendstream
endobj
"""

transp_templ = """%d 0 obj
  << /Type /ExtGState
     /ca %f
  >>
endobj
"""

transp_dict_templ = """%d 0 obj
  << %s >>
endobj
"""

patterndraw_templ = """  %d 0 0 %d 0 0 cm
  /FLAT_%s Do
"""

resitem_templ = "/%s %d 0 R \n"

trailer_templ = """trailer
  << /Size %d
     /Root 1 0 R
     /Info %d 0 R
  >>
"""

infobj_templ = """%d 0 obj
  << /Title (%s)
     %s
     /Producer (Wad2PDF)
     /CreationDate (%s)
  >>
endobj
"""

ender = "%%EOF\n"


# This string contains links to sprite graphics. It is initialized in
# function createsprites and used in createpatdata. It is global only
# for convenience.

spriterestext = ''

# Index to the resource of the first level. The others follow after it.
firstlevelres = 0

# This object contains a resource subdictionary for the transparency
# settings.

transp_dictref = '<< >>' # By default do nothing.

def create_transdict(offset):
    """Create graphics state dictionaries for transparent drawing,
    which is used to fake sector lighting."""
    global config, transp_dictref

    # Do we need to do anything at all?
    if not config['drawsubsectors'] or \
       not config['lighting']:
        return []

    # Doom has 32 distinct light levels, create corresponding
    # transparency masks.
    lightlevels = 31
    result = []
    dlist = []
    for i in range(lightlevels+1):
        clevel = float(i)/lightlevels
        clobj = transp_templ % (offset+i, clevel)
        result.append(clobj)
        dentry = '  /LIGHT_LEVEL_%d %d 0 R\n' % (i, offset+i)
        dlist.append(dentry)

    sdnum = offset+lightlevels+1
    transp_dictref = "%d 0 R\n" % sdnum
    trdict = transp_dict_templ % (sdnum, ''.join(dlist))
    result.append(trdict)
    return result
        
        

def drawlevellines(vertices, linedefs):
    """Converts linedefs to PDF drawing commands."""
    cmnds = []
    for ld in linedefs:
        fv = vertices[ld[0]]
        tv = vertices[ld[1]]
        cmnds.append('  %d %d m\n' % fv)
        cmnds.append('  %d %d l\n  s\n' % tv)
    return ''.join(cmnds)

def minmax(arr):
    #print len(arr)
    maxx = minx = arr[0][0]
    maxy = miny = arr[0][1]
    #print minx, maxx, miny, maxy
    for el in arr:
        if el[0] > maxx:
            maxx = el[0]
        if el[0] < minx:
            minx = el[0]
        if el[1] > maxy:
            maxy = el[1]
        if el[1] < miny:
            miny = el[1]
    bob = (minx, maxx, miny, maxy)
    return map(float, bob)

def createpageobjects(pagelistobjnum, numpages, pagewidth, pageheight, contentoffset):
    """Create a page element for each level."""
    global firstlevelres
    pltemplate = '%d 0 obj\n  << /Type /Pages\n  /Kids [%s]\n /Count %d \n >>\nendobj\n'
    pagetemplate = '%d 0 obj\n << /Type /Page\n /Parent %d 0 R\n /MediaBox [0 0 %d %d]\n /Contents %d 0 R\n /Resources %d 0 R\n  >>\nendobj\n'

    kids = ''
    for i in range(numpages):
        kids = kids + '%d 0 R\n' % (pagelistobjnum + i + 1)
    plist = pltemplate % (pagelistobjnum, kids, numpages)

    pageobjects = [plist]
    for i in range(numpages):
        page = pagetemplate % ((pagelistobjnum + i + 1), pagelistobjnum, \
                               pagewidth, pageheight, \
                               contentoffset + i,
                               firstlevelres + i)
        pageobjects.append(page)
    return pageobjects

def gettranslation(verts, pagewidth, pageheight):
    """Returns parameters that scale Doom coordinates to PDF properly."""
    # Find out proper scaling term.
    (minx, maxx, miny, maxy) = minmax(verts)
    xspan = maxx - minx
    yspan = maxy - miny
    xcenter = minx + xspan/2
    ycenter = miny + yspan/2
    if pageheight/yspan < pagewidth/xspan:
        scaling = pageheight/yspan
    else:
        scaling = pagewidth/xspan
    scaling = 0.9*scaling
    dx = -minx + (pagewidth/scaling-xspan)/2
    dy = -miny + (pageheight/scaling-yspan)/2
    return ((minx, maxx, miny, maxy), dx, dy, scaling)
    
    #s1 = '  1 0 0 1 %d %d cm\n' % (-minx + (pagewidth/scaling-xspan)/2,
    #                               -miny + (pageheight/scaling-yspan)/2)
    #        s1 = '  1 0 0 1 %d %d cm\n' % (-minx, -miny)
    #s2 = '  %f 0 0 %f 0 0 cm\n' % (scaling, scaling)
    #oscale = '  q\n' + s2 + s1
    #return oscale

def createpatdata(wadfile, dx, dy, scaling, resobj, pattobj, resoffset,
                  pattoffset):
    global spriterestext, transp_dictref
    curres = resoffset + len(resobj)
    curpatt = pattoffset + len(pattobj)
    reslist = []

    for flat in wadfile.flats:
        w = flat.width
        h = flat.height

        pdraw = patterndraw_templ % (w, h, flat.name)
        pobj = pattobj_templ % (curpatt, w, h, w, h, len(pdraw),
                                scaling, scaling, scaling*dx,
                                scaling*dy, pdraw)
        pattobj.append(pobj)
        cres = resitem_templ % (flat.name, curpatt)
        reslist.append(cres)
        
        curpatt += 1
        
    res = levelresource_templ % (curres, spriterestext, ''.join(reslist),
                                 transp_dictref)
    resobj.append(res)

def createdrawobjects(wadfile, pagewidth, pageheight, objoffset, thingdict):
    global firstlevelres
    lineobjs = [] # Every level has one of these.
    resobjs = []  # Also one of these.
    pattobjs = []  # Every level has #(flats) amount of these.
    timeoffset = config['textoffset']
    resoffset = objoffset + len(wadfile.levels)
    pattoffset = resoffset + len(wadfile.levels)

    firstlevelres = resoffset
    
    i = -1

    for level in wadfile.levels:
        i = i+1
        starttime = time.time()
        processtext = 'Processing level ' + level.header.name + '.'
        processtext += ' '*(timeoffset - len(processtext))
        print processtext,
        sys.stdout.flush() # Otherwise the previous line won't show.
        verts = level.getvertices()
        lds = level.getlinedefs()
        things = level.getthings()
        segs = level.getsegs()
        ssectors = level.getsubsectors()
        
        (limits, dx, dy, scaling) = gettranslation(verts, pagewidth,
                                                   pageheight)
        s1 = '  1 0 0 1 %d %d cm\n' % (dx, dy)
        s2 = '  %f 0 0 %f 0 0 cm\n' % (scaling, scaling)
        oscale = '  q\n' + s2 + s1

        # Create scaled and translated patterns and resource objects
        # for them. We have to do this separately for every single
        # level, because PDF does not allow altering the texture
        # matrices during draw commands. Thanks a f*cking lot, Adobe!
        
        createpatdata(wadfile, dx, dy, scaling, resobjs, pattobjs,
                      resoffset, pattoffset)

        # Every subelement must be self-contained (meaning PDF graphic
        # state changes must not leak outside the command block.

        # Linedefs can be drawn with a single transformation matrix.
        olines = oscale + drawlevellines(verts, lds) + '  Q\n'
        #olines = ''

        # Things require individual transformations.
        if config['drawthinggraphics']:
            othings = drawlevelsprites(things, thingdict, limits, dx, dy,
                                       scaling, pagewidth, pageheight)
        else:
            othings = ''
            
        if config['drawthingcrosses']:
            othings = othings + drawthingcrosses(things, dx, dy, scaling)

        # Finally draw and fill the subsectors.
        if config['drawsubsectors']:
            ossecs = drawsubsectors(level)
        else:
            ossecs = ''

        ossecs = oscale + ossecs + '  Q\n'
        drawstream = ossecs + olines + othings
        if config['compresslevels']:
            drawstream = zlib.compress(drawstream, 9)
            dcmnd = '/Filter /FlateDecode'
        else:
            dcmnd = ''
        ostart = '\n%d 0 obj %% %s\n  << /Length %d %s >>\nstream\n' % \
                 (objoffset + i, level.header.name, len(drawstream),\
                  dcmnd)
        oend = '\nendstream\nendobj\n'
        drawing = ostart + drawstream + oend
        #drawing = ostart + ossecs + olines + othings + oend
        lineobjs.append(drawing)

        # Print out how long it took.
        endtime = time.time()
        dur = int(endtime-starttime)
        if dur < 60:
            if dur == 0:
                durtxt = '>1 s'
            else:
                durtxt =  '%2d s' % dur
        else:
            durtxt = '%2d m %2d s' % (dur/60, dur%60)

        print durtxt.rjust(9)
        

    return lineobjs + resobjs + pattobjs

def drawthingcrosses(things, dx, dy, scaling):
    if len(things[0]) == 5: # Doom
        xind = 0
        yind = 1
    else:                   # Hexen
        xind = 1
        yind = 2
    s1 = '  1 0 0 1 %d %d cm\n' % (dx, dy)
    s2 = '  %f 0 0 %f 0 0 cm\n' % (scaling, scaling)
    cmd  = ['q\n', s2, s1]
    for t in things:
        x = t[xind]
        y = t[yind]
        cmd.append('  %d %d m\n' % (x-10, y))
        cmd.append('  %d %d l\n  s\n' % (x+10, y))
        cmd.append('  %d %d m\n' % (x, y-10))
        cmd.append('  %d %d l\n  s\n' % (x, y+10))
    cmd.append('  Q\n')
    return ''.join(cmd)

def drawsubsectors(level):
    """Draw out subsectors using GL nodes. Regular nodes are
    inappropriate, because their leafs are not sufficiently convex."""
    global config, transp_dictref
    
    glvertflag = int(1l << 31)
    verts = level.getvertices()
    glverts = level.getglvertices()
    glsegs = level.getglsegs()
    glssectors = level.getglsubsectors()
    sectors = level.getsectors()
    sidedefs = level.getsidedefs()
    linedefs = level.getlinedefs()
    if config['useblockmap']:
        blockmap = level.getblockmap()
    else:
        blockmap = None
    cmds = ['  q\n'] 
    for ssec in glssectors:
        # First create an array of coordinates.
        coords = []
        segbase = ssec[1]
        segcount = ssec[0]
        fv = glsegs[segbase][0]
        
        if fv & glvertflag:
            fv = fv - glvertflag
            fx = glverts[fv][1]
            fy = glverts[fv][3]
        else:
            fx = verts[fv][0]
            fy = verts[fv][1]
        coords.append((fx, fy))

        cursegs = glsegs[segbase:segbase+segcount]
        for cseg in cursegs:
            #cseg = glsegs[segbase + segoff]
            tv = cseg[1]

            if tv & glvertflag:
                tv = tv - glvertflag
                tx = glverts[tv][1]
                ty = glverts[tv][3]
            else:
                tx = verts[tv][0]
                ty = verts[tv][1]
            coords.append((tx, ty))

        # Now we have the coordinates that make up a subsector. Draw it.
        firstvertex = 1
        cursector = findsector(coords, verts, linedefs,
                               sidedefs, sectors, blockmap)
        flatname = sectors[cursector][2] # Floor texture for this sector.
        if flatname == 'flat10': # TNT MAP11 has a couple of these.
            flatname = flatname.upper()
        cmds.append('  /Pattern cs\n')
        cmds.append('  /%s scn\n' % flatname)
        polycoords = []
        for cc in coords:
            if firstvertex == 1:
                dc = '  %d %d m\n' % cc
                firstvertex = 0
            else:
                dc = '  %d %d l\n' % cc
            polycoords.append(dc)

        cmds += polycoords
        cmds.append('  f\n')

        # Now we do sector lighting, if necessary. This is
        # accomplished by drawing black blob on top of the subsector.
        if config['lighting']:
            
            lightdraw = ['  %f g\n' % config['lightvalue']]
            lightlevel = sectors[cursector][4]/8

            # Set transparency
            trdic = '  /LIGHT_LEVEL_%d gs\n' % lightlevel
            lightdraw.append(trdic)

            # Drawing commands are the same as for the texture mapping
            # above.
            lightdraw += polycoords
            
            lightdraw.append('  f\n')

            # Reset transparency.
            notransp = '  /LIGHT_LEVEL_31 gs\n'
            lightdraw.append(notransp)

            # That's it then.
            cmds += lightdraw
            
    cmds.append('  Q\n')
    return ''.join(cmds)

def getcloselinedefs(x, y, blockmap):
    blocksize = 128
    blocks = blockmap[1]
    xblock = (int(x)-blockmap[0][0])/blocksize
    yblock = (int(y)-blockmap[0][1])/blocksize
    blockwidth = len(blocks[0])
    blockheight = len(blocks)

    # Examine a 3x3 area centered around the block that holds
    # (cx, cy).
    lddict = {}
    for dx in [-1, 0, 1]:
        for dy in [-1, 0, 1]:
            curx = xblock + dx
            cury = yblock + dy

            # Are we outside the blockmap?
            # print 'blockw', blockwidth
            # print 'blockh', blockheight
            # print 'curx', curx
            # print 'cury', cury
            if curx < 0 or curx >= blockwidth or \
               cury < 0 or cury >= blockheight:
                continue

            # Add linedefs in the current block.
            for lnum in blocks[cury][curx]:
                lddict[lnum] = True
            
    # Place linedef numbers to an array and return it.
    result = []
    for lnum in lddict.keys():
        result.append(lnum)
    return result
    

def findsector(ssect, vertices, linedefs, sidedefs, sectors, blockmap):
    """Determines what sector the specified subsector is in.
    Subsectors are always wholly inside a sector."""
    global config

    csum = reduce(lambda x1, x2 : (x1[0] + x2[0], x1[1] + x2[1]), ssect)
    cx = float(csum[0])/ len(ssect)
    cy = float(csum[1])/ len(ssect)

    # Find relevant linedefs using blockmap.
    if config['useblockmap']:
        ldlist = getcloselinedefs(cx, cy, blockmap)
    else:
        ldlist = []

    # Either blockmap is not used, or no linedefs were found in the
    # immediate vicinity. In this case we check every linedef.
    if len(ldlist) == 0:
        ldlist = range(len(linedefs))

    mindist = 50000
    for ldnum in ldlist:
        ld = linedefs[ldnum]
        (x1, y1) = vertices[ld[0]]
        (x2, y2) = vertices[ld[1]]
        v1x = x2 - x1
        v1y = y2 - y1
        v2x = cx - x1
        v2y = cy - y1

        # Check for zero-length linedefs. They are non-orientable, and
        # thus can be ignored (and cause a div by zero).
        if v1x == 0 and v1y == 0:
            continue

        factor = (v1x*v2x + v1y*v2y)/(v1x*v1x + v1y*v1y)
        if factor > 1:
            cdist = math.sqrt((x2-cx)*(x2-cx) + (y2-cy)*(y2-cy))
        elif factor < 0:
            cdist = math.sqrt((x1-cx)*(x1-cx) + (y1-cy)*(y1-cy))
        else:
            v1x *= factor;
            v1y *= factor;
            
            px = v2x - v1x;
            py = v2y - v1y;
            
            cdist = math.sqrt(px*px + py*py)                  

        if cdist < mindist:
            mindist = cdist
            minld = ld

    # We have a linedef. Find out which sidedef to use.
    (fx, fy) = vertices[minld[0]]
    (tx, ty) = vertices[minld[1]]
    
    x1 = cx - fx
    y1 = cy - fy
    x2 = tx - fx
    y2 = ty - fy

    if x1*y2 - x2*y1 > 0:
        sd = sidedefs[minld[-2]]
    else:
        sd = sidedefs[minld[-1]]

    #print sd

    # Should check here that SD is valid (not -1). Has not been a
    # problem thus far, though.
    secnum = sd[-1]

    return secnum
    
#    sec = sectors[secnum]
#    return sec[2]
        
        
def drawlevelsprites(things, thingmapper, limits, dx, dy, scaling, wi, he):
    spdraw = []
    (minx, maxx, miny, maxy) = limits

    dwi = (wi-(maxx-minx)*scaling)/2
    dhe = (he-(maxy-miny)*scaling)/2

    assert dwi >= 0
    assert dhe >= 0

    a1 = (wi-2*dwi)/(maxx-minx)
    b1 = dwi-a1*minx
    a2 = (he-2*dhe)/(maxy-miny)
    b2 = dhe-a2*miny

    #a1 = dwi/(maxx-minx)
    #b1 = dwi-a1*minx
    #a2 = dhe/(maxy-miny)
    #b2 = dhe-a2*miny

    s1 = '  1 0 0 1 -0.5 -0.5 cm\n'
    s3 = '  1 0 0 1 %f %f cm\n' % (dx, dy)
    s4 = '  %f 0 0 %f 0 0 cm\n' % (scaling, scaling)
    if len(things[0]) == 5: # Doom
        xind = 0
        yind = 1
        idind = 3
    else:                   # Hexen
        xind = 1
        yind = 2
        idind = 5
    for thing in things:
        tid = thing[idind]
        try:
            item = thingmapper[tid]
        except KeyError: # ERROR, unknown item in level. Just pass it.
            continue
        if item is None: # Some things do not have graphics.
            continue
        flags = thing[4]
        if(flags & 4 != 4): # Ultra violence items only
            continue
        if(flags & 16 == 16): # Hide multiplayer (deathmatch) only items
            continue
        (sname, w, h) = item
        x = thing[xind]
        y = thing[yind]
        grawid = w*scaling
        grahei = h*scaling
        s69 = ' %f 0 0 %f %f %f cm\n' % (grawid, grahei,
                                         a1*x+b1 - grawid/2,
                                         a2*y+b2 - grahei/2)
        sscale = '  q\n' + s69
        drawcmd = '  /%s Do\n  Q\n' % (sname)
        spdraw.append(sscale + drawcmd)        
    return ''.join(spdraw)
        


def createsprites(wad, thingdic, offset):
    """Create Doom item graphics, their image masks, and flats. Also
    create a resource object to hold them and a dictionary that maps
    item numbers to information about the graphics."""
    global imageobj_templ, maskobj_templ, spriterestext
    graphobjects = []
    graphresitems = []
    patterngraphresitems = []
    thingmapper = {}
    processed = {}

    # Start with the sprite graphics.
    for tnum in thingdic.keys():
        tname = thingdic[tnum]
        if tname is None:  # Some items do not have graphics.
            thingmapper[tnum] = None
            continue
        if processed.has_key(tname): # Some graphics are repeated.
            thingmapper[tnum] = processed[tname]
            continue
        for graph in wad.sprites: # Linear searching is _fun_.
            if graph.name == tname:
                # Unpack graphics.
                (w, h, gra) = indexed2rgba(graph.getgraphic(),
                                           wad.playpal.palettes[0])
                (gra, mask) = image2pdf(gra, w, h)

                # Compress the images with Flate.
                gra = zlib.compress(gra, 9)
                mask = zlib.compress(mask, 9)
                
                imageobj = spriteobj_templ % (offset, offset + 1, w, h,
                                             len(gra), gra)
                graphobjects.append(imageobj)
                # Create resource item.
                res = resitem_templ % (graph.name, offset)
                graphresitems.append(res)
                
                # Create a bitmask for the graphic and compress it.
                offset = offset + 1
                maskobj = maskobj_templ % (offset, w, h, len(mask), mask)
                graphobjects.append(maskobj)
                offset = offset + 1

                # Add an etry to the dictionary.
                thingmapper[tnum] = (tname, w, h)
                processed[tname] = (tname, w, h)
                break # Move to the next thing number

    # Then add the flats.
    for flat in wad.flats:
        # First create an image.
        (w, h, gra) = indexed2rgba(flat.getgraphic(), wad.playpal.palettes[0])
        (gra, mask) = image2pdf(gra, w, h) # Flats do not have/need masks.
        gra = zlib.compress(gra, 9)
        imageobj = flatobj_templ % (offset, w, h, len(gra), gra)
        graphobjects.append(imageobj)
        res = resitem_templ % ('FLAT_' + flat.name, offset)
        patterngraphresitems.append(res)
        offset = offset + 1

        # The pattern resources for flats are created elsewhere,
        # because they are unique to every level.

    spriterestext = ''.join(graphresitems)
    presource = patternresource_templ % ''.join(patterngraphresitems)
    return (presource, thingmapper, graphobjects)

def image2pdf(imdata, w, h):
    """Unpacks a stream of (RGBA) image data to an RGB image and a 1-bit
    imagemask."""

    if len(imdata) % 4 != 0:
        raise Exception('Image data size not multiple of four.')

    imarray = []
    maskarray = []
    # Unpack data.
    for i in range(len(imdata)/4):
        ib = imdata[i*4:i*4+3]
        mb = struct.unpack('B', imdata[i*4+3])[0]
        imarray.append(ib)
        maskarray.append(mb)
    assert w*h == len(imarray)
    assert w*h == len(maskarray)
    mbarray = []
    for j in range(h):
        curline = maskarray[j*w:(j+1)*w]
        assert len(curline) == w
        clarray = [0]*int(len(curline)/8.0 + 0.9)
        #debugline = ''
        for i in range(len(curline)):
            ind = i/8
            offs = 7 - i%8
            #print 'Maskarray on', maskarray[i]
            #debugline = debugline + str(maskarray[i])
            if curline[i] < 127: # Transparent pixel
                clarray[ind] = clarray[ind] | (1 << offs)
                assert clarray[ind] <= 255
        #print debugline
        mbarray = mbarray + clarray
    #import sys
    #sys.exit(-1)
    mbarray = map(lambda x : struct.pack('B', x)[0], mbarray)
    image = ''.join(imarray)
    mask = ''.join(mbarray)
    #print 'Image data size is', len(imdata)
    #print 'Image size is', len(imarray)
    #print 'Bits needed for mask', len(maskarray)
    #print 'Bytes needed for mask', len(mbarray)
    #print 'Size of RBG image', len(image)
    #print 'Size of bitmask', len(mask)
    return (image, mask)

def createoutlineobjects(wad, offset, pageoffset, lnames):
    #global levelnamemapper
    #try:
    #    lnames = levelnamemapper[os.path.basename(wad.fname)]
    #except KeyError:
    #    lnames = {}
    objs = []
    for i in range(len(wad.levels)):
        links = ''
        levelname = wad.levels[i].header.name
        try:
            levelname = levelname + ': ' + lnames[levelname]
        except KeyError:
            pass
        if i > 0:
            links = links + '     /Prev %d 0 R\n' % (offset + i - 1)
        if i < len(wad.levels)-1:
            links = links + '     /Next %d 0 R\n' % (offset + i + 1)

        cobj = outline_templ % (offset + i, levelname, links, pageoffset + i)
        objs.append(cobj)
    return objs
                                

def createinfoobject(number):
    global config
    title = config['title']
    extrainfo = ''
    if config.has_key('creator'):
        extrainfo += '/Creator (%s)\n' % config['creator']
    if config.has_key('author'):
        extrainfo += '/Author (%s)\n' % config['author']
    if config.has_key('keywords'):
        extrainfo += '/Keywords (%s)\n' % config['keywords']
    if config.has_key('subject'):
        extrainfo += '/Subject (%s)\n' % config['subject']
        
    
    tz = time.timezone
    if tz < 0:
        sign = '-'
        tz = -tz
    else:
        sign = '+'
    hoff = int(tz/3600)
    tz = tz - 3600*hoff
    moff = int(tz/60)
    
    tstr = 'D:%d%02d%02d%02d%02d%02d%s%02d\'%02d\'' % (time.localtime()[:6] +
                                                       (sign, hoff, moff))
    return infobj_templ % (number, title, extrainfo, tstr)
    

def createpdf(w, outfilename, mapper):

    # Lighting requires transparency, which requires pdf version 1.4.
    if config['lighting']:
        pdfheader = pdf14header
    else:
        pdfheader = pdf13header

    levelnames = config['levelnames']

    objects = ['CATALOGDUMMY', outlines, 'PATTERNRESOURCEDUMMY']
    (pagewidth, pageheight) = config['papersize']
    textoffset = config['textoffset']

    graphstarttime = time.time()

    # Create transparency items.
    objects += create_transdict(len(objects)+1)

    infotxt = 'Converting graphics.'
    infotxt += ' '*(textoffset - len(infotxt))
    print infotxt,
    sys.stdout.flush()

    # Convert the graphics.
    (pres, thingmapper, graphobjects) = createsprites(w, mapper,
                                                      len(objects) + 1)
    objects += graphobjects

    # Print how long it took.
    graphendtime = time.time()
    dur = int(graphendtime-graphstarttime)
    if dur < 60:
        if dur == 0:
            durtxt = '>1 s'
        else:
            durtxt =  '%2d s' % dur
    else:
        durtxt = '%2d m %2d s' % (dur/60, dur%60)
    print durtxt.rjust(9)


    # Draw the graphics to pages.
    contentsoffset = len(objects) + 1
    drawobjects = createdrawobjects(w, pagewidth, pageheight,
                                    contentsoffset, thingmapper)
    objects = objects + drawobjects

    # Set up references in first objects.
    objects[2] = pres
    objects[0] = catalog % (len(objects) + 1)

    pageoffset = len(objects) + 1 # Page definitions start here.
    pageobjects = createpageobjects(pageoffset, len(w.levels),
                                    pagewidth, pageheight, contentsoffset)
    objects = objects + pageobjects

    # Bookmark navigation links.
    outlineoffset = len(objects) + 1
    outlineobjects = createoutlineobjects(w, outlineoffset, pageoffset+1,
                                          levelnames)
    objects = objects + outlineobjects
    # Make Outlines point to the correct element.
    olen = len(outlineobjects)
    objects[1] = objects[1] % (outlineoffset, outlineoffset+olen-1,
                               olen)

    objects.append(createinfoobject(len(objects)+1))

    ofile = file(outfilename, 'wb')
    offsets = []
    trailer = trailer_templ % (len(objects) + 1, len(objects))
    ofile.write(pdfheader)

    for o in objects:
        offsets.append(ofile.tell())
        ofile.write(o)
    startxref = ofile.tell()

    # Write trailer crapola.
    eolmarker = '\x0D\x0A' # PDF requires CR+LF here.
    ofile.write('xref\n0 %d%s' % (len(objects)+1, eolmarker))
    ofile.write('%010d 65535 f%s' % (0, eolmarker))
    for off in offsets:
        ofile.write('%010d 00000 n%s' % (off, eolmarker))
    ofile.write(trailer)
    ofile.write('startxref%s' % eolmarker)
    ofile.write('%d%s' % (startxref, eolmarker))
    ofile.write(ender)
    ofile.close()
