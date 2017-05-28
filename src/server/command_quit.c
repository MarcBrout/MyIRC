#include <string.h>
#include "replies.h"

int command_quit(t_server *srv, Socket sock, char *cmd)
{
  char *param;

  strtok(cmd, " ");
  if ((param = strtok(NULL, " ")))
  {
    //TODO copy to all channel quit message
  }
  srv->clients[sock].quit = true;
  return (reply(srv, sock, "%s :%s\r\n", "ERROR", "Client quit"));
}

