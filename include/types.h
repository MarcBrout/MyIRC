/*
** types.h for myirc in /home/brout_m/rendu/system/PSU_2016_myirc
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Wed May 31 11:17:19 2017 brout_m
** Last update Wed May 31 11:19:55 2017 brout_m
*/

#ifndef TYPES_H_
# define TYPES_H_

# include <stddef.h>
# include <stdbool.h>
# include "circular_tools.h"

# define NICKNAME_MAX_SIZE 10
# define USERNAME_MAX_SIZE 513
# define USER_MAX_CHAN 10
# define FD_MAX 255
# define CHANNEL_MAX 51
# define CHANNEL_NAME_SIZE 201
# define IS_CBUFF_FULL(n) ((n).len > 0)

enum			e_rights
  {
    USER = 0,
    OPERATOR
  };

enum			e_mode
  {
    NORMAL = 0,
    INVITE
  };

typedef int		Socket;
typedef struct		s_client t_client;
typedef struct		s_server t_server;
typedef struct		s_channel t_channel;
typedef struct		sockaddr_in sockaddr_in_t;
typedef struct		sockaddr sockaddr_t;

struct			s_channel
{
  enum e_mode		mode;
  char			name[CHANNEL_NAME_SIZE];
  char			topic[MESSAGE_MAX_SIZE];
  size_t		clients_count;
  Socket		clients[FD_MAX];
};

struct			s_client
{
  bool			active;
  bool			connected;
  bool			quit;
  enum			e_rights right;
  char			nickname[NICKNAME_MAX_SIZE];
  char			username[USERNAME_MAX_SIZE];
  char			realname[MESSAGE_MAX_SIZE];
  size_t		channel_count;
  int			channels[USER_MAX_CHAN];
  t_circular		r;
  t_circular		w;
};

struct			s_server
{
  char			address[16];
  Socket		server_socket;
  t_client		clients[FD_MAX];
  t_channel		channels[CHANNEL_MAX];
};

#endif /* !TYPES_H_ */
