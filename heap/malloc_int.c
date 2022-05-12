/* This code is part of OREO project, all rights reserved to the owners
 * Wrote by: [Gabriel Correia]
 * Create at: 2022/05/06
*/

#include "malloc_int.h"

#include "libc/stdio.h"
#include "libc/unistd.h"
#include "libc/mutex.h"
#include "libc/branch.h"

/* Calculate the correctly alignment from the machine architecture 
 * This function shouldn't be exported to the binary image file
*/
static __inline mu64_t
aling_memory_block
(mu64_t size)
{
  /* https://developer.ibm.com/articles/pa-dalign/ */
  /* Aling to 8 bytes block for better use the memory access granularity from the CPU,
   * and help for avoid performance penality
  */
  return ((sizeof (u0_t*) + size - 1) & ~(sizeof (u0_t*) - 1));
}

struct malloc_int_header
{
  mutex_t malloc_mutex;
  u0_t *base_address;
  mu64_t malloc_chunk_size;
  mu64_t malloc_size;

} malloc_int = {
  .malloc_mutex = MUTEX_INIT,
  .base_address = NULL
};

struct block_header 
{
  mu64_t blk_size;
  bool_t blk_inuse;

  struct block_header *next;

  u0_t *blk_ptr;
};


u0_t*
O_malloc
(mu64_t size)
{
  MUTEX_LOCK(&malloc_int.malloc_mutex);
  u0_t **ba_ptr = &malloc_int.base_address;

#define BLK_HEADER_SIZE sizeof (struct block_header)

  mu64_t need_size = aling_memory_block(BLK_HEADER_SIZE + size); 
 
  struct block_header *block = NULL;
  
  if (!*ba_ptr) {
    *ba_ptr = O_sbrk(need_size);
    block = *ba_ptr;
  }

  block->blk_size = need_size;
  block->blk_ptr = ((u8_t*)block) + BLK_HEADER_SIZE;

  /* It's know the next block location */
  block->next = (struct block_header*)((u8_t*)block + block->blk_size);

  block->blk_inuse = true;

  MUTEX_UNLOCK(&malloc_int.malloc_mutex);

  return (block->blk_ptr);
}

u0_t
O_free
(u0_t *ptr)
{
  struct block_header *block = (struct block_header*)((u8_t*)ptr - BLK_HEADER_SIZE);
  if (ptr) {
    if (block->blk_inuse) {

      block->blk_inuse = false;

    } else {
      exit(O_puts("Double free detected, you can't free a memory area that's alredy be freeded"));
    }
  }
}

#undef BLK_HEADER_SIZE

