/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/04/27
*/

#include "string.h"
#include "stdio.h"

#include "test/expect.h"

u0 strrchrTest(u0)
{
#define SEARCH_CHAR 'i'
  int8 someStr[] = "Gabriel Correia is writing this code";
  int8 *lastChar = oStrrchr(someStr, SEARCH_CHAR);
  EXPECT_EQ_CHAR(*lastChar, SEARCH_CHAR);
  EXPECT_EQ(lastChar - someStr, 29);
  oPuts("Test> oStrrchr is ok");

  int8 *testOneStr = "s", *testTwoStr = "s";

  EXPECT_EQ(oStrCmp(testOneStr, testTwoStr), 0);
  oPuts("Test> oStrCmp is ok");

}
u0 memsetTest(u0)
{
  u8 someData[100];
  oMemset(someData, 0xf1, sizeof(someData));
  
  for (i32 iLoop = 0; iLoop < sizeof(someData); iLoop++)
    EXPECT_EQ(someData[iLoop], 0xf1);

  oPuts("Test> oMemset is ok");

}

i32 oMain(u0)
{
  strrchrTest();
  memsetTest();

  return (0);
}



