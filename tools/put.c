/*
 *  megatools - Mega.nz client library and tools
 *  Copyright (C) 2013  Ondřej Jirman <megous@megous.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "tools.h"

static gchar* opt_path = "/Root";
static gboolean opt_noprogress = FALSE;
static gboolean opt_abortonerror = FALSE;
static gboolean opt_no_previews;

static GOptionEntry entries[] =
{
  { "path",             '\0',   0, G_OPTION_ARG_STRING,  &opt_path,         "Remote path to save files to",          "PATH" },
  { "no-progress",      '\0',   0, G_OPTION_ARG_NONE,    &opt_noprogress,   "Disable progress bar",                  NULL   },
  { "disable-previews", '\0',   0, G_OPTION_ARG_NONE,    &opt_no_previews,  "Don't generate previews",               NULL   },
  { "abort-on-error",   '\0',   0, G_OPTION_ARG_NONE,    &opt_abortonerror, "Abort on error (non zero exit code)",   NULL   },
  { NULL }
};

static gchar* cur_file = NULL;

static gboolean status_callback(mega_status_data* data, gpointer userdata)
{
  if (data->type == MEGA_STATUS_FILEINFO)
  {
    cur_file = g_strdup(data->fileinfo.name);
  }

  if (!opt_noprogress && data->type == MEGA_STATUS_PROGRESS)
    tool_show_progress(cur_file, data);

  return FALSE;
}

int main(int ac, char* av[])
{
  gc_error_free GError *local_err = NULL;
  mega_session* s;

  tool_init(&ac, &av, "- upload files to mega.nz", entries, TOOL_INIT_AUTH);

  if (ac < 2)
  {
    g_printerr("ERROR: No files specified for upload!\n");
    tool_fini(NULL);
    return 1;
  }

  s = tool_start_session(TOOL_SESSION_OPEN);
  if (!s)
    return 1;

  mega_session_enable_previews(s, !opt_no_previews);

  mega_session_watch_status(s, status_callback, NULL);

  gint errcode = 0;
  gint i;
  for (i = 1; i < ac && !errcode; i++)
  {
    gc_free gchar* path = tool_convert_filename(av[i], TRUE);
    cur_file = g_path_get_basename(path);

    // perform download
    if (!mega_session_put(s, opt_path, path, &local_err))
    {
      if (!opt_noprogress)
        g_print("\r" ESC_CLREOL "\n");

      g_printerr("ERROR: Upload failed for '%s': %s\n", path, local_err->message);
      g_clear_error(&local_err);

      if (opt_abortonerror)
        errcode = 2;
    }
    else
    {
      if (!opt_noprogress)
        g_print("\r" ESC_CLREOL "Uploaded %s\n", cur_file);
    }
  }

  mega_session_save(s, NULL);

  tool_fini(s);
  return errcode;
}
