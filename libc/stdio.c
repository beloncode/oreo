/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/04/28
*/

#include "stdio.h"
#include "unistd.h"

#include "branch.h"

#include "string.h"

mu64 oFWrite(const u0 *ptr, mu64 size, mu64 nmemb, IOFILE *stream)
{
  MUTEX_LOCK(&stream->fileLock);

  unlikely (stream == NULL || ptr == NULL)
    return -1;
  
  mu64 wrote = 0;

  for (mu64 i_loop = 0; i_loop < nmemb; i_loop++) {
    wrote += write(stream->fd, ptr, size);
  }
  MUTEX_UNLOCK(&stream->fileLock);

  return wrote;
}

/* Returns the file descriptor associated with the IOFILE IO structure */
__attribute__((unused)) i32 oFileno(const IOFILE *stream)
{
  unlikely (stream == NULL)
    return -1;
  return __STATIC_O_FILENO(stream);
}

__attribute__((unused)) i32 oFPutc(i32 ch, IOFILE *stream)
{
  i32 ret = -1;
  unlikely (stream == NULL)
    return ret;
  if (oFWrite((int8 *) &ch, sizeof(char), 1, stream) != EOF)
    ret = ch;

  return ret; 
}

i32 oFPuts(const int8 *str, IOFILE *stream)
{
  unlikely (stream == NULL)
    return -1;
  i32 wrote = (i32)oFWrite(str, oStrlen(str), 1, stream);
  wrote += (i32)oFWrite("\n", 1, 1, stream);
  return wrote;
}

i32 oPuts(const int8 *str)
{
  return oFPuts(str, stdout);
}
