#pragma once

#include <QMainWindow>
#include <QtNetwork>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QByteArray>
#include<ui_BeanComServer.h>
#include<QtWidgets>

class BeanComServer : public QMainWindow
{
    Q_OBJECT

public:
    explicit BeanComServer(QWidget* parent = 0);
    ~BeanComServer();

public:
    void init();

private slots:
    void sendMessage(); //发送消息
    void onReciveData();  //接收数据
    void newListen(); //建立tcp监听事件
    void acceptConnection(); //接收客户端连接
    void showError(QAbstractSocket::SocketError); //错误输出

private:
    Ui::BeanComServerClass* ui;

private:
    QTcpSocket* tcpSocket;
    QTcpServer* tcpServer;
    // QTimer *timer;
    QByteArray mChat;
    //
    QPushButton* sendBtn;
    QLineEdit* lineEdit;
    QTextEdit* btextEdit;
};
