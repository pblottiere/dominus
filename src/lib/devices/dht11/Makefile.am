MAINTAINERCLEANFILES = Makefile.in

include $(top_srcdir)/common.mk

AM_CPPFLAGS = -I$(top_srcdir)/src/lib/
AM_LDFLAGS = -L$(top_srcdir)/src/lib/devices/device -ldevice \
	     -L$(top_srcdir)/src/lib/devices/gpio -lgpio \
	     -lwiringPi

dominuslib_LTLIBRARIES = libdht11.la
libdht11_la_SOURCES = dht11.cpp
