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
