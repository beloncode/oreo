/* This code is part of OREO project, all rights reserved to the owners
 * Wrote by: [Gabriel Correia]
 * Create at: 2022/04/28
*/

#include "string.h"
#include "stddef.h"

#include "alloca.h"
#include "unistd.h"

/* Move a block of memory from a address to other 
 * This function is more slow than the O_memcpy, because his copy the src buffer for
 * a auxiliary buffer and then copy from the auxilirary to the dest location,
 * basically a swap operation.
*/

u0_t*
O_memmove
(u0_t *dest, const u0_t *src, mu64_t num)
{
  u8_t *mem_copy = NULL;
  if (num < MAX_STACK_ALLOC_SIZE)
    mem_copy = (u8_t*)alloca(num);
  else
    exit(-1);
  O_memcpy(mem_copy, (u0_t*)src, num);
  O_memcpy(dest, mem_copy, num);
  return (dest);
}
