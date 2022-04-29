/* This code is part of OREO project, all rights reserved to the owners
 * Wrote by: [Gabriel Correia]
 * Create at: 2022/04/28
*/

#include "stdio.h"
#include "unistd.h"

#include "branch.h"

mu64_t 
O_fwrite
(const u0_t *ptr, mu64_t size, mu64_t nmemb, O_FILE *stream)
{
  MUTEX_LOCK(&stream->file_lock);

  unlikely (stream == NULL || ptr == NULL)
    return (-1);
  
  mu64_t writed = 0;

  for (mu64_t i_loop = 0; i_loop < nmemb; i_loop++) {
    writed += write(stream->fd, ptr, size);
  }
  MUTEX_UNLOCK(&stream->file_lock);

  return (writed);  
}

/* Returns the file descriptor associated with the O_FILE IO structure */
i32_t
O_fileno
(const O_FILE *stream)
{
  unlikely (stream == NULL)
    return (-1);
  return (__STATIC_O_FILENO(stream));
}
