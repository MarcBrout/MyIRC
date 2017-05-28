cmake_minimum_required(VERSION 3.6)
project(myirc)

set(CMAKE_C_STANDARD 99)

include_directories(
        /usr/include
        ./include
)

set(MYIRC
        ./include
        ./include/types.h
        include/socket.h
        include/proceed.h
        include/circular_tools.h
        src/server/circular_buffer.c
        src/server/server.c
        src/server/socket.c
        src/server/proceed.c
        src/server/server_init.c include/server.h src/server/proceed_commands.c src/server/replies.c include/replies.h src/server/command_pass.c include/commands.h src/server/command_nick.c src/server/command_quit.c)

add_executable(myirc ${MYIRC})