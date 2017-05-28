//
// Created by brout_m on 28/05/17.
//

#ifndef CHANNELS_H_
# define CHANNELS_H_

# include "types.h"

int send_to_channel(Socket sender, t_server *srv,
                    t_channel *channel, char *message);
int user_send_all_channel(Socket sender, t_server *srv, char *message);
void parting_from_channel(t_server *srv, Socket sock, int channel);


#endif /* !MYIRC_CHANNELS_H_ */
