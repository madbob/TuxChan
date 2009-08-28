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

#include "editable-text.h"

enum
{
    PROP_0,
    PROP_STANDY_TEXT
};

struct _EditableTextPrivate
{
    gboolean            is_standby;
    gchar               *standby_text;
};

G_DEFINE_TYPE (EditableText, editable_text, CLUTTER_TYPE_TEXT);

#define EDITABLE_TEXT_GET_PRIVATE(obj)   (G_TYPE_INSTANCE_GET_PRIVATE ((obj), EDITABLE_TEXT_TYPE, EditableTextPrivate))

static void editable_text_set_property (GObject *gobject, guint prop_id, const GValue *value, GParamSpec *pspec)
{
    EditableText *actor = EDITABLE_TEXT (gobject);

    switch (prop_id) {
        case PROP_STANDY_TEXT:
            if (actor->priv->standby_text != NULL)
                g_free (actor->priv->standby_text);
            actor->priv->standby_text = g_strdup (g_value_get_string (value));
            break;

        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID (gobject, prop_id, pspec);
            break;
    }
}

static void editable_text_get_property (GObject *gobject, guint prop_id, GValue *value, GParamSpec *pspec)
{
    EditableText *actor = EDITABLE_TEXT (gobject);

    switch (prop_id) {
        case PROP_STANDY_TEXT:
            g_value_set_string (value, actor->priv->standby_text);
            break;

        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID (gobject, prop_id, pspec);
            break;
    }
}

static void editable_text_finalize (GObject *gobject)
{
    EditableText *editable;

    editable = EDITABLE_TEXT (gobject);
    g_free (editable->priv->standby_text);

    G_OBJECT_CLASS (editable_text_parent_class)->finalize (gobject);
}

static void editable_text_class_init (EditableTextClass *klass)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
    GParamSpec *pspec;

    g_type_class_add_private (klass, sizeof (EditableTextPrivate));

    gobject_class->set_property = editable_text_set_property;
    gobject_class->get_property = editable_text_get_property;
    gobject_class->finalize = editable_text_finalize;

    /**
        TODO    Implement key_press_event to handle clipboard
    */

    pspec = g_param_spec_string ("standby", "Standby Text",
                                 "Text to show when in standby",
                                 NULL,
                                 G_PARAM_READABLE | G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY);
    g_object_class_install_property (gobject_class, PROP_STANDY_TEXT, pspec);
}

static void remove_standby_text (ClutterActor *actor, gpointer useless)
{
    EditableText *editable;

    editable = EDITABLE_TEXT (actor);

    if (editable->priv->is_standby == TRUE) {
        clutter_text_set_text (CLUTTER_TEXT (editable), "");
        editable->priv->is_standby = FALSE;
    }
}

static void editable_text_init (EditableText *actor)
{
    actor->priv = EDITABLE_TEXT_GET_PRIVATE (actor);
    actor->priv->is_standby = TRUE;
    clutter_text_set_editable (CLUTTER_TEXT (actor), TRUE);
    clutter_actor_set_reactive (CLUTTER_ACTOR (actor), TRUE);
    g_signal_connect (actor, "key-focus-in", G_CALLBACK (remove_standby_text), NULL);
}

ClutterActor* editable_text_new (const gchar *font_name, const gchar *standby, const ClutterColor *color) {
    return g_object_new (EDITABLE_TEXT_TYPE, "standby", standby, "font-name", font_name, "color", color, NULL);
}

void editable_text_go_standby (EditableText *text)
{
    clutter_text_set_text (CLUTTER_TEXT (text), text->priv->standby_text);
    text->priv->is_standby = TRUE;
}

gboolean editable_text_is_set (EditableText *text)
{
    return (text->priv->is_standby == FALSE);
}
