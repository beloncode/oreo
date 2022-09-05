/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/05/06
*/

#ifndef HEAP_MALLOC_INT_H
#define HEAP_MALLOC_INT_H

#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/mutex.h"

struct freeList
{
  struct freeList *prev, *next;
};

struct blockHeader
{
  struct freeList freeNode;

  mu64 blkSize;
  bool blkInUse;
  /* Pointer received by the user as the malloc result */
  u0 *blkPtr;
};

struct mallocIntHeader
{
  mutex_t mallocMutex;
  u0 *baseAddress;
  struct freeList *freeListHeap;
  mu64 heapSize;
};

extern struct mallocIntHeader mallocIntHeader;

__attribute__((unused)) extern u0* oMalloc(mu64 size);
__attribute__((unused)) extern u0 oFree(u0 *ptr);

#endif
