/* This code is part of OREO project, all rights reserved to the owners
 * Wrote by: [Gabriel Correia]
 * Create at: 2022/04/30
*/

#ifndef LIBC_ALLOCA_H
#define LIBC_ALLOCA_H

#include "branch.h"
#include "string.h"

#ifndef alloca
#define alloca __builtin_alloca
#endif

#endif
