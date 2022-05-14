/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Create at: 2022/06/13
*/

#include "malloc_int.h"

i32_t O_main(u0_t)
{
  char_t *data = O_malloc(10);
  O_memset(data, 'A', 5);
  O_free(data);
  data = O_malloc(10);
  if (*data == 'A')
    O_puts("Re-using the freed memory of the same size");
  else
    exit(O_puts("Wait, there's somes problems in free-list"));
  O_free(data);

  /* Reusing the same memory block */
  data = O_malloc(11);
  O_free(data);

  return 0;
}
