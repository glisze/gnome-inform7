/*  Copyright 2006 P.F. Chimento
 *  This file is part of GNOME Inform 7.
 * 
 *  GNOME Inform 7 is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  GNOME Inform 7 is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with GNOME Inform 7; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
 
#ifndef _SEARCHWINDOW_H
#define _SEARCHWINDOW_H

#include <gnome.h>
#include "story.h"

enum {
    RESULT_TYPE_PROJECT,
    RESULT_TYPE_EXTENSION,
    RESULT_TYPE_DOCUMENTATION
};

typedef struct {
    gchar *context;
    gchar *source_sort;
    gchar *source_location;
    gchar *source_file;
    int result_type;
    int lineno;
} Result;

void result_free(Result *foo);
GList *search_doc(const gchar *text, gboolean ignore_case, int algorithm);
GList *search_project(const gchar *text, struct story *thestory,
  gboolean ignore_case, int algorithm);
GList *search_extensions(const gchar*text, gboolean ignore_case, int algorithm);
GtkWidget *new_search_window(GtkWidget *main_window, const gchar *text,
  GList *results);

void
on_search_results_view_row_activated   (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

#endif /* _SEARCHWINDOW_H */
