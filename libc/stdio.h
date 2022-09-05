/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/04/28
*/

#ifndef LIBC_STDIO_H
#define LIBC_STDIO_H

#include "stddef.h"
#include "malloc.h"
#include "mutex.h"

typedef struct _IO_O_FILE
{
  const int8 *filename;
  /* Secure lock test-and-set for protect from race condition */
  mutex_t fileLock;
  /* Associated file descriptor with the FILE structure */
  i32 fd;
} IOFILE;

/* Captured std IO files */
__attribute__((unused)) extern IOFILE *stdin;
extern IOFILE *stdout;

extern mu64 oFWrite(const u0 *ptr, mu64 size, mu64 nmemb, IOFILE *stream);

extern i32 oFPuts(const int8 *str, IOFILE *stream);
extern i32 oPuts(const int8 *str);

__attribute__((unused)) extern i32 oFPutc(i32 ch, IOFILE *stream);

#define STDOUT_FILENO 0
#define STDIN_FILENO  1

#define EOF (-1)

#define __STATIC_O_FILENO(stream)\
  stream->fd

__attribute__((unused)) extern i32 oFileno(const IOFILE *stream);

#endif

