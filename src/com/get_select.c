/*
** get_select.c for myirc in /home/brout_m/rendu/system/PSU_2016_myirc
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sat Jun  3 16:34:12 2017 brout_m
** Last update Wed Jun  7 10:45:02 2017 brout_m
*/
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include "client.h"

static int		write_out(t_client *client,
				  Socket sock,
				  char out[MESSAGE_MAX_SIZE], bool cond)
{
  size_t		len;
  ssize_t		written;
  ssize_t		notwritten;

  len = strlen(out);
  if (cond)
    {
      out[len] = '\r';
      out[len + 1] = '\n';
    }
  if ((written = write(sock, out, len + 2)) < 0)
    {
      perror("Write to server error");
      return (1);
    }
  notwritten = (len + 2) - written;
  if (notwritten > 0)
    {
      client->w.remains = true;
      client->w.pos -= notwritten > client->w.pos ?
	BUFFER_MAX_SIZE - (notwritten - client->w.pos) :
	client->w.pos - notwritten;
      client->w.len += notwritten;
    }
  return (0);
}

static int		send_client(t_client *client, Socket sock)
{
  size_t		len;
  char			out[MESSAGE_MAX_SIZE];

  memset(out, 0, MESSAGE_MAX_SIZE);
  while (strfromcircular(&client->w, out))
    {
      len = strlen(out);
      if (write_out(client, sock, out, len > 0))
	return (1);
      memset(out, 0, MESSAGE_MAX_SIZE);
    }
  return (write_out(client, sock, out, strlen(out) > 0));
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

static int		read_client(t_client *client, Socket sock)

{
  char			buff[MESSAGE_MAX_SIZE];
  ssize_t		len;

  memset(buff, 0, MESSAGE_MAX_SIZE);
  if ((len = read(sock, buff, 512)) < 0)
    {
      perror("Read from client error");
      return (1);
    }
  if (!len || strchr(buff, 4))
    {
      close(sock);
      memset(client, 0, sizeof(t_client));
      return (0);
    }
  if (strcmp(buff, "\r\n"))
    strncircular(&client->r, buff, len);
  return (0);
}

extern "C" int		get_select(t_client_data *data)
{
  struct timeval	tim;
  fd_set		reads;
  fd_set		writes;
  int			retval;

  FD_ZERO(&reads);
  FD_ZERO(&writes);
  FD_SET(data->sock, &reads);
  tim.tv_usec = 100;
  tim.tv_sec = 0;
  if (find_command(&data->client.w))
    FD_SET(data->sock, &writes);
  retval = select(data->sock + 1, &reads, &writes, NULL, &tim);
  if (retval < 0)
    return (1);
  if ((FD_ISSET(data->sock, &writes) &&
       write_client(&data->client, data->sock)) ||
      (FD_ISSET(data->sock, &reads) &&
       read_client(&data->client, data->sock)))
    return (1);
  return (0);
}
