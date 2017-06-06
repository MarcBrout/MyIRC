//
// main.cpp for main in /home/duhieu_b/PSU/PSU_2016_myirc/client
//
// Made by duhieu_b
// Login   <benjamin.duhieu@epitech.eu>
//
// Started on  Tue Jun  6 15:57:11 2017 duhieu_b
// Last update Tue Jun  6 15:57:13 2017 duhieu_b
//

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
