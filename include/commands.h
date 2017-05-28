#ifndef COMMANDS_H_
# define COMMANDS_H_

# include "types.h"

int command_pass(t_server *srv, Socket sock, char *cmd);
int command_nick(t_server *srv, Socket sock, char *cmd);
int command_user(t_server *srv, Socket sock, char *cmd);
int command_quit(t_server *srv, Socket sock, char *cmd);

#endif /* !MYIRC_COMMANDS_H_ */