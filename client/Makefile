##
## Makefile for Makefile in /home/duhieu_b/PSU/PSU_2016_myirc/client
##
## Made by duhieu_b
## Login   <benjamin.duhieu@epitech.eu>
##
## Started on  Tue Jun  6 12:04:07 2017 duhieu_b
## Last update Tue Jun  6 16:41:30 2017 duhieu_b
##


CLIENT=			client

CLIENT_FOLDER=		./

SERVEUR_FOLDER= 	../src/

CLIENT_RAW_SRC=		main.cpp 			\
			mainwindow.cpp 			\

CLIENT_SERV_SRC=	com/connect_to_server.c 	\
			com/get_select.c 		\
			com/proceed_client_commands.c	\
			server/circular_buffer.c	\


CLIENT_SRC=		$(addprefix $(CLIENT_FOLDER), $(CLIENT_RAW_SRC))

CLIENT_SRCS=		$(addprefix $(SERVEUR_FOLDER), $(CLIENT_SERV_SRC))

CLIENT_OBJ=		$(CLIENT_SRC:.cpp=.o)

CLIENT_OBJ +=		$(CLIENT_SRCS:.c=.o);

LOCAL_CXXFLAGS= 	-I/usr/include/qt -I./../include

LOCAL_LDFLAGS += 	-L/usr/lib/Qt5 -lQt5Widgets -lQt5Core -lQt5Gui -Wl, -rpath=/usr/lib/Qt5
LOCAL_CXXFLAGS += 	-fPIC -I/usr/include/qt/QtWidgets -I/usr/include/qt/QtCore -I/usr/include/qt/ $(LOCAL_LDFLAGS)

CXX=			g++ -std=c++14

CFLAGS=			-W -Wall -Werror $(LOCAL_CXXFLAGS)

CXXFLAGS=       -W -Wall -Werror $(LOCAL_CXXFLAGS)

ifeq ($(DEBUG),yes)
CFLAGS+=		-g3
CXXFLAGS+=      -g3
endif

$(CLIENT): $(CLIENT_OBJ)
	$(CC) -o $(CLIENT) $(CLIENT_OBJ) $(LOCAL_LDFLAGS)

all: $(CLIENT)

clean:
	rm -f $(CLIENT_OBJ)

fclean: clean
	rm -f $(CLIENT)

re: fclean all

.PHONY: all clean fclean re client
