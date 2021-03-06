##
## Makefile for  in /home/brout_m/rendu/system/PSU_2016_myirc
##
## Made by brout_m
## Login   <marc.brout@epitech.eu>
##
## Started on  Wed May 24 23:04:21 2017 brout_m
## Last update Thu Jun  8 20:26:41 2017 brout_m
##

SERVER=		server

SERVER_FOLDER=	src/server/

SERVER_RAW_SRC=	circular_buffer.c	\
		proceed.c		\
		server.c		\
		socket.c		\
		server_init.c		\
		replies.c		\
		proceed_commands.c 	\
		proceed_writes.c	\
		server_tools.c		\
		command_pass.c		\
		command_nick.c 		\
		command_quit.c		\
		command_join.c 		\
		channel_com.c 		\
		command_part.c 		\
		command_privmsg.c 	\
		command_list.c 		\
		command_names.c 	\
		command_user.c


SERVER_SRC=	$(addprefix $(SERVER_FOLDER), $(SERVER_RAW_SRC))

SERVER_OBJ=	$(SERVER_SRC:.c=.o)

INC=		-I./include

CC=		gcc

CFLAGS=		-W -Wall -Werror $(INC)

ifeq ($(DEBUG),yes)
CFLAGS+=	-g3
endif

$(SERVER): $(SERVER_OBJ)
	$(CC) -o $(SERVER) $(SERVER_OBJ) $(INC)

client: $(SERVER)
	cp server client

gui:
	mv ./bonus/client/Makefile2 ./bonus/client/Makefile
	$(MAKE) -C ./bonus/client
	mv ./bonus/client/Makefile ./bonus/client/Makefile2

all: $(SERVER) gui

clean:
	rm -f $(SERVER_OBJ)
	mv ./bonus/client/Makefile2 ./bonus/client/Makefile
	$(MAKE) -C ./bonus/client clean
	mv ./bonus/client/Makefile ./bonus/client/Makefile2

fclean: clean
	rm -f $(SERVER)

re: fclean all

.PHONY: all clean fclean re client
