lib_LTLIBRARIES	= libmpegsound.la

libmpegsound_la_SOURCES  = soundinputstream.cc fileinput.cc httpinput.cc \
			  soundplayer.cc rawplayer.cc rawtofile.cc \
			  mpegtable.cc filter.cc filter_2.cc \
			  mpegtoraw.cc mpeglayer1.cc mpeglayer2.cc \
			  mpeglayer3.cc bitwindow.cc huffmantable.cc \
			  wavetoraw.cc sidplayer.cc \
			  fileplayer.cc nasplayer.cc oggplayer.cc \
				xingheader.cc xingheader.h esdplayer.cc \
				sdlplayer.cc cyclicbuffer.cc cyclicbuffer.h

include_HEADERS		= mpegsound.h mpegsound_locals.h

INCLUDES                = -I$(srcdir) -I$(includedir)
