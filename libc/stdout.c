/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/04/28
*/

#include "stdio.h"

#define STDOUT_FD 0

struct _IO_O_FILE __stdout = {
  .filename = "stdout",
  .file_lock = MUTEX_INIT,
  .fd = STDOUT_FD
};

O_FILE *stdout = &__stdout; 
