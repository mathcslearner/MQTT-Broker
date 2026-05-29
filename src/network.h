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

/* I/O management functions */

/*
 * Send all data in a loop, avoiding interruption based on the kernel buffer
 * availability
 */
ssize_t send_bytes(int, const unsigned char *, size_t);

/*
 * Receive (read) an arbitrary number of bytes from a file descriptor and
 * store them in a buffer
 */
ssize_t recv_bytes(int, unsigned char *, size_t);

/* Event loop wrapper structure, define an EPOLL loop and his status. The
 * EPOLL instance use EPOLLONESHOT for each event and must be re-armed
 * manually, in order to allow future uses on a multithreaded architecture.
 */
struct evloop {
    int epollfd;
    int max_events;
    int timeout;
    int status;
    struct epoll_event *events;
    /* Dynamic array of periodic tasks, a pair descriptor - closure */
    int periodic_maxsize;
    int periodic_nr;
    struct {
        int timerfd;
        struct closure *closure;
    } **periodic_tasks;
} evloop;

typedef void callback(struct evloop *, void *);

/*
 * Callback object, represents a callback function with an associated
 * descriptor if needed, args is a void pointer which can be a structure
 * pointing to callback parameters and closure_id is a UUID for the closure
 * itself.
 * The last two fields are payload, a serialized version of the result of
 * a callback, ready to be sent through wire and a function pointer to the
 * callback function to execute.
 */
struct closure {
    int fd;
    void *obj;
    void *args;
    char closure_id[UUID_LEN];
    struct bytestring *payload;
    callback *call;
};

struct evloop *evloop_create(int, int);
void evloop_init(struct evloop *, int, int);
void evloop_free(struct evloop *);

#endif