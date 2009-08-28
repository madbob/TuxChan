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

#ifndef __CHANNEL_SELECTOR_H__
#define __CHANNEL_SELECTOR_H__

#include "common.h"

G_BEGIN_DECLS

#define CHANNEL_SELECTOR_TYPE               (channel_selector_get_type ())
#define CHANNEL_SELECTOR(obj)               (G_TYPE_CHECK_INSTANCE_CAST ((obj), CHANNEL_SELECTOR_TYPE, ChannelSelector))
#define IS_CHANNEL_SELECTOR(obj)            (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CHANNEL_SELECTOR_TYPE))
#define CHANNEL_SELECTOR_CLASS(klass)       (G_TYPE_CHECK_CLASS_CAST ((klass), CHANNEL_SELECTOR_TYPE, ChannelSelectorClass))
#define IS_CHANNEL_SELECTOR_CLASS(klass)    (G_TYPE_CHECK_CLASS_TYPE ((klass), CHANNEL_SELECTOR_TYPE))
#define CHANNEL_SELECTOR_GET_CLASS(obj)     (G_TYPE_INSTANCE_GET_CLASS ((obj), CHANNEL_SELECTOR_TYPE, ChannelSelectorClass))

typedef struct _ChannelSelector             ChannelSelector;
typedef struct _ChannelSelectorPrivate      ChannelSelectorPrivate;
typedef struct _ChannelSelectorClass        ChannelSelectorClass;

struct _ChannelSelector
{
    ClutterActor                parent_instance;
    ChannelSelectorPrivate      *priv;
};

struct _ChannelSelectorClass
{
    ClutterActorClass           parent_class;
};

GType           channel_selector_get_type           (void) G_GNUC_CONST;
ClutterActor*   channel_selector_new                ();

void            channel_selector_set_channels       (ChannelSelector *selector, Channel *channels);
void            channel_selector_enable_on_select   (ChannelSelector *selector, gboolean enable);
Channel*        channel_selector_get_selected       (ChannelSelector *selector);

G_END_DECLS

#endif /* __CHANNEL_SELECTOR_H__ */
