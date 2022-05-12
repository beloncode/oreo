#include "malloc_int.h"

i32_t
O_main
(u0_t)
{
  char_t *data = O_malloc(10);
  O_free(data);

  return (0);
}
