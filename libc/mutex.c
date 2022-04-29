/* This code is part of OREO project, all rights reserved to the owners
 * Wrote by: [Gabriel Correia]
 * Create at: 2022/04/28
*/

#include "libc/mutex.h"

static i32_t
__test_and_set
(mutex_t *lock)
{
  i32_t def_lock = *lock;
  *lock = 1;
  return (def_lock);
}

u0_t
_mutex_lock
(mutex_t *lock_address)
{
  while (__test_and_set(lock_address) == 1);
}

u0_t
_mutex_unlock
(mutex_t *lock_address)
{
  *lock_address = 0;
}
