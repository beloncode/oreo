/* This code is part of OREO project, all rights reserved to the owners
 * Wrote by: [Gabriel Correia]
 * Create at: 2022/04/28
*/

#include "string.h"
#include "emmintrin.h"

#include "xmmintrin.h"

u0_t*
O_memcpy
(u0_t *dest, u0_t *src, mu64_t num)
{
  __m128i *src_128 = (__m128i*)src;
  __m128i *dest_128 = (__m128i*)dest;

  mu64_t copied = 0;
  for (; num - copied > sizeof (__m128i) && copied < num; copied += sizeof (__m128i))
    _mm_storeu_si128(dest_128++, _mm_loadu_si128(src_128++));

  u8_t *dest_ = dest + copied;
  u8_t *src_ = src + copied;

  while (copied++ != num)
    *dest_++ = *src_++;
  
  return (dest);
}
