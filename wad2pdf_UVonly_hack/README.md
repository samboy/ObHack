# Note

This is a fork of [wad2pdf](http://wad2pdf.sourceforge.net/) for only 
making PDFs from Doom2 .wad files; it will only show Ultra Violence 
items, and will not show multiplayer only items.

# LEGAL

Wad2PDF is (c) 2005-2008 Jussi Pakkanen. It is released under the GNU
General Public License v2. Please read the included LICENSE text for
important legal information.


# Introduction

Wad2PDF is a program that converts levels from games like Doom into
PDF graphics. The resulting images can be viewed, printed, or
otherwise examined. Note that the produced PDF files contain images
and other material from the original WAD files. All copyright
restrictions on the original files will also apply to the PDF files.

# Using

You need Python, glBSP and some wad files to get started. Wad2PDF is a
command line program, so all the following commands must be run from
the command promp. 

For people downloading this version of wad2pdf, `glbsp` is available
in the folder `glbsp-2.24-source` of the parent directory.

First you create level 5 GL nodes for the wad files in question:

```
glbsp -v5 doom2.wad
```

Repeat this for all wad files you want to run through Wad2PDF. Then
just run Wad2PDF:

```
wad2pdf {IWAD file} {resource wad files} {PWAD files} {parameters}
```

Only the first parameter is necessary, and it always has to be an IWAD
file. The optional resource and pwad files override graphics and
levels in earlier wads. The program will now generate a PDF file whose
name is taken from the last wad file listed.

For example, let's create a PDF file for TeamTNT's Icarus megawad. The
necessary commands are:

```
glbsp -v5 doom2.wad           # if gl nodes don't already exist
glbsp -v5 icarus.wad          # ditto
wad2pdf doom2.wad icarus.wad
```

This results in a PDF file called icarus.pdf, which contains the
levels and updated graphics of Icarus. You can customize the result
by appending suitable parameters. Parameters and their effects are
listed below.


```
--thingcrosses
```

Draws things as small line crosses instead of sprites

```
--nothings
```

Does not draw things at all.

```
--nosubsectors
```

Does not draw the floor textures.

```
--mergelevels
```

Wad2PDF's default behaviour is to only use the levels from the last
wad file that has them. Usually pwads have only a few levels and
taking the rest from the IWAD is not desired. This switch makes
Wad2PDF not throw away the levels in earlier wad files. Levels with
the same name get overwritten by the newer ones, while new levels are
simply added to the level list.

```
--levelnamefile {filename}
```

You can specify level names, which are shown in PDF bookmarks, with
this switch. The parameter is the name of the file which contains the
level names, one per line. The first word on every line defines the
level and the rest of the line is the name. For example:

```
MAP01 Entryway
MAP02 Underhalls
MAP03 The Gantlet
[and so on]
```

```
--noblockmap
```

When drawing textured floors Wad2PDF uses a fast blockmap-based
algorithm. It can, in some very rare cases, lead to incorrect floor
textures. This switch tells Wad2PDF to use a different, 100% correct
algorithm. The downside is that it runs 30-50 times slower than the
blockmap algorithm. Wad2PDF automatically falls back to the slower
algorithm for levels that do not have a blockmap.

```
--papersize <param>
```

Defines the canvas size. Acceptable values include A0 to A5, letter,
legal and tabloid. You can also define a custom paper size. In this
case the parameter must have the form width x height (written
together). The values are interpreted as points. For example to set
the page size to 300 points wide and 400 points high, you would use
'--papersize 300x400'.

```
--landscape
```

Flips the paper 90 degrees. To get a landscape A3 print, the needed
parameters are '--papersize a3 --landscape'.

```
-o {outfilename}
```

By default, Wad2PDF saves its output to a file whose name is the same
as the final used wad's. This parameter allows you to override it.

```
--lighting
```

This option attempts to imitate the lighting in Doom. This shows
things such as shadows cast by torches and so on. It is not enabled by
default, because the results can look quite funky at times.

```
--lightvalue {value as a float}
```

This parameter affects how strong the lighting effect is. You can set
it to any value between 0.0 and 1.0, but values less than 0.4 are
recommended. 

The following commands set PDF properties. They all take one
parameter. If the parameter contains spaces, you must quote it.

```
--title      The name of the document. Usually wad name.
--author     Who created the wad.
--creator    Tools used to create the wad, e.g. WadAuthor
--keywords   Keywords describing the PDF file.
--subject    Subject of the document.
```

# Common problems

Wad2PDF has been tested with several large wads, and it works quite
well. Even large wads like TNT Evilution are processed in a minute or
so. However the resulting files may be very large and slow on PDF
viewer programs. The resulting PDF files have been tested with
Acroread, KPDF and Ghostscript with no errors.

The IWAD and possible pwads must match. That is, you can't take a Doom
II pwad and try to run it with the IWAD of Ultimate Doom, Heretic, or
Hexen. The results of such attempts are undefined, and probably lead
to funky graphical errors or even crashes in the PDF viewer or wad2pdf.

# Feedback

Questions? Comments? Open up a GirHub issue; to contact the original
author of wad2pdf, send mail to jussi dot pakkanen at nbl dot fi.
