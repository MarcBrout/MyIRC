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
    return (reply(srv, sock, "322 %s\r\n", channel->name));
  return (reply(srv, sock, "322 %s :%s\r\n", channel->name, channel->topic));
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
  reply(srv, sock, "323 :%s\r\n", "End of LIST");
  return (0);
}
