/*
** command_names.c for myirc in /home/brout_m/rendu/system/PSU_2016_myirc
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Wed May 31 11:26:02 2017 brout_m
** Last update Wed May 31 11:27:07 2017 brout_m
*/
#include <string.h>
#include "commands.h"
#include "replies.h"

char const	*replies[ERR_END];

static int	list_one_channel_names(t_server *srv, Socket sock,
				       t_channel *chan)
{
  size_t	i;

  i = 0;
  if (reply(srv, sock, ":myirc 353 %s = %s :", srv->clients[sock].nickname,
            chan->name))
    return (1);
  while (i < chan->clients_count)
    {
      if (reply(srv, sock, "%s", srv->clients[chan->clients[i]].nickname))
	return (1);
      if (i < chan->clients_count - 1 &&
	  reply(srv, sock, " "))
	return (1);
      ++i;
    }
  return (reply(srv, sock, "\r\n:myirc 366 %s %s :End of /NAMES list\r\n",
                srv->clients[sock].nickname,
                chan->name));
}

static int	list_all_channels_names(t_server *srv, Socket sock)
{
  size_t	i;

  i = 0;
  while (i < CHANNEL_MAX)
    {
      if (strlen(srv->channels[i].name) > 0 &&
	  list_one_channel_names(srv, sock, &srv->channels[i]))
	return (1);
      ++i;
    }
  return (0);
}

int		command_names(t_server *srv, Socket sock, char *cmd)
{
  char		*param;
  int		channel;

  strtok(cmd, " ");
  if (!(param = strtok(NULL, " ")))
    return (list_all_channels_names(srv, sock));
  if ((channel = find_channel(srv, param)) >= 0)
    return (list_one_channel_names(srv, sock, &srv->channels[channel]));
  return (reply(srv, sock, "366 %s :End of NAMES list\r\n", param));
}
