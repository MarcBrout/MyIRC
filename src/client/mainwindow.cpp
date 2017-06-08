//
// mainwindow.cpp for mainwindow in /home/duhieu_b/PSU/PSU_2016_myirc/client
//
// Made by duhieu_b
// Login   <benjamin.duhieu@epitech.eu>
//
// Started on  Tue Jun  6 15:57:26 2017 duhieu_b
// Last update Thu Jun  8 09:51:56 2017 duhieu_b
//

#include <QtWidgets/QWidget>
#include <iostream>
#include <sstream>
#include <cstring>
#include <map>
#include <sys/socket.h>
#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "circular_tools.h"
#include "client.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), m_time(this)
{
    ui->setupUi(this);
    connect(&m_time, &QTimer::timeout, this, &MainWindow::sendMessage);
    memset(&m_client, 0, sizeof(t_client_data));
    m_time.start(100);
    m_enter = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

static t_client_command	commands[10] =
  {
    { "PRIVMSG", 7, &MainWindow::getMsg},
    {"331", 3, &MainWindow::getJoin},
    {"332", 3, &MainWindow::getJoin},
    {"322", 3, &MainWindow::getList},
    {"323", 3, &MainWindow::getList},
    {"353", 3, &MainWindow::getNames},
    {"366", 3, &MainWindow::getNames},
    {"001", 3, &MainWindow::getNick},
    {"PART", 4, &MainWindow::getQuit},
    { NULL, 0, NULL}
  };


void MainWindow::writeOnBuffer()
{
    if (m_client.client.connected)
    {
        if (m_client.client.active)
        {
            static std::map<std::string, void (MainWindow::*)()> l_map =
            {
                {"/nick", &MainWindow::sendNick},
                {"/list", &MainWindow::listChannel},
                {"/join", &MainWindow::joinChannel},
                {"/part", &MainWindow::quitChannel},
                {"/users", &MainWindow::listNickNameServer},
                {"/names", &MainWindow::listNickNameChannel},
                {"/msg", &MainWindow::sendSpecificMessage},
                {"/accept_file", &MainWindow::acceptFile}
            };
            if (m_enter)
            {
                std::cout << ui->lineEdit->text().toStdString() << std::endl;
                std::map<std::string, void (MainWindow::*)()>::iterator l_it;
                for (l_it = l_map.begin(); l_it != l_map.end(); ++l_it)
                {
                    std::cout << "Line : " << l_it->first << " with length : " << l_it->first.length() << std::endl;
                    if (!strncmp(l_it->first.c_str(), ui->lineEdit->text().toStdString().c_str(), l_it->first.length()))
                    {
                        (this->*l_it->second)();
                        break;
                    }
                }
                if (l_it == l_map.end() && m_channels.size() >= 1)
                {
                    std::string l_msg;
                    std::string l_nick(m_client.client.nickname);

                    l_msg = "PRIVMSG " + m_channels[m_curChannel] + " :" + ui->lineEdit->text().toStdString() + "\r\n";
                    std::cout << "MSG :" << l_msg << std::endl;
                    strncircular(&m_client.client.w, l_msg.c_str(), l_msg.length());
                    ui->plainTextEdit->insertPlainText(QString::fromStdString(l_nick + ": " + l_msg.substr(l_msg.find(':')) + "\n"));
                }
            }
        }
        else
        {
         if (!m_client.client.sendName)
         {
             sendName();
             m_client.client.sendName = true;
         }
         else
         {
             sendPass();
             m_client.client.active = true;
         }
        }
    }
    else
        connectServer();
}

void MainWindow::listChannel()
{
    std::string l_msg;

    if (ui->lineEdit->text().toStdString().length() == 5)
        l_msg = "LIST\r\n";
    else
        l_msg = "LIST " + ui->lineEdit->text().toStdString().substr(ui->lineEdit->text().toStdString().find(" ") + 1) + "\r\n";
    std::cout << l_msg << std::endl;
    strncircular(&m_client.client.w, l_msg.c_str(), l_msg.length());
}

void MainWindow::joinChannel()
{
    std::string l_msg;

    if (m_channels.size() >= USER_MAX_CHAN)
        return;
    l_msg = "JOIN " + ui->lineEdit->text().toStdString().substr(ui->lineEdit->text().toStdString().find(" ") + 1) + "\r\n";
    std::cout << "I want to join :" << l_msg << std::endl;
    strncircular(&m_client.client.w, l_msg.c_str(), l_msg.length());
}

void MainWindow::quitChannel()
{
    std::string l_msg;

    l_msg = "PART " + ui->lineEdit->text().toStdString().substr(ui->lineEdit->text().toStdString().find(" ") + 1) + "\r\n";
    strncircular(&m_client.client.w, l_msg.c_str(), l_msg.length());
}

void MainWindow::listNickNameServer()
{
    std::string l_msg;

    l_msg = "NAMES\r\n";
    strncircular(&m_client.client.w, l_msg.c_str(), l_msg.length());
}

void MainWindow::listNickNameChannel()
{
    std::string l_msg;

    l_msg = "NAMES " + ui->lineEdit->text().toStdString().substr(ui->lineEdit->text().toStdString().find(" ") + 1) + "\r\n";
    strncircular(&m_client.client.w, l_msg.c_str(), l_msg.length());
}

void MainWindow::sendSpecificMessage()
{
    std::string l_msg;
    std::string l_nick(m_client.client.nickname);
    std::string l_text = ui->lineEdit->text().toStdString();
    std::string l_word[4];
    std::stringstream l_ssin(l_text);
    int l_i(0);

    while (l_ssin.good() && l_i < 4)
    {
        l_ssin >> l_word[l_i];
        ++l_i;
    }
    if (l_i == 3)
    {
        l_msg = "PRIVMSG " + l_word[1] + " :" + l_word[2] + "\r\n";
        std::cout << "MSG :" << l_msg << std::endl;
        strncircular(&m_client.client.w, l_msg.c_str(), l_msg.length());
    }
    else if (l_i == 4)
    {
        //TODO: Implement transfer file send
    }
}

void MainWindow::acceptFile()
{
    //TODO: Implement trasnfer file accept
}

void MainWindow::sendName()
{
    std::string l_msg;
    std::string l_user(m_client.client.username);
    std::string l_real(m_client.client.realname);

    l_msg = "USER " + l_user + " 0 * :" + l_real + "\r\n";
    std::cout << "Send : " << l_msg << std::endl;
    strncircular(&m_client.client.w, l_msg.c_str(), l_msg.length());
}

void MainWindow::sendPass()
{
    std::string l_msg;
    std::string l_pass(m_client.client.password);

    l_msg = "PASS " + ui->lineEdit->text().toStdString().substr(ui->lineEdit->text().toStdString().find(" ") + 1) + "\r\n";
    std::cout << "SEND : " << l_msg << std::endl;
    strncircular(&m_client.client.w, l_msg.c_str(), l_msg.length());
}

void MainWindow::sendNick()
{
    std::string l_msg;

    l_msg = "NICK " + ui->lineEdit->text().toStdString().substr(ui->lineEdit->text().toStdString().find(" ") + 1) + "\r\n";
    std::cout << "Send " << l_msg << std::endl;
    strncircular(&m_client.client.w, l_msg.c_str(), l_msg.length());
}

void MainWindow::connectServer()
{
    std::string l_text = ui->lineEdit->text().toStdString();
    std::string l_word[2];
    std::string l_delim(":");
    std::stringstream l_ssin(l_text);
    int l_i(0);

    l_word[0] = "";
    l_word[1] = "";
    if (l_text.length() >= 1)
      {
    while (l_ssin.good() && l_i < 2)
	  {
	    l_ssin >> l_word[l_i];
	    ++l_i;
	  }
    if (!l_word[0].compare("/server"))
	  {
        std::cout << l_word[0] << std::endl;
        std::cout << l_word[1] << std::endl;
        if (l_word[1].find(l_delim) == std::string::npos)
            return;
        std::string l_host = l_word[1].substr(0, l_word[1].find(l_delim));
        std::string l_port = l_word[1].substr(l_word[1].find(l_delim) + 1);
        if (l_port.length() > 1 && m_enter)
        {
            std::cout << l_port << std::endl;
            std::cout << l_host << std::endl;
            if (!(connect_to_server(&m_client, l_host.c_str(), static_cast<uint16_t>(stoi(l_port)))))
                m_client.client.connected = true;
        }
	  }
      }
}

void MainWindow::sendMessage()
{
    writeOnBuffer();
    get_select(&m_client);
    proceedClientCommands();
    m_time.start(100);
}

void MainWindow::proceedClientCommands()
{
    while (find_command(&m_client.client.r) && !m_client.client.quit)
    {
       memset(m_client.cmd, 0, MESSAGE_MAX_SIZE);
       memset(m_client.prefix, 0, MESSAGE_MAX_SIZE);
       strfromcircular(&m_client.client.r, m_client.cmd);
       remove_prefix(m_client.cmd, m_client.prefix);
       processing();
    }
}

void    MainWindow::getJoin()
{
    std::string l_msg(m_client.cmd);
    l_msg = l_msg.substr(4);
    std::cout << "JOINNNNNNNN" << std::endl;
    ui->plainTextEdit->insertPlainText(QString::fromStdString(l_msg + "\n"));
    l_msg = l_msg.substr(0, l_msg.find(' '));
    std::cout << l_msg << std::endl;
    std::vector<std::string>::iterator l_it = std::find(m_channels.begin(), m_channels.end(), l_msg);
    if (l_it != m_channels.end())
    {
        size_t i;
        for (i = 0; i < m_channels.size(); ++i)
        {
            if (m_channels[i] == *l_it)
                break;
        }
        m_curChannel = i;
    }
    else
    {
        m_channels.push_back(l_msg);
        m_curChannel = m_channels.size() - 1;
    }
}

void    MainWindow::getNick()
{
    std::string tmp(m_client.cmd);
    tmp = tmp.substr(tmp.find(' ') + 1);
    ui->plainTextEdit->insertPlainText(QString::fromStdString(tmp) + "\n");
    tmp = tmp.substr(42);
    tmp = tmp.substr(0, tmp.find('!'));
    strcpy(m_client.client.nickname, tmp.c_str());
}

void    MainWindow::getList()
{
    std::string l_msg(m_client.cmd);
    l_msg = l_msg.substr(5);
    ui->plainTextEdit->insertPlainText(QString::fromStdString(l_msg + "\n"));
}

void    MainWindow::getNames()
{
    std::string l_msg(m_client.cmd);
    l_msg = l_msg.substr(4);
    ui->plainTextEdit->insertPlainText(QString::fromStdString(l_msg + "\n"));
}

void    MainWindow::getQuit()
{
    std::string l_msg(m_client.cmd);
    ui->plainTextEdit->insertPlainText(QString::fromStdString(l_msg + "\n"));
    l_msg = l_msg.substr(5);
    std::vector<std::string>::iterator l_it = std::find(m_channels.begin(), m_channels.end(), l_msg);
    if (l_it != m_channels.end())
    {
        m_channels.erase(l_it);
        ui->plainTextEdit->insertPlainText("Quit " + QString::fromStdString(*l_it) + "channel\n");
    }
}

void    MainWindow::getMsg()
{
    std::string l_msg(m_client.cmd);
    l_msg = l_msg.substr(8);
    ui->plainTextEdit->insertPlainText(QString::fromStdString(l_msg + "\n"));
}

void    MainWindow::getError()
{
    std::string l_msg;

    l_msg = l_msg.substr(4);
    ui->plainTextEdit->insertPlainText("Error : " + QString::fromStdString(l_msg + "\n"));
}

void MainWindow::processing()
{
    int i(0);

    while (commands[i].exec)
    {
        exec_t &ex = commands[i].exec;
        std::cout << "serv: " << commands[i].cmd << std::endl;
        if (!strncasecmp(commands[i].cmd, m_client.cmd, commands[i].len))
        {
            (this->*ex)();
            break;
        }
        ++i;
    }
    if (i == 9)
    {
        getError();
    }
}

void MainWindow::on_lineEdit_returnPressed()
{
    m_enter = true;
    sendMessage();
    ui->lineEdit->clear();
    m_enter = false;
}

void MainWindow::on_pushButton_pressed()
{
    if (ui->lineEdit_2->text() != "" &&
        ui->lineEdit_3->text() != "" &&
        ui->lineEdit_4->text() != "")
    {
        if (ui->lineEdit_2->text().length() >= MESSAGE_MAX_SIZE)
            ui->lineEdit_2->text().toStdString() = ui->lineEdit_2->text().toStdString().substr(MESSAGE_MAX_SIZE);
        if (ui->lineEdit_3->text().length() >= PASSWORD_MAX_SIZE)
            ui->lineEdit_3->text().toStdString() = ui->lineEdit_2->text().toStdString().substr(PASSWORD_MAX_SIZE);
        if (ui->lineEdit_4->text().length() >= USERNAME_MAX_SIZE)
            ui->lineEdit_4->text().toStdString() = ui->lineEdit_2->text().toStdString().substr(USERNAME_MAX_SIZE);
        strcpy(m_client.client.realname, ui->lineEdit_2->text().toStdString().c_str());
        strcpy(m_client.client.password, ui->lineEdit_3->text().toStdString().c_str());
        strcpy(m_client.client.username, ui->lineEdit_4->text().toStdString().c_str());
        ui->mdiArea->close();
    }
    else
    {
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
    }
}
