#include <signal.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "server.h"
#include "proceed.h"
#include "socket.h"

static bool gl_stop = false;

static inline void set_quit(int sig)
{
  (void)sig;
  gl_stop = true;
}

static int set_fds(t_server *server, fd_set *fds_read, fd_set *fds_write)
{
  Socket sock;
  int fd_max;

  sock = 0;
  FD_ZERO(fds_read);
  FD_ZERO(fds_write);
  FD_SET(server->server_socket, fds_read);
  fd_max = server->server_socket;
  while (sock < FD_MAX)
  {
    if (server->clients[sock].active)
    {
      FD_SET(sock, fds_read);
      if (find_command(&server->clients[sock].w))
        FD_SET(sock, fds_write);
      fd_max = sock;
    }
    ++sock;
  }
  return (fd_max + 1);
}

static int start_server(uint16_t port)
{
  fd_set fds_read;
  fd_set fds_write;
  t_server *server;
  Socket fd_max;

  server = server_init();
  if (create_server_socket(server, port))
    return (EXIT_FAILURE);
  while (!gl_stop)
  {
    fd_max = set_fds(server, &fds_read, &fds_write);
    if (select(fd_max, &fds_read, &fds_write, NULL, NULL) < 0)
    {
      perror("Select error");
      free(server);
      return (EXIT_FAILURE);
    }
    else if (proceed(server, &fds_read, &fds_write))
      return (EXIT_FAILURE);
  }
  free(server);
  return (EXIT_SUCCESS);
}

int main(int ac, char **av)
{
  uint16_t  port;
  struct sigaction action;

  if (ac < 2 || !strcmp(av[1], "--help"))
    return (printf("USAGE: %s port\n", av[0]));
  port = (uint16_t)atoi(av[1]);
  if (!port)
    return (printf("Port range [1-65535]\n") || EXIT_FAILURE);
  memset(&action, 0, sizeof(action));
  action.sa_handler = &set_quit;
  action.sa_flags = SA_SIGINFO;
  sigaction(SIGINT, &action, NULL);
  signal(SIGPIPE, SIG_IGN);
  return (start_server(port));
}