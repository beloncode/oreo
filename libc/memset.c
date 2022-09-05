/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/04/28
*/

#include "string.h"

#include "emmintrin.h"

#undef memset

/* Avoid compiler warnings */

/* The symbol 'memset' must be exported */
/* inline __attribute__((always_inline)) */ u0* memset(u0 *dest, i32 c, mu64 n)
{
  uint8 *destPtr = (uint8*)dest;
  while (n-- > 0)
    *destPtr++ = (u8)c;
  return dest;
}

u0* oMemset(u0 *dest, i32 constant, mu64 num)
{
  i8 blockData[] = {(i8)constant, (i8)constant, (i8)constant, (i8)constant};
  /* Hack trick: Fill a 16 bytes vector range with 4 constant values :0 */
  const _Alignas(16) i32 constants[] = {
    *((i32*)&blockData),
    *((i32*)&blockData),
    *((i32*)&blockData),
    *((i32*)&blockData)
  };
  register __m128i const128 = _mm_loadu_si128((__m128i*)constants);
  __m128i *dest128 = (__m128i*)dest;
  mu64 copied = 0;
  
  for (; num - copied > sizeof(__m128i) && copied < num; copied += sizeof(__m128i))
    _mm_storeu_si128(dest128++, const128);
  
  u8 *dest_ = dest + copied;
  memset(dest_, constant, num - copied);

  return dest;
}

