/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/05/03
*/

#ifndef LIBM_DIFF_H
#define LIBM_DIFF_H

#include "libc/stddef.h"

__inline mu64 oMin(mu64 x, mu64 y)
{
  return x > y ? y : x;
}

#endif
