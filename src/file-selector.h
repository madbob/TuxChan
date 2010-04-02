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

#ifndef __FILE_SELECTOR_H__
#define __FILE_SELECTOR_H__

#include "common.h"

G_BEGIN_DECLS

#define FILE_SELECTOR_TYPE                  (file_selector_get_type ())
#define FILE_SELECTOR(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), FILE_SELECTOR_TYPE, FileSelector))
#define IS_FILE_SELECTOR(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), FILE_SELECTOR_TYPE))
#define FILE_SELECTOR_CLASS(klass)          (G_TYPE_CHECK_CLASS_CAST ((klass), FILE_SELECTOR_TYPE, FileSelectorClass))
#define IS_FILE_SELECTOR_CLASS(klass)       (G_TYPE_CHECK_CLASS_TYPE ((klass), FILE_SELECTOR_TYPE))
#define FILE_SELECTOR_GET_CLASS(obj)        (G_TYPE_INSTANCE_GET_CLASS ((obj), FILE_SELECTOR_TYPE, FileSelectorClass))

typedef struct _FileSelector                FileSelector;
typedef struct _FileSelectorPrivate         FileSelectorPrivate;
typedef struct _FileSelectorClass           FileSelectorClass;

struct _FileSelector
{
    ClutterText                 parent_instance;
    FileSelectorPrivate         *priv;
};

struct _FileSelectorClass
{
    ClutterTextClass            parent_class;
};

GType           file_selector_get_type      (void) G_GNUC_CONST;
ClutterActor*   file_selector_new           (const gchar *font_name, const ClutterColor *color);

void            file_selector_set_uri       (FileSelector *selector, gchar *uri);
void            file_selector_go_standby    (FileSelector *selector);
gboolean        file_selector_is_set        (FileSelector *selector);
void            file_selector_notify_unset  (FileSelector *selector);

G_END_DECLS

#endif /* __FILE_SELECTOR_H__ */
