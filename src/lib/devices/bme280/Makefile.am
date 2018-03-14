MAINTAINERCLEANFILES = Makefile.in

include $(top_srcdir)/common.mk

AM_CPPFLAGS = -I$(top_srcdir)/src/lib/
AM_LDFLAGS = -L$(top_srcdir)/src/lib/devices/device -ldevice

dominuslib_LTLIBRARIES = libbme280.la
libbme280_la_SOURCES = bme280.cpp
