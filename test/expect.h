/* This code is part of OREO project, all rights reserved to the owners
 * Wrote by: [Gabriel Correia]
 * Create at: 2022/04/27
*/

#ifndef TEST_EXPECT_H
#define TEST_EXPECT_H

#include "libc/stddef.h"
#include "libc/branch.h"

#include "fatal.h"

extern const char_t unexpected_str[];

#define EXPECT(expr)\
  do {\
    unlikely (!(expr)) {\
    fatal_error(unexpected_str, #expr, __FILE__, __LINE__);\
    __builtin_unreachable();\
    }\
  } while (0)

#define EXPECT_EQ(a, b)\
  EXPECT(a == b)

#define EXPECT_EQ_CHAR(a, b)\
  EXPECT(a == b)

#define EXPECT_EQ_PTR(a, b)\
  EXPECT(a == b)

#endif

