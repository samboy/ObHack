
#Redistribution and use in source and binary forms, with or without
#modification, are permitted provided that the following conditions
#are met:
#
#    Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#    Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#    The name of the author may not be used to endorse or promote products
#    derived from this software without specific prior written permission.
#
#THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
#IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
#OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
#IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
#INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
#BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
#USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
#THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
#THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.



CC = gcc

RM = rm

EXE_SUFFIX = .exe

CFLAGS = -Wall -g -O0
#CFLAGS = -Wall -O3

O = obj

LFLAGS =



OBJS=					\
	$(O)/main.o			\
	$(O)/midimerge.o		\
	$(O)/parsemidi.o		\
	$(O)/convert.o			\
	$(O)/smalloc.o


all:	$(OBJS)	midi3mus$(EXE_SUFFIX)

include $(O)/main.po
include $(O)/midimerge.po
include $(O)/parsemidi.po
include $(O)/convert.po
include $(O)/smalloc.po

clean:
	$(RM) $(O)/*.o


$(O)/%.o:   %.c
	$(CC) $(CFLAGS)	-c $< -o $@ -MD -MP -MF $(O)/$*.po -MT $@ 




midi3mus$(EXE_SUFFIX): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o midi3mus$(EXE_SUFFIX) $(LFLAGS)


