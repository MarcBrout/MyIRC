#include <string.h>
#include <stdlib.h>
#include "types.h"

static void circular_init(t_circular *c)
{
  c->len = 0;
  c->pos = 0;
  memset(c->buffer, 0, MESSAGE_MAX_SIZE);
}

void client_init(t_client *client)
{
  client->active = false;
  client->connected = false;
  client->right = USER;
  memset(client->nickname, 0, NICKNAME_MAX_SIZE);
  memset(client->username, 0, USERNAME_MAX_SIZE);
  memset(client->channels, 0, USER_MAX_CHAN * sizeof(int));
  circular_init(&client->r);
  circular_init(&client->w);
}

void channel_init(t_channel *channel)
{
  channel->mode = NORMAL;
  memset(channel->name, 0, CHANNEL_NAME_SIZE);
  memset(channel->clients, 0, FD_MAX * sizeof(Socket));
}

t_server *server_init()
{
  // Socket sock;
  t_server *server;

  if (!(server = malloc(sizeof(t_server))))
    return (NULL);
  memset(server, 0, sizeof(t_server));
/*  server->server_socket = 0;
  sock = 0;
  while (sock < FD_MAX)
  {
    client_init(&server->clients[sock]);
    ++sock;
  }
  sock = 0;
  while (sock < CHANNEL_MAX)
  {
    channel_init(&server->channels[sock]);
    ++sock;
  } */
  return (server);
}