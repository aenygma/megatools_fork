# {{{ global flags

BUILT_SOURCES =
CLEANFILES =
EXTRA_DIST =
DISTCLEANFILES =

AM_CFLAGS = \
	$(GLIB_CFLAGS) \
	$(OPENSSL_CFLAGS) \
	$(LIBCURL_CFLAGS) \
	-DG_LOG_DOMAIN=\"Mega\" \
	-I$(srcdir)/lib \
	-I$(srcdir)

# }}}
# {{{ libmega

noinst_LIBRARIES = libmega.a

libmega_a_SOURCES = \
	lib/sjson.gen.c \
	lib/sjson.h \
	lib/http.c \
	lib/http.h \
	lib/mega.c \
	lib/mega.h \
	lib/tools.c \
	lib/tools.h \
	lib/alloc.h \
	lib/utils.c \
	lib/utils.h \
	lib/mega.h

# }}}
# {{{ tools

EXTRA_DIST += \
	lib/sjson.c

LDADD = \
	libmega.a \
	$(GLIB_LIBS) \
	$(OPENSSL_LIBS) \
	$(LIBCURL_LIBS)

megafs_LDADD = \
	$(LDADD) \
	$(FUSE_LIBS)

megafs_CFLAGS = \
	$(AM_CFLAGS) \
	$(FUSE_CFLAGS)

bin_PROGRAMS = megadf megadl megaget megals megamkdir megaput megareg megarm megacopy

megadf_SOURCES     = tools/df.c
megadl_SOURCES     = tools/dl.c
megaget_SOURCES    = tools/get.c
megals_SOURCES     = tools/ls.c
megamkdir_SOURCES  = tools/mkdir.c
megaput_SOURCES    = tools/put.c
megareg_SOURCES    = tools/reg.c
megarm_SOURCES     = tools/rm.c
megacopy_SOURCES   = tools/copy.c

if ENABLE_FUSE
bin_PROGRAMS += megafs
megafs_SOURCES     = tools/fs.c $(TOOLS_SOURCES)
endif

# }}}
# {{{ docs

MAN1 = megadf megadl megaget megals megamkdir megaput megareg megarm megacopy
MAN5 = megarc
MAN7 = megatools

if ENABLE_FUSE
MAN1 += megafs
endif

man1_MANS = $(addprefix docs/,$(addsuffix .1, $(MAN1)))
man5_MANS = $(addprefix docs/,$(addsuffix .5, $(MAN5)))
man7_MANS = $(addprefix docs/,$(addsuffix .7, $(MAN7)))

MANS_ALL = $(man1_MANS) $(man5_MANS) $(man7_MANS)

BUILT_SOURCES += $(MANS_ALL)

EXTRA_DIST += \
	docs/asciidoc.conf \
	docs/footer.txt \
	docs/remote-paths.txt \
	docs/shared-options.txt \
	$(man1_MANS:.1=.txt) \
	$(man5_MANS:.5=.txt) \
	$(man7_MANS:.7=.txt) \
	$(MANS_ALL)

if ENABLE_DOCS_BUILD

DISTCLEANFILES += $(MANS_ALL)

%.1 %.5 %.7: %.txt docs/shared-options.txt docs/remote-paths.txt docs/footer.txt docs/asciidoc.conf
	$(AM_V_GEN)a2x --asciidoc-opts="-f docs/asciidoc.conf" -f manpage $<
	@sed -i 's/\[FIXME: manual]/Megatools Manual/' $@
	@sed -i 's/\[FIXME: source]/megatools $(VERSION)/' $@

else

%.1 %.5 %.7:
	@echo You need to use --enable-docs-build if building from git tree
	@false

endif

# }}}
# {{{ tests

EXTRA_DIST += LICENSE HACKING

doc_DATA = LICENSE NEWS TODO README INSTALL HACKING

# }}}

export MAKEFLAGS += --no-print-directory -s
ACLOCAL_AMFLAGS = -I m4
