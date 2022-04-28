/* This code is part of OREO project, all rights reserved to the owners
 * Wrote by: [Gabriel Correia]
 * Create at: 2022/04/27
*/

#include "crt.h"
#include "unistd.h"
#include "stdlib.h"

/* Address of the initial code segment */
extern u64ptr_t __text__start;
/* Addres of the end */
extern u64ptr_t __text_end;

extern i32_t O_main(i32_t, char_t**);

u0_t
__libc_before_exit
(u0_t)
{
}

u0_t
O__libc_start_main
(i32_t argc, char_t **argv, char_t **env,
 i32_t (*main_callback)(i32_t, char_t **argv))
{

  i32_t main_ret = main_callback(argc, argv);
  O_atexit(__libc_before_exit);

  exit(main_ret);

  __builtin_unreachable();
}

__asm__(
  ".intel_syntax noprefix\n"
  ".globl O_start\n"
  ".type O_start,@function\n"
  "O_start:\n"
  "xor rax, rax\n"
  "mov edi, [rsp]\n"
  "lea rsi, [rsp+8]\n"
  /* Calculating the effective address of environment variable array list */
  "lea rdx, [rsi+rdi*8]\n"
  "add rdx, 8\n"
  "lea rcx, [O_main + rip]\n"
  "call O__libc_start_main\n"

  /* Unreachable code  */
  "add rax, 1\n"
  "and rax, 2\n"
  "xor rax, rax\n"
  "call rax\n"
  ".att_syntax\n"
);

