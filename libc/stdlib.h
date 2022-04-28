/* This code is part of OREO project, all rights reserved to the owners
 * Wrote by: [Gabriel Correia]
 * Create at: 2022/04/28
*/

#ifndef LIBC_STDLIB_H
#define LIBC_STDLIB_H

#include "stddef.h"

extern u0_t (*g_user_exit_handler)(u0_t);

extern u0_t O_atexit (u0_t (*reg_callback)(u0_t));

#endif


