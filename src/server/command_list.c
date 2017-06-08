/*
** command_list.c for myirc in /home/brout_m/rendu/system/PSU_2016_myirc
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Wed May 31 11:25:26 2017 brout_m
** Last update Fri Jun  2 14:33:28 2017 brout_m
*/
#include <stdio.h>
#include <string.h>
#include "replies.h"

char const	*replies[ERR_END];

static int	add_to_list(t_server *srv, Socket sock,
			    t_channel *channel)
{
  if (!strlen(channel->topic))
    return (reply(srv, sock, ":myirc 322 %s %s %d\r\n",
                  srv->clients[sock].nickname,
                  channel->name,
                  channel->clients_count));
  return (reply(srv, sock, ":myric 322 %s %s %d :%s\r\n",
                srv->clients[sock].nickname,
                channel->name,
                channel->clients_count,
                channel->topic));
}

int		command_list(t_server *srv, Socket sock, char *cmd)
{
  size_t	i = 0;

  (void)cmd;
  while (i < CHANNEL_MAX)
    {
      if (strlen(srv->channels[i].name))
	{
	  if (add_to_list(srv, sock, &srv->channels[i]))
	    return (1);
	}
      ++i;
    }
  reply(srv, sock, ":myirc 323 %s :%s\r\n",
        srv->clients[sock].nickname,
        "End of LIST");
  return (0);
}
