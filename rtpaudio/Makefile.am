# ##########################################################################
# ####                                                                  ####
# ####                      RTP Audio Server Project                    ####
# ####                    ============================                  ####
# ####                                                                  ####
# #### Makefile.am                                                      ####
# ####                                                                  ####
# ####           Copyright (C) 2011-2014 by Thomas Dreibholz            ####
# ####                                                                  ####
# #### Contact:                                                         ####
# ####    EMail: dreibh@iem.uni-due.de                                  ####
# ####    WWW:   http://www.iem.uni-due.de.de/~dreibh/rtpaudio          ####
# ####                                                                  ####
# #### ---------------------------------------------------------------- ####
# ####                                                                  ####
# #### This program is free software: you can redistribute it and/or    ####
# #### modify it under the terms of the GNU General Public License as   ####
# #### published by the Free Software Foundation, either version 3 of   ####
# #### the License, or (at your option) any later version.              ####
# ####                                                                  ####
# #### This program is distributed in the hope that it will be useful,  ####
# #### but WITHOUT ANY WARRANTY; without even the implied warranty of   ####
# #### MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the    ####
# #### GNU General Public License for more details.                     ####
# ####                                                                  ####
# #### You should have received a copy of the GNU General Public        ####
# #### License along with this program.  If not, see                    ####
# #### <http://www.gnu.org/licenses/>.                                  ####
# ####                                                                  ####
# ##########################################################################
# $Id: convert-to-ogg 1177 2011-12-11 09:35:23Z dreibh $


INCLUDES = $(all_includes) -I../libmpegsound


EXTRA_DIST = AudioServer.config StandardAllClasses.sla Test.list


lib_LTLIBRARIES = libtdtoolbox.la libmediainfo.la libaudiocommon.la libaudioreader.la libaudiowriter.la librtpcommon.la librtpserver.la librtpclient.la libaudiocodeccommon.la libaudioencoder.la libaudiodecoder.la librtpaudiocommon.la librtpaudioserver.la librtpaudioclient.la libqosmgr.la


libtdtoolbox_la_SOURCES = \
 breakdetector.cc breakdetector.h \
 condition.cc condition.h condition.icc \
 ext_socket.h \
 internetaddress.cc internetaddress.h internetaddress.icc internetflow.cc internetflow.h internetflow.icc \
 multitimerthread.h multitimerthread.icc \
 packetaddress.cc packetaddress.h packetaddress.icc \
 portableaddress.h portableaddress.icc \
 randomizer.cc randomizer.h randomizer.icc \
 ringbuffer.cc ringbuffer.h ringbuffer.icc \
 seqnumvalidator.cc seqnumvalidator.h seqnumvalidator.icc \
 socketaddress.cc socketaddress.h socketaddress.icc \
 synchronizable.cc synchronizable.h synchronizable.icc \
 tdsystem.h tdin6.h \
 tdmessage.h tdmessage.icc \
 tdsocket.cc tdsocket.h tdsocket.icc \
 tdstrings.cc tdstrings.h tdstrings.icc \
 thread.cc thread.h thread.icc timedthread.cc timedthread.h timedthread.icc \
 tools.cc tools.h tools.icc \
 trafficclassvalues.cc trafficclassvalues.h trafficclassvalues.icc \
 unixaddress.cc unixaddress.h unixaddress.icc
libtdtoolbox_la_LIBADD = $(sctplib_LIBS) $(socketapi_LIBS) $(glib_LIBS) -lpthread

libmediainfo_la_SOURCES = \
 mediainfo.cc mediainfo.h
libmediainfo_la_LIBADD =


libaudiocommon_la_SOURCES = \
 audioquality.cc audioquality.h audioquality.icc \
 audioqualityinterface.h audioqualityinterface.icc \
 audioconverter.cc audioconverter.h
libaudiocommon_la_LIBADD = libtdtoolbox.la -lm

libaudioreader_la_SOURCES = \
 audioreaderinterface.cc audioreaderinterface.h \
 mp3audioreader.cc mp3audioreader.h \
 multiaudioreader.cc multiaudioreader.h \
 wavaudioreader.cc wavaudioreader.h
libaudioreader_la_LIBADD = libaudiocommon.la libmediainfo.la libtdtoolbox.la ../libmpegsound/libmpegsound.la

libaudiowriter_la_SOURCES = \
 audiowriterinterface.cc audiowriterinterface.h \
 multiaudiowriter.cc multiaudiowriter.h \
 audiodebug.cc audiodebug.h \
 audiodevice.cc audiodevice.h audiodevice.icc \
 audiomixer.cc audiomixer.h audiomixer.icc \
 audionull.cc audionull.h \
 spectrumanalyzer.cc spectrumanalyzer.h \
 fft.cc fft.h
libaudiowriter_la_LIBADD = libaudiocommon.la libtdtoolbox.la $(PULSEAUDIO_LIBS)


librtpcommon_la_SOURCES = \
 rtcppacket.cc rtcppacket.h rtcppacket.icc \
 rtppacket.cc rtppacket.h rtppacket.icc
librtpcommon_la_LIBADD =

librtpserver_la_SOURCES = \
 abstractlayerdescription.cc abstractlayerdescription.h abstractlayerdescription.icc \
 abstractqosdescription.cc abstractqosdescription.h abstractqosdescription.icc \
 bandwidthinfo.cc bandwidthinfo.h bandwidthinfo.icc \
 encoderinterface.h \
 encoderrepositoryinterface.h \
 frameratescalabilityinterface.h framesizescalabilityinterface.h \
 managedstreaminterface.h qosmanagerinterface.h \
 resourceutilizationpoint.cc resourceutilizationpoint.h resourceutilizationpoint.icc \
 rtcpabstractserver.cc rtcpabstractserver.h rtcpabstractserver.icc \
 rtcpreceiver.cc rtcpreceiver.h \
 rtpsender.cc rtpsender.h rtpsender.icc \
 trafficshaper.cc trafficshaper.h trafficshaper.icc
librtpserver_la_LIBADD = librtpcommon.la libtdtoolbox.la

librtpclient_la_SOURCES = \
 decoderinterface.h decoderrepositoryinterface.h \
 rtcpsender.cc rtcpsender.h \
 rtpreceiver.cc rtpreceiver.h rtpreceiver.icc \
 sourcestateinfo.cc sourcestateinfo.h sourcestateinfo.icc
librtpclient_la_LIBADD = librtpcommon.la libtdtoolbox.la


libaudiocodeccommon_la_SOURCES = \
 advancedaudiopacket.cc advancedaudiopacket.h \
 simpleaudiopacket.cc simpleaudiopacket.h
libaudiocodeccommon_la_LIBADD = libaudiocommon.la libtdtoolbox.la

libaudioencoder_la_SOURCES = \
 advancedaudioencoder.cc advancedaudioencoder.h \
 audioencoderinterface.cc audioencoderinterface.h \
 audioencoderrepository.cc audioencoderrepository.h audioencoderrepository.icc \
 simpleaudioencoder.cc simpleaudioencoder.h
libaudioencoder_la_LIBADD = libaudiocodeccommon.la libaudiocommon.la

libaudiodecoder_la_SOURCES = \
 advancedaudiodecoder.cc advancedaudiodecoder.h \
 audiodecoderinterface.cc audiodecoderinterface.h \
 audiodecoderrepository.cc audiodecoderrepository.h audiodecoderrepository.icc \
 simpleaudiodecoder.cc simpleaudiodecoder.h
libaudiodecoder_la_LIBADD = libaudiocodeccommon.la libaudiocommon.la libmediainfo.la libtdtoolbox.la


librtpaudiocommon_la_SOURCES = \
 audioclientapppacket.cc audioclientapppacket.h
librtpaudiocommon_la_LIBADD =

librtpaudioserver_la_SOURCES = \
 audioserver.cc audioserver.h audioserver.icc
librtpaudioserver_la_LIBADD = librtpaudiocommon.la libaudioencoder.la librtpserver.la libaudioreader.la libtdtoolbox.la

librtpaudioclient_la_SOURCES = \
 audioclient.cc audioclient.h audioclient.icc
librtpaudioclient_la_LIBADD = librtpaudiocommon.la libaudiodecoder.la libaudiocommon.la librtpclient.la libmediainfo.la libtdtoolbox.la

libqosmgr_la_SOURCES = \
 bandwidthmanager.cc bandwidthmanager.h bandwidthmanager.icc \
 servicelevelagreement.cc servicelevelagreement.h servicelevelagreement.icc \
 pingerhost.h pingerhost.icc \
 roundtriptimepinger.cc roundtriptimepinger.h roundtriptimepinger.icc \
 sessiondescription.h \
 streamdescription.h  streamdescription.cc
libqosmgr_la_LIBADD = librtpserver.la libtdtoolbox.la


if BUILD_QT_PROGRAMS
%.moc.cc: %.h
	$(MOC) -o $@ $<

%.h: %.ui
	$(UIC) -o $@ $<

%.cc: %.ui
	$(UIC) -o $@ -impl $*.h $<
endif


bin_PROGRAMS  = rtpa-server   rtpa-client   rtpa-vclient
dist_man_MANS = rtpa-server.1 rtpa-client.1 rtpa-vclient.1
if BUILD_QT_PROGRAMS
bin_PROGRAMS  += rtpa-qclient
dist_man_MANS += rtpa-qclient.1
endif


rtpa_server_SOURCES = rtpa-server.cc
rtpa_server_LDADD   = libqosmgr.la librtpaudioserver.la librtpserver.la libtdtoolbox.la -lm

rtpa_client_SOURCES = rtpa-client.cc
rtpa_client_LDADD   = librtpaudioclient.la libaudiodecoder.la libaudiowriter.la libaudiocommon.la libtdtoolbox.la -lm

rtpa_vclient_SOURCES = rtpa-vclient.cc
rtpa_vclient_LDADD   = librtpaudioclient.la libaudiodecoder.la libaudiowriter.la libaudiocommon.la libtdtoolbox.la -lm


if BUILD_QT_PROGRAMS
RTPAQCLIENTMOCHEADER = rtpa-qclient.h qinfotabwidget.h qspectrumanalyzer.h qaudiomixer.h
RTPAQCLIENTMOCEDFILES = $(RTPAQCLIENTMOCHEADER:%.h=%_moc.cc)
CLEANFILES = $(RTPAQCLIENTMOCEDFILES)

%_moc.cc: %.h
	$(MOC) -o $@ $<

# To compile (i.e. generate object files), first create MOC file.
# This MOC file is included by rtpa_qclient.cc, so no compile step is necessary.
$(rtpa_qclient_OBJECTS): $(RTPAQCLIENTMOCEDFILES)

rtpa_qclient_CXXFLAGS = $(QT_CXXFLAGS)
rtpa_qclient_SOURCES  = rtpa-qclient.cc rtpa-qclient.h qinfotabwidget.cc qinfotabwidget.h qspectrumanalyzer.cc qspectrumanalyzer.h qaudiomixer.cc qaudiomixer.h
rtpa_qclient_LDADD    = $(QT_LDADD) librtpaudioclient.la libaudiodecoder.la libaudiowriter.la libaudiocommon.la libtdtoolbox.la -lm
endif


# bin_PROGRAMS += t1
# t1_SOURCES = t1.cc
# t1_LDADD   = librtpaudiocommon.la libaudioencoder.la libtdtoolbox.la librtpserver.la
