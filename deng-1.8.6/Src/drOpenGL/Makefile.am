lib_LTLIBRARIES = libdropengl.la

includedir = $(top_srcdir)/Include
INCLUDES = -I$(includedir) -I$(includedir)/drOpenGL
DEFS = -DUNIX -D@FIXED_IMPL@ -D__DROPENGL__ -DUSE_MULTITEXTURE

libdropengl_la_CFLAGS = @SDL_CFLAGS@ 
libdropengl_la_LDFLAGS = @SDL_LIBS@ -module -version-info 0:0:0 \
	-L/usr/X11R6/lib -lGL -lGLU 

libdropengl_la_SOURCES = Unix/main.c draw.c ext.c common.c texture.c 
