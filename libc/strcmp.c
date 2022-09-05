/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/05/03
*/

#include "string.h"

i32 oStrncmp(const int8 *dest, const int8 *src, mu64 len)
{
  const uint8 *destS0 = (const uint8*)dest,
    *src_s1 = (const uint8*)src;
  while (len-- > 1 && *destS0 != '\0' && *src_s1 != '\0' && destS0++ == src_s1++) ;
  return *destS0 - *src_s1;
}

i32 oStrCmp(const int8 *dest, const int8 *src)
{
  const uint8 *destS0 = (const uint8*)dest,
    *src_s1 = (const uint8*)src;
  while (/*len-- > 0 &&*/ *destS0 != '\0' && *src_s1 != '\0' && destS0++ == src_s1++) ;
  return *destS0 - *src_s1;
}

