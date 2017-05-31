/*
** socket.h for myirc in /home/brout_m/rendu/system/PSU_2016_myirc
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Wed May 31 11:16:58 2017 brout_m
** Last update Wed May 31 11:17:13 2017 brout_m
*/
#ifndef SOCKET_H_
# define SOCKET_H_

#include <stdint.h>
#include "types.h"

int create_server_socket(t_server *server, uint16_t port);
int accept_new_client(t_server *server);

#endif /* !SOCKET_H_ */
