/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/04/27
*/

#ifndef FATAL_H
#define FATAL_H

#include "libc/stddef.h"

extern u0_t fatal_error(const char_t *fmt, ...) __attribute__((noreturn));

#endif


