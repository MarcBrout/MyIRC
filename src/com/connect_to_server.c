/*
** connect_to_server.c for  in /home/brout_m/rendu/system/PSU_2016_myirc
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sat Jun  3 16:33:27 2017 brout_m
** Last update Sat Jun  3 16:39:16 2017 brout_m
*/
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "client.h"

int			connect_to_server(t_client_data *data,
					  char *address, uint16_t port)
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

/* MAIN EXAMPLE
int main(int ac, char **av)
{
  uint16_t port = atoi(av[2]);
  t_client_data client;

  memset(&client, 0, sizeof(t_client_data));
  if (connect_to_server(&client, av[1], port))
    return (1);
  while (1)
  {
    if (get_select(&client))
      return (1);
    if (proceed_client_commands(&client))
      return (1);
  }
}
