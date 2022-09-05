/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/04/29
*/

#ifndef EMMINTRIN_H
#define EMMINTRIN_H

#ifndef __clang__
#pragma GCC target("sse2")
#endif

__attribute__((unused)) typedef double __v2df __attribute__((__vector_size__(16)));
__attribute__((unused)) typedef long long __v2di __attribute__((__vector_size__(16)));
__attribute__((unused)) typedef unsigned long long __v2du __attribute__((__vector_size__(16)));
__attribute__((unused)) typedef int __v4si __attribute__((__vector_size__(16)));
__attribute__((unused)) typedef unsigned int __v4su __attribute__((__vector_size__(16)));
__attribute__((unused)) typedef short __v8hi __attribute__((__vector_size__(16)));
__attribute__((unused)) typedef unsigned short __v8hu __attribute__((__vector_size__(16)));
__attribute__((unused)) typedef char __v16qi __attribute__((__vector_size__(16)));
__attribute__((unused)) typedef signed char __v16qs __attribute__((__vector_size__(16)));
__attribute__((unused)) typedef unsigned char __v16qu __attribute__((__vector_size__(16)));

typedef long long __m128i __attribute__((__vector_size__ (16)));
typedef long long __m128i_u __attribute__((__vector_size__(16), __aligned__(1)));

/* Creates a vector of 16 bytes boundary with zeros value */
extern __inline __m128i __attribute__((__gnu_inline__, __always_inline__, __artificial__)) _mm_setzero_si128(u0)
{
  return __extension__(__m128i)(__v4si){0, 0, 0, 0};
}

/* Load 16 bytes from memory without alignment */
extern __inline __m128i __attribute__((__gnu_inline__, __always_inline__, __artificial__)) _mm_loadu_si128(__m128i_u const *dest)
{
  return *dest;
}

extern __inline __m128i __attribute__((__gnu_inline__, __always_inline__, __artificial__)) _mm_cmpeq_epi8(__m128i dest, __m128i src)
{
  return (__m128i)((__v16qi)dest == (__v16qi)src);
}

extern __inline i32 __attribute__((__gnu_inline__, __always_inline__, __artificial__)) _mm_movemask_epi8(__m128i dest)
{
  return __builtin_ia32_pmovmskb128((__v16qi)dest);
}

extern __inline u0 __attribute__((__gnu_inline__, __always_inline__, __artificial__)) _mm_storeu_si128(__m128i_u *dest, __m128i src)
{
  *dest = src;
}

#endif


