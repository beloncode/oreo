/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/04/27
*/

#include "fatal.h"

#include "libc/stdio.h"
#include "libc/unistd.h"

u0_t fatal_error(const char_t *fmt, ...)
{
  exit(O_puts("A fatal error has ocurred"));

}

