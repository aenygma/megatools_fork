/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*-
 *
 * Copyright (C) 2012 Colin Walters <walters@verbum.org>.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef __GSYSTEM_LOCAL_ALLOC_H__
#define __GSYSTEM_LOCAL_ALLOC_H__

#include <gio/gio.h>

G_BEGIN_DECLS

#define GS_DEFINE_CLEANUP_FUNCTION(Type, name, func) \
  static inline void name (void *v) \
  { \
    func (*(Type*)v); \
  }

#define GS_DEFINE_CLEANUP_FUNCTION0(Type, name, func) \
  static inline void name (void *v) \
  { \
    if (*(Type*)v) \
      func (*(Type*)v); \
  }

/* These functions shouldn't be invoked directly;
 * they are stubs that:
 * 1) Take a pointer to the location (typically itself a pointer).
 * 2) Provide %NULL-safety where it doesn't exist already (e.g. g_object_unref)
 */
GS_DEFINE_CLEANUP_FUNCTION0(GArray*, gs_local_array_unref, g_array_unref)
GS_DEFINE_CLEANUP_FUNCTION0(GBytes*, gs_local_bytes_unref, g_bytes_unref)
GS_DEFINE_CLEANUP_FUNCTION0(GChecksum*, gs_local_checksum_free, g_checksum_free)
GS_DEFINE_CLEANUP_FUNCTION0(GError*, gs_local_free_error, g_error_free)
GS_DEFINE_CLEANUP_FUNCTION0(GHashTable*, gs_local_hashtable_unref, g_hash_table_unref)
GS_DEFINE_CLEANUP_FUNCTION0(GObject*, gs_local_obj_unref, g_object_unref)
GS_DEFINE_CLEANUP_FUNCTION0(GPtrArray*, gs_local_ptrarray_unref, g_ptr_array_unref)
GS_DEFINE_CLEANUP_FUNCTION0(GVariant*, gs_local_variant_unref, g_variant_unref)
GS_DEFINE_CLEANUP_FUNCTION0(GVariantBuilder*, gs_local_variant_builder_unref, g_variant_builder_unref)
GS_DEFINE_CLEANUP_FUNCTION0(GVariantIter*, gs_local_variant_iter_free, g_variant_iter_free)
GS_DEFINE_CLEANUP_FUNCTION0(GRegex*, gs_local_regex_unref, g_regex_unref)
GS_DEFINE_CLEANUP_FUNCTION0(GMatchInfo*, gs_local_match_info_unref, g_match_info_unref)
GS_DEFINE_CLEANUP_FUNCTION0(GKeyFile*, gs_local_key_file_unref, g_key_file_unref)

GS_DEFINE_CLEANUP_FUNCTION(char**, gs_local_strfreev, g_strfreev)
GS_DEFINE_CLEANUP_FUNCTION(void*, gs_local_free, g_free)

#define gs_free __attribute__ ((cleanup(gs_local_free)))
#define gs_unref_object __attribute__ ((cleanup(gs_local_obj_unref)))
#define gs_unref_variant __attribute__ ((cleanup(gs_local_variant_unref)))
#define gs_free_variant_iter __attribute__ ((cleanup(gs_local_variant_iter_free)))
#define gs_unref_variant_builder __attribute__ ((cleanup(gs_local_variant_builder_unref)))
#define gs_unref_array __attribute__ ((cleanup(gs_local_array_unref)))
#define gs_unref_ptrarray __attribute__ ((cleanup(gs_local_ptrarray_unref)))
#define gs_unref_hashtable __attribute__ ((cleanup(gs_local_hashtable_unref)))
#define gs_free_checksum __attribute__ ((cleanup(gs_local_checksum_free)))
#define gs_unref_bytes __attribute__ ((cleanup(gs_local_bytes_unref)))
#define gs_strfreev __attribute__ ((cleanup(gs_local_strfreev)))
#define gs_free_error __attribute__ ((cleanup(gs_local_free_error)))
#define gs_unref_match_info __attribute__ ((cleanup(gs_local_match_info_unref)))
#define gs_unref_regex __attribute__ ((cleanup(gs_local_regex_unref)))
#define gs_key_file_unref __attribute__ ((cleanup(gs_local_key_file_unref)))

G_END_DECLS

#endif
