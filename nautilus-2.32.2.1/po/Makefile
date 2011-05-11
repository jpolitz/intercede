# Makefile for program source directory in GNU NLS utilities package.
# Copyright (C) 1995, 1996, 1997 by Ulrich Drepper <drepper@gnu.ai.mit.edu>
# Copyright (C) 2004-2008 Rodney Dawes <dobey.pwns@gmail.com>
#
# This file may be copied and used freely without restrictions.  It may
# be used in projects which are not available under a GNU Public License,
# but which still want to provide support for the GNU gettext functionality.
#
# - Modified by Owen Taylor <otaylor@redhat.com> to use GETTEXT_PACKAGE
#   instead of PACKAGE and to look for po2tbl in ./ not in intl/
#
# - Modified by jacob berkman <jacob@ximian.com> to install
#   Makefile.in.in and po2tbl.sed.in for use with glib-gettextize
#
# - Modified by Rodney Dawes <dobey.pwns@gmail.com> for use with intltool
#
# We have the following line for use by intltoolize:
# INTLTOOL_MAKEFILE

GETTEXT_PACKAGE = nautilus
PACKAGE = nautilus
VERSION = 2.32.2.1

SHELL = /bin/bash

srcdir = .
top_srcdir = ..
top_builddir = ..


prefix = /home/joe
exec_prefix = ${prefix}
datadir = ${datarootdir}
datarootdir = ${prefix}/share
libdir = ${exec_prefix}/lib
DATADIRNAME = share
itlocaledir = $(prefix)/$(DATADIRNAME)/locale
subdir = po
install_sh = ${SHELL} /home/joe/src/nautilus-2.32.2.1/install-sh
# Automake >= 1.8 provides /bin/mkdir -p.
# Until it can be supposed, use the safe fallback:
mkdir_p = $(install_sh) -d

INSTALL = /usr/bin/install -c
INSTALL_DATA = ${INSTALL} -m 644

GMSGFMT = /usr/bin/msgfmt
MSGFMT = /usr/bin/msgfmt
XGETTEXT = /usr/bin/xgettext
INTLTOOL_UPDATE = /usr/bin/intltool-update
INTLTOOL_EXTRACT = /usr/bin/intltool-extract
MSGMERGE = INTLTOOL_EXTRACT=$(INTLTOOL_EXTRACT) srcdir=$(srcdir) $(INTLTOOL_UPDATE) --gettext-package $(GETTEXT_PACKAGE) --dist
GENPOT   = INTLTOOL_EXTRACT=$(INTLTOOL_EXTRACT) srcdir=$(srcdir) $(INTLTOOL_UPDATE) --gettext-package $(GETTEXT_PACKAGE) --pot

ALL_LINGUAS = 

PO_LINGUAS=$(shell if test -r $(srcdir)/LINGUAS; then grep -v "^\#" $(srcdir)/LINGUAS; else echo "$(ALL_LINGUAS)"; fi)

USER_LINGUAS=$(shell if test -n "$(LINGUAS)"; then LLINGUAS="$(LINGUAS)"; ALINGUAS="$(ALL_LINGUAS)"; for lang in $$LLINGUAS; do if test -n "`grep \^$$lang$$ $(srcdir)/LINGUAS 2>/dev/null`" -o -n "`echo $$ALINGUAS|tr ' ' '\n'|grep \^$$lang$$`"; then printf "$$lang "; fi; done; fi)

USE_LINGUAS=$(shell if test -n "$(USER_LINGUAS)" -o -n "$(LINGUAS)"; then LLINGUAS="$(USER_LINGUAS)"; else if test -n "$(PO_LINGUAS)"; then LLINGUAS="$(PO_LINGUAS)"; else LLINGUAS="$(ALL_LINGUAS)"; fi; fi; for lang in $$LLINGUAS; do printf "$$lang "; done)

POFILES=$(shell LINGUAS="$(PO_LINGUAS)"; for lang in $$LINGUAS; do printf "$$lang.po "; done)

DISTFILES = Makefile.in.in POTFILES.in $(POFILES)
EXTRA_DISTFILES = ChangeLog POTFILES.skip Makevars LINGUAS

POTFILES = \
	../cut-n-paste-code/libegg/eggdesktopfile.c \
	../cut-n-paste-code/libegg/eggsmclient.c \
	../data/browser.xml \
	../data/nautilus.xml.in \
	../eel/eel-alert-dialog.c \
	../eel/eel-canvas.c \
	../eel/eel-editable-label.c \
	../eel/eel-gconf-extensions.c \
	../eel/eel-glib-extensions.c \
	../eel/eel-gnome-extensions.c \
	../eel/eel-stock-dialogs.c \
	../eel/eel-vfs-extensions.c \
	../libnautilus-extension/nautilus-column.c \
	../libnautilus-extension/nautilus-menu-item.c \
	../libnautilus-extension/nautilus-property-page.c \
	../libnautilus-private/apps_nautilus_preferences.schemas.in \
	../libnautilus-private/nautilus-autorun.c \
	../libnautilus-private/nautilus-clipboard.c \
	../libnautilus-private/nautilus-column-chooser.c \
	../libnautilus-private/nautilus-column-utilities.c \
	../libnautilus-private/nautilus-customization-data.c \
	../libnautilus-private/nautilus-desktop-directory-file.c \
	../libnautilus-private/nautilus-desktop-icon-file.c \
	../libnautilus-private/nautilus-desktop-link-monitor.c \
	../libnautilus-private/nautilus-desktop-link.c \
	../libnautilus-private/nautilus-dnd.c \
	../libnautilus-private/nautilus-emblem-utils.c \
	../libnautilus-private/nautilus-entry.c \
	../libnautilus-private/nautilus-file-conflict-dialog.c \
	../libnautilus-private/nautilus-file-operations.c \
	../libnautilus-private/nautilus-file-utilities.c \
	../libnautilus-private/nautilus-file.c \
	../libnautilus-private/nautilus-global-preferences.c \
	../libnautilus-private/nautilus-icon-canvas-item.c \
	../libnautilus-private/nautilus-icon-container.c \
	../libnautilus-private/nautilus-icon-dnd.c \
	../libnautilus-private/nautilus-mime-actions.c \
	../libnautilus-private/nautilus-mime-application-chooser.c \
	../libnautilus-private/nautilus-open-with-dialog.c \
	../libnautilus-private/nautilus-program-choosing.c \
	../libnautilus-private/nautilus-progress-info.c \
	../libnautilus-private/nautilus-query.c \
	../libnautilus-private/nautilus-search-directory-file.c \
	../libnautilus-private/nautilus-tree-view-drag-dest.c \
	../libnautilus-private/nautilus-undo-signal-handlers.c \
	../libnautilus-private/nautilus-vfs-file.c \
	../data/nautilus-autorun-software.desktop.in.in \
	../data/nautilus-browser.desktop.in.in \
	../data/nautilus-computer.desktop.in.in \
	../data/nautilus-file-management-properties.desktop.in.in \
	../data/nautilus-folder-handler.desktop.in.in \
	../data/nautilus-home.desktop.in.in \
	../data/nautilus.desktop.in.in \
	../src/file-manager/fm-desktop-icon-view.c \
	../src/file-manager/fm-directory-view.c \
	../src/file-manager/fm-ditem-page.c \
	../src/file-manager/fm-error-reporting.c \
	../src/file-manager/fm-icon-container.c \
	../src/file-manager/fm-icon-view.c \
	../src/file-manager/fm-list-model.c \
	../src/file-manager/fm-list-view.c \
	../src/file-manager/fm-properties-window.c \
	../src/file-manager/fm-tree-model.c \
	../src/file-manager/fm-tree-view.c \
	../src/file-manager/nautilus-desktop-icon-view-ui.xml \
	../src/file-manager/nautilus-directory-view-ui.xml \
	../src/file-manager/nautilus-icon-view-ui.xml \
	../src/file-manager/nautilus-list-view-ui.xml \
	../src/nautilus-application.c \
	../src/nautilus-autorun-software.c \
	../src/nautilus-bookmarks-window.c \
	../src/nautilus-bookmarks-window.ui \
	../src/nautilus-connect-server-dialog-main.c \
	../src/nautilus-connect-server-dialog.c \
	../src/nautilus-desktop-window.c \
	../src/nautilus-emblem-sidebar.c \
	../src/nautilus-file-management-properties-main.c \
	../src/nautilus-file-management-properties.c \
	../src/nautilus-file-management-properties.ui \
	../src/nautilus-history-sidebar.c \
	../src/nautilus-image-properties-page.c \
	../src/nautilus-information-panel.c \
	../src/nautilus-location-bar.c \
	../src/nautilus-location-dialog.c \
	../src/nautilus-location-entry.c \
	../src/nautilus-main.c \
	../src/nautilus-navigation-window-menus.c \
	../src/nautilus-navigation-window-pane.c \
	../src/nautilus-navigation-window-ui.xml \
	../src/nautilus-navigation-window.c \
	../src/nautilus-notebook.c \
	../src/nautilus-notes-viewer.c \
	../src/nautilus-pathbar.c \
	../src/nautilus-places-sidebar.c \
	../src/nautilus-property-browser.c \
	../src/nautilus-query-editor.c \
	../src/nautilus-search-bar.c \
	../src/nautilus-shell-ui.xml \
	../src/nautilus-side-pane.c \
	../src/nautilus-sidebar-title.c \
	../src/nautilus-spatial-window-ui.xml \
	../src/nautilus-spatial-window.c \
	../src/nautilus-trash-bar.c \
	../src/nautilus-window-bookmarks.c \
	../src/nautilus-window-manage-views.c \
	../src/nautilus-window-menus.c \
	../src/nautilus-window-private.h \
	../src/nautilus-window-slot.c \
	../src/nautilus-window-toolbars.c \
	../src/nautilus-window.c \
	../src/nautilus-x-content-bar.c \
	../src/nautilus-zoom-control.c \
	../src/network-scheme.desktop.in

CATALOGS=$(shell LINGUAS="$(USE_LINGUAS)"; for lang in $$LINGUAS; do printf "$$lang.gmo "; done)

.SUFFIXES:
.SUFFIXES: .po .pox .gmo .mo .msg .cat

.po.pox:
	$(MAKE) $(GETTEXT_PACKAGE).pot
	$(MSGMERGE) $< $(GETTEXT_PACKAGE).pot -o $*.pox

.po.mo:
	$(MSGFMT) -o $@ $<

.po.gmo:
	file=`echo $* | sed 's,.*/,,'`.gmo \
	  && rm -f $$file && $(GMSGFMT) -o $$file $<

.po.cat:
	sed -f ../intl/po2msg.sed < $< > $*.msg \
	  && rm -f $@ && gencat $@ $*.msg


all: all-yes

all-yes: $(CATALOGS)
all-no:

$(GETTEXT_PACKAGE).pot: $(POTFILES)
	$(GENPOT)

install: install-data
install-data: install-data-yes
install-data-no: all
install-data-yes: all
	linguas="$(USE_LINGUAS)"; \
	for lang in $$linguas; do \
	  dir=$(DESTDIR)$(itlocaledir)/$$lang/LC_MESSAGES; \
	  $(mkdir_p) $$dir; \
	  if test -r $$lang.gmo; then \
	    $(INSTALL_DATA) $$lang.gmo $$dir/$(GETTEXT_PACKAGE).mo; \
	    echo "installing $$lang.gmo as $$dir/$(GETTEXT_PACKAGE).mo"; \
	  else \
	    $(INSTALL_DATA) $(srcdir)/$$lang.gmo $$dir/$(GETTEXT_PACKAGE).mo; \
	    echo "installing $(srcdir)/$$lang.gmo as" \
		 "$$dir/$(GETTEXT_PACKAGE).mo"; \
	  fi; \
	  if test -r $$lang.gmo.m; then \
	    $(INSTALL_DATA) $$lang.gmo.m $$dir/$(GETTEXT_PACKAGE).mo.m; \
	    echo "installing $$lang.gmo.m as $$dir/$(GETTEXT_PACKAGE).mo.m"; \
	  else \
	    if test -r $(srcdir)/$$lang.gmo.m ; then \
	      $(INSTALL_DATA) $(srcdir)/$$lang.gmo.m \
		$$dir/$(GETTEXT_PACKAGE).mo.m; \
	      echo "installing $(srcdir)/$$lang.gmo.m as" \
		   "$$dir/$(GETTEXT_PACKAGE).mo.m"; \
	    else \
	      true; \
	    fi; \
	  fi; \
	done

# Empty stubs to satisfy archaic automake needs
dvi info ctags tags CTAGS TAGS ID:

# Define this as empty until I found a useful application.
install-exec installcheck:

uninstall:
	linguas="$(USE_LINGUAS)"; \
	for lang in $$linguas; do \
	  rm -f $(DESTDIR)$(itlocaledir)/$$lang/LC_MESSAGES/$(GETTEXT_PACKAGE).mo; \
	  rm -f $(DESTDIR)$(itlocaledir)/$$lang/LC_MESSAGES/$(GETTEXT_PACKAGE).mo.m; \
	done

check: all $(GETTEXT_PACKAGE).pot
	rm -f missing notexist
	srcdir=$(srcdir) $(INTLTOOL_UPDATE) -m
	if [ -r missing -o -r notexist ]; then \
	  exit 1; \
	fi

mostlyclean:
	rm -f *.pox $(GETTEXT_PACKAGE).pot *.old.po cat-id-tbl.tmp
	rm -f .intltool-merge-cache

clean: mostlyclean

distclean: clean
	rm -f Makefile Makefile.in POTFILES stamp-it
	rm -f *.mo *.msg *.cat *.cat.m *.gmo

maintainer-clean: distclean
	@echo "This command is intended for maintainers to use;"
	@echo "it deletes files that may require special tools to rebuild."
	rm -f Makefile.in.in

distdir = ../$(PACKAGE)-$(VERSION)/$(subdir)
dist distdir: $(DISTFILES)
	dists="$(DISTFILES)"; \
	extra_dists="$(EXTRA_DISTFILES)"; \
	for file in $$extra_dists; do \
	  test -f $(srcdir)/$$file && dists="$$dists $(srcdir)/$$file"; \
	done; \
	for file in $$dists; do \
	  test -f $$file || file="$(srcdir)/$$file"; \
	  ln $$file $(distdir) 2> /dev/null \
	    || cp -p $$file $(distdir); \
	done

update-po: Makefile
	$(MAKE) $(GETTEXT_PACKAGE).pot
	tmpdir=`pwd`; \
	linguas="$(USE_LINGUAS)"; \
	for lang in $$linguas; do \
	  echo "$$lang:"; \
	  result="`$(MSGMERGE) -o $$tmpdir/$$lang.new.po $$lang`"; \
	  if $$result; then \
	    if cmp $(srcdir)/$$lang.po $$tmpdir/$$lang.new.po >/dev/null 2>&1; then \
	      rm -f $$tmpdir/$$lang.new.po; \
            else \
	      if mv -f $$tmpdir/$$lang.new.po $$lang.po; then \
	        :; \
	      else \
	        echo "msgmerge for $$lang.po failed: cannot move $$tmpdir/$$lang.new.po to $$lang.po" 1>&2; \
	        rm -f $$tmpdir/$$lang.new.po; \
	        exit 1; \
	      fi; \
	    fi; \
	  else \
	    echo "msgmerge for $$lang.gmo failed!"; \
	    rm -f $$tmpdir/$$lang.new.po; \
	  fi; \
	done

Makefile POTFILES: stamp-it
	@if test ! -f $@; then \
	  rm -f stamp-it; \
	  $(MAKE) stamp-it; \
	fi

stamp-it: Makefile.in.in $(top_builddir)/config.status POTFILES.in
	cd $(top_builddir) \
	  && CONFIG_FILES=$(subdir)/Makefile.in CONFIG_HEADERS= CONFIG_LINKS= \
	       $(SHELL) ./config.status

# Tell versions [3.59,3.63) of GNU make not to export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
