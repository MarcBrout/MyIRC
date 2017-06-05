/*
** client.h for myirc in /home/brout_m/rendu/system/PSU_2016_myirc
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sat Jun  3 16:31:52 2017 brout_m
** Last update Sat Jun  3 16:33:03 2017 brout_m
*/
#ifndef CLIENT_H_
# define CLIENT_H_

# include <stdint.h>
# include "types.h"

typedef struct s_client_command		t_client_command;
typedef struct s_client_data		t_client_data;
typedef int				(*exec_t)(t_client_data *);

struct					s_client_command
{
  const char				*cmd;
  const int				len;
  const exec_t				exec;
};

struct					s_client_data
{
  t_client				client;
  Socket				sock;
  char					cmd[MESSAGE_MAX_SIZE];
  char					prefix[MESSAGE_MAX_SIZE];
};

int connect_to_server(t_client_data *data, char *address, uint16_t port);
int get_select(t_client_data *data);
int proceed_client_commands(t_client_data *data);

#endif /* !CLIENT_H_ */
