//
// Created by brout_m on 28/05/17.
//

#include <string.h>
#include "channels.h"
#include "commands.h"
#include "replies.h"

char const *replies[ERR_END];

static int channel_part(t_server *srv, Socket sock, int channel, char *msg)
{
  if (send_to_channel(sock, srv, &srv->channels[channel - 1], msg))
    return (1);
  parting_from_channel(srv, sock, channel);
  return (0);
}

int command_part(t_server *srv, Socket sock, char *cmd)
{
  char *line;
  char *name;
  char *message;
  int channel;

  line = strtok(cmd, " ");
  if (!(name = strtok(NULL, " ")))
    return (needmoreparams(srv, sock, line));
  if ((channel = find_channel(srv, name)) < 0)
    return (reply(srv, sock, "%s %s %s\r\n", "403", name,
                  replies[ERR_NOSUCHCHANNEL]));
  if (!already_in_channel(srv, sock, channel))
    return (reply(srv, sock, "%s %s %s\r\n", "442", name,
                  replies[ERR_NOTONCHANNEL]));
  message = strtok(NULL, " ");
  if (message)
    return (channel_part(srv, sock, channel, &message[1]));
  return (channel_part(srv, sock, channel, srv->clients[sock].nickname));
}