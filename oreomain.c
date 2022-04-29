/* This code is part of OREO project, all rights reserved to the owners
 * Wrote by: [Gabriel Correia]
 * Create at: 2022/04/27
*/

#include "libc/stddef.h"
#include "libc/stdio.h"

i32_t
O_main
(u0_t)
{
  const char_t hello[] = "Hello world\n";
  O_fwrite(hello, sizeof(hello), 10, stdout);

  return (0);
}


