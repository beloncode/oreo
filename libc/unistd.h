/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/04/27
*/

#ifndef LIBC_UNISTD_H
#define LIBC_UNISTD_H

#include "stddef.h"

extern u0_t exit(i32_t code) __attribute__((noreturn));

extern mi64_t write(i32_t fd, const u0_t *buf, mu64_t count);

extern i32_t brk(u0_t *addr);

extern u0_t* O_sbrk(mu64_t increment);

#endif

