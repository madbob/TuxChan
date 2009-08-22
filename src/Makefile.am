NULL =

INCLUDES = \
	-DPREFIX=\""$(prefix)"\"				\
	-DLIBDIR=\""$(libdir)"\"				\
	-DDATADIR=\""$(datadir)"\"				\
	-DGNOMELOCALEDIR=\""$(prefix)/$(DATADIRNAME)/locale"\"	\
	$(NULL)

common_cflags = \
	-I$(top_srcdir) \
	$(TUXCHAN_CFLAGS) \
	$(NULL)

common_ldadd = \
	$(TUXCHAN_LIBS) \
	$(NULL)

bin_PROGRAMS = tuxchan

# tuxchan_h = \
# 	icons.h \
# 	$(NULL)

tuxchan_SOURCES = main.c icons.h
tuxchan_CFLAGS = $(common_cflags)
tuxchan_LDADD = $(common_ldadd)
