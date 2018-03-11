MAINTAINERCLEANFILES = Makefile.in

AM_LDFLAGS = -L$(top_srcdir)/src/lib/net/ -lnet \
	     -L$(top_srcdir)/src/lib/logger/ -llogger
AM_CPPFLAGS = -I$(top_srcdir)/src/lib/

bin_PROGRAMS = dominus-client
dominus_client_SOURCES = client.cpp
