/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/04/28
*/

#include "stdio.h"

#define STDIN_FD 1

struct _IO_O_FILE __stdin = {
  .filename = "stdin",
  .fileLock = MUTEX_INIT,
  .fd = STDIN_FD
};

__attribute__((unused)) IOFILE *stdin = &__stdin;


