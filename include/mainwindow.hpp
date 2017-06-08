/*
** mainwindow.h for mainwindow in /home/duhieu_b/PSU/PSU_2016_myirc/client
**
** Made by duhieu_b
** Login   <benjamin.duhieu@epitech.eu>
**
** Started on  Tue Jun  6 15:58:28 2017 duhieu_b
** Last update Wed Jun  7 01:05:24 2017 brout_m
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtCore/QTimer>
#include "client.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit                    MainWindow(QWidget *parent = 0);
    virtual			~MainWindow();

    void                        getJoin();
    void                        getUser();
    void                        getNick();
    void                        getList();
    void                        getNames();
    void                        getQuit();
    void                        getMsg();

private slots:
    void                        on_lineEdit_returnPressed();

    void                        on_pushButton_pressed();

private:
    void                        sendMessage();
    void                        sendName();
    void                        sendPass();
    void                        sendNick();
    void                        listChannel();
    void                        joinChannel();
    void                        quitChannel();
    void                        listNickNameServer();
    void                        listNickNameChannel();
    void                        sendSpecificMessage();
    void                        acceptFile();

    void                        writeOnBuffer();
    void                        proceedClientCommands();
    void                        connectServer();
    void                        processing();

    Ui::MainWindow              *ui;
    QTimer                      m_time;
    t_client_data               m_client;
    std::int32_t                m_curChannel;
    std::vector<std::string>    m_channels;
    bool                        m_enter;
};

typedef struct s_client_command		t_client_command;
typedef void                            (MainWindow::*exec_t)();

struct					s_client_command
{
    const char				*cmd;
    const int				len;
    exec_t                              exec;
};

#endif // MAINWINDOW_H
