//
// main.cpp for main in /home/duhieu_b/PSU/PSU_2016_myirc/client
//
// Made by duhieu_b
// Login   <benjamin.duhieu@epitech.eu>
//
// Started on  Tue Jun  6 15:57:11 2017 duhieu_b
// Last update Thu Jun  8 15:14:13 2017 brout_m
//

#include <QtWidgets/QApplication>
#include <iostream>
#include "mainwindow.hpp"

int main(int argc, char *argv[])
{
    try
    {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
	return a.exec();
    }
    catch (std::exception const &e)
    {
        std::cout << e.what() << std::endl;
	return (84);
    }
}
