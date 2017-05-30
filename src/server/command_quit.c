#include <string.h>
#include "replies.h"
#include "channels.h"

static void parting_from_all_channel(t_server *srv, int sock)
{
  t_client *client;
  size_t i;

  i = 0;
  client = &srv->clients[sock];
  while (i < client->channel_count)
  {
    parting_from_channel(srv, sock, client->channels[i]);
    ++i;
  }
}

int command_quit(t_server *srv, Socket sock, char *cmd)
{
  static char *quit = "Quit";
  char *param;

  strtok(cmd, " ");
  if (!(param = strtok(NULL, ":")))
  {
    if (user_send_all_channel(sock, srv, quit))
      return (1);
  }
  else
  {
    if (user_send_all_channel(sock, srv, param))
      return (1);
  }
  parting_from_all_channel(srv, sock);
  srv->clients[sock].quit = true;
  return (reply(srv, sock, "%s :%s\r\n", "ERROR", "Client quit"));
}