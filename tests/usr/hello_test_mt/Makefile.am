# this is example file: examples/hello_world/Makefile.am

# additional include pathes necessary to compile the C programs
AM_CFLAGS = -I$(top_srcdir)/include @AM_CFLAGS@

AM_LDFLAGS = -lxio -libverbs -lrdmacm -lrt -lpthread \
	     -L$(top_builddir)/src/usr/

###############################################################################
# THE PROGRAMS TO BUILD
###############################################################################

# the program to build (the names of the final binaries)
bin_PROGRAMS = xio_mt_client \
	       xio_mt_server
	
# list of sources for the 'xio_perftest' binary
xio_mt_client_SOURCES =  xio_msg.c		\
		         xio_mt_client.c		
		
xio_mt_server_SOURCES =  xio_msg.c		\
		         xio_mt_server.c		
	

# the additional libraries needed to link xio_client
xio_mt_client_LDADD = 	$(AM_LDFLAGS)
xio_mt_server_LDADD = 	$(AM_LDFLAGS)

EXTRA_DIST = xio_msg.h	

###############################################################################
