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
../com/connect_to_server.c\
../com/proceed_client_commands.c\
../com/get_select.c\
../server/circular_buffer.c \
    moc_mainwindow.cpp

HEADERS  += ../../include/mainwindow.h\
../../include/circular_tools.h\
../../include/client.h \
    ui_mainwindow.h

FORMS    += mainwindow.ui
