/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/05/14
*/

#ifndef HEAP_HEAP_H
#define HEAP_HEAP_H

#include "mallocInt.h"

__attribute__((unused)) extern struct blockHeader* heapGrow(mu64 size);

__attribute__((unused)) extern struct blockHeader* heapSearchBlock(mu64 size);

__attribute__((unused)) extern u0 heapRemove(struct blockHeader *block);

__attribute__((unused)) extern u0 heapAdd(struct blockHeader *block);

#endif
