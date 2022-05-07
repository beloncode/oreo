/* This code is part of OREO project, all rights reserved to the owners
 * Wrote by: [Gabriel Correia]
 * Create at: 2022/05/06
*/

#include "malloc_int.h"

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
} malloc_int = {
  .malloc_mutex = MUTEX_INIT,
  .base_address = 0
};

struct block_header 
{
  mu64_t blk_size;
  struct block_header *left, *right;
  u0_t *blk_ptr;
};

u0_t*
O_malloc
(mu64_t size)
{
  MUTEX_LOCK(&malloc_int.malloc_mutex);
  struct block_header *blk_h = malloc_int.base_address;

  mu64_t alloc_space = aling_memory_block(size + sizeof(struct block_header));
  if (!malloc_int.base_address) {
    malloc_int.base_address = sbrk(alloc_space);
    blk_h = (struct block_header*)malloc_int.base_address;
    blk_h->blk_size = alloc_space | 1; /* Indicate that the memory is allocated */
    blk_h->left = blk_h->right = NULL;
  }
 
  MUTEX_UNLOCK(&malloc_int.malloc_mutex);

  return (blk_h->blk_ptr);
}

u0_t
O_free
(u0_t *ptr)
{
  unlikely (ptr == NULL)
    return;
  struct block_header *blk_h = ptr - sizeof(struct block_header);
  if (blk_h->blk_size & 1) {
    /* The space is valid and is allocated */
    blk_h->blk_size ^= 1;
  }
}

