/*
** server.h for myirc in /home/brout_m/rendu/system/PSU_2016_myirc
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Wed May 31 11:16:19 2017 brout_m
** Last update Wed May 31 11:16:33 2017 brout_m
*/

#ifndef SERVER_H_
# define SERVER_H_

#include "types.h"

t_server *server_init();
void client_init(t_client *client);

#endif /* !SERVER_H_ */
