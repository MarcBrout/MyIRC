#-------------------------------------------------
#
# Project created by QtCreator 2017-05-24T18:17:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ../../client
TEMPLATE = app


SOURCES += main.cpp\
mainwindow.cpp\
../../src/com/connect_to_server.c\
../../src/com/proceed_client_commands.c\
../../src/com/get_select.c\
../../src/server/circular_buffer.c

HEADERS  += ../../include/mainwindow.hpp\
../../include/circular_tools.h\
../../include/client.h

FORMS    += mainwindow.ui
