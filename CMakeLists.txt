cmake_minimum_required(VERSION 3.6)
project(myirc)

set(CMAKE_C_STANDARD 99)

include_directories(
        /usr/include
        ./include
)

set(MYIRC
        ./include
        )

add_executable(myirc ${MYIRC})