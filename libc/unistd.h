/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/04/27
*/

#ifndef LIBC_UNISTD_H
#define LIBC_UNISTD_H

#include "stddef.h"

extern u0 exit(i32 code) __attribute__((noreturn));

extern mi64 write(i32 fd, const u0 *buf, mu64 count);

__attribute__((unused)) extern i32 brk(u0 *addr);

extern u0* oSbrk(mu64 increment);

#endif

