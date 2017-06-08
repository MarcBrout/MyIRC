/*
** command_nick.c for myirc in /home/brout_m/rendu/system/PSU_2016_myirc
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Wed May 31 11:27:44 2017 brout_m
** Last update Thu Jun  8 18:13:46 2017 brout_m
*/
#include <string.h>
#include <stdio.h>
#include "server.h"
#include "commands.h"
#include "channels.h"
#include "replies.h"

char const	*replies[ERR_END];

int		needmoreparams(t_server *srv, Socket sock, char *line)
{
  return (reply(srv, sock, "%s %s %s\r\n", "461", line,
                replies[ERR_NEEDMOREPARAMS]));
}

static int	check_disponibility(t_server *srv, char *nick)
{
  size_t	channel = 0;
  size_t	client = 0;

  while (channel < CHANNEL_MAX)
    {
      if (!strcasecmp(nick, srv->channels[channel].name))
	return (0);
      ++channel;
    }
  while (client < FD_MAX)
    {
      if (!strcasecmp(nick, srv->clients[client].nickname))
	return (0);
      ++client;
    }
  return (1);
}

static int	reply_to_client(t_server *srv, Socket sock,
				char old[MESSAGE_MAX_SIZE])
{
  return (reply(srv, sock, ":%s!%s@%s NICK %s\r\n",
                old,
                srv->clients[sock].username,
                srv->clients[sock].address,
                srv->clients[sock].nickname));
}

static int	ending_nick_command(t_server *srv, Socket sock,
				    char out[MESSAGE_MAX_SIZE],
                                    char old[MESSAGE_MAX_SIZE])
{
  if (srv->clients[sock].channel_count &&
      (snprintf(out, MESSAGE_MAX_SIZE, ":%s!%s@%s NICK %s\r\n",
                old, srv->clients[sock].username,
                srv->clients[sock].address,
                srv->clients[sock].nickname) < 0 ||
       send_all_channel_unique(srv, sock, out)))
    return (1);
  if (!strlen(srv->clients[sock].username))
    return (0);
  if (srv->clients[sock].connected)
    {
      if (srv->clients[sock].channel_count)
	return (0);
      return (reply_to_client(srv, sock, old));
    }
  srv->clients[sock].connected = true;
  return (reply(srv, sock, ":myirc 001 %s :%s %s!%s@%s\r\n",
                srv->clients[sock].nickname,
                replies[RPL_WELCOME],
                srv->clients[sock].nickname, srv->clients[sock].username,
                srv->address));
}

int		command_nick(t_server *srv, Socket sock, char *cmd)
{
  char		out[MESSAGE_MAX_SIZE];
  char		old[MESSAGE_MAX_SIZE];
  char		*line;

  strtok(cmd, " ");
  memset(out, 0, MESSAGE_MAX_SIZE);
  memset(old, 0, MESSAGE_MAX_SIZE);
  line = strtok(NULL, " ");
  if (!line)
    return (reply(srv, sock, "431 %s\r\n", replies[ERR_NONICKNAMEGIVEN]));
  if (strlen(line) >= NICKNAME_MAX_SIZE)
    return (reply(srv, sock, "432 %s %s\r\n", line,
                  replies[ERR_ERRONEUSNICKNAME]));
  if (!check_disponibility(srv, line))
    return (reply(srv, sock, "433 %s %s\r\n", line,
                  replies[ERR_NICKNAMEINUSE]));
  strcat(old, srv->clients[sock].nickname);
  memset(srv->clients[sock].nickname, 0, NICKNAME_MAX_SIZE);
  strcat(srv->clients[sock].nickname, line);
  return (ending_nick_command(srv, sock, out, old));
}
