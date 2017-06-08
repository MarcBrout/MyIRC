/*
** proceed.c for myirc in /home/brout_m/rendu/system/PSU_2016_myirc
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Wed May 31 11:34:28 2017 brout_m
** Last update Wed May 31 11:38:06 2017 brout_m
*/
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include "socket.h"
#include "proceed.h"

static int		read_client(t_client *client, Socket sock)
{
  static char const	ctrl_c[5] = {0xff, 0xf4, 0xff, 0xfd, 0x06};
  char			buff[MESSAGE_MAX_SIZE];
  ssize_t		len;

  memset(buff, 0, MESSAGE_MAX_SIZE);
  if ((len = read(sock, buff, 512)) < 0)
    {
      perror("Read from client error");
      memset(client, 0, sizeof(t_client));
      return (0);
    }
  if (!len || strchr(buff, 4) ||
      (len == sizeof(ctrl_c) && !memcmp(buff, ctrl_c, sizeof(ctrl_c))))
    {
      close(sock);
      memset(client, 0, sizeof(t_client));
      return (0);
    }
  if (strcmp(buff, "\r\n"))
    strncircular(&client->r, buff, len);
  return (0);
}

static int		proceed_reads(t_server *server, fd_set *fds_read)
{
  Socket		sock;

  sock = 0;
  while (sock < FD_MAX)
    {
      if (FD_ISSET(sock, fds_read))
	{
	  if ((sock == server->server_socket && accept_new_client(server)) ||
	      (sock != server->server_socket &&
	       read_client(&server->clients[sock], sock)))
	    return (1);
	}
      ++sock;
    }
  return (0);
}

int			proceed(t_server *server,
				fd_set *fds_read, fd_set *fds_write)
{
  return (proceed_reads(server, fds_read) ||
	  proceed_commands(server) ||
	  proceed_writes(server, fds_write));
}
