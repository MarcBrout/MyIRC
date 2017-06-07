/*
** command_part.c for myirc in /home/brout_m/rendu/system/PSU_2016_myirc
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Wed May 31 11:28:25 2017 brout_m
** Last update Wed Jun  7 10:39:11 2017 brout_m
*/
#include <stdio.h>
#include <string.h>
#include "channels.h"
#include "commands.h"
#include "replies.h"

char const	*replies[ERR_END];

static int	channel_part(t_server *srv, Socket sock,
			     int channel, char *msg)
{
  if (send_to_channel(sock, srv, &srv->channels[channel], msg))
    return (1);
  parting_from_channel(srv, sock, channel);
  if (!srv->channels[channel].clients_count)
    memset(&srv->channels[channel], 0, sizeof(t_channel));
  return (0);
}

int		command_part(t_server *srv, Socket s, char *cmd)
{
  char		to_send[MESSAGE_MAX_SIZE];
  char		*message;
  char		*line;
  char		*name;
  int		channel;

  line = strtok(cmd, " ");
  if (!(name = strtok(NULL, " ")))
    return (needmoreparams(srv, s, line));
  if ((channel = find_channel(srv, name)) < 0)
    return (reply(srv, s, "403 %s %s\r\n", name, replies[ERR_NOSUCHCHANNEL]));
  if (!already_in_channel(srv, s, channel))
    return (reply(srv, s, "442 %s %s\r\n", name, replies[ERR_NOTONCHANNEL]));
  memset(to_send, 0, MESSAGE_MAX_SIZE);
  message = strtok(NULL, " ");
  if (message)
    {
      if (snprintf(to_send, MESSAGE_MAX_SIZE, "PART %s :\"%s\"",
		   srv->channels[channel].name, message) < 0)
	return (1);
    }
  else if (snprintf(to_send, MESSAGE_MAX_SIZE, "PART %s",
		    srv->channels[channel].name) < 0)
    return (1);
  return (channel_part(srv, s, channel, to_send));
}
