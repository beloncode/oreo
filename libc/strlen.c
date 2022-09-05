/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/04/29
*/

#include "string.h"

#include "branch.h"
#include "emmintrin.h"

mu64 oStrlen(const int8 *dest)
{
  mu64 strSize = 0;

  unlikely (dest == NULL || *dest == '\0')
    return strSize;

  /* The compiler will optimize this, ever try to read some data from this pointer
   * will result into a read of 16 bytes from memory, in an only and complex mov instruction.
  */ 
  const __m128i *strSource = (const __m128i*)dest;
  register const __m128i mask asm("xmm1") = _mm_setzero_si128();
  i32 nonZero = false;

  __m128i bytesRead;

  for (; 1;) {
    __m128i cmp;
    /* This copy will perform a one cache line configuration */
    bytesRead = _mm_loadu_si128(strSource++);
    cmp = _mm_cmpeq_epi8(bytesRead, mask);
    nonZero = _mm_movemask_epi8(cmp);
    if (nonZero) {
      /* This will force the compiler to put the "bytesRead" 16 bytes variable in the stack
       * so, will get the address from him!
      */
      const u8 *extra_bytes = (const u8*)&bytesRead;
      while (*extra_bytes++)
        strSize++;
      break;
    }
    strSize += sizeof (__m128i);

  }
  
  return strSize;
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
eb f5                   jmp    1341 <oStrlen+0x35>
c3                      ret    
c3                      ret    
*/
