#ifndef TYPES_H_
# define TYPES_H_

# include <stdbool.h>
# include "circular_tools.h"

# define NICKNAME_MAX_SIZE 10
# define USERNAME_MAX_SIZE 513
# define USER_MAX_CHAN 10
# define FD_MAX 255
# define CHANNEL_MAX 50
# define CHANNEL_NAME_SIZE 201

enum e_rights
{
  USER = 0,
  OPERATOR
};

enum e_mode
{
  NORMAL = 0,
  INVITE
};

typedef int socket;
typedef struct s_client t_client;
typedef struct s_server t_server;
typedef struct s_channel t_channel;

struct s_channel
{
  enum e_mode mode;
  char name[CHANNEL_NAME_SIZE];
  socket clients[FD_MAX];
};

struct s_client
{
  bool connected;
  enum e_rights right;
  char nickname[NICKNAME_MAX_SIZE];
  char username[USERNAME_MAX_SIZE];
  int channels[USER_MAX_CHAN];
  t_circular c;
};

struct s_server
{
  socket server_socket;
  t_client clients[FD_MAX];
  t_channel channels[CHANNEL_MAX];
};

#endif /* !TYPES_H_ */