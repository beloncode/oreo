/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/04/30
*/

#ifndef LIBC_ALLOCA_H
#define LIBC_ALLOCA_H

#include "branch.h"
#include "string.h"

#ifndef alloca
#define alloca __builtin_alloca
#endif

#endif
