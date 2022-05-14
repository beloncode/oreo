/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/05/14
*/

#ifndef HEAP_HEAP_H
#define HEAP_HEAP_H

#include "malloc_int.h"

extern struct block_header* heap_grow(mu64_t size);

extern struct block_header* heap_search_block(mu64_t size);

extern u0_t heap_remove(struct block_header *block);

extern u0_t heap_add(struct block_header *block);

#endif
