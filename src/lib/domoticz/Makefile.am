MAINTAINERCLEANFILES = Makefile.in

include $(top_srcdir)/common.mk

AM_LDFLAGS = -lcurl
AM_CPPFLAGS = -I$(top_srcdir)/src/lib/

dominuslib_LTLIBRARIES = libdomoticz.la
libdomoticz_la_SOURCES = domoticz.cpp
