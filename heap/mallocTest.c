/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Create at: 2022/06/13
*/

#include "mallocInt.h"

i32 oMain(u0)
{
  int8 *data = oMalloc(10);
  oMemset(data, 'A', 5);
  oFree(data);
  data = oMalloc(10);
  if (*data == 'A')
    oPuts("Re-using the freed memory of the same size");
  else
    exit(oPuts("Wait, there's sames problems in free-list"));
  oFree(data);

  /* Reusing the same memory block */
  data = oMalloc(11);
  oFree(data);

  return 0;
}
