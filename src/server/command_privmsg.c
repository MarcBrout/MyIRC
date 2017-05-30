#include <string.h>
#include <channels.h>
#include <stdio.h>
#include "replies.h"

char const *replies[ERR_END];

static int is_channel(t_server *srv, char const *channel)
{
  int i;

  i = 0;
  while (i < CHANNEL_MAX)
  {
    if (!strcmp(channel, srv->channels[i].name))
      return (i);
    ++i;
  }
  return (-1);
}

static int is_client(t_server *srv, char const *client)
{
  int i;

  i = 0;
  while (i < FD_MAX)
  {
    if (!strcmp(client, srv->clients[i].nickname) ||
        !strcmp(client, srv->clients[i].username))
      return (i);
    ++i;
  }
  return (-1);
}

static int send_to_client(t_server *srv, int sender,
                          int client, char *msg)
{
  if (reply(srv, client, ":%s :%s\r\n",
               srv->clients[sender].nickname, msg) < 0)
    return (1);
  return (0);
}

int command_privmsg(t_server *srv, Socket sock, char *cmd)
{
  char *line;
  char *target;
  char *msg;
  int channel;

  line = strtok(cmd, " ");
  if (!(target = strtok(NULL, " ")))
    return (reply(srv, sock, "%s %s (%s)\r\n", "411",
                  replies[ERR_NORECIPIENT], line));
  if (!(msg = strtok(NULL, ":")))
    return (reply(srv, sock, "%s %s\r\n", "412", replies[ERR_NOTEXTTOSEND]));
  if ((channel = is_channel(srv, target)) < 0)
  {
    if ((channel = is_client(srv, target)) < 0)
      return (reply(srv, sock , "%s %s %s\r\n", "401", target,
                    replies[ERR_NOSUCHNICK]));
    return (send_to_client(srv, sock, channel, msg));
  }
  return (send_to_channel(sock, srv, &srv->channels[channel], msg));
}