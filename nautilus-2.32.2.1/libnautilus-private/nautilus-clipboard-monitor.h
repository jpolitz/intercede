/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 8; tab-width: 8 -*-

   nautilus-clipboard-monitor.h: lets you notice clipboard changes.
    
   Copyright (C) 2004 Red Hat, Inc.
  
   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.
  
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.
  
   You should have received a copy of the GNU General Public
   License along with this program; if not, write to the
   Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.
  
   Author: Alexander Larsson <alexl@redhat.com>
*/

#ifndef NAUTILUS_CLIPBOARD_MONITOR_H
#define NAUTILUS_CLIPBOARD_MONITOR_H

#include <gtk/gtk.h>

#define NAUTILUS_TYPE_CLIPBOARD_MONITOR nautilus_clipboard_monitor_get_type()
#define NAUTILUS_CLIPBOARD_MONITOR(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), NAUTILUS_TYPE_CLIPBOARD_MONITOR, NautilusClipboardMonitor))
#define NAUTILUS_CLIPBOARD_MONITOR_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), NAUTILUS_TYPE_CLIPBOARD_MONITOR, NautilusClipboardMonitorClass))
#define NAUTILUS_IS_CLIPBOARD_MONITOR(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), NAUTILUS_TYPE_CLIPBOARD_MONITOR))
#define NAUTILUS_IS_CLIPBOARD_MONITOR_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), NAUTILUS_TYPE_CLIPBOARD_MONITOR))
#define NAUTILUS_CLIPBOARD_MONITOR_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), NAUTILUS_TYPE_CLIPBOARD_MONITOR, NautilusClipboardMonitorClass))

typedef struct NautilusClipboardMonitorDetails NautilusClipboardMonitorDetails;
typedef struct NautilusClipboardInfo NautilusClipboardInfo;

typedef struct {
	GObject parent_slot;

	NautilusClipboardMonitorDetails *details;
} NautilusClipboardMonitor;

typedef struct {
	GObjectClass parent_slot;
  
	void (* clipboard_changed) (NautilusClipboardMonitor *monitor);
	void (* clipboard_info) (NautilusClipboardMonitor *monitor,
	                         NautilusClipboardInfo *info);
} NautilusClipboardMonitorClass;

struct NautilusClipboardInfo {
	GList *files;
	gboolean cut;
};

GType   nautilus_clipboard_monitor_get_type (void);

NautilusClipboardMonitor *   nautilus_clipboard_monitor_get (void);
void nautilus_clipboard_monitor_set_clipboard_info (NautilusClipboardMonitor *monitor,
                                                    NautilusClipboardInfo *info);
NautilusClipboardInfo * nautilus_clipboard_monitor_get_clipboard_info (NautilusClipboardMonitor *monitor);
void nautilus_clipboard_monitor_emit_changed (void);

void nautilus_clear_clipboard_callback (GtkClipboard *clipboard,
                                        gpointer      user_data);
void nautilus_get_clipboard_callback   (GtkClipboard     *clipboard,
                                        GtkSelectionData *selection_data,
                                        guint             info,
                                        gpointer          user_data);



#endif /* NAUTILUS_CLIPBOARD_MONITOR_H */

