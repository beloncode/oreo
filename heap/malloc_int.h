/* This code is part of OREO project, all rights reserved to the owners
 * Wrote by: [Gabriel Correia]
 * Create at: 2022/05/06
*/

#ifndef HEAP_MALLOC_INT_H
#define HEAP_MALLOC_INT_H

#include "libc/stddef.h"

extern u0_t* O_malloc(mu64_t size);

extern u0_t O_free(u0_t *ptr);

#endif
