
#ifndef LIBC_BRANCH_H
#define LIBC_BRANCH_H

#define likely(expr)\
  if (__builtin_expect(!!(expr), 1))
#define unlikely(expr)\
  if (__builtin_expect(!!(expr), 0))

#endif


