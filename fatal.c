/* This code is part of OREO project, all rights reserved to the owners
 * Wrote by: [Gabriel Correia]
 * Create at: 2022/04/27
*/

#include "fatal.h"

#include "libc/unistd.h"

u0_t
fatal_error
(const char_t *fmt, ...)
{
  exit(1);

}

