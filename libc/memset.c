/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/04/28
*/

#include "string.h"

#include "emmintrin.h"

#undef memset

/* Avoid compiler warnings */

/* The symbol 'memset' must be exported */
/* inline __attribute__((always_inline)) */ u0_t* memset(u0_t *dest, i32_t c, mu64_t n)
{
  uchar_t *dest_ = (uchar_t*)dest;
  while (n-- > 0)
    *dest_++ = (u8_t)c;
  return dest;
}

u0_t* O_memset(u0_t *dest, i32_t constant, mu64_t num)
{
  i8_t block_data[] = {(i8_t)constant, (i8_t)constant, (i8_t)constant, (i8_t)constant};
  /* Hack trick: Fill a 16 bytes vector range with 4 constant values :0 */
  const _Alignas(16) i32_t constants[] = {
    *((i32_t*)&block_data),
    *((i32_t*)&block_data),
    *((i32_t*)&block_data),
    *((i32_t*)&block_data)
  };
  register __m128i const_128 = _mm_loadu_si128((__m128i*)constants);
  __m128i *dest_128 = (__m128i*)dest;
  mu64_t copied = 0;
  
  for (; num - copied > sizeof (__m128i) && copied < num; copied += sizeof (__m128i))
    _mm_storeu_si128(dest_128++, const_128);
  
  u8_t *dest_ = dest + copied;
  memset(dest_, constant, num - copied);

  return dest;
}

