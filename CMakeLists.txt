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
        main.c server/circular_buffer.c include/circular_tools.h)

add_executable(myirc ${MYIRC})