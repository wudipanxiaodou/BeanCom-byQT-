/************************************************* 
Copyright: wudipanxiaodou
Author: wudipanxiaodou
Date:2021-8-23
Description:to realize BeanComServer's basic functions
**************************************************/  

#include "BeanComServer.h"

#include <QObject>
#include <QString>
#include <QTextEdit>
#include <QHostAddress>
#include <QByteArray>
#include "BeanComServer.h"

BeanComServer::BeanComServer(QWidget* parent) : QMainWindow(parent), ui(new Ui::BeanComServerClass)
{
    ui->setupUi(this);
    sendBtn = new QPushButton(this);
    lineEdit = new QLineEdit(this);
    btextEdit = new QTextEdit(this);
    sendBtn->setGeometry(10, 10, 200, 50);
    lineEdit->setGeometry(10, 100, 500, 60);
    btextEdit->setGeometry(10, 200, 1600, 1000);
    init();

    setWindowTitle(QString::fromLocal8Bit("��������"));
    connect(sendBtn, SIGNAL(clicked(bool)), SLOT(sendMessage()));
}

BeanComServer::~BeanComServer()
{
    delete ui;
}

void BeanComServer::init()
{
    // timer = new QTimer;

    tcpServer = new QTcpServer;
    tcpSocket = new QTcpSocket;

    newListen();
    connect(tcpServer, SIGNAL(newConnection()), SLOT(acceptConnection()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(showError(QAbstractSocket::SocketError)));

}

void BeanComServer::sendMessage()  //��������
{
    QString textEdit = lineEdit->text();
    QString strData = QString::fromLocal8Bit("Time: ") + QTime::currentTime().toString() + "\n" + textEdit.toLocal8Bit();
    QByteArray sendMessage = strData.toLocal8Bit();
    mChat += ("\nSend " + sendMessage);
    btextEdit->setText(mChat);
    tcpSocket->write(sendMessage);
    lineEdit->clear();
    qDebug() << "?!?";
}

void BeanComServer::onReciveData()  //��ȡ����
{
    QString data = tcpSocket->readAll();
    mChat += ("\nRecv " + data);
    btextEdit->setText(mChat);
}

void BeanComServer::newListen()
{
    if (!tcpServer->listen(QHostAddress::Any, 6666))
    {
        qDebug() << tcpServer->errorString();

        tcpServer->close();
    }
}

void BeanComServer::acceptConnection()
{
    tcpSocket = tcpServer->nextPendingConnection();
    connect(tcpSocket, SIGNAL(readyRead()), SLOT(onReciveData()));
}

void BeanComServer::showError(QAbstractSocket::SocketError)
{
    qDebug() << tcpSocket->errorString();
    tcpSocket->close();
}