/* This code is part of OREO project, all rights reserved to the owners
 * Wrote by: [Gabriel Correia]
 * Create at: 2022/04/27
*/

#include "libc/stddef.h"
#include "libc/stdio.h"
#include "libc/string.h"

i32_t
O_main
(u0_t)
{
  const char_t hello[] = "Hello world\n";
  O_fputs(hello, stdout);

  return (0);
}


