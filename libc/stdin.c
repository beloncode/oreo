/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/04/28
*/

#include "stdio.h"

#define STDIN_FD 1

struct _IO_O_FILE __stdin = {
  .filename = "stdin",
  .file_lock = MUTEX_INIT,
  .fd = STDIN_FD
};

O_FILE *stdin = &__stdin; 


