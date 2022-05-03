/* This code is part of OREO project, all rights reserved to the owners
 * Wrote by: [Gabriel Correia]
 * Create at: 2022/05/03
*/

#include "memory.h"

#include "libc/string.h"

u0_t* Zmem(u0_t *dest, mu64_t size)
{
  return O_memset(dest, 0, size);
}
