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
#define POLLHUP    0x010
#define POLLNVAL   0x020
#define POLLRDNORM 0x040
#define POLLRDBAND 0x080

struct O_pollfd
{
  /* File descriptor for monitor */
  i32_t fd;
  /* Requested events */ 
  i16_t events;
  /* Returned events */
  i16_t revents;
};

typedef mu64_t nfds_t;

extern i32_t O_poll(struct O_pollfd *fds, nfds_t nfds, i32_t timeout);

#endif
