/* This code is part of OREO project, all rights reserved to the owners
 * Wrote by: [Gabriel Correia]
 * Create at: 2022/04/28
*/

#include "unistd.h"

u0_t __attribute__((noreturn))
__stack_chk_fail
(u0_t)
{
  exit(10);
}


