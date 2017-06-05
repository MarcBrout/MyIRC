#include <QWidget>
#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), m_time(this)
{
    ui->setupUi(this);
    connect(&m_time, &QTimer::timeout, this, &MainWindow::sendMessage);
    m_time.start(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendMessage()
{
    m_time.start(1);

}

void MainWindow::on_lineEdit_returnPressed()
{
    ui->plainTextEdit->insertPlainText(ui->lineEdit->text() + "\n");
    ui->lineEdit->clear();
}

void MainWindow::on_pushButton_pressed()
{
    if (ui->lineEdit_2->text() != "" &&
        ui->lineEdit_3->text() != "" &&
        ui->lineEdit_4->text() != "")
    {
        m_realName = ui->lineEdit_2->text().toStdString();
        m_password = ui->lineEdit_3->text().toStdString();
        m_nickName = ui->lineEdit_4->text().toStdString();
        ui->mdiArea->close();
    }
    else
    {
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
    }
}
