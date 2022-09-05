/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/05/03
*/

#include "memory.h"

#include "libc/string.h"

__attribute__((unused)) u0* zMem(u0 *dest, mu64 size)
{
  return oMemset(dest, 0, size);
}
