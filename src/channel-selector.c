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

#include "channel-selector.h"

struct _ChannelSelectorPrivate
{
    ClutterActor    *main;
    GList           *options;
    gboolean        enable_on_select;
};

typedef struct {
    ChannelSelector     *parent;
    ClutterActor        *label;
    Channel             *chan;
    gboolean            selected;
} SelectableOption;

G_DEFINE_TYPE (ChannelSelector, channel_selector, CLUTTER_TYPE_ACTOR);

#define CHANNEL_SELECTOR_GET_PRIVATE(obj)   (G_TYPE_INSTANCE_GET_PRIVATE ((obj), CHANNEL_SELECTOR_TYPE, ChannelSelectorPrivate))

static void channel_selector_allocate (ClutterActor *actor, const ClutterActorBox *box, ClutterAllocationFlags flags)
{
    ChannelSelectorPrivate *priv = CHANNEL_SELECTOR (actor)->priv;

    CLUTTER_ACTOR_CLASS (channel_selector_parent_class)->allocate (actor, box, flags);
    clutter_actor_allocate (priv->main, box, flags);
}

static void channel_selector_paint (ClutterActor *self)
{
    ChannelSelectorPrivate *priv = CHANNEL_SELECTOR (self)->priv;

    clutter_actor_paint (priv->main);
}

static void channel_selector_pick (ClutterActor *self, const ClutterColor *color)
{
    ChannelSelectorPrivate *priv = CHANNEL_SELECTOR (self)->priv;

    clutter_actor_paint (priv->main);
}

static void channel_selector_map (ClutterActor *actor)
{
    ChannelSelectorPrivate *priv = CHANNEL_SELECTOR (actor)->priv;

    CLUTTER_ACTOR_CLASS (channel_selector_parent_class)->map (actor);
    clutter_actor_map (priv->main);
}

static void channel_selector_unmap (ClutterActor *actor)
{
    ChannelSelectorPrivate *priv = CHANNEL_SELECTOR (actor)->priv;

    CLUTTER_ACTOR_CLASS (channel_selector_parent_class)->unmap (actor);
    clutter_actor_unmap (priv->main);
}

static void channel_selector_parent_set (ClutterActor *widget, ClutterActor *old_parent)
{
    ChannelSelectorPrivate *priv = CHANNEL_SELECTOR (widget)->priv;

    clutter_actor_set_parent (priv->main, widget);
}

static void channel_selector_finalize (GObject *gobject)
{
    ChannelSelector *selector;

    selector = CHANNEL_SELECTOR (gobject);
    g_object_unref (selector->priv->main);
    g_list_free (selector->priv->options);

    G_OBJECT_CLASS (channel_selector_parent_class)->finalize (gobject);
}

static void channel_selector_class_init (ChannelSelectorClass *klass)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
    ClutterActorClass *actor_class = CLUTTER_ACTOR_CLASS (klass);

    g_type_class_add_private (klass, sizeof (ChannelSelectorPrivate));

    gobject_class->finalize = channel_selector_finalize;

    actor_class->allocate = channel_selector_allocate;
    actor_class->paint = channel_selector_paint;
    actor_class->pick = channel_selector_pick;
    actor_class->map = channel_selector_map;
    actor_class->unmap = channel_selector_unmap;
    actor_class->parent_set = channel_selector_parent_set;
}

static void channel_selector_init (ChannelSelector *actor)
{
    actor->priv = CHANNEL_SELECTOR_GET_PRIVATE (actor);
    actor->priv->main = clutter_group_new ();
    actor->priv->enable_on_select = FALSE;

    clutter_actor_set_reactive (CLUTTER_ACTOR (actor), TRUE);
    clutter_actor_set_reactive (actor->priv->main, TRUE);
}

ClutterActor* channel_selector_new () {
    return g_object_new (CHANNEL_SELECTOR_TYPE, NULL);
}

static gboolean enable_channel (ClutterActor *label, ClutterEvent *event, SelectableOption *option)
{
    GList *iter;
    static ClutterColor enabled_text_color = ACTIVE_CHANNEL_COLOR;
    static ClutterColor disabled_text_color = UNACTIVE_CHANNEL_COLOR;
    SelectableOption *other_option;

    option->selected = (option->selected == FALSE);

    if (option->selected == TRUE)
        clutter_text_set_color (CLUTTER_TEXT (label), &enabled_text_color);
    else
        clutter_text_set_color (CLUTTER_TEXT (label), &disabled_text_color);

    if (option->parent->priv->enable_on_select) {
        option->chan->enabled = option->selected;
    }
    else {
        if (option->selected == TRUE) {
            for (iter = option->parent->priv->options; iter; iter = g_list_next (iter)) {
                other_option = (SelectableOption*) iter->data;

                if (other_option != option) {
                    other_option->selected = FALSE;
                    clutter_text_set_color (CLUTTER_TEXT (other_option->label), &disabled_text_color);
                }
            }
        }
    }

    return TRUE;
}

void channel_selector_set_channels (ChannelSelector *selector, Channel *channels)
{
    register int i;
    int row;
    gfloat vertical_offset;
    gfloat width;
    gfloat orizzontal_offsets [10];
    gchar chan_label [50];
    ClutterActor *label;
    static ClutterColor enabled_text_color = ACTIVE_CHANNEL_COLOR;
    static ClutterColor disabled_text_color = UNACTIVE_CHANNEL_COLOR;
    Channel *chan;
    SelectableOption *opt;

    vertical_offset = 15;

    for (i = 0; i < 10; i++)
        orizzontal_offsets [i] = 10;

    for (i = 0; channels [i].name != NULL; i++) {
        chan = &(channels [i]);

        row = chan->category;
        if (row >= 10) {
            g_warning ("No room for so many categories!");
            continue;
        }

        snprintf (chan_label, 50, "/%s", chan->name);

        if (selector->priv->enable_on_select == TRUE && chan->enabled == TRUE)
            label = clutter_text_new_full (CONF_FONT, chan_label, &enabled_text_color);
        else
            label = clutter_text_new_full (CONF_FONT, chan_label, &disabled_text_color);

        clutter_container_add_actor (CLUTTER_CONTAINER (selector->priv->main), label);
        clutter_actor_set_fixed_position_set (label, TRUE);
        clutter_actor_set_position (label, orizzontal_offsets [row], (row * vertical_offset) + 20);

        clutter_actor_get_size (label, &width, NULL);
        orizzontal_offsets [row] += (width + 5);

        opt = g_new0 (SelectableOption, 1);
        opt->parent = selector;
        opt->chan = chan;
        opt->label = label;
        opt->selected = FALSE;
        selector->priv->options = g_list_prepend (selector->priv->options, opt);

        clutter_actor_set_reactive (label, TRUE);
        g_signal_connect (G_OBJECT (label), "button-press-event", G_CALLBACK (enable_channel), opt);
    }
}

void channel_selector_enable_on_select (ChannelSelector *selector, gboolean enable)
{
    GList *iter;
    static ClutterColor enabled_text_color = ACTIVE_CHANNEL_COLOR;
    static ClutterColor disabled_text_color = UNACTIVE_CHANNEL_COLOR;
    SelectableOption *option;

    if (selector->priv->enable_on_select == enable)
        return;

    selector->priv->enable_on_select = enable;

    if (enable) {
        for (iter = selector->priv->options; iter; iter = g_list_next (iter)) {
            option = (SelectableOption*) iter->data;

            if (option->chan->enabled == TRUE) {
                option->selected = TRUE;
                clutter_text_set_color (CLUTTER_TEXT (option->label), &enabled_text_color);
            }
        }
    }
    else {
        for (iter = selector->priv->options; iter; iter = g_list_next (iter)) {
            option = (SelectableOption*) iter->data;
            option->selected = FALSE;
            clutter_text_set_color (CLUTTER_TEXT (option->label), &disabled_text_color);
        }
    }
}

Channel* channel_selector_get_selected (ChannelSelector *selector)
{
    GList *iter;
    SelectableOption *option;

    if (selector->priv->enable_on_select == TRUE) {
        g_warning ("This function cannot be invoked if enable_on_select is actived");
        return NULL;
    }

    for (iter = selector->priv->options; iter; iter = g_list_next (iter)) {
        option = (SelectableOption*) iter->data;
        if (option->selected == TRUE)
            return option->chan;
    }

    return NULL;
}
