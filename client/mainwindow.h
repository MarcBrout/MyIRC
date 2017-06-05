#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_lineEdit_returnPressed();

    void on_pushButton_pressed();

private:
    void sendMessage();

    Ui::MainWindow *ui;
    std::string m_realName;
    std::string m_nickName;
    std::string m_password;
    QTimer m_time;
};

#endif // MAINWINDOW_H
