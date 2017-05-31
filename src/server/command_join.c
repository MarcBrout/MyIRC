/*
** command_join.c for myric in /home/brout_m/rendu/system/PSU_2016_myirc
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Wed May 31 11:23:10 2017 brout_m
** Last update Wed May 31 11:25:20 2017 brout_m
*/
#include <stdio.h>
#include <string.h>
#include "replies.h"

char const	*replies[ERR_END];

int		already_in_channel(t_server *srv, Socket sock, int channel)
{
  size_t i;

  i = 0;
  while (i < srv->clients[sock].channel_count &&
	 srv->clients[sock].channels[i] != channel + 1)
    {
      ++i;
    }
  if (i != srv->clients[sock].channel_count)
    return (1);
  return (0);
}

static int	join_channel(t_server *srv, Socket sock, int channel)
{
  if (srv->channels[channel].clients_count == FD_MAX - 1)
    return (reply(srv, sock, "%s %s %s\r\n", "471",
                  srv->channels[channel].name, replies[ERR_CHANNELISFULL]));
  if (srv->clients[sock].channel_count == USER_MAX_CHAN - 1)
    return (reply(srv, sock, "%s %s %s\r\n", "405",
                  srv->channels[channel].name, replies[ERR_TOOMANYCHANNELS]));
  srv->channels[channel].clients[srv->channels[channel].clients_count] = sock;
  ++srv->channels[channel].clients_count;
  srv->clients[sock].channels[srv->clients[sock].channel_count] = channel + 1;
  ++srv->clients[sock].channel_count;
  if (strlen(srv->channels[channel].topic))
    return (reply(srv, sock, "%s %s :%s\r\n", "332",
                  srv->channels[channel].name, srv->channels[channel].topic));
  return (reply(srv, sock, "%s %s %s\r\n", "331", srv->channels[channel].name,
                replies[RPL_NOTOPIC]));
}

static int	create_channel(t_server *srv, Socket sock, char const *name)
{
  int		index;

  index = 0;
  while (index < CHANNEL_MAX && strlen(srv->channels[index].name))
    {
      ++index;
    }
  if (index == CHANNEL_MAX)
    return (reply(srv, sock, "%s %s %s\r\n", "403", name,
                  replies[ERR_NOSUCHCHANNEL]));
  strncpy(srv->channels[index].name, name, CHANNEL_NAME_SIZE);
  return (join_channel(srv, sock, index));
}

int		find_channel(t_server *srv, char *chan)
{
  int		channel;

  channel = 0;
  while (channel < CHANNEL_MAX)
    {
      if (!strcmp(chan, srv->channels[channel].name))
	return (channel);
      ++channel;
    }
  return (-1);
}

int		command_join(t_server *srv, Socket sock, char *cmd)
{
  char		*line;
  char		*channel;
  int		index;

  line = strtok(cmd, " ");
  channel = strtok(NULL, " ");
  if (!channel)
    return (needmoreparams(srv, sock, line));
  if ((index = find_channel(srv, channel)) < 0)
    return (create_channel(srv, sock, channel));
  if (already_in_channel(srv, sock, index))
    return (0);
  return (join_channel(srv, sock, index));
}
