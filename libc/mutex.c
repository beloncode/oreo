/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/04/28
*/

#include "libc/mutex.h"

static i32 testAndSet(mutex_t *lock)
{
  i32 defLock = *lock;
  *lock = 1;
  return defLock;
}

u0 mutexLock(mutex_t *lockAddress)
{
  while (testAndSet(lockAddress) == 1);
}

u0 mutexUnlock(mutex_t *lockAddress)
{
  *lockAddress = 0;
}
