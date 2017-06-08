/*
** client.h for myirc in /home/brout_m/rendu/system/PSU_2016_myirc
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sat Jun  3 16:31:52 2017 brout_m
** Last update Thu Jun  8 18:14:26 2017 brout_m
*/
#ifdef __cplusplus
extern "C" {
#endif

#ifndef CLIENT_H_
# define CLIENT_H_

# include <stdint.h>
# include "types.h"

typedef struct s_client_data	t_client_data;

struct				s_client_data
{
  t_client			client;
  Socket			sock;
  char				cmd[MESSAGE_MAX_SIZE];
  char				prefix[MESSAGE_MAX_SIZE];
};

extern "C" int connect_to_server(t_client_data *data,
                                 const char *address,
                                 uint16_t port);
extern "C" int get_select(t_client_data *data);
extern "C" void remove_prefix(char cmd[MESSAGE_MAX_SIZE],
                              char prefix[MESSAGE_MAX_SIZE]);
#endif /* !CLIENT_H_ */

#ifdef __cplusplus
}
#endif
