/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/04/27
*/

#include "unistd.h"

#include "arch/asm.h"

#include "stdlib.h"

u0 exit(i32 code)
{
  if (gUserExitHandler) {
    gUserExitHandler();
  }

  __syscall1(SYS_EXIT, (u64)code);

  __builtin_unreachable();
}

mi64 write(i32 fd, const u0 *buf, mu64 count)
{
  return (mi64)__syscall3(SYS_WRITE, fd, (u64)buf, count);
}

#define DO_BRK(value) __syscall1(SYS_BRK, (u64)(value))

__attribute__((unused)) i32 brk(u0 *addr)
{
  return !DO_BRK(addr);
}

/* Increment the program data segment */
u0* oSbrk(mu64 increment)
{
  u64 brkAddr = DO_BRK(0);
  u64 newBrk = brkAddr + increment;
  DO_BRK(newBrk);
  return (u0*)brkAddr;
}

