/*
** command_quit.c for myirc in /home/brout_m/rendu/system/PSU_2016_myirc
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Wed May 31 11:32:07 2017 brout_m
** Last update Wed Jun  7 10:40:48 2017 brout_m
*/
#include <string.h>
#include <stdio.h>
#include "replies.h"
#include "channels.h"

static void	parting_from_all_channel(t_server *srv, int sock)
{
  t_client	*client;
  size_t	i;

  i = 0;
  client = &srv->clients[sock];
  while (i < client->channel_count)
    {
      parting_from_channel(srv, sock, client->channels[i] - 1);
      ++i;
    }
}

int		command_quit(t_server *srv, Socket sock, char *cmd)
{
  char		quit[MESSAGE_MAX_SIZE];
  char		*param;

  strtok(cmd, " ");
  memset(quit, 0, MESSAGE_MAX_SIZE);
  if ((param = strtok(NULL, ":")))
    {
      if ((snprintf(quit, MESSAGE_MAX_SIZE,
		    "QUIT :Self-Quit: :%s", param) < 0))
	return (1);
    }
  else if (snprintf(quit, MESSAGE_MAX_SIZE, "QUIT :Self-Quit:") < 0)
    return (1);
  if (user_send_all_channel(sock, srv, quit))
    return (1);
  parting_from_all_channel(srv, sock);
  srv->clients[sock].quit = true;
  return (reply(srv, sock, "%s :%s\r\n", "ERROR", "Client quit"));
}
