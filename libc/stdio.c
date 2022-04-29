/* This code is part of OREO project, all rights reserved to the owners
 * Wrote by: [Gabriel Correia]
 * Create at: 2022/04/28
*/

#include "stdio.h"

#include "unistd.h"

mu64_t 
O_fwrite
(const u0_t *ptr, mu64_t size, mu64_t nmemb, O_FILE *stream)
{
  MUTEX_LOCK(&stream->file_lock);
  
  mu64_t writed = 0;

  for (mu64_t i_loop = 0; i_loop < nmemb; i_loop++) {
    writed += write(stream->fd, ptr, size);
  }
  MUTEX_UNLOCK(&stream->file_lock);

  return (writed);  
}

