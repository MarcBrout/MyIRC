#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include "socket.h"
#include "server.h"
#include "circular_tools.h"

int proceed_writes(t_server *server, fd_set *fds_write)
{
  Socket sock;

  sock = 0;
  (void)server;
  while (sock < FD_MAX)
  {
    if (FD_ISSET(sock, fds_write))
    {
      //TODO write function
    }
    ++sock;
  }
  return (0);
}

int proceed_reads(t_server *server, fd_set *fds_read)
{
  static char ctrl_c[5] = {0xff, 0xf4, 0xff, 0xfd, 0x06};
  Socket sock;
  ssize_t len;
  char buff[MESSAGE_MAX_SIZE];
  char out[MESSAGE_MAX_SIZE];

  sock = 0;
  while (sock < FD_MAX)
  {
    if (FD_ISSET(sock, fds_read))
    {
      if (sock == server->server_socket && accept_new_client(server))
          return (1);
      else if (sock != server->server_socket)
      {
        memset(buff, 0, MESSAGE_MAX_SIZE);
        memset(out, 0, MESSAGE_MAX_SIZE);
        if ((len = read(sock, buff, 512)) < 0)
          return (1);
        if (len == sizeof(ctrl_c) && !memcmp(buff, ctrl_c, sizeof(ctrl_c)))
        {
          close(sock);
          memset(&server->clients[sock], 0, sizeof(t_client));
          return (0);
        }
        printf("len %ld raw = %s\n", len, buff);
        strncircular(&server->clients[sock].r, buff, len);
        strfromcircular(&server->clients[sock].r, out);
        printf("received : %s\n", out);
      }
    }
    ++sock;
  }
  return (0);
}

int proceed(t_server *server, fd_set *fds_read, fd_set *fds_write)
{
  return (proceed_reads(server, fds_read) ||
      proceed_writes(server, fds_write));
}
