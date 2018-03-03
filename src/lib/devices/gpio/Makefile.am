MAINTAINERCLEANFILES = Makefile.in

AM_CPPFLAGS = -I$(top_srcdir)/src/lib/
AM_LDFLAGS = -L$(top_srcdir)/src/lib/devices/device -ldevice

lib_LTLIBRARIES = libgpio.la
libgpio_la_SOURCES = gpio.cpp
