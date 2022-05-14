/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/04/28
*/

#include "mutex.h"
#include "unistd.h"

#if __clang__
u0_t (*g_user_exit_handler)(u0_t) = NULL;
#else
volatile u0_t (*g_user_exit_handler)(u0_t) = NULL;
#endif

static mutex_t lock = MUTEX_INIT;

u0_t O_atexit(u0_t (*reg_callback)(u0_t))
{
  MUTEX_LOCK(&lock);
  g_user_exit_handler = reg_callback;
  MUTEX_UNLOCK(&lock);
}
