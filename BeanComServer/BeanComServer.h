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
    void sendMessage(); //������Ϣ
    void onReciveData();  //��������
    void newListen(); //����tcp�����¼�
    void acceptConnection(); //���տͻ�������
    void showError(QAbstractSocket::SocketError); //�������

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
