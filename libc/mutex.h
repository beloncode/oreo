#ifndef LIBC_MUTEX_H
#define LIBC_MUTEX_H

/* This mutex implementation is based on Test-and-set */

#include "libc/stddef.h"

#define MUTEX_INIT 0

typedef volatile _Atomic i32_t mutex_t;

extern u0_t _mutex_lock(mutex_t *lock_address);

extern u0_t _mutex_unlock(mutex_t *lock_address);

#define MUTEX_LOCK(mutex)\
  _mutex_lock(mutex)

#define MUTEX_UNLOCK(mutex)\
  _mutex_unlock(mutex)

#endif


