MAINTAINERCLEANFILES = Makefile.in aclocal.m4 configure COPYING \
		       INSTALL config.h.in config

ACLOCAL_AMFLAGS = -I m4

maintainer-clean-local:
	-rm -rf config
	-cd m4 && find * | grep -v "ax_cxx_compile_stdcxx.*"| xargs rm

SUBDIRS = src examples
