/* This code is part of OREO project, all rights reserved to the owners
 * Wrote by: [Gabriel Correia]
 * Create at: 2022/04/29
*/

#include "string.h"

#include "branch.h"
#include "emmintrin.h"

mu64_t
O_strlen
(const char_t *dest)
{
  mu64_t str_lenght = 0;

  unlikely (dest == NULL || *dest == '\0')
    return (str_lenght);

  /* The compiler will optimize this, ever try to read some data from this pointer
   * will result into a read of 16 bytes from memory, in a only and comprex mov instruction.
  */ 
  const __m128i *str_source = (const __m128i*)dest;
  register const __m128i mask asm("xmm1") = _mm_setzero_si128();
  bool_t non_zero = false;

  __m128i bytes_readed;

  for (; non_zero != true ;) {
    __m128i cmp;
    /* This copy will performs a one cache line configuration */
    bytes_readed = _mm_loadu_si128(str_source++);
    cmp = _mm_cmpeq_epi8(bytes_readed, mask);
    non_zero = _mm_movemask_epi8(cmp);
    if (non_zero) {
      /* This will force the compiler to put the "bytes_readed" 16 bytes variable in the stack 
       * so, will can get the address from him!
      */
      const u8_t *extra_bytes = (const u8_t*)&bytes_readed;
      while (*extra_bytes++)
        str_lenght++;
      break;
    }
    str_lenght += sizeof (__m128i);

  }
  
  return (str_lenght);
}

/* The compiler will generate something like this: Very interesting ;)
31 c0                   xor    eax,eax
48 85 ff                test   rdi,rdi
74 3a                   je     134d <O_strlen+0x41>
80 3f 00                cmp    BYTE PTR [rdi],0x0
0f 57 d2                xorps  xmm2,xmm2
74 32                   je     134d <O_strlen+0x41>
0f 10 04 07             movups xmm0,XMMWORD PTR [rdi+rax*1]
0f 28 c8                movaps xmm1,xmm0
66 0f 74 ca             pcmpeqb xmm1,xmm2
66 0f d7 d1             pmovmskb edx,xmm1
85 d2                   test   edx,edx
75 06                   jne    1334 <O_strlen+0x28>
48 83 c0 10             add    rax,0x10
eb e7                   jmp    131b <O_strlen+0xf>
48 8d 54 24 e8          lea    rdx,[rsp-0x18]
0f 29 44 24 e8          movaps XMMWORD PTR [rsp-0x18],xmm0
48 29 c2                sub    rdx,rax
80 3c 02 00             cmp    BYTE PTR [rdx+rax*1],0x0
74 05                   je     134c <O_strlen+0x40>
48 ff c0                inc    rax
eb f5                   jmp    1341 <O_strlen+0x35>
c3                      ret    
c3                      ret    
*/
