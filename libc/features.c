/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/04/28
*/

#include "stdio.h"
#include "unistd.h"

__attribute__((unused)) u0 __attribute__((noreturn)) __stack_chk_fail(u0)
{
  exit(oPuts("Error: stack smashing detected"));
  
}


