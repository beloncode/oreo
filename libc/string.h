/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/04/27
*/

#ifndef LIBC_STRING_H
#define LIBC_STRING_H

#include "stddef.h"

__attribute__((unused)) extern int8* oStrrchr(const int8* dest, i32 character)
  __attribute__((nonnull(1)));

extern int8* oStrchr(const int8 *dest, i32 character)
  __attribute__((nonnull(1)));

extern i32 oStrncmp(const int8 *dest, const int8 *src, mu64 len);
extern i32 oStrCmp(const int8 *dest, const int8 *src);

extern mu64 oStrlen(const int8 *dest);

__attribute__((unused)) extern u0* oMemMove(u0 *dest, const u0 *src, mu64 num);
extern u0* oMemCpy(u0 *dest, u0 *src, mu64 num);
extern u0* oMemset(u0 *dest, i32 constant, mu64 num);

#endif


