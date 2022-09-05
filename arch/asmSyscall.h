/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/04/27
*/

#ifndef ARCH_ASM_SYSCALL_H
#define ARCH_ASM_SYSCALL_H

#include "libc/stddef.h"

static __inline u64 __syscall1(u64 num, u64 rdi)
{
  u64 ret;
  __asm__ __volatile__("syscall" : "=a"(ret) : "a"(num), "D"(rdi)
    : "rcx", "r11", "memory"
  );
  return ret;
}

static __inline u64 __syscall3(u64 num, u64 rdi, u64 rsi, u64 rdx)
{
  u64 ret;
  __asm__ __volatile__("syscall" : "=a"(ret) : "a"(num), "D"(rdi), "S"(rsi), "d"(rdx)
    : "rcx", "r11", "memory"
  );
  return ret;
}

#endif

