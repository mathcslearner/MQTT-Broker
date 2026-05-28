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

/* Auxiliary function for creating epoll server */
int create_and_bind(const char *, const char *, int);

/**
 * Create a non-blocking socket and make it listen on the specified address and port
*/
int make_listen(const char *, const char *, int);

/* Accept a connection and add it to the right epollfd */
int accept_connection(int);

#endif