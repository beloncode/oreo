/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/04/29
*/

#include "poll.h"

#include "arch/systable.h"
#include "arch/asm.h"

i32 oPoll(struct pollFD *fds, nFDs nfds, i32 timeout)
{
  /* TODO: to set errno */
  return (i32)__syscall3(SYS_POLL, (u64)fds, (u64)nfds, (u64)timeout);
}
