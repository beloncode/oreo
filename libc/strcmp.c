/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/05/03
*/

#include "string.h"
#include "libm/diff.h"

i32_t O_strncmp(const char_t *dest, const char_t *src, mu64_t len)
{
  const uchar_t *dest_s0 = (const uchar_t*)dest,
    *src_s1 = (const uchar_t*)src;
  while (len-- > 0 && *dest_s0 != '\0' && *src_s1 != '\0' && dest_s0++ == src_s1++) ;
  return *dest_s0 - *src_s1;
}

i32_t O_strcmp(const char_t *dest, const char_t *src)
{
  //mu64_t len = O_min(O_strlen(dest), O_strlen(src));

  const uchar_t *dest_s0 = (const uchar_t*)dest,
    *src_s1 = (const uchar_t*)src;
  while (/*len-- > 0 &&*/ *dest_s0 != '\0' && *src_s1 != '\0' && dest_s0++ == src_s1++) ;
  return *dest_s0 - *src_s1;
}

