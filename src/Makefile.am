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
    -lmagic \
	$(NULL)

bin_PROGRAMS = tuxchan

tuxchan_SOURCES = \
    common.h \
    main.c \
    channel-selector.c \
    editable-text.c \
    file-selector.c \
    icons.h \
    channel-selector.h \
    editable-text.h \
    file-selector.h

tuxchan_CFLAGS = $(common_cflags)
tuxchan_LDADD = $(common_ldadd)
