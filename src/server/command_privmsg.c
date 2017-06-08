/*
** command_privmsg.c for myirc in /home/brout_m/rendu/system/PSU_2016_myirc
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Wed May 31 11:30:33 2017 brout_m
** Last update Fri Jun  2 14:35:46 2017 brout_m
*/
#include <string.h>
#include <channels.h>
#include <stdio.h>
#include "replies.h"

char const		*replies[ERR_END];

static int		is_channel(t_server *srv, char const *channel)
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

static int		is_client(t_server *srv, char const *client)
{
  int			i;

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

int		send_to_client(t_server *srv, int sen, int client, char *msg)
{
  if (reply(srv, client, ":%s!%s@%s %s\r\n",
	    srv->clients[sen].nickname,
            srv->clients[sen].username,
            srv->clients[sen].address,
            msg))
    return (1);
  return (0);
}

int is_client_in_channel(t_server *srv, Socket sock, int channel)
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

int			command_privmsg(t_server *srv, Socket sock, char *cmd)
{
  char			out[MESSAGE_MAX_SIZE];
  char cpy[MESSAGE_MAX_SIZE];
  char			*line;
  char			*target;
  char			*msg;
  int			channel;

  memset(cpy, 0, MESSAGE_MAX_SIZE);
  strcpy(cpy, cmd);
  line = strtok(cmd, " ");
  memset(out, 0, MESSAGE_MAX_SIZE);
  if (!(target = strtok(NULL, " ")))
    return (reply(srv, sock, "%s %s (%s)\r\n", "411",
                  replies[ERR_NORECIPIENT], line));
  if (*(msg = (strstr(cpy, target)) + strlen(target) + 1) != ':' ||
      &msg[1] == 0)
    return (reply(srv, sock, "%s %s\r\n", "412", replies[ERR_NOTEXTTOSEND]));
  if (snprintf(out, MESSAGE_MAX_SIZE, "PRIVMSG %s :%s",
               target, &msg[1]) < 0)
    return (1);
  if ((channel = is_channel(srv, target)) < 0)
    {
      if ((channel = is_client(srv, target)) < 0)
	return (reply(srv, sock , "%s %s %s\r\n", "401", target,
		      replies[ERR_NOSUCHNICK]));
      return (send_to_client(srv, sock, channel, out));
    }
  if (!is_client_in_channel(srv, sock, channel))
    reply(srv, sock, ":myirc 404 %s %s %s\r\n",
          srv->clients[sock].nickname, srv->channels[channel].name,
          replies[ERR_CANNOTSENDTOCHAN]);
  return (send_to_channel(sock, srv, &srv->channels[channel], out));
}
