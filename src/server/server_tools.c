/*
** server_tools.c for myirc in /home/brout_m/rendu/system/PSU_2016_myirc
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Thu Jun  8 17:06:49 2017 brout_m
** Last update Thu Jun  8 18:11:38 2017 brout_m
*/
#include <string.h>
#include "replies.h"
#include "server.h"

int		send_all_channel_unique(t_server *srv,
					Socket sender, char *msg)
{
  Socket	tab[FD_MAX];
  t_channel	*chan;
  size_t	channel;
  size_t	client;

  channel = 0;
  memset(tab, 0, sizeof(Socket) * FD_MAX);
  while (channel < srv->clients[sender].channel_count)
    {
      chan = &srv->channels[srv->clients[sender].channels[channel] - 1];
      client = 0;
      while (client < chan->clients_count)
	{
	  if (!tab[chan->clients[client]] &&
	      tab[chan->clients[client]] != sender)
	    {
	      if (reply(srv, chan->clients[client], "%s", msg))
		return (1);
	      tab[chan->clients[client]] = 1;
	    }
	  ++client;
	}
      ++channel;
    }
  return (0);
}

int		is_client_in_channel(t_server *srv, Socket sock, int channel)
{
  size_t client;

  client = 0;
  while (client < srv->channels[channel].clients_count)
  {
    if (srv->channels[channel].clients[client] == sock)
      return (1);
    ++client;
  }
  return (0);
}

int		is_channel(t_server *srv, char const *channel)
{
  int			i;

  i = 0;
  while (i < CHANNEL_MAX)
    {
      if (!strcasecmp(channel, srv->channels[i].name))
	return (i);
      ++i;
    }
  return (-1);
}

int		is_client(t_server *srv, char const *client)
{
  int		i;

  i = 0;
  while (i < FD_MAX)
    {
      if (!strcasecmp(client, srv->clients[i].nickname) ||
	  !strcmp(client, srv->clients[i].username))
	return (i);
      ++i;
    }
  return (-1);
}
