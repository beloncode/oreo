#ifndef ARCH_ASM_SYSCALL_H
#define ARCH_ASM_SYSCALL_H

#include "libc/stddef.h"

static __inline long
__syscall1
(u64_t num, u64_t rdi)
{
  u64_t ret;
  __asm__ __volatile__(
    "syscall"
    : "=a"(ret)
    : "a"(num), "D"(rdi)
    : "rcx", "r11", "memory");
  return ret;
}

#endif


