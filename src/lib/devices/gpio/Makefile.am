MAINTAINERCLEANFILES = Makefile.in

include $(top_srcdir)/common.mk

AM_CPPFLAGS = -I$(top_srcdir)/src/lib/ -I$(top_srcdir)
AM_LDFLAGS = -L$(top_srcdir)/src/lib/devices/device -ldevice -lwiringPi

dominuslib_LTLIBRARIES = libgpio.la
libgpio_la_SOURCES = gpio.cpp
