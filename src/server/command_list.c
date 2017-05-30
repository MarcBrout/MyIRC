#include <stdio.h>
#include <string.h>
#include "replies.h"

char const *replies[ERR_END];

static int add_to_list(t_server *srv, Socket sock,
                       t_channel *channel)
{
  printf("channel found : %s\n", channel->name);
  if (!strlen(channel->topic))
    return (reply(srv, sock, "322 %s :No topic set\r\n", channel->name));
  return (reply(srv, sock, "322 %s :%s\r\n", channel->name, channel->topic));
}

int command_list(t_server *srv, Socket sock, char *cmd)
{
  size_t i = 0;

  (void)cmd;
  while (i < CHANNEL_MAX)
  {
    if (strlen(srv->channels[i].name))
    {
      if (add_to_list(srv, sock, &srv->channels[i]))
        return (1);
      printf("ADDED CHANNEL... !%s!\n", srv->clients[sock].w.buffer);
    }
    ++i;
  }
  reply(srv, sock, "323 :%s\r\n", "End of LIST");
  return (0);
}
