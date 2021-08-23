#pragma once

#include <QtWidgets/QMainWindow>
#include <QList>
#include <ui_BeanComUI.h>
#include <beanUI.h>
#include <QTcpSocket>
#include <QtNetwork>
#include <BeanComError.h>
#include <QFileDialog>
//#include <BeanComDES.h>

class BeanComTCP;

class BeanComUI : public QMainWindow
{
    Q_OBJECT

public:
    BeanComUI(QWidget* parent = Q_NULLPTR);
public slots:

    //����
public:

    //TCP
public:

    QTcpSocket* client;
    QTcpSocket* toBeanComServer;
    QByteArray mChat;
    QByteArray toServerChat;
    //
    QString get_ip, get_dname;
    QString message;
    QString strIpAddress;
    QString strMacAddress;
    QTimer* timer;
    QString server_ip, server_host;
    QString sendCache;
    QString targetIP;
    void get_information();
    void set_connect_ui(QMainWindow ui);
    void keyPressEvent(QKeyEvent* event);
    //��ʼ��
    void makeFile();
    QString rootPath;
public:
    //����ģ��
    BeanComError error;
    //����״̬
    bool connectStatus;
    bool readStatus1, readStatus2;
protected slots:
    //ͨ��
    void setConnectStatus(bool status);
    void connectServer();
    void disConnectServer();
    void sendMessage();
    void signup();
    void signInSuccess();
    void signUpSuccess();
    void BTalkingStart();
    void BSendMessage();
    void BReceivingMessage();
private:
    bool getImStatus;
    Ui::BeanComUIClass ui;
    beanUI bui;
    //tools
    bool fileWrite(QString path, QString s1);
    QString fileRead(QString path);
    bool makeDir(QString path);
};