/*
** server.h for myirc in /home/brout_m/rendu/system/PSU_2016_myirc
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Wed May 31 11:16:19 2017 brout_m
** Last update Fri Jun  2 14:31:27 2017 brout_m
*/
#ifndef SERVER_H_
# define SERVER_H_

# include "types.h"

t_server *server_init();
void client_init(t_client *client);
int is_client_in_channel(t_server *srv, Socket sock, int channel);
int is_channel(t_server *srv, char const *channel);
int is_client(t_server *srv, char const *client);
int send_all_channel_unique(t_server *srv, Socket sender, char *msg);

#endif /* !SERVER_H_ */
