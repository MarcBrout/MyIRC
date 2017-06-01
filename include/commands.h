/*
** commands.h for myirc in /home/brout_m/rendu/system/PSU_2016_myirc
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Wed May 31 11:12:35 2017 brout_m
** Last update Wed May 31 11:12:42 2017 brout_m
*/

#ifndef COMMANDS_H_
# define COMMANDS_H_

# include "types.h"

int find_channel(t_server *srv, char *chan);
int already_in_channel(t_server *srv, Socket sock, int channel);
int command_pass(t_server *srv, Socket sock, char *cmd);
int command_nick(t_server *srv, Socket sock, char *cmd);
int command_user(t_server *srv, Socket sock, char *cmd);
int command_quit(t_server *srv, Socket sock, char *cmd);
int command_join(t_server *srv, Socket sock, char *cmd);
int command_part(t_server *srv, Socket s, char *cmd);
int command_list(t_server *srv, Socket sock, char *cmd);
int command_names(t_server *srv, Socket sock, char *cmd);
int command_privmsg(t_server *srv, Socket sock, char *cmd);

#endif /* !MYIRC_COMMANDS_H_ */
