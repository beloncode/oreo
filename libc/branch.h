/* This code is part of OREO project, all rights reserved to the owners
 * Wrote by: [Gabriel Correia]
 * Create at: 2022/04/28
*/

#ifndef LIBC_BRANCH_H
#define LIBC_BRANCH_H

#define likely(expr)\
  if (__builtin_expect(!!(expr), 1))
#define unlikely(expr)\
  if (__builtin_expect(!!(expr), 0))

#endif


