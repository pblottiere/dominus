MAINTAINERCLEANFILES = Makefile.in

bin_PROGRAMS = main_server main_client
main_server_SOURCES = main_server.c
main_server_LDADD = ../lib/gpio/libgpio_switch.la \
                    ../lib/tcp/libtcp_server.la 
main_client_SOURCES = main_client.c
main_client_LDADD = ../lib/tcp/libtcp_client.la 
