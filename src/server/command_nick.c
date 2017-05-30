#include <string.h>
#include <stdio.h>
#include "replies.h"

char const *replies[ERR_END];

int needmoreparams(t_server *srv, Socket sock, char *line)
{
  return (reply(srv, sock, "%s %s %s\r\n", "461", line,
                replies[ERR_NEEDMOREPARAMS]));
}

static int check_disponibility(t_server *srv, char *nick)
{
  size_t channel = 0;
  size_t client = 0;

  while (channel < CHANNEL_MAX)
  {
    if (!strcmp(nick, srv->channels[channel].name))
      return (0);
    ++channel;
  }
  while (client < FD_MAX)
  {
    if (!strcmp(nick, srv->clients[client].nickname))
      return (0);
    ++client;
  }
  return (1);
}

int command_nick(t_server *srv, Socket sock, char *cmd)
{
  char *line;

  strtok(cmd, " ");
  line = strtok(NULL, " ");
  if (!line)
    return (reply(srv, sock, "431 %s\r\n", replies[ERR_NONICKNAMEGIVEN]));
  if (strlen(line) >= NICKNAME_MAX_SIZE)
    return (reply(srv, sock, "432 %s %s\r\n", line,
                  replies[ERR_ERRONEUSNICKNAME]));
  if (!check_disponibility(srv, line))
    return (reply(srv, sock, "433 %s %s\r\n", line,
                  replies[ERR_NICKNAMEINUSE]));
  strcat(srv->clients[sock].nickname, line);
  if (!strlen(srv->clients[sock].username))
    return (0);
  srv->clients[sock].connected = true;
  return (reply(srv, sock, "001 %s %s!%s@%s\r\n", replies[RPL_WELCOME],
                srv->clients[sock].nickname, srv->clients[sock].username,
                srv->address));
}
