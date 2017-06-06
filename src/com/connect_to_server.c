/*
** connect_to_server.c for  in /home/brout_m/rendu/system/PSU_2016_myirc
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sat Jun  3 16:33:27 2017 brout_m
** Last update Tue Jun  6 13:37:00 2017 duhieu_b
*/
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "client.h"

int			connect_to_server(t_client_data *data,
					  const char *address, uint16_t port)
{
  Socket		sock;
  sockaddr_in_t		add;
  int			ok;
  struct protoent	*pe;

  ok = 1;
  add.sin_family = AF_INET;
  add.sin_port = htons(port);
  add.sin_addr.s_addr = inet_addr(address);
  if (!(pe = getprotobyname("TCP")) ||
      (sock = socket(PF_INET, SOCK_STREAM, pe->p_proto)) < 0 ||
      setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &ok, sizeof(int)) < 0 ||
      connect(sock, (const sockaddr_t *)&add, sizeof(add)) < 0)
    {
      perror("Server Connection error");
      return (1);
    }
  data->sock = sock;
  return (0);
}
