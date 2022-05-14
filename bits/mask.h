/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/04/27
*/

#ifndef BITS_MASK_H
#define BITS_MASK_H

/* 
  101001
  001000 ---|
  &=        |
  001000 ---|
*/

#define TEST_SPECIFIC_BIT(value,bit_mask)\
  ((value & bit_mask) == bit_mask)

#endif

