/* This code is part of OREO project, all rights reserved to the owners
 * Wrote by: [Gabriel Correia]
 * Create at: 2022/04/28
*/

#include "string.h"

#include "emmintrin.h"

u0_t*
O_memset
(u0_t *dest, i32_t constant, mu64_t num)
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

  while (copied++ < num)
    *dest_++ = constant;
  
  return (dest);
}


