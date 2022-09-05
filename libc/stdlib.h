/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/04/28
*/

#ifndef LIBC_STDLIB_H
#define LIBC_STDLIB_H

#include "stddef.h"

extern u0 (*gUserExitHandler)(u0);

__attribute__((unused)) extern u0 oAtExit(u0 (*regCallback)(u0));

#endif


