## Process this file with automake to produce Makefile.in

## Created by Anjuta

uidir = $(datadir)/audics/ui
ui_DATA = audics.ui

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(AUDICS_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = audics

audics_SOURCES = \
	callbacks.c \
	callbacks.h \
	main.c \
	testn.c \
	testn.h

audics_LDFLAGS = \
	-Wl,--export-dynamic

audics_LDADD = $(AUDICS_LIBS)

EXTRA_DIST = $(ui_DATA)

# Remove ui directory on uninstall
uninstall-local:
	-rm -r $(uidir)
	-rm -r $(datadir)/audics
