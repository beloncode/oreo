/* This code is part of OREO project, all rights reserved to the owners
 * Wrote by: [Gabriel Correia]
 * Create at: 2022/04/27
*/

#include "string.h"

#include "branch.h"

char_t*
O_strchr
(const char_t *dest, i32_t character)
{
  char_t *first = NULL;

  while (*dest != '\0' && *dest++ != character) ;

  if (*dest != '\0')
    /* The character has been found */
    first = (char_t*)dest;

  return (first);
}

char_t*
O_strrchr
(const char_t *dest, i32_t character)
{
  char_t *last = NULL;

  do {
    while (*dest && *dest != (char_t)character) dest++;
    if (*dest)
      last = (char_t*)dest;
  } while (*dest++);

  return (last);
}


