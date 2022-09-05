/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/04/28
*/

#include "mutex.h"

#if __clang__
u0 (*gUserExitHandler)(u0) = NULL;
#else
volatile u0 (*gUserExitHandler)(u0) = NULL;
#endif

static mutex_t lock = MUTEX_INIT;

__attribute__((unused)) u0 oAtExit(u0 (*regCallback)(u0))
{
  MUTEX_LOCK(&lock);
  gUserExitHandler = regCallback;
  MUTEX_UNLOCK(&lock);
}
