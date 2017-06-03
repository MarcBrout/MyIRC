//
// Created by brout_m on 03/06/17.
//

#include <string.h>
#include "client.h"
#include "proceed.h"

int unknown_cmd(t_client_data *data)
{
  return (0);
}

static t_client_command const	commands[2] =
    {
        { "PRIVMSG", 7, &unknown_cmd },
        { NULL, 0, NULL }
    };


static int processing(t_client_data *data)
{
  int i;

  i = 0;
  while (commands[i].exec)
  {
    ++i;
  }
  if (commands[i].exec == NULL)
    return (unknown_cmd(data));
}

static void		remove_prefix(char cmd[MESSAGE_MAX_SIZE],
                                         char prefix[MESSAGE_MAX_SIZE])
{
  int			i;
  int                   j;

  if (cmd[0] == ':')
  {
    j = 0;
    while (cmd[0] != ' ')
    {
      i = 0;
      prefix[j] = cmd[0];
      while (cmd[i])
      {

        cmd[i] = cmd[i + 1];
        ++i;
      }
      ++j;
    }
    i = 0;
    while (cmd[i])
    {
      cmd[i] = cmd[i + 1];
      ++i;
    }
    prefix[j] = 0;
  }
}

int proceed_client_commands(t_client *client, Socket sock)
{
  t_client_data data;

  data.sock = sock;
  data.client = client;
  while (find_command(&client->r) && !client->quit)
  {
    memset(data.cmd, 0, MESSAGE_MAX_SIZE);
    memset(data.prefix, 0, MESSAGE_MAX_SIZE);
    strfromcircular(&client->r, data.cmd);
    remove_prefix(data.cmd, data.prefix);
    if (processing(&data))
      return (1);
  }
  return (0);
}