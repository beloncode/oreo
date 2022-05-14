/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/05/03
*/

#include "memory.h"

#include "libc/string.h"

u0_t* Zmem(u0_t *dest, mu64_t size)
{
  return O_memset(dest, 0, size);
}
