/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Create at: 2022/05/14
*/

#include "heap.h"

#include "log/trace.h"
#include "libc/unistd.h"

struct block_header* heap_grow(mu64_t size)
{
  struct block_header *user_block = NULL;

  S_TRACE("Growing up the heap chunk");
  
  malloc_int.heap_size += size;
  user_block = O_sbrk(size);
  
  mu64_t *size_ptr = &malloc_int.heap_size;
  *size_ptr += size;

  return user_block;
}

static struct block_header* heap_search_select(struct free_list *list, mu64_t size)
{
  struct block_header* block = (struct block_header*)list;

  if (!list)
    return block;

  mu64_t blk_size = block->blk_size;

  struct block_header *prev = NULL, *next = NULL;

  if (blk_size != size) {
    if (blk_size < size)
      next = heap_search_select(list->next, size);
    else if (blk_size > size)
      prev = heap_search_select(list->prev, size);
  }

  if (next && next->blk_size >= size)
    block = next;
  else if (prev && prev->blk_size >= size)
    block = prev;

  return block;
}

struct block_header* heap_search_block(mu64_t size)
{
  struct block_header *block = NULL;
  struct free_list *list = malloc_int.free_list_heap;
  if (!list)
    return block;
    
  block = heap_search_select(list, size);
  return block;
}

u0_t heap_remove(struct block_header *block)
{
  struct free_list *free = (struct free_list*)block;

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

u0_t heap_add(struct block_header *block)
{
   /* Is the same as block->free_node */
  struct free_list *free = (struct free_list*)block;
  struct free_list **list = &malloc_int.free_list_heap;

  /* Get a block less or equal than the actual block size */
  struct block_header *good_block = heap_search_select(*list, block->blk_size);
  /* 10 > */
  if (!good_block) {
    *list = (struct free_list*)block;
    return;
  }

  struct free_list *last = (struct free_list*)good_block;
  free->prev = last->prev;
  free->next = last;
  last->prev = free;

}

