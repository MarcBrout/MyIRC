#include <string.h>
#include <stdio.h>
#include "replies.h"

char const *replies[ERR_END];

int needmoreparams(t_server *srv, Socket sock, char *line)
{
  return (reply(srv, sock, "%s %s %s\r\n", "461", line,
                replies[ERR_NEEDMOREPARAMS]));
}

int command_user(t_server *srv, Socket sock, char *cmd)
{
  char *line;
  char *param;

  line = strtok(cmd, " ");
  if (srv->clients[sock].connected)
    return (reply(srv, sock, "%s %s %s\r\n", "462", line,
                  replies[ERR_ALREADYREGISTRED]));
  if (!(param = strtok(NULL, " ")))
    return (needmoreparams(srv, sock, line));
  strcat(srv->clients[sock].username, param);
  if (!(param = strtok(NULL, " ")) || !(param = strtok(NULL, " ")) ||
      !(param = strtok(NULL, " ")))
    return (needmoreparams(srv, sock, line));
  strcat(srv->clients[sock].realname, &param[1]);
  if (!strlen(srv->clients[sock].nickname))
    return (0);
  srv->clients[sock].connected = true;
  return (reply(srv, sock, "%s %s %s!%s@%s\r\n", "001", replies[RPL_WELCOME],
                srv->clients[sock].nickname, srv->clients[sock].username,
                srv->address));
}

int command_nick(t_server *srv, Socket sock, char *cmd)
{
  char *line;

  strtok(cmd, " ");
  line = strtok(NULL, " ");
  if (!line)
    return (reply(srv, sock, "%s %s\r\n", "431", replies[ERR_NONICKNAMEGIVEN]));
  if (strlen(line) >= NICKNAME_MAX_SIZE)
    return (reply(srv, sock, "%s %s %s\r\n", "432", line,
                  replies[ERR_ERRONEUSNICKNAME]));
  strcat(srv->clients[sock].nickname, line);
  if (!strlen(srv->clients[sock].username))
    return (0);
  printf("nick ok\n");
  srv->clients[sock].connected = 1;
  return (reply(srv, sock, "%s %s %s!%s@%s\r\n", "001", replies[RPL_WELCOME],
                srv->clients[sock].nickname, srv->clients[sock].username,
                srv->address));
}
