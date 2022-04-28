/* This code is part of OREO project, all rights reserved to the owners
 * Wrote by: [Gabriel Correia]
 * Create at: 2022/04/28
*/

#include "mutex.h"
#include "unistd.h"

u0_t (*g_user_exit_handler)(u0_t) = NULL;

static mutex_t lock = MUTEX_INIT;

u0_t
O_atexit
(u0_t (*reg_callback)(u0_t))
{
  MUTEX_LOCK(&lock);
  g_user_exit_handler = reg_callback;
  MUTEX_UNLOCK(&lock);
}

