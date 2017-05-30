#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include "socket.h"
#include "proceed.h"

static int send_client(t_client *client, Socket sock)
{
  size_t len;
  char out[MESSAGE_MAX_SIZE];

  memset(out, 0, MESSAGE_MAX_SIZE);
  while (strfromcircular(&client->w, out) ||
      (strlen(out) && !strncmp("322", out, 3)))
  {
    printf("OUT = %s\n", out);
    len = strlen(out);
    if (len && !strncmp("322", out, 3))
    {
      out[len] = '\r';
      out[len + 1] = '\n';
    }
    if (write(sock, out, strlen(out)) < 0)
    {
      perror("Write to client error");
      return (1);
    }
    memset(out, 0, MESSAGE_MAX_SIZE);
  }
  if ((len = strlen(out)))
  {
    out[len] = '\r';
    out[len + 1] = '\n';
    if (write(sock, out, strlen(out)) < 0)
    {
      perror("Write to client error");
      return (1);
    }
  }
  return (0);
}

static int write_client(t_client *client, Socket sock)
{
  printf("trying to find...\n");
  while (find_command(&client->w))
  {
    printf("found!...\n");
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

static int proceed_writes(t_server *server, fd_set *fds_write)
{
  Socket sock;

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

static int read_client(t_client *client, Socket sock)
{
  static char const ctrl_c[5] = {0xff, 0xf4, 0xff, 0xfd, 0x06};
  char buff[MESSAGE_MAX_SIZE];
  ssize_t len;

  memset(buff, 0, MESSAGE_MAX_SIZE);
  if ((len = read(sock, buff, 512)) < 0)
  {
    perror("Read from client error");
    return (1);
  }
  if (!len || strchr(buff, 4) ||
      (len == sizeof(ctrl_c) && !memcmp(buff, ctrl_c, sizeof(ctrl_c))))
  {
    printf("CTRLD\n");
    close(sock);
    memset(client, 0, sizeof(t_client));
    return (0);
  }
  printf("raw cmd = %s\n", buff);
  if (strcmp(buff, "\r\n"))
    strncircular(&client->r, buff, len);
  return (0);
}

static int proceed_reads(t_server *server, fd_set *fds_read)
{
  Socket sock;

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

int proceed(t_server *server, fd_set *fds_read, fd_set *fds_write)
{
  return (proceed_reads(server, fds_read) ||
      proceed_commands(server) ||
      proceed_writes(server, fds_write));
}
