##
## Makefile for  in /home/brout_m/rendu/system/PSU_2016_myirc
##
## Made by brout_m
## Login   <marc.brout@epitech.eu>
##
## Started on  Wed May 24 23:04:21 2017 brout_m
## Last update Thu May 25 00:33:35 2017 brout_m
##

SERVER=		server

SERVER_FOLDER=	src/server/

SERVER_RAW_SRC=	circular_buffer.c	\
		proceed.c		\
		server.c		\
		socket.c		\
		server_init.c

SERVER_SRC=	$(addprefix $(SERVER_FOLDER), $(SERVER_RAW_SRC))

SERVER_OBJ=	$(SERVER_SRC:.c=.o)

INC=		-I./include

CC=		gcc

CFLAGS=		-W -Wall -Werror -Ofast $(INC)

ifeq ($(DEBUG),yes)
CFLAGS+=	-g3
endif

$(SERVER): $(SERVER_OBJ)
	$(CC) -o $(SERVER) $(SERVER_OBJ) $(INC)

all: $(SERVER)

clean:
	rm -f $(SERVER_OBJ)

fclean: clean
	rm -f $(SERVER)

re: fclean all

.PHONY: all clean fclean re
