/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Create at: 2022/05/14
*/

#include "heap.h"

#include "log/trace.h"
#include "libc/unistd.h"

__attribute__((unused)) struct blockHeader* heapGrow(mu64 size)
{
  struct blockHeader *userBlock = NULL;

  S_TRACE("Growing up the heap chunk");

  mallocIntHeader.heapSize += size;
  userBlock = oSbrk(size);
  
  mu64 *sizePtr = &mallocIntHeader.heapSize;
  *sizePtr += size;

  return userBlock;
}

static struct blockHeader* heapSearchSelect(struct freeList *list, mu64 size)
{
  struct blockHeader* block = (struct blockHeader*)list;

  if (!list)
    return block;

  mu64 blkSize = block->blkSize;

  struct blockHeader *prev = NULL, *next = NULL;

  if (blkSize != size) {
    if (blkSize < size)
      next = heapSearchSelect(list->next, size);
    else if (blkSize > size)
      prev = heapSearchSelect(list->prev, size);
  }

  if (next && next->blkSize >= size)
    block = next;
  else if (prev && prev->blkSize >= size)
    block = prev;

  return block;
}

__attribute__((unused)) struct blockHeader* heapSearchBlock(mu64 size)
{
  struct blockHeader *block = NULL;
  struct freeList *list = mallocIntHeader.freeListHeap;
  if (!list)
    return block;
   
  block = heapSearchSelect(list, size);
  return block;
}

__attribute__((unused)) u0 heapRemove(struct blockHeader *block)
{
  struct freeList *free = (struct freeList*)block;

  if (free->prev)
    /* free->prev->next == free; */
    free->prev->next = free->next;
    /* [BLK 1]-><-[BLK 2]-><-[BLK 3]-><-[BLK 4]*/
    /* To remove 3 block */
    /* [BLK 3]->{BLK 2}->{BLK 3} = [BLK 3]->{BLK 4} */
  if (free->next)
  /* [BLK 3]->{BLK 4}->{BLK 3} = [BLK 3]->{BLK 2} */
    free->next->prev = free->prev;
}

__attribute__((unused)) u0 heapAdd(struct blockHeader *block)
{
   /* Is the same as block->freeNode */
  struct freeList *free = (struct freeList*)block;
  struct freeList **list = &mallocIntHeader.freeListHeap;

  /* Get a block less or equal than the actual block size */
  struct blockHeader *good_block = heapSearchSelect(*list, block->blkSize);
  /* 10 > */
  if (!good_block) {
    *list = (struct freeList*)block;
    return;
  }

  struct freeList *last = (struct freeList*)good_block;
  free->prev = last->prev;
  free->next = last;
  last->prev = free;

}

