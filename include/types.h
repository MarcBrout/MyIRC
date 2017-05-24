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
# define IS_CBUFF_FULL(n) ((n).len > 0)

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

typedef int Socket;
typedef struct s_client t_client;
typedef struct s_server t_server;
typedef struct s_channel t_channel;
typedef struct sockaddr_in sockaddr_in_t;
typedef struct sockaddr	sockaddr_t;

struct s_channel
{
  enum e_mode mode;
  char name[CHANNEL_NAME_SIZE];
  Socket clients[FD_MAX];
};

struct s_client
{
  bool active;
  bool connected;
  enum e_rights right;
  char nickname[NICKNAME_MAX_SIZE];
  char username[USERNAME_MAX_SIZE];
  int channels[USER_MAX_CHAN];
  t_circular r;
  t_circular w;
};

struct s_server
{
  Socket server_socket;
  t_client clients[FD_MAX];
  t_channel channels[CHANNEL_MAX];
};

#endif /* !TYPES_H_ */