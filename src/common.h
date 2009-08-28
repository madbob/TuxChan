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

#ifndef __TUXCHAN_COMMON_H__
#define __TUXCHAN_COMMON_H__

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <glib.h>
#include <gio/gio.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <gtk/gtk.h>
#include <clutter/clutter.h>
#include <libsoup/soup.h>
#include <magic.h>

#define CONF_FONT                   "Mono Bold 15px"
#define INPUT_FONT                  "Mono Bold 12px"
#define TEXT_COLOR                  {0x33, 0xFF, 0x33, 0xFF}
#define ACTIVE_CHANNEL_COLOR        TEXT_COLOR
#define UNACTIVE_CHANNEL_COLOR      {0x11, 0x77, 0x11, 0xFF}

typedef struct {
    int             category;
    const gchar     *name;
    const gchar     *upload_server;
    gboolean        enabled;
} Channel;

#endif
