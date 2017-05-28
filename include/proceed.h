#ifndef PROCEED_H_
# define PROCEED_H_

#include <sys/socket.h>
#include "types.h"

typedef int (*func_t)(t_server *server, Socket sock, char *cmd);

typedef struct s_command
{
  const char *cmd;
  const int len;
  const func_t exec;
} t_command;

int proceed(t_server *server, fd_set *fds_read, fd_set *fds_write);
int proceed_commands(t_server *srv);

#endif /* !MYIRC_PROCEED_H */
