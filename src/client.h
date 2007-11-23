#ifndef CLIENT_H
#define CLIENT_H 1

#include "server.h"
#include <stddef.h>


struct server
{
  char *host;
  char *port;
  int fd;
};


struct client
{
  struct server *servers;
  char *namespace_prefix;
  size_t namespace_prefix_len;
  size_t server_count;
  size_t server_capacity;
  int connect_timeout;          /* 1/1000 sec.  */
  int io_timeout;               /* 1/1000 sec.  */
  int close_on_error;
};


extern
int
client_init(struct client *c);

extern
void
client_destroy(struct client *c);

extern
int
client_add_server(struct client *c, const char *host, size_t host_len,
                  const char *port, size_t port_len);

extern
int
client_set_namespace(struct client *c, const char *ns, size_t ns_len);

static inline
void
client_set_connect_timeout(struct client *c, int to)
{
  c->connect_timeout = to;
}

static inline
void
client_set_io_timeout(struct client *c, int to)
{
  c->io_timeout = to;
}

static inline
void
client_set_close_on_error(struct client *c, int enable)
{
  c->close_on_error = enable;
}

extern
int
client_set(struct client *c, const char *key, size_t key_len,
           flags_type flags, exptime_type exptime,
           const void *buf, size_t buf_size);

extern
int
client_get(struct client *c, const char *key, size_t key_len,
           alloc_value_func alloc_value, void *alloc_value_arg);


#endif /* ! CLIENT_H */
