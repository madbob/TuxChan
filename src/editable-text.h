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

#ifndef __EDITABLE_TEXT_H__
#define __EDITABLE_TEXT_H__

#include "common.h"

G_BEGIN_DECLS

#define EDITABLE_TEXT_TYPE                  (editable_text_get_type ())
#define EDITABLE_TEXT(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), EDITABLE_TEXT_TYPE, EditableText))
#define IS_EDITABLE_TEXT(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), EDITABLE_TEXT_TYPE))
#define EDITABLE_TEXT_CLASS(klass)          (G_TYPE_CHECK_CLASS_CAST ((klass), EDITABLE_TEXT_TYPE, EditableTextClass))
#define IS_EDITABLE_TEXT_CLASS(klass)       (G_TYPE_CHECK_CLASS_TYPE ((klass), EDITABLE_TEXT_TYPE))
#define EDITABLE_TEXT_GET_CLASS(obj)        (G_TYPE_INSTANCE_GET_CLASS ((obj), EDITABLE_TEXT_TYPE, EditableTextClass))

typedef struct _EditableText                EditableText;
typedef struct _EditableTextPrivate         EditableTextPrivate;
typedef struct _EditableTextClass           EditableTextClass;

struct _EditableText
{
    ClutterText                 parent_instance;
    EditableTextPrivate         *priv;
};

struct _EditableTextClass
{
    ClutterTextClass            parent_class;
};

GType           editable_text_get_type      (void) G_GNUC_CONST;
ClutterActor*   editable_text_new           (const gchar *font_name, const gchar *standby, const ClutterColor *color);

void            editable_text_go_standby    (EditableText *text);
gboolean        editable_text_is_set        (EditableText *text);

G_END_DECLS

#endif /* __EDITABLE_TEXT_H__ */
