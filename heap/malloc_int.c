/* This code is part of OREO project, all rights reserved to the owners
 * Wrote by: [Gabriel Correia]
 * Create at: 2022/05/06
*/

#include "malloc_int.h"

#include "libc/stdio.h"
#include "libc/unistd.h"
#include "libc/mutex.h"
#include "libc/branch.h"

#include "log/trace.h"

/* Calculate the correctly alignment from the machine architecture 
 * This function shouldn't be exported to the binary image file
*/
static inline mu64_t
aling_memory_block
(mu64_t size)
{
  /* https://developer.ibm.com/articles/pa-dalign/ */
  /* Aling to 8 bytes block for better use the memory access granularity from the CPU,
   * and help for avoid performance penality
  */
  return ((sizeof (u0_t*) + size - 1) & ~(sizeof (u0_t*) - 1));
}

struct free_list
{
  struct free_list *next;
};

struct block_header 
{
  struct free_list *free_node;

  mu64_t blk_size;
  bool_t blk_inuse;
  struct block_header *prev, *next;

  /* Pointer received by the user as the malloc result */
  u0_t *blk_ptr;
};

struct malloc_int_header
{
  mutex_t malloc_mutex;
  u0_t *base_address;
  struct block_header *head, *tail;
  struct free_list *free_block_list;

  mu64_t heap_size;

} malloc_int = {
  .malloc_mutex = MUTEX_INIT,
  .base_address = NULL,
  .head = NULL,
  .tail = NULL,
  .free_block_list = NULL,
  .heap_size = 0
};

#define foreach_free_list(node, head)\
  for (node = head; node != NULL; node = node->next)

static __inline u0_t
malloc_free_list_push
(struct block_header *block)
{
  struct free_list **head_ptr = &malloc_int.free_block_list;
  block->free_node = *head_ptr;
  *head_ptr = (struct free_list*)block;
}

static struct block_header*
malloc_heap_grow
(mu64_t size)
{
  struct block_header *user_block = NULL;

  S_TRACE("Growing up the heap chunk");
  
  malloc_int.heap_size += size;
  user_block = O_sbrk(size);
  
  mu64_t *size_ptr = &malloc_int.heap_size;
  *size_ptr += size;
  
  struct block_header **head_ptr = &malloc_int.head;
  struct block_header **tail_ptr = &malloc_int.tail;

  /* It's know the next block location */
  if (!*head_ptr) {
    *tail_ptr = *head_ptr = user_block;
  } else {
    user_block->prev = *tail_ptr;
    (*tail_ptr)->next = user_block;
    *tail_ptr = user_block;
  }

  return (user_block);
}

static struct block_header*
malloc_request_memory
(mu64_t size)
{
  struct block_header *user_block = NULL;
  struct free_list *free, *last = NULL,
    **list_ptr = &malloc_int.free_block_list;

  foreach_free_list (free, *list_ptr) {
    struct block_header *block = (struct block_header*)free;

    if (block->blk_size < size) {
      /* Update the last free node pointer and go to the next */
      last = free;
      continue;
    }

    /* Remove the actual pointer from the free-list linked list */
    if (last != NULL)
      last->next = free->next;
    else
      *list_ptr = free->next;
    
    block->free_node = NULL;
    block->blk_inuse = true;

    user_block = block;
    break;
  }

  return (user_block ? user_block : malloc_heap_grow(size));
}
#undef foreach_free_list

u0_t*
O_malloc
(mu64_t size)
{
  MUTEX_LOCK(&malloc_int.malloc_mutex);

#define BLK_HEADER_SIZE sizeof (struct block_header)

  mu64_t need_size = aling_memory_block(BLK_HEADER_SIZE + size); 
 
  struct block_header *block = NULL;
  
  block = malloc_request_memory(need_size);

  block->blk_size = need_size;
  block->blk_ptr = ((u8_t*)block) + BLK_HEADER_SIZE;
  block->free_node = NULL;

  block->blk_inuse = true;

  MUTEX_UNLOCK(&malloc_int.malloc_mutex);

  return (block->blk_ptr);
}

u0_t
O_free
(u0_t *ptr)
{
  struct block_header *block = (struct block_header*)((u8_t*)ptr - BLK_HEADER_SIZE);
  if (!ptr)
    return;
  
  if (block->blk_inuse == false)
    exit(O_puts("Double free detected, you can't free a memory area that's alredy be freeded"));
  
  block->blk_inuse = false;
  
  malloc_free_list_push(block);

}

#undef BLK_HEADER_SIZE

