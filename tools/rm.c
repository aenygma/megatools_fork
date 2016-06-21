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

static gboolean opt_abortonerror = FALSE;

static GOptionEntry entries[] =
{
  { "abort-on-error",'\0',   0, G_OPTION_ARG_NONE,    &opt_abortonerror,"Abort on error (non zero exit code)",   NULL},
  { NULL }
};

int main(int ac, char* av[])
{
  gc_error_free GError *local_err = NULL;
  static mega_session* s;

  tool_init(&ac, &av, "- remove files from mega.nz", entries);

  if (ac < 2)
  {
    g_printerr("ERROR: No files specified for removal!\n");
    tool_fini(NULL);
    return 1;
  }

  s = tool_start_session();
  if (!s)
  {
    tool_fini(NULL);
    return 1;
  }

  gint errcode = 0;
  gint i;
  for (i = 1; i < ac && !errcode; i++)
  {
    gc_free gchar* path = tool_convert_filename(av[i], FALSE);

    if (!mega_session_rm(s, path, &local_err))
    {
      g_printerr("ERROR: Can't remove %s: %s\n", path, local_err->message);
      g_clear_error(&local_err);

      if (opt_abortonerror)
        errcode = 2;
    }
  }

  mega_session_save(s, NULL);

  tool_fini(s);
  return errcode;
}
