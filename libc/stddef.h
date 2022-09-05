/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/04/27
*/

#ifndef LIBC_STDDEF_H
#define LIBC_STDDEF_H

#include "stdint.h"
#include "stdbool.h"

#ifndef int8
typedef char int8;
#endif

#ifndef uchar
typedef unsigned char uint8;
#endif

#ifndef NULL
#define NULL ((u0*)0)
#endif

#ifndef u64ptr
typedef unsigned long u64ptr;
#endif

#ifndef mu64_t
typedef unsigned long mu64;
#endif

#ifndef mi64
typedef signed long mi64;
#endif

#ifndef i8
typedef signed char i8;
#endif

#ifndef u8
typedef unsigned char u8;
#endif

/* The maximum bytes that alloca can allocate into the stack */
#define MAX_STACK_ALLOC_SIZE 0x1ff

#ifndef f32
typedef float f32;
#endif

#endif

