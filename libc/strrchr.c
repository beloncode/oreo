/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/04/27
*/

#include "string.h"

int8* oStrchr(const int8 *dest, i32 character)
{
  int8 *first = NULL;

  while (*dest != '\0' && *dest != character) dest++;

  if (*dest != '\0')
    /* The character has been found */
    first = (int8*)dest;

  return first;
}

__attribute__((unused)) int8* oStrrchr(const int8 *dest, i32 character)
{
  int8 *last = NULL;

  do {
    while (*dest && *dest != (int8)character) dest++;
    if (*dest)
      last = (int8*)dest;
  } while (*dest++);

  return last;
}


