MAN1 = megadf megadl megaget megals megamkdir megaput megareg megarm megamv megasync megafs
MAN5 = megarc
MAN7 = megatools

man1_MANS = $(addsuffix .1, $(MAN1))
man5_MANS = $(addsuffix .5, $(MAN5))
man7_MANS = $(addsuffix .7, $(MAN7))

BUILT_SOURCES = $(man1_MANS) $(man5_MANS) $(man7_MANS)

EXTRA_DIST = \
	asciidoc.conf \
	footer.txt \
	remote-paths.txt \
	shared-options.txt \
	$(addsuffix .txt, $(MAN1) $(MAN5) $(MAN7)) \
	$(BUILT_SOURCES)

if ENABLE_DOCS_BUILD

DISTCLEANFILES = $(BUILT_SOURCES)

%.1 %.5 %.7: %.txt shared-options.txt remote-paths.txt footer.txt asciidoc.conf
	a2x --asciidoc-opts="-f asciidoc.conf" -f manpage $<
	sed -i 's/\[FIXME: manual]/Megatools Manual/' $@
	sed -i 's/\[FIXME: source]/megatools $(VERSION)/' $@

else

# These targets do nothing, but satisfy the man file dependencies as if they
# were actually there, which they might not be because docs building is
# disabled.
%.1 %.5 %.7:
	@# If we don't have this noop rule, make won't use this rule to satisfy
	@# the man file dependencies.
	@:

# We must wrap the setting of NORMAL_INSTALL because automake already defines
# it and will not let us redefine it (by ignoring any attempts to redefine the
# variable).  By setting NORMAL_INSTALL we can tell the install targets to
# fail early if a generated man file does not exist, thus not trying to install
# non-existant man pages and spitting out a bunch of errors.  If all the man
# file do exist, then the statement returns true and allows the installation
# to proceed as normal.
$(eval NORMAL_INSTALL = stat -c '' $(BUILT_SOURCES) &>/dev/null || false)

endif
