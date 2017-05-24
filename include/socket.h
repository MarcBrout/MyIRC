#ifndef SOCKET_H_
# define SOCKET_H_

#include <stdint.h>
#include "types.h"

int create_server_socket(t_server *server, uint16_t port);
int accept_new_client(t_server *server);

#endif /* !MYIRC_SOCKET_H */
