/*
** channels.h for myirc in /home/brout_m/rendu/system/PSU_2016_myirc
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Wed May 31 11:11:26 2017 brout_m
** Last update Wed Jun  7 10:59:36 2017 brout_m
*/
#ifndef CHANNELS_H_
# define CHANNELS_H_

# include "types.h"

int send_to_channel(Socket sender, t_server *srv,
                    t_channel *channel, char *message);
int user_send_all_channel(Socket sender, t_server *srv, char *message);
void parting_from_channel(t_server *srv, Socket sock, int channel);

#endif /* !CHANNELS_H_ */
