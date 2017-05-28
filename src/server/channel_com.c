#include <string.h>
#include <stdio.h>
#include "types.h"

int send_to_channel(Socket sender, t_server *srv,
                    t_channel *channel, char *message)
{
  Socket sock;
  int len;

  sock = 0;
  len = strlen(message);
  while (sock < FD_MAX)
  {
    if (sender != sock && channel->clients[sock] > 0)
      strncircular(&srv->clients[sock].w, message, len);
    ++sock;
  }
  return (0);
}

static int find_pos(int *tab, int find, size_t size)
{
  size_t i;

  i = 0;
  while (i < size)
  {
    if (tab[i] == find)
      return ((int)i);
    ++i;
  }
  return (-1);
}

static void reallign(int *tab, int value, size_t size)
{
  int pos;
  int sizei;

  sizei = (int)size;
  if ((pos = find_pos(tab, value, size)) != -1)
  {
    while (pos < sizei - 1)
    {
      tab[pos] = tab[pos + 1];
      ++pos;
    }
    tab[pos] = 0;
  }
}

void parting_from_channel(t_server *srv, Socket sock, int channel)
{
  reallign(srv->clients[sock].channels, channel,
           srv->clients[sock].channel_count);
  --(srv->clients[sock].channel_count);
  reallign(srv->channels[channel - 1].clients, sock,
           srv->channels[channel - 1].clients_count);
  --(srv->channels[channel - 1].clients_count);
}

int user_send_all_channel(Socket sender, t_server *srv, char *message)
{
  int index;
  int channel;

  index = 0;
  while (index < USER_MAX_CHAN)
  {
    channel = srv->clients[sender].channels[index];
    if (channel > 0)
    {
      if (send_to_channel(sender, srv, &srv->channels[channel - 1], message))
        return (1);
    }
    ++index;
  }
  return (0);
}