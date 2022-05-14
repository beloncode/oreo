/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/05/06
*/

#include "malloc_int.h"

#include "libc/stdio.h"
#include "libc/string.h"
#include "libc/branch.h"

#include "log/trace.h"

#include "heap.h"

/* Calculate the correctly alignment from the machine architecture 
 * This function shouldn't be exported to the binary image file
*/
static inline mu64_t aling_size(mu64_t size)
{
  /* https://developer.ibm.com/articles/pa-dalign/ */
  /* Aling to 8 bytes block for better use the memory access granularity from the CPU,
   * and help for avoid performance penality
  */
  return (sizeof (u0_t*) + size - 1) & ~(sizeof (u0_t*) - 1);
}

struct malloc_int_header malloc_int = {
  .malloc_mutex = MUTEX_INIT,
  .base_address = NULL,
  .free_list_heap = NULL,
  .heap_size = 0
};

static struct block_header* malloc_request_memory(mu64_t size)
{
  struct block_header *user_block = NULL;
  
  struct block_header *block = heap_search_block(size);
  if (block) {
    heap_remove(block);
    O_memset(&block->free_node, 0, sizeof (struct free_list));
    block->blk_inuse = true;
  }
  user_block = block;

  return user_block ? user_block : heap_grow(size);
}

u0_t* O_malloc(mu64_t size)
{
  MUTEX_LOCK(&malloc_int.malloc_mutex);

#define BLK_HEADER_SIZE sizeof (struct block_header)

  mu64_t need_size = aling_size(BLK_HEADER_SIZE + size); 
 
  struct block_header *block = NULL;
  
  block = malloc_request_memory(need_size);

  block->blk_size = need_size;
  block->blk_ptr = ((u8_t*)block) + BLK_HEADER_SIZE;
  O_memset(&block->free_node, 0, sizeof (struct free_list));

  block->blk_inuse = true;

  MUTEX_UNLOCK(&malloc_int.malloc_mutex);

  return block->blk_ptr;
}

u0_t O_free(u0_t *ptr)
{
  MUTEX_LOCK(&malloc_int.malloc_mutex);

  struct block_header *block = (struct block_header*)((u8_t*)ptr - BLK_HEADER_SIZE);
  if (!ptr)
    return;
  
  if (block->blk_inuse == false)
    exit(O_puts("Double free detected, you can't free a memory area that's alredy be freeded"));
  
  block->blk_inuse = false;
  heap_add(block);

  MUTEX_UNLOCK(&malloc_int.malloc_mutex);
}

#undef BLK_HEADER_SIZE

