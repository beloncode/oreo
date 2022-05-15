/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/04/27
*/

#include "string.h"
#include "stdio.h"

#include "test/expect.h"

u0_t strrchr_test(u0_t)
{
#define SEARCH_CHAR 'i'
  char_t some_str[] = "Gabriel Correia is writing this code";
  char_t *lastest_char = O_strrchr(some_str, SEARCH_CHAR);
  EXPECT_EQ_CHAR(*lastest_char, SEARCH_CHAR);
  EXPECT_EQ(lastest_char - some_str, 29);
  O_puts("Test> O_strrchar is ok");

  char_t TEST_ONE = 's', TEST_TWO = 's';
  EXPECT_EQ(O_strncmp(&TEST_ONE, &TEST_TWO, 1), 0);
  O_puts("Test> O_strncmp is ok");

}
u0_t memset_test(u0_t)
{
  u8_t some_data[100];
  O_memset(some_data, 0xf1, sizeof (some_data)); 
  
  for (i32_t i_loop = 0; i_loop < sizeof (some_data); i_loop++)
    EXPECT_EQ(some_data[i_loop], 0xf1);

  O_puts("Test> O_memset is ok");

}

i32_t O_main(u0_t)
{
  strrchr_test();
  memset_test();

  return (0);
}



