#ifndef NETWORK_H
#define NETWORK_H

#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>

// Socket families
#define UNIX 0
#define INET 1

/* Set non-blocking socket */
int set_nonblocking(int);

/**
 * Set TCP_NODELAY flag to true, disabling Nagle's algorithm, no more waiting
 * for incoming packets on the buffer
*/
int set_tcp_nodelay(int);

#endif