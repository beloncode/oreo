/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/04/28
*/

#include "stdio.h"
#include "unistd.h"

u0_t __attribute__((noreturn)) __stack_chk_fail(u0_t)
{
  exit(O_puts("Error: stack smashing detected"));
  
}


