/*
** proceed.h for myirc in /home/brout_m/rendu/system/PSU_2016_myirc
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Wed May 31 11:12:52 2017 brout_m
** Last update Fri Jun  2 14:31:43 2017 brout_m
*/
#ifndef PROCEED_H_
# define PROCEED_H_

# include <sys/socket.h>
# include "types.h"

typedef int		(*func_t)(t_server *server, Socket sock, char *cmd);

typedef struct		s_command
{
  const char		*cmd;
  const int		len;
  const func_t		exec;
}			t_command;

int proceed(t_server *server, fd_set *fds_read, fd_set *fds_write);
int proceed_commands(t_server *srv);
int proceed_writes(t_server *server, fd_set *fds_write);

#endif /* !PROCEED_H_ */
