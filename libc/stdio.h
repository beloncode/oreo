/* This code is part of OREO project, all rights reserved to the owners
 * Wrote by: [Gabriel Correia]
 * Create at: 2022/04/28
*/

#ifndef LIBC_STDIO_H
#define LIBC_STDIO_H

#include "stddef.h"
#include "mutex.h"

typedef struct _IO_O_FILE {
  const char_t *filename;
  /* Secure lock test-and-set for protect from race condition */
  mutex_t file_lock;
  /* Associated file descriptor with the FILE structure */
  i32_t fd;
} O_FILE;

/* Captured std IO files */
extern O_FILE *stdin;
extern O_FILE *stdout;

extern mu64_t O_fwrite(const u0_t *ptr, mu64_t size, mu64_t nmemb, O_FILE *stream);

extern i32_t O_fputs(const char_t *str, O_FILE *stream);
extern i32_t O_fputc(i32_t ch, O_FILE *stream);

#define STDOUT_FILENO 0
#define STDIN_FILENO  1

#define EOF -1

#define __STATIC_O_FILENO(stream)\
  stream->fd

extern i32_t O_fileno(const O_FILE *stream);

#endif

