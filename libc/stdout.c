/* This code is part of OREO project, all rights reserved to the owners
 * Wrote by: [Gabriel Correia]
 * Create at: 2022/04/28
*/

#include "stdio.h"

#define STDOUT_FD 0

struct _IO_O_FILE __stdout = {
  .filename = "stdout",
  .file_lock = MUTEX_INIT,
  .fd = STDOUT_FD
};

O_FILE *stdout = &__stdout; 
