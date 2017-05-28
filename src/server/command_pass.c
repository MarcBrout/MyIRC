#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "replies.h"

char const *replies[ERR_END];

int reply(t_server *srv, Socket sock, char *const fmt, ...)
{
  static char buff[MESSAGE_MAX_SIZE];
  va_list val;

  memset(buff, 0, MESSAGE_MAX_SIZE);
  va_start(val, fmt);
  if (vsnprintf(buff, MESSAGE_MAX_SIZE - 1, fmt, val) < 0)
    return (1);
  strncircular(&srv->clients[sock].w, buff, strlen(buff));
  va_end(val);
  return (0);
}

int command_pass(t_server *srv, Socket sock, char *cmd)
{
  static char const *password = "password";
  char *line;
  char *line2;

  line = strtok(cmd, " ");
  if (srv->clients[sock].connected)
    return (reply(srv, sock, "%s %s %s\r\n", "462", line,
                  replies[ERR_ALREADYREGISTRED]));
  line2 = strtok(NULL, " ");
  if (!line2)
    return (reply(srv, sock, "%s %s %s\r\n", "461", line,
                  replies[ERR_NEEDMOREPARAMS]));
  if (strcmp(password, line2))
    return (reply(srv, sock, "%s %s\r\n", "464", replies[ERR_PASSWDMISMATCH]));
  srv->clients[sock].connected = true;
  return (0);
}