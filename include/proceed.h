#ifndef PROCEED_H_
# define PROCEED_H_

#include <sys/socket.h>
#include "types.h"

int proceed_writes(t_server *server, fd_set *fds_write);
int proceed_reads(t_server *server, fd_set *fds_read);
int proceed(t_server *server, fd_set *fds_read, fd_set *fds_write);

#endif /* !MYIRC_PROCEED_H */
