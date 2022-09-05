/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/04/27
*/

#include "fatal.h"

#include "libc/stdio.h"
#include "libc/unistd.h"

__attribute__((unused)) u0 fatalError(__attribute__((unused)) const int8 *fmt, ...)
{
  exit(oPuts("A fatal error has occurred"));

}

