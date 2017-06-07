/*
** socket.c for myirc in /home/brout_m/rendu/system/PSU_2016_myirc
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Wed May 31 11:43:50 2017 brout_m
** Last update Wed Jun  7 10:43:49 2017 brout_m
*/
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include "types.h"

int			accept_new_client(t_server *server)
{
  sockaddr_in_t	addr;
  socklen_t		len;
  int			sock;

  len = sizeof(addr);
  if ((sock = accept(server->server_socket, (sockaddr_t *)&addr, &len)) < 0 ||
      getsockname(sock, (sockaddr_t *)&addr, &len) < 0)
    {
      perror("Client accept error");
      return (1);
    }
  if (!strlen(server->address))
    strcat(server->address, inet_ntoa(addr.sin_addr));
  server->clients[sock].active = true;
  len = sizeof(addr);
  if (getpeername(sock, (sockaddr_t *)&addr, &len))
    return (1);
  strcat(server->clients[sock].address, inet_ntoa(addr.sin_addr));
  return (0);
}

static int		bind_and_listen(t_server *server, uint16_t port)
{
  sockaddr_in_t	addr;

  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = INADDR_ANY;
  if (bind(server->server_socket, (sockaddr_t const *)&addr, sizeof(addr)) < 0
      || listen(server->server_socket, 512) < 0)
    {
      perror("Server bind error");
      return (1);
    }
  return (0);
}

int			create_server_socket(t_server *server, uint16_t port)
{
  int			sock;
  int			ok;
  struct protoent	*pe;

  ok = 1;
  if (!(pe = getprotobyname("TCP")) ||
      (sock = socket(PF_INET, SOCK_STREAM, pe->p_proto)) < 0 ||
      setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &ok, sizeof(int)) < 0)
    {
      perror("Socket creation error");
      return (1);
    }
  server->server_socket = sock;
  return (bind_and_listen(server, port));
}
