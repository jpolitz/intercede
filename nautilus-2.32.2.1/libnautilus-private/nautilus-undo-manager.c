/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 8; tab-width: 8 -*- */

/* NautilusUndoManager - Undo/Redo transaction manager.
 *
 * Copyright (C) 2000 Eazel, Inc.
 *
 * Author: Gene Z. Ragan <gzr@eazel.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include <config.h>
#include <libnautilus-private/nautilus-undo-manager.h>
#include <libnautilus-private/nautilus-undo-transaction.h>

#include <eel/eel-gtk-macros.h>
#include <eel/eel-gtk-extensions.h>
#include <gtk/gtk.h>
#include "nautilus-undo-private.h"

struct NautilusUndoManagerDetails {
	NautilusUndoTransaction *transaction;

	/* These are used to tell undo from redo. */
	gboolean current_transaction_is_redo;
	gboolean new_transaction_is_redo;

	/* These are used only so that we can complain if we get more
	 * than one transaction inside undo.
	 */
	gboolean undo_in_progress;
        int num_transactions_during_undo;
};

enum {
	CHANGED,
	LAST_SIGNAL
};
static guint signals[LAST_SIGNAL];

typedef struct {
#ifdef UIH
	BonoboUIHandler *handler;
#endif /* UIH */
	char *path;
	char *no_undo_menu_item_label;
	char *no_undo_menu_item_hint;
} UndoMenuHandlerConnection;

G_DEFINE_TYPE (NautilusUndoManager,
	       nautilus_undo_manager,
	       G_TYPE_OBJECT)

static void
release_transaction (NautilusUndoManager *manager)
{
	NautilusUndoTransaction *transaction;

	transaction = manager->details->transaction;
	manager->details->transaction = NULL;
	if (transaction != NULL) {
		g_object_unref (transaction);
	}
}

void
nautilus_undo_manager_append (NautilusUndoManager *manager,
			      NautilusUndoTransaction *transaction)
{
	NautilusUndoTransaction *duplicate_transaction;

	/* Check, complain, and ignore the passed-in transaction if we
	 * get more than one within a single undo operation. The single
	 * transaction we get during the undo operation is supposed to
	 * be the one for redoing the undo (or re-undoing the redo).
	 */
	if (manager->details->undo_in_progress) {
		manager->details->num_transactions_during_undo += 1;
		g_return_if_fail (manager->details->num_transactions_during_undo == 1);		
	}
	
	g_return_if_fail (transaction != NULL);

	/* Keep a copy of this transaction (dump the old one). */
	duplicate_transaction = g_object_ref (transaction);
	release_transaction (manager);
	manager->details->transaction = duplicate_transaction;
	manager->details->current_transaction_is_redo =
		manager->details->new_transaction_is_redo;
	
	/* Fire off signal indicating that the undo state has changed. */
	g_signal_emit (manager, signals[CHANGED], 0);
}

void
nautilus_undo_manager_forget (NautilusUndoManager *manager,
			      NautilusUndoTransaction *transaction)
{
	/* Nothing to forget unless the item we are passed is the
	 * transaction we are currently holding.
	 */
	if (transaction != manager->details->transaction) {
		return;
	}

	/* Get rid of the transaction we are holding on to. */
	release_transaction (manager);
	
	/* Fire off signal indicating that the undo state has changed. */
	g_signal_emit (manager, signals[CHANGED], 0);
}

NautilusUndoManager *
nautilus_undo_manager_new (void)
{
	return NAUTILUS_UNDO_MANAGER (g_object_new (nautilus_undo_manager_get_type (), NULL));
}

static void
nautilus_undo_manager_init (NautilusUndoManager *manager)
{
	manager->details = g_new0 (NautilusUndoManagerDetails, 1);
}

void
nautilus_undo_manager_undo (NautilusUndoManager *manager)
{
	NautilusUndoTransaction *transaction;

	g_return_if_fail (NAUTILUS_IS_UNDO_MANAGER (manager));

	transaction = manager->details->transaction;
	manager->details->transaction = NULL;
	if (transaction != NULL) {
		/* Perform the undo. New transactions that come in
		 * during an undo are redo transactions. New
		 * transactions that come in during a redo are undo
		 * transactions. Transactions that come in outside
		 * are always undo and never redo.
		 */
		manager->details->new_transaction_is_redo =
			!manager->details->current_transaction_is_redo;
		manager->details->undo_in_progress = TRUE;
		manager->details->num_transactions_during_undo = 0;
		nautilus_undo_transaction_undo (transaction);
		manager->details->undo_in_progress = FALSE;
		manager->details->new_transaction_is_redo = FALSE;

		/* Let go of the transaction. */
		g_object_unref (transaction);

		/* Fire off signal indicating the undo state has changed. */
		g_signal_emit (manager, signals[CHANGED], 0);
	}
}

static void
finalize (GObject *object)
{
	NautilusUndoManager *manager;

	manager = NAUTILUS_UNDO_MANAGER (object);

	release_transaction (manager);

	g_free (manager->details);

	if (G_OBJECT_CLASS (nautilus_undo_manager_parent_class)->finalize) {
		(* G_OBJECT_CLASS (nautilus_undo_manager_parent_class)->finalize) (object);
	}
}

void
nautilus_undo_manager_attach (NautilusUndoManager *manager, GObject *target)
{
	g_return_if_fail (NAUTILUS_IS_UNDO_MANAGER (manager));
	g_return_if_fail (G_IS_OBJECT (target));

	nautilus_undo_attach_undo_manager (G_OBJECT (target), manager);
}

#ifdef UIH
static void
update_undo_menu_item (NautilusUndoManager *manager,
		       UndoMenuHandlerConnection *connection)
{
	CORBA_Environment ev;
	Nautilus_Undo_MenuItem *menu_item;

	g_assert (NAUTILUS_IS_UNDO_MANAGER (manager));
	g_assert (connection != NULL);
	g_assert (BONOBO_IS_UI_HANDLER (connection->handler));
	g_assert (connection->path != NULL);
	g_assert (connection->no_undo_menu_item_label != NULL);
	g_assert (connection->no_undo_menu_item_hint != NULL);
	
	CORBA_exception_init (&ev);

	if (CORBA_Object_is_nil (manager->details->transaction, &ev)) {
		menu_item = NULL;
	} else {
		if (manager->details->current_transaction_is_redo) {
			menu_item = Nautilus_Undo_Transaction__get_redo_menu_item
				(manager->details->transaction, &ev);
		} else {
			menu_item = Nautilus_Undo_Transaction__get_undo_menu_item
				(manager->details->transaction, &ev);
		}
	}

	bonobo_ui_handler_menu_set_sensitivity
		(connection->handler, connection->path,
		 menu_item != NULL);
	bonobo_ui_handler_menu_set_label
		(connection->handler, connection->path,
		 menu_item == NULL
		 ? connection->no_undo_menu_item_label
		 : menu_item->label);
	bonobo_ui_handler_menu_set_hint
		(connection->handler, connection->path,
		 menu_item == NULL
		 ? connection->no_undo_menu_item_hint
		 : menu_item->hint);
	
	CORBA_free (menu_item);
	
	CORBA_exception_free (&ev);
}

static void
undo_menu_handler_connection_free (UndoMenuHandlerConnection *connection)
{
	g_assert (connection != NULL);
	g_assert (BONOBO_IS_UI_HANDLER (connection->handler));
	g_assert (connection->path != NULL);
	g_assert (connection->no_undo_menu_item_label != NULL);
	g_assert (connection->no_undo_menu_item_hint != NULL);

	g_free (connection->path);
	g_free (connection->no_undo_menu_item_label);
	g_free (connection->no_undo_menu_item_hint);
	g_free (connection);
}

static void
undo_menu_handler_connection_free_cover (gpointer data)
{
	undo_menu_handler_connection_free (data);
}

void
nautilus_undo_manager_set_up_bonobo_ui_handler_undo_item (NautilusUndoManager *manager,
							  BonoboUIHandler *handler,
							  const char *path,
							  const char *no_undo_menu_item_label,
							  const char *no_undo_menu_item_hint)
{
	UndoMenuHandlerConnection *connection;

	connection = g_new (UndoMenuHandlerConnection, 1);
	connection->handler = handler;
	connection->path = g_strdup (path);
	connection->no_undo_menu_item_label = g_strdup (no_undo_menu_item_label);
	connection->no_undo_menu_item_hint = g_strdup (no_undo_menu_item_hint);

	/* Set initial state of menu item. */
	update_undo_menu_item (manager, connection);

	/* Update it again whenever the changed signal is emitted. */
	eel_gtk_signal_connect_full_while_alive
		(GTK_OBJECT (manager), "changed",
		 G_CALLBACK (update_undo_menu_item), NULL,
		 connection, undo_menu_handler_connection_free_cover,
		 FALSE, FALSE,
		 GTK_OBJECT (handler));
}
#endif /* UIH */

static void
nautilus_undo_manager_class_init (NautilusUndoManagerClass *class)
{
	G_OBJECT_CLASS (class)->finalize = finalize;

	signals[CHANGED] = g_signal_new
		("changed",
		 G_TYPE_FROM_CLASS (class),
		 G_SIGNAL_RUN_LAST,
		 G_STRUCT_OFFSET (NautilusUndoManagerClass,
				  changed),
		 NULL, NULL,
		 g_cclosure_marshal_VOID__VOID,
		 G_TYPE_NONE, 0);
}
