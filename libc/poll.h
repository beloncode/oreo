/* This code is part of oreo project, all rights reserved (See LICENSE)
 * Wrote by: "Gabriel Correia"
 * Created at: 2022/04/29
*/

#ifndef LIBC_POLL_H
#define LIBC_POLL_H

#include "stddef.h"

#define POLLIN     0x001
#define POLLPRI    0x002
#define POLLOUT    0x004
#define POLLERR    0x008
/* #define POLLHUP    0x010 */
#define POLLNVAL   0x020
/* #define POLLRDNORM 0x040 */
/* #define POLLRDBAND 0x080 */

struct pollFD
{
  /* File descriptor for monitor */
  i32 fd;
  /* Requested events */
  i16 events;
  /* Returned events */
  i16 rEvents;
};

typedef mu64 nFDs;

extern i32 oPoll(struct pollFD *fds, nFDs nfds, i32 timeout);

#endif
