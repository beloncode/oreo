/* This code is part of OREO project, all rights reserved to the owners
 * Wrote by: [Gabriel Correia]
 * Create at: 2022/04/28
*/

#include "stdio.h"

#define STDIN_FD 1

struct _IO_O_FILE __stdin = {
  .filename = "stdin",
  .file_lock = MUTEX_INIT,
  .fd = STDIN_FD
};

O_FILE *stdin = &__stdin; 


