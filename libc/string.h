/* This code is part of OREO project, all rights reserved to the owners
 * Wrote by: [Gabriel Correia]
 * Create at: 2022/04/27
*/

#ifndef LIBC_STRING_H
#define LIBC_STRING_H

#include "stddef.h"

extern char_t* O_strrchr(const char_t* dest, i32_t character)
  __attribute__((nonnull(1)));

extern char_t* O_strchr(const char_t *dest, i32_t character)
  __attribute__((nonnull(1)));

extern i32_t O_strncmp(const char_t *dest, const char_t *src, mu64_t len);
extern i32_t O_strcmp(const char_t *dest, const char_t *src);

extern mu64_t O_strlen(const char_t *dest);
extern u0_t* O_memmove (u0_t *dest, const u0_t *src, mu64_t num);
extern u0_t* O_memcpy(u0_t *dest, u0_t *src, mu64_t num);
extern u0_t* O_memset(u0_t *dest, i32_t constant, mu64_t num);

#endif


