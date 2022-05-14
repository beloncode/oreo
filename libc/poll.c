/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/04/29
*/

#include "poll.h"

#include "arch/systable.h"
#include "arch/asm.h"

i32_t O_poll(struct O_pollfd *fds, nfds_t nfds, i32_t timeout)
{
  /* TODO: to set errno */
  return (i32_t)__syscall3(SYS_POLL, (u64_t)fds, (u64_t)nfds, (u64_t)timeout);
}
