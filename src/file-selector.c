/*  tuxchan 0.2
 *  Copyright (C) 2009 Roberto -MadBob- Guido <madbob@users.barberaware.org>
 *
 *  This is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "file-selector.h"

struct _FileSelectorPrivate
{
    gboolean            is_standby;
    GtkWidget           *dialog;
};

G_DEFINE_TYPE (FileSelector, file_selector, CLUTTER_TYPE_TEXT);

#define FILE_SELECTOR_GET_PRIVATE(obj)   (G_TYPE_INSTANCE_GET_PRIVATE ((obj), FILE_SELECTOR_TYPE, FileSelectorPrivate))

static void file_selector_finalize (GObject *gobject)
{
    FileSelector *selector;

    selector = FILE_SELECTOR (gobject);
    gtk_widget_destroy (selector->priv->dialog);

    G_OBJECT_CLASS (file_selector_parent_class)->finalize (gobject);
}

static void file_selector_class_init (FileSelectorClass *klass)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

    g_type_class_add_private (klass, sizeof (FileSelectorPrivate));

    gobject_class->finalize = file_selector_finalize;

    /**
        TODO    Implement key_press_event to handle clipboard
    */
}

static void show_dialog (ClutterActor *actor, gpointer useless)
{
    gchar *filename;
    FileSelector *selector;

    selector = FILE_SELECTOR (actor);

    if (gtk_dialog_run (GTK_DIALOG (selector->priv->dialog)) == GTK_RESPONSE_ACCEPT) {
        filename = gtk_file_chooser_get_uri (GTK_FILE_CHOOSER (selector->priv->dialog));
        clutter_text_set_text (CLUTTER_TEXT (selector), filename);
        g_free (filename);
        selector->priv->is_standby = FALSE;
        gtk_widget_hide (selector->priv->dialog);
    }
}

static void file_selector_init (FileSelector *actor)
{
    actor->priv = FILE_SELECTOR_GET_PRIVATE (actor);
    actor->priv->is_standby = TRUE;

    actor->priv->dialog = gtk_file_chooser_dialog_new ("Choose File", NULL, GTK_FILE_CHOOSER_ACTION_OPEN,
                                                       GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT, NULL);

    clutter_actor_set_reactive (CLUTTER_ACTOR (actor), TRUE);
    g_signal_connect (actor, "button-press-event", G_CALLBACK (show_dialog), NULL);
}

ClutterActor* file_selector_new (const gchar *font_name, const ClutterColor *color) {
    return g_object_new (FILE_SELECTOR_TYPE, "font-name", font_name, "color", color, NULL);
}

void file_selector_go_standby (FileSelector *text)
{
    clutter_text_set_text (CLUTTER_TEXT (text), "Click to Choose a File");
    text->priv->is_standby = TRUE;
}

gboolean file_selector_is_set (FileSelector *text)
{
    return (text->priv->is_standby == FALSE);
}
