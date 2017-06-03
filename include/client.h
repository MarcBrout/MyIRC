//
// Created by brout_m on 03/06/17.
//

#ifndef CLIENT_H_
# define CLIENT_H_

#include "types.h"

typedef struct s_client_command t_client_command;
typedef struct s_client_data t_client_data;
typedef int (*exec_t)(t_client_data *);

struct s_client_command
{
  const char *cmd;
  const int len;
  const exec_t exec;
};

struct s_client_data
{
  t_client *client;
  Socket sock;
  char cmd[MESSAGE_MAX_SIZE];
  char prefix[MESSAGE_MAX_SIZE];
};

int proceed_client_commands(t_client *client, Socket sock);
int get_select(Socket sock,  t_client *client);

#endif /* !MYIRC_CLIENT_H_ */
