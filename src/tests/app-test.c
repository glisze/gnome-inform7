/*  Copyright (C) 2011 P. F. Chimento
 *  This file is part of GNOME Inform 7.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "app-test.h"
#include "app.h"
#include "colorscheme.h"

void
test_app_create(void)
{
	I7App *theapp = i7_app_get();

	g_assert(I7_IS_APP(theapp));
	g_assert_cmpint(i7_app_get_num_open_documents(theapp), ==, 0);
}

static void
check_file(GFile *file, const char *name)
{
	char *basename;

	g_assert(G_IS_FILE(file));
	basename = g_file_get_basename(file);
	g_assert_cmpstr(basename, ==, name);
	g_free(basename);
	g_object_unref(file);
}

void
test_app_files(void)
{
	GFile *file;
	I7App *theapp = i7_app_get();

	file = i7_app_check_data_file(theapp, "Extensions");
	check_file(file, "Extensions");

	file = i7_app_check_data_file_va(theapp, "ui", "gnome-inform7.ui", NULL);
	check_file(file, "gnome-inform7.ui");
	
	file = i7_app_get_data_file(theapp, "Extensions");
	check_file(file, "Extensions");

	file = i7_app_get_data_file_va(theapp, "ui", "gnome-inform7.ui", NULL);
	check_file(file, "gnome-inform7.ui");

	file = i7_app_get_binary_file(theapp, "ni");
	check_file(file, "ni");

	g_assert(i7_app_check_data_file(theapp, "nonexistent") == NULL);
	g_assert(i7_app_check_data_file_va(theapp, "nonexistent", "nonexistent", NULL) == NULL);

	/* TODO: How to test the functions that open an error dialog when they fail? */
}

void
test_app_colorscheme_install_remove(void)
{
	GFile *file = g_file_new_for_path("tests/test_color_scheme.xml");

	/* Test installing */
	const char *id = install_scheme(file);
	g_object_unref(file);
	g_assert_cmpstr(id, ==, "test_color_scheme");

	/* Check if the file is really installed */
	char *installed_path = g_build_filename(g_get_user_config_dir(), "inform7", "styles", "test_color_scheme.xml", NULL);
	GFile *installed_file = g_file_new_for_path(installed_path);
	g_free(installed_path);
	g_assert(g_file_query_exists(installed_file, NULL));

	g_assert(is_user_scheme(id));

	/* Test uninstalling */
	g_assert(uninstall_scheme(id));

	/* Check if file is really uninstalled */
	g_assert(g_file_query_exists(installed_file, NULL) == FALSE);

	g_object_unref(installed_file);
}
