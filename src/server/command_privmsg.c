/*
** command_privmsg.c for myirc in /home/brout_m/rendu/system/PSU_2016_myirc
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Wed May 31 11:30:33 2017 brout_m
** Last update Thu Jun  8 18:07:53 2017 brout_m
*/
#include <string.h>
#include <channels.h>
#include <stdio.h>
#include "replies.h"
#include "server.h"

char const		*replies[ERR_END];

int			send_to_client(t_server *srv, int sen,
				       int client, char *msg)
{
  if (reply(srv, client, ":%s!%s@%s %s\r\n",
	    srv->clients[sen].nickname,
            srv->clients[sen].username,
            srv->clients[sen].address,
            msg))
    return (1);
  return (0);
}

static int		end_privmsg(t_server *srv, Socket sock,
				    char *target, char out[MESSAGE_MAX_SIZE])
{
  int			channel;

  channel = -1;
  if ((channel = is_channel(srv, target)) < 0)
    {
      if ((channel = is_client(srv, target)) < 0)
	return (reply(srv, sock , "%s %s %s\r\n", "401", target,
		      replies[ERR_NOSUCHNICK]));
      return (send_to_client(srv, sock, channel, out));
    }
  if (!is_client_in_channel(srv, sock, channel))
    reply(srv, sock, ":myirc 404 %s %s %s\r\n", srv->clients[sock].nickname,
          srv->channels[channel].name, replies[ERR_CANNOTSENDTOCHAN]);
  return (send_to_channel(sock, srv, &srv->channels[channel], out));
}

int			command_privmsg(t_server *srv, Socket sock, char *cmd)
{
  char			out[MESSAGE_MAX_SIZE];
  char			cpy[MESSAGE_MAX_SIZE];
  char			*line;
  char			*target;
  char			*msg;

  memset(cpy, 0, MESSAGE_MAX_SIZE);
  strcpy(cpy, cmd);
  line = strtok(cmd, " ");
  memset(out, 0, MESSAGE_MAX_SIZE);
  if (!(target = strtok(NULL, " ")))
    return (reply(srv, sock, "%s %s (%s)\r\n", "411",
                  replies[ERR_NORECIPIENT], line));
  if (*(msg = (strstr(cpy, target)) + strlen(target) + 1) != ':' ||
      !(&msg[1]))
    return (reply(srv, sock, "%s %s\r\n", "412", replies[ERR_NOTEXTTOSEND]));
  if (snprintf(out, MESSAGE_MAX_SIZE, "PRIVMSG %s :%s", target, &msg[1]) < 0)
    return (1);
  return (end_privmsg(srv, sock, target, out));
}
