#include <stdio.h>
#include <string.h>
#include "replies.h"

static void epur_str(char *cmd, char out[MESSAGE_MAX_SIZE])
{
  int i = 0;
  int j = 0;

  while (cmd[i])
  {
    if (i && cmd[i] == ' ' && cmd[i - 1] != ' ')
    {
      out[j] = ' ';
      ++j;
    }
    else if (cmd[i] != ' ')
    {
      out[j] = cmd[i];
      ++j;
    }
    ++i;
  }
  if (out[j] == ' ')
    out[j] = 0;
}

static bool verify_args(char out[MESSAGE_MAX_SIZE])
{
  int i = 0;
  int spaces = 0;

  while (out[i])
  {
    if (out[i] == ' ')
      ++spaces;
    if (spaces == 4)
      return (out[i + 1] == ':');
    ++i;
  }
  return (false);
}

int command_user(t_server *srv, Socket sock, char *cmd)
{
  char pure[MESSAGE_MAX_SIZE] = {};
  char cpy[MESSAGE_MAX_SIZE] = {};
  char name[USERNAME_MAX_SIZE] = {};
  char *line;
  char *param;

  strcat(cpy, cmd);
  line = strtok(cmd, " ");
  if (srv->clients[sock].connected)
    return (reply(srv, sock, "%s %s %s\r\n", "462", line,
                  replies[ERR_ALREADYREGISTRED]));
  if (!(param = strtok(NULL, " ")))
    return (needmoreparams(srv, sock, line));
  strcat(name, param);
  epur_str(cpy, pure);
  if (!verify_args(pure) || !strtok(NULL, " ") || !strtok(NULL, " "))
    return (needmoreparams(srv, sock, line));
  param = strtok(NULL, ":");
  strcat(srv->clients[sock].realname, param);
  strcat(srv->clients[sock].username, name);
  if (!strlen(srv->clients[sock].nickname))
    return (0);
  srv->clients[sock].connected = true;
  return (reply(srv, sock, "%s %s %s!%s@%s\r\n", "001", replies[RPL_WELCOME],
                srv->clients[sock].nickname, srv->clients[sock].username,
                srv->address));
}
