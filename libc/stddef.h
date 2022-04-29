/* This code is part of OREO project, all rights reserved to the owners
 * Wrote by: [Gabriel Correia]
 * Create at: 2022/04/27
*/

#ifndef LIBC_STDDEF_H
#define LIBC_STDDEF_H

#include "stdint.h"

#ifndef char_t
typedef char char_t;
#endif

#ifndef uchar_t
typedef unsigned char uchar_t;
#endif

#ifndef NULL
#define NULL ((u0_t*)0)
#endif

#ifndef u64ptr_t
typedef unsigned long u64ptr_t;
#endif

#ifndef mu64_t
typedef unsigned long mu64_t;
#endif

#ifndef mi64_t
typedef signed long mi64_t;
#endif

#endif

