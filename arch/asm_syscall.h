/* This code is part of OREO project, all rights reserved to the owners
 * Wrote by: [Gabriel Correia]
 * Create at: 2022/04/27
*/

#ifndef ARCH_ASM_SYSCALL_H
#define ARCH_ASM_SYSCALL_H

#include "libc/stddef.h"

static __inline u64_t
__syscall1
(u64_t num, u64_t rdi)
{
  u64_t ret;
  __asm__ __volatile__("syscall" : "=a"(ret) : "a"(num), "D"(rdi)
    : "rcx", "r11", "memory"
  );
  return (ret);
}

static __inline u64_t
__syscall3
(u64_t num, u64_t rdi, u64_t rsi, u64_t rdx)
{
  u64_t ret;
  __asm__ __volatile__("syscall" : "=a"(ret) : "a"(num), "D"(rdi), "S"(rsi), "d"(rdx)
    : "rcx", "r11", "memory");
  return (ret);
}

#endif

