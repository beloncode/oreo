/* This code is part of OREO project, all rights reserved to the owners
 * Wrote by: [Gabriel Correia]
 * Create at: 2022/04/27
*/

#ifndef FATAL_H
#define FATAL_H

#include "libc/stddef.h"

extern u0_t fatal_error(const char_t *fmt, ...) __attribute__((noreturn));

#endif


