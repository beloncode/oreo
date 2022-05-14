/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/05/06
*/

#ifndef HEAP_MALLOC_INT_H
#define HEAP_MALLOC_INT_H

#include "libc/stddef.h"
#include "libc/mutex.h"

struct free_list
{
  struct free_list *prev, *next;
};

struct block_header 
{
  struct free_list free_node;

  mu64_t blk_size;
  bool_t blk_inuse;

  /* Pointer received by the user as the malloc result */
  u0_t *blk_ptr;
};

struct malloc_int_header
{
  mutex_t malloc_mutex;
  u0_t *base_address;
  struct free_list *free_list_heap;

  mu64_t heap_size;
};

extern struct malloc_int_header malloc_int;

extern u0_t* O_malloc(mu64_t size);

extern u0_t O_free(u0_t *ptr);

#endif
