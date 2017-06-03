/*
** proceed_client_commands.c for  in /home/brout_m/rendu/system/PSU_2016_myirc
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sat Jun  3 16:36:33 2017 brout_m
** Last update Sat Jun  3 16:38:50 2017 brout_m
*/
#include <string.h>
#include "client.h"
#include "proceed.h"

int				unknown_cmd(t_client_data *data)
{
  (void)data;
  return (0);
}

static t_client_command const	commands[2] =
  {
    { "PRIVMSG", 7, &unknown_cmd },
    { NULL, 0, NULL }
  };

static int			processing(t_client_data *data)
{
  int				i;

  i = 0;
  while (commands[i].exec)
    {
      if (!strncasecmp(commands[i].cmd, data->cmd, commands[i].len))
	return (commands[i].exec(data));
      ++i;
    }
  return (unknown_cmd(data));
}

static void		remove_prefix(char cmd[MESSAGE_MAX_SIZE],
				      char prefix[MESSAGE_MAX_SIZE])
{
  int			i;
  int			j;

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

int			proceed_client_commands(t_client_data *data)
{
  while (find_command(&data->client.r) && !data->client.quit)
    {
      memset(data->cmd, 0, MESSAGE_MAX_SIZE);
      memset(data->prefix, 0, MESSAGE_MAX_SIZE);
      strfromcircular(&data->client.r, data->cmd);
      remove_prefix(data->cmd, data->prefix);
      if (processing(data))
	return (1);
    }
  return (0);
}
