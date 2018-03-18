MAINTAINERCLEANFILES = Makefile.in

AM_LDFLAGS = -L$(top_srcdir)/src/lib/domoticz -ldomoticz \
	     -L$(top_srcdir)/src/lib/devices/device -ldevice \
	     -L$(top_srcdir)/src/lib/devices/bme280 -lbme280 \
	     -L$(top_srcdir)/src/lib/net/ -lnet \
	     -L$(top_srcdir)/src/lib/devices/gpio -lgpio \
	     -L$(top_srcdir)/src/lib/logger/ -llogger \
	     -lconfig++
AM_CPPFLAGS = -I$(top_srcdir)/src/lib/

bin_PROGRAMS = dominus-server
dominus_server_SOURCES = server.cpp
