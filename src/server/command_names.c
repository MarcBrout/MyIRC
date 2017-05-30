#include <string.h>
#include "commands.h"
#include "replies.h"

char const *replies[ERR_END];

static int list_one_channel_names(t_server *srv, Socket sock,
                                  t_channel *channel)
{
  size_t i = 0;

  if (reply(srv, sock, "353 %s :", channel->name))
    return (1);
  while (i < channel->clients_count)
  {
    if (reply(srv, sock, "%s", srv->clients[channel->clients[i]].nickname))
      return (1);
    if (i < channel->clients_count - 1 &&
        reply(srv, sock, " "))
      return (1);
    ++i;
  }
  return (reply(srv, sock, "\r\n366 %s :End of NAMES list\r\n",
                channel->name));
}

static int list_all_channels_names(t_server *srv, Socket sock)
{
  size_t  i = 0;

  while (i < CHANNEL_MAX)
  {
    if (strlen(srv->channels[i].name) > 0 &&
        list_one_channel_names(srv, sock, &srv->channels[i]))
      return (1);
    ++i;
  }
  return (0);
}

int command_names(t_server *srv, Socket sock, char *cmd)
{
  char *param;
  int channel;

  strtok(cmd, " ");
  if (!(param = strtok(NULL, " ")))
    return (list_all_channels_names(srv, sock));
  if ((channel = find_channel(srv, param)) >= 0)
    return (list_one_channel_names(srv, sock, &srv->channels[channel]));
  return (reply(srv, sock, "366 %s :End of NAMES list\r\n", param));
}
