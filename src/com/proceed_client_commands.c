/*
** proceed_client_commands.c for  in /home/brout_m/rendu/system/PSU_2016_myirc
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sat Jun  3 16:36:33 2017 brout_m
** Last update Tue Jun  6 13:37:15 2017 duhieu_b
*/
#include <string.h>
#include "client.h"
#include "proceed.h"

extern "C" void		remove_prefix(char cmd[MESSAGE_MAX_SIZE],
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
