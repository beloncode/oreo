/* This code is part of OREO project, all rights reserved to the owners
 * Wrote by: [Gabriel Correia]
 * Create at: 2022/04/27
*/

#include "string.h"
#include "test/expect.h"

u0_t
strrchr_test
(u0_t)
{
#define SEARCH_CHAR 'i'
  char_t some_str[] = "Gabriel Correia is writing this code";
  char_t *lastest_char = O_strrchr(some_str, SEARCH_CHAR);
  EXPECT_EQ_CHAR(*lastest_char, SEARCH_CHAR);
  EXPECT_EQ(lastest_char - some_str, 29);
  //EXPECT_EQ_PTR(O_strrchr(NULL, 0), NULL);

}

i32_t
O_main
(u0_t)
{
  strrchr_test();

  return (0);
}



