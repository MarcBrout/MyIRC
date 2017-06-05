/*
** proceed_commands.c for myirc in /home/brout_m/rendu/system/PSU_2016_myirc
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Wed May 31 11:38:12 2017 brout_m
** Last update Sat Jun  3 16:45:33 2017 brout_m
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <replies.h>
#include "commands.h"
#include "proceed.h"

char const		*replies[ERR_END];

int			unsupported_cmd(t_server *srv, Socket sock, char *cmd)
{
  char			buff[MESSAGE_MAX_SIZE];
  char			*line;

  line = strtok(cmd, " ");
  memset(buff, 0, MESSAGE_MAX_SIZE);
  if (snprintf(buff, MESSAGE_MAX_SIZE - 1, "%s %s %s\r\n", "421",
               line, replies[ERR_UNKOWNCOMMAND]) < 0)
    return (1);
  strncircular(&srv->clients[sock].w, buff, strlen(buff));
  return (0);
}

static t_command const	commands[42] =
  {
    {"PASS", 4, &command_pass},
    {"NICK", 4, &command_nick},
    {"USER", 4, &command_user},
    {"SERVER", 6, &unsupported_cmd},
    {"OPER", 4, &unsupported_cmd},
    {"QUIT", 4, &command_quit},
    {"SQUIT", 5, &unsupported_cmd},
    {"JOIN", 4, &command_join},
    {"PART", 4, &command_part},
    {"MODE", 4, &unsupported_cmd},
    {"TOPIC", 5, &unsupported_cmd},
    {"NAMES", 5, &command_names},
    {"LIST", 4, &command_list},
    {"INVITE", 6, &unsupported_cmd},
    {"KICK", 4, &unsupported_cmd},
    {"VERSION", 7, &unsupported_cmd},
    {"STATS", 5, &unsupported_cmd},
    {"LINKS", 5, &unsupported_cmd},
    {"TIME", 4, &unsupported_cmd},
    {"CONNECT", 7, &unsupported_cmd},
    {"TRACE", 4, &unsupported_cmd},
    {"ADMIN", 5, &unsupported_cmd},
    {"INFO", 4, &unsupported_cmd},
    {"PRIVMSG", 7, &command_privmsg},
    {"NOTICE", 6, &unsupported_cmd},
    {"NOTICE", 6, &unsupported_cmd},
    {"WHO", 3, &unsupported_cmd},
    {"WHOIS", 5, &unsupported_cmd},
    {"WHOWAS", 6, &unsupported_cmd},
    {"KILL", 4, &unsupported_cmd},
    {"PING", 4, &unsupported_cmd},
    {"PONG", 4, &unsupported_cmd},
    {"ERROR", 5, &unsupported_cmd},
    {"AWAY", 4, &unsupported_cmd},
    {"REHASH", 6, &unsupported_cmd},
    {"RESTART", 7, &unsupported_cmd},
    {"SUMMON", 6, &unsupported_cmd},
    {"USERS", 5, &unsupported_cmd},
    {"WALLOPS", 7, &unsupported_cmd},
    {"USERHOST", 8, &unsupported_cmd},
    {"ISON", 4, &unsupported_cmd},
    {"NULL", 4, NULL}
  };

static void		remove_prefix(char cmd[MESSAGE_MAX_SIZE])
{
  int			i;

  if (cmd[0] == ':')
    {
      while (cmd[0] != ' ')
	{
	  i = 0;
	  while (cmd[i])
	    {
	      cmd[i] = cmd[i + 1];
	      ++i;
	    }
	}
      i = 0;
      while (cmd[i])
	{
	  cmd[i] = cmd[i + 1];
	  ++i;
	}
    }
}

static int		processing(t_server *srv,
				   Socket sock, char cmd[MESSAGE_MAX_SIZE])
{
  int			i;

  i = 0;
  while (commands[i].exec != NULL)
    {
      if (!strncasecmp(commands[i].cmd, cmd, commands[i].len) &&
	  (cmd[commands[i].len] == ' ' || !cmd[commands[i].len]))
	return (commands[i].exec(srv, sock, cmd));
      ++i;
    }
  return (unsupported_cmd(srv, sock, cmd));
}

int			proceed_commands(t_server *srv)
{
  char			cmd[MESSAGE_MAX_SIZE];
  Socket		sock;

  sock = 0;
  while (sock < FD_MAX)
    {
      while (find_command(&srv->clients[sock].r) && !srv->clients[sock].quit)
	{
	  memset(cmd, 0, MESSAGE_MAX_SIZE);
	  strfromcircular(&srv->clients[sock].r, cmd);
	  remove_prefix(cmd);
	  if (processing(srv, sock, cmd))
	    return (1);
	}
      ++sock;
    }
  return (0);
}
