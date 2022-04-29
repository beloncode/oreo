/* This code is part of OREO project, all rights reserved to the owners
 * Wrote by: [Gabriel Correia]
 * Create at: 2022/04/27
*/

#include "unistd.h"

#include "crt.h"

#include "arch/systable.h"
#include "arch/asm.h"

#include "stdlib.h"

u0_t
exit
(i32_t code)
{
  if (g_user_exit_handler)
    g_user_exit_handler();

  __syscall1(SYS_EXIT, (u64_t)code);

  __builtin_unreachable();
}

mi64_t
write
(i32_t fd, const u0_t *buf, mu64_t count)
{
  return ((mi64_t)__syscall3(SYS_WRITE, fd, (u64_t)buf, count));
}


