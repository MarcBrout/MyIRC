#include <string.h>
#include <stdio.h>
#include "replies.h"
#include "types.h"

int send_to_channel(Socket sender, t_server *srv,
                    t_channel *channel, char *message)
{
  Socket sock;

  sock = 0;
  while (sock < (int)channel->clients_count)
  {
    if (sender != sock)
    {
      printf("Sending to ... %d\n", channel->clients[sock]);
      reply(srv, channel->clients[sock], "%s :%s\r\n",
            srv->clients[sender].nickname, message);
    }
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
  printf("value = %d, size = %ld\n", value, size);
  if ((pos = find_pos(tab, value, size)) != -1)
  {
    printf("pos = %d\n", pos);
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
  reallign(srv->clients[sock].channels, channel + 1,
           srv->clients[sock].channel_count);
  --(srv->clients[sock].channel_count);
  reallign(srv->channels[channel].clients, sock,
           srv->channels[channel].clients_count);
  --(srv->channels[channel].clients_count);
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