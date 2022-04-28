
#include "unistd.h"

u0_t __attribute__((noreturn))
__stack_chk_fail
(u0_t)
{
  exit(10);
}


