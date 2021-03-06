/* go-string-to-int-array.c -- convert a string to an array of ints in Go.

   Copyright 2010 The Go Authors. All rights reserved.
   Use of this source code is governed by a BSD-style
   license that can be found in the LICENSE file.  */

#include "go-alloc.h"
#include "go-string.h"
#include "array.h"
#include "runtime.h"
#include "malloc.h"

struct __go_open_array
__go_string_to_int_array (struct __go_string str)
{
  size_t c;
  const unsigned char *p;
  const unsigned char *pend;
  uint32_t *data;
  uint32_t *pd;
  struct __go_open_array ret;

  c = 0;
  p = str.__data;
  pend = p + str.__length;
  while (p < pend)
    {
      int rune;

      ++c;
      p += __go_get_rune (p, pend - p, &rune);
    }

  data = (uint32_t *) runtime_mallocgc (c * sizeof (uint32_t), RefNoPointers,
					1, 0);
  p = str.__data;
  pd = data;
  while (p < pend)
    {
      int rune;

      p += __go_get_rune (p, pend - p, &rune);
      *pd++ = rune;
    }

  ret.__values = (void *) data;
  ret.__count = c;
  ret.__capacity = c;
  return ret;
}
