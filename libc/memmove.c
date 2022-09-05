/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/04/28
*/

#include "string.h"
#include "stddef.h"

#include "alloca.h"
#include "unistd.h"

/* Move a block of memory from an address to other location
 * This function is slower than the oMemCpy, because his copy the src buffer for
 * an auxiliary buffer and then copy from the auxiliary buffer to the dest location,
 * basically a SWAP operation.
*/

__attribute__((unused)) u0* oMemMove(u0 *dest, const u0 *src, mu64 num)
{
  u8 *memCopy = NULL;
  if (num < MAX_STACK_ALLOC_SIZE)
    memCopy = (u8*)alloca(num);
  else
    exit(-1);
  oMemCpy(memCopy, (u0 *) src, num);
  oMemCpy(dest, memCopy, num);
  return dest;
}
