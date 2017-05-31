/*
** proceed_writes.c for myirc in /home/brout_m/rendu/system/PSU_2016_myirc
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Wed May 31 11:58:46 2017 brout_m
** Last update Wed May 31 11:59:43 2017 brout_m
*/
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "types.h"

static int		write_out(Socket sock,
				  char out[MESSAGE_MAX_SIZE], bool cond)
{
  size_t		len;

  len = strlen(out);
  if (cond)
    {
      out[len] = '\r';
      out[len + 1] = '\n';
    }
  if (write(sock, out, strlen(out)) < 0)
    {
      perror("Write to client error");
      return (1);
    }
  return (0);
}

static int		send_client(t_client *client, Socket sock)
{
  size_t		len;
  char			out[MESSAGE_MAX_SIZE];

  memset(out, 0, MESSAGE_MAX_SIZE);
  while (strfromcircular(&client->w, out) ||
         (strlen(out) && !strncmp("322", out, 3)))
    {
      len = strlen(out);
      if (write_out(sock, out, len && !strncmp("322", out, 3)))
	return (1);
      memset(out, 0, MESSAGE_MAX_SIZE);
    }
  return (write_out(sock, out, strlen(out) > 0));
}

static int		write_client(t_client *client, Socket sock)
{
  while (find_command(&client->w))
    {
      if (send_client(client, sock))
	return (1);
      if (client->quit)
	{
	  memset(client, 0, sizeof(*client));
	  close(sock);
	}
    }
  return (0);
}

int			proceed_writes(t_server *server, fd_set *fds_write)
{
  Socket		sock;

  sock = 0;
  while (sock < FD_MAX)
    {
      if (FD_ISSET(sock, fds_write) &&
	  write_client(&server->clients[sock], sock))
	return (1);
      ++sock;
    }
  return (0);
}
