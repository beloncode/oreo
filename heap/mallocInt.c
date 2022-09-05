/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/05/06
*/

#include "mallocInt.h"

#include "libc/stdio.h"
#include "libc/string.h"
#include "libc/branch.h"

#include "log/trace.h"

#include "heap.h"

/* Calculate the correct alignment from the machine architecture
 * This function shouldn't be exported to the binary image file
*/
static inline mu64 alignSize(mu64 size)
{
  /* https://developer.ibm.com/articles/pa-dalign/ */
  /* Align to 8 bytes block for better use the memory access granularity from the CPU,
   * and help for avoid performance issues
  */
  return (sizeof(u0*) + size - 1) & ~(sizeof(u0*) - 1);
}

static struct blockHeader* mallocRequestMemory(mu64 size)
{
  struct blockHeader *user_block = NULL;
  
  struct blockHeader *block = heapSearchBlock(size);
  if (block) {
    heapRemove(block);
    oMemset(&block->freeNode, 0, sizeof(struct freeList));
    block->blkInUse = true;
  }
  user_block = block;

  return user_block ? user_block : heapGrow(size);
}

__attribute__((unused)) u0* oMalloc(mu64 size)
{
  MUTEX_LOCK(&mallocIntHeader.mallocMutex);

#define BLK_HEADER_SIZE sizeof (struct blockHeader)

  mu64 needSize = alignSize(BLK_HEADER_SIZE + size);
 
  struct blockHeader *block = NULL;
  
  block = mallocRequestMemory(needSize);

  block->blkSize = needSize;
  block->blkPtr = ((u8*)block) + BLK_HEADER_SIZE;
  oMemset(&block->freeNode, 0, sizeof(struct freeList));
  block->blkInUse = true;
  MUTEX_UNLOCK(&mallocIntHeader.mallocMutex);
  return block->blkPtr;
}

__attribute__((unused)) u0 oFree(u0 *ptr)
{
  MUTEX_LOCK(&mallocIntHeader.mallocMutex);

  struct blockHeader *block = (struct blockHeader*)((u8*)ptr - BLK_HEADER_SIZE);
  if (!ptr)
    return;
  if (block->blkInUse == false)
    exit(oPuts("Double free detected, you can't free a memory area that's already be freed"));

  block->blkInUse = false;
  heapAdd(block);

  MUTEX_UNLOCK(&mallocIntHeader.mallocMutex);
}

#undef BLK_HEADER_SIZE

struct mallocIntHeader mallocIntHeader = {
  .mallocMutex = MUTEX_INIT,
  .baseAddress = NULL,
  .freeListHeap = NULL,
  .heapSize = 0
};
