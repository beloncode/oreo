/* This code is part of OREO project, all rights reserved to the owners
 * Wrote by: [Gabriel Correia]
 * Create at: 2022/04/29
*/

#include "string.h"

#include "branch.h"
#include "emmintrin.h"

extern mu64_t
O_strlen
(const char_t *dest)
{
  mu64_t str_lenght = 0;

  unlikely (dest == NULL || dest[0] == '\0')
    return (str_lenght);

  /* The compiler will optimize this, ever try to read some data from this pointer
   * will result into a read of 16 bytes from memory, in a only and comprex mov instruction.
  */ 
  const __m128i *str_source = (const __m128i*)dest;
  register const __m128i mask asm("xmm1") = _mm_setzero_si128();
  
  __m128i bytes_readed;

  for (;;) {
    __m128i cmp;
    /* This copy will performs a one cache line configuration */
    bytes_readed = _mm_loadu_si128(str_source);
    cmp = _mm_cmpeq_epi8(bytes_readed, mask);
    if (_mm_movemask_epi8(cmp)) {
      /* This will force the compiler to put the "bytes_readed" 16 bytes variable in the stack 
       * so, will can get the address from him!
      */
      const u8_t *extra_bytes = (const u8_t*)&bytes_readed;
      while (*extra_bytes++)
        str_lenght++;
      break;
    }
    str_lenght += sizeof(__m128i);

  }
  
  return (str_lenght);
}

/* The compiler will generate something like this: Very interesting ;) 

48 85 ff                test   rdi,rdi
74 31                   je     1213 <O_strlen+0x36>
80 3f 00                cmp    BYTE PTR [rdi],0x0
74 2c                   je     1213 <O_strlen+0x36>
0f 10 0f                movups xmm1,XMMWORD PTR [rdi]
0f 57 c0                xorps  xmm0,xmm0
66 0f 74 c1             pcmpeqb xmm0,xmm1
66 0f d7 c0             pmovmskb eax,xmm0
85 c0                   test   eax,eax
74 18                   je     1211 <O_strlen+0x34>
0f 29 4c 24 e8          movaps XMMWORD PTR [rsp-0x18],xmm1
31 c0                   xor    eax,eax
48 8d 54 24 e8          lea    rdx,[rsp-0x18]
80 3c 02 00             cmp    BYTE PTR [rdx+rax*1],0x0
74 05                   je     1210 <O_strlen+0x33>
48 ff c0                inc    rax
eb f5                   jmp    1205 <O_strlen+0x28>
c3                      ret    
eb fe                   jmp    1211 <O_strlen+0x34>
31 c0                   xor    eax,eax
c3                      ret
*/

