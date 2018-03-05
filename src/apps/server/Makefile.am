MAINTAINERCLEANFILES = Makefile.in

AM_LDFLAGS = -L$(top_srcdir)/src/lib/domoticz -ldomoticz \
	     -L$(top_srcdir)/src/lib/devices/device -ldevice \
	     -L$(top_srcdir)/src/lib/devices/bme280 -lbme280 \
	     -lconfig++
AM_CPPFLAGS = -I$(top_srcdir)/src/lib/

bin_PROGRAMS = dominus-server
dominus_server_SOURCES = dominus.cpp
