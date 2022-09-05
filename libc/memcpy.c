/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/04/28
*/

#include "string.h"
#include "emmintrin.h"

u0* oMemCpy(u0 *dest, u0 *src, mu64 num)
{
  __m128i *src128 = (__m128i*)src;
  __m128i *dest128 = (__m128i*)dest;

  mu64 copied = 0;
  for (; num - copied > sizeof (__m128i) && copied < num; copied += sizeof (__m128i))
    _mm_storeu_si128(dest128++, _mm_loadu_si128(src128++));

  u8 *destPtr = dest + copied;
  u8 *srcPtr = src + copied;

  while (copied++ != num)
    *destPtr = *srcPtr++;
  
  return dest;
}
