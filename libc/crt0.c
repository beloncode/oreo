/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/04/27
*/

#include "crt.h"
#include "unistd.h"
#include "stdio.h"
#include "poll.h"

#include "bits/mask.h"

/* Address of the initial code segment */
__attribute__((unused)) extern u64ptr textStart;
/* Address of the end */
__attribute__((unused)) extern u64ptr textEnd;

__attribute__((unused)) extern i32 oMain(i32 argc, int8 **argv);

#define WAIT_FOR_FDS 5000 /* 5 seconds */

static u0 libcBeforeExit(u0) {}

__attribute__((unused)) u0 oLibcStartMain(i32 argc, int8 **argv, __attribute__((unused)) int8 **env,
                                          i32 (*main_callback)(i32, int8 **argv))
{
  libcBeforeExit();

  static struct pollFD stdIOPoll[] = {
    /* Wait until the stdout is ready for write and check for possible errors */
    {STDOUT_FILENO, POLLPRI | POLLOUT},
    /* Check for some data and check for possible errors */
    {STDIN_FILENO,  POLLIN  | POLLPRI}
  };
  #define POOL_COUNT (sizeof(stdIOPoll)/sizeof(struct pollFD))

  i32 pRet = oPoll(stdIOPoll, POOL_COUNT, WAIT_FOR_FDS);
  if (pRet == -1)
    /* A error has occurred */ 
    exit(pRet);

  if (pRet > 0) {
    /* Non-zero poll return indicates that an entry in stdIOPoll as been filled with non-zeros values */
    for (i32 countPoll = 0; countPoll < POOL_COUNT; countPoll++) {
      struct pollFD *test = &stdIOPoll[countPoll];
      i16 request = test->rEvents;
      
      if (TEST_SPECIFIC_BIT(request, (POLLERR | POLLNVAL))) {
        exit(request);
      }
    }
  }

  i32 main_ret = main_callback(argc, argv);

  exit(main_ret);

  /* __builtin_unreachable(); */
}

__asm__(
  ".intel_syntax noprefix\n"
  ".globl oStart\n"
  ".type oStart,@function\n"
  "oStart:\n"
  "xor rax, rax\n"
  "mov edi, [rsp]\n"
  "lea rsi, [rsp+8]\n"
  /* Calculating the effective address of environment variable array list */
  "lea rdx, [rsi+rdi*8]\n"
  "add rdx, 8\n"
  "lea rcx, [oMain + rip]\n"
  "call oLibcStartMain\n"

  /* Unreachable code  */
  "add rax, 1\n"
  "and rax, 2\n"
  "xor rax, rax\n"
  "call rax\n"
  ".att_syntax\n"
);

