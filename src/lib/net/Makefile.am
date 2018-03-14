MAINTAINERCLEANFILES = Makefile.in server.la client.la

include $(top_srcdir)/common.mk

AM_CPPFLAGS = -I$(top_srcdir)/src/lib/

dominuslib_LTLIBRARIES = libnet.la
libnet_la_SOURCES = server.cpp client.cpp
