#include <BeanComUI.h>


BeanComUI::BeanComUI(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    bui.Setup_ALL(this);
    getImStatus = 1;
    client = NULL;
    toBeanComServer = NULL;
    readStatus1 = true;
    readStatus2 = true;
    setConnectStatus(false);
    client = new QTcpSocket(this);
    toBeanComServer = new QTcpSocket(this);
    toBeanComServer->abort();
    toBeanComServer->connectToHost("127.0.0.1", 6666);
    bui.inputServerHost->setMaxLength(8);
    bui.inputServerIP->setMaxLength(15);
    makeFile();
    bui.connectServerButton->setText(QString::fromLocal8Bit("connect"));
    get_information();
    bui.ipNumberLabel->setText("IP: NULL");
    bui.macNumberLabel->setText("MAC: NULL");
    connect(bui.send_button, &QPushButton::clicked,
        [=]() {sendMessage(); });
    connect(bui.controlButton, &QPushButton::clicked,
        [=]() {bui.BeanComControl->show(); });
    connect(bui.getImformation, &QPushButton::clicked,
        [=]() {
            QString data = "hello world";
            QByteArray text = data.toLocal8Bit();
            QByteArray by = text.toBase64();
            QString stra = by;
            qDebug() << stra;
            //
            QByteArray texta = stra.toLocal8Bit();
            QByteArray bya = text.fromBase64(texta);
            QString str = QString::fromLocal8Bit(bya);
            qDebug() << str;
            if (getImStatus) {
                get_information();
                bui.ipNumberLabel->setText("IP: " + strIpAddress);
                bui.macNumberLabel->setText("MAC: " + strMacAddress);
                getImStatus = 0;
            }
            else {
                bui.macNumberLabel->clear();
                bui.macNumberLabel->setText(QString::fromLocal8Bit("MAC: NULL"));
                bui.ipNumberLabel->clear();
                bui.ipNumberLabel->setText(QString::fromLocal8Bit("IP: NULL"));
                getImStatus = 1;
            }
        });
    connect(bui.beanTalking, &QPushButton::clicked, [=]() {signup(); });
    connect(bui.connectServerButton, &QPushButton::clicked, [=]() {
        //判断连接状态
        if (!connectStatus) {
            connectServer();
        }
        else {
            disConnectServer();
        }
        });
    timer = new QTimer(this);
    bool testStatus = 0;
    timer->start(3000);
}

void BeanComUI::makeFile() {
    rootPath = "H:\\小哥软件\\BeanComUI\\";
    makeDir(QString(rootPath + "‪File"));
    makeDir(QString(rootPath + "‪File\\Key"));
    makeDir(QString(rootPath + "‪File\\User"));
    makeDir(QString(rootPath + "‪File\\file"));
    qDebug() << "?????????????";
    //makeDir(QString(rootPath + "File\\"));
}

void BeanComUI::get_information() {

    //QString strIpAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // 获取第一个本主机的IPv4地址
    int nListSize = ipAddressesList.size();
    for (int i = 0; i < nListSize; ++i)
    {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            strIpAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // 如果没有找到，则以本地IP地址为IP
    if (strIpAddress.isEmpty())
        strIpAddress = QHostAddress(QHostAddress::LocalHost).toString();

    QList<QNetworkInterface> nets = QNetworkInterface::allInterfaces();// 获取所有网络接口列表
    int nCnt = nets.count();
    for (int i = 0; i < nCnt; i++)
    {
        // 如果此网络接口被激活并且正在运行并且不是回环地址，则就是我们需要找的Mac地址
        if (nets[i].flags().testFlag(QNetworkInterface::IsUp) && nets[i].flags().testFlag(QNetworkInterface::IsRunning) && !nets[i].flags().testFlag(QNetworkInterface::IsLoopBack))
        {
            strMacAddress = nets[i].hardwareAddress();
            break;
        }
    }
}

void BeanComUI::set_connect_ui(QMainWindow ui) {

}

void BeanComUI::keyPressEvent(QKeyEvent* event)
{
    if (event->modifiers() == (Qt::AltModifier)) {
        if (!this->objectName().isEmpty()) {
            QWidget* currentFocusWidget = this->focusWidget();//QApplication::focusWidget();能够获取聚焦控件
            //qDebug() << currentFocusWidget << " " << bui.talking_send;
            if (currentFocusWidget == bui.talking_send) {
                qDebug() << "111";
                sendMessage();
            }
            else if (currentFocusWidget == bui.inputServerIP) {
                qDebug() << "222";
            }
            else if (currentFocusWidget == bui.inputServerHost) {
                qDebug() << "333";
            }
        }
    }
    else {
        switch (event->key())
        {
        case Qt::Key_F1:
            message = bui.talking_send->QTextEdit::toPlainText();
            bui.talking_seceive->QTextEdit::append("send:" + message + "/");
            bui.talking_send->clear();
            qDebug() << "send_clicked";
            break;
        default:return;//忽略其他按键
        }
    }
}

void BeanComUI::sendMessage() {
    if (connectStatus == true) {
        message = bui.talking_send->toPlainText();
        if (!message.isEmpty()) {
            qDebug() << "%" << strIpAddress;
            QString textEdit = bui.talking_send->toPlainText();
            QString strData = QString::fromLocal8Bit("Time: ") + QTime::currentTime().toString() + "\n" + strIpAddress + "/: \n" + textEdit.toLocal8Bit();
            QByteArray sendMessage = strData.toLocal8Bit();
            mChat += ("\nSend " + sendMessage);
            client->write(sendMessage);
            bui.talking_seceive->setFontPointSize(8);
            bui.talking_seceive->setText(mChat);
            bui.talking_send->clear();
            qDebug() << "send_clicked";
        }
        else {
            QString returnError = error.sendTextError1.errorName;
            bui.TalkingMessageWidget->setFontPointSize(6);
            bui.TalkingMessageWidget->append(QString::fromLocal8Bit("/*发送失败*/"));
            bui.TalkingMessageWidget->append("ERROR 0001");
            bui.TalkingMessageWidget->append(returnError);
        }
    }
    else {
        QString returnError = error.sendTextError2.errorName;
        bui.TalkingMessageWidget->setFontPointSize(6);
        bui.TalkingMessageWidget->append("ERROR 0002");
        bui.TalkingMessageWidget->append(returnError);
    }
}

void BeanComUI::connectServer() {
    client = new QTcpSocket(this);
    QString host = bui.inputServerHost->QLineEdit::text();
    QString ip = bui.inputServerIP->QLineEdit::text();
    qDebug() << host << endl << ip;
    server_host = host;
    server_ip = ip;
    client->abort();
    client->connectToHost(ip, host.toInt());
    connect(client, &QTcpSocket::readyRead, [=]() {
        QString data = client->readAll();
        qDebug() << data;
        mChat += ("\nRecv: \n" + ip + " /" + data);
        qDebug() << "???1";
        bui.talking_seceive->setText(mChat);
        });
    setConnectStatus(true);
}

void BeanComUI::disConnectServer() {
    client->close();
    client->disconnectFromHost();
    setConnectStatus(false);
}

void BeanComUI::setConnectStatus(bool status) {
    if (status) {
        bui.connectServerButton->setText(QString::fromLocal8Bit("disconnect"));
        bui.TalkingMessageWidget->append(QString::fromLocal8Bit("成功与服务器连接"));
        connectStatus = true;
        bui.talking_send->setReadOnly(false);
        bui.inputServerHost->setReadOnly(true);
        bui.inputServerIP->setReadOnly(true);
    }
    else {
        bui.connectServerButton->setText(QString::fromLocal8Bit("connect"));
        bui.TalkingMessageWidget->append(QString::fromLocal8Bit("与服务器断开连接"));
        connectStatus = false;
        sendCache = bui.talking_send->toPlainText();
        bui.talking_send->setReadOnly(true);
        bui.talking_send->clear();
        if (!sendCache.isEmpty()) {
            bui.TalkingMessageWidget->append(QString::fromLocal8Bit("发送缓存区内容:"));
            bui.TalkingMessageWidget->append(sendCache);
        }
        else {
            sendCache.clear();
        }
        bui.inputServerHost->setReadOnly(false);
        bui.inputServerIP->setReadOnly(false);
        server_host.clear();
        server_ip.clear();
    }
}

void BeanComUI::signup() {
    bui.beanComSignUp->show();
    bui.inputAccount->setMaxLength(16);
    bui.inputPassword->setMaxLength(16);
    bui.inputPassword->setEchoMode(QLineEdit::Password);
    bui.inputAccounts->setMaxLength(16);
    bui.inputPasswords->setMaxLength(16);
    bui.inputPasswordsa->setMaxLength(16);
    bui.inputPasswords->setEchoMode(QLineEdit::Password);
    bui.inputPasswordsa->setEchoMode(QLineEdit::Password);
    connect(bui.signUpButton, &QPushButton::clicked, [=]() {
        bui.signInWidget->hide();
        bui.signUpWidget->show();
        });
    connect(bui.signInButton, &QPushButton::clicked, [=]() {
        bui.signUpWidget->hide();
        bui.signInWidget->show();
        });
    connect(bui.passwordVisual, &QRadioButton::toggled, [=]() {
        if (bui.passwordVisual->isChecked())
            bui.inputPassword->setEchoMode(QLineEdit::Normal);
        else
            bui.inputPassword->setEchoMode(QLineEdit::Password);
        });
    connect(bui.passwordVisuals, &QRadioButton::toggled, [=]() {
        if (bui.passwordVisuals->isChecked()) {
            bui.inputPasswordsa->setEchoMode(QLineEdit::Normal);
            bui.inputPasswords->setEchoMode(QLineEdit::Normal);
        }
        else {
            bui.inputPasswords->setEchoMode(QLineEdit::Password);
            bui.inputPasswordsa->setEchoMode(QLineEdit::Password);
        }
        });

    connect(bui.finishSignUp, &QPushButton::clicked, [=]() {
        QString accounts = bui.inputAccount->text();
        QString password = bui.inputPassword->text();
        if (accounts.isEmpty() || password.isEmpty()) {
            bui.inputError->append(QString::fromLocal8Bit("操作失败:用户名与密码不得为空"));
        }
        else {
            toBeanComServer = new QTcpSocket(this);
            toBeanComServer->abort();
            toBeanComServer->connectToHost("127.0.0.1", 6666);
            QString signInMessage;
            signInMessage =
                "@SIGNUP//<<" +
                bui.inputAccount->text() +
                ">+<" +
                bui.inputPassword->text() +
                ">>?";
            bui.inputError->append(bui.inputAccount->text() + bui.inputPassword->text());
            QByteArray sendMessage = signInMessage.toLocal8Bit();
            toBeanComServer->write(sendMessage);
            //
            bui.inputError->append(QString::fromLocal8Bit("操作成功:请求已发送至 BeancomServer"));
            //
            connect(toBeanComServer, &QTcpSocket::readyRead, [=]() {
                QString data = toBeanComServer->readAll();
                toServerChat += data;
                qDebug() << "///" + data;
                if (data == "Verification(true)") {
                    bui.inputError->append(QString::fromLocal8Bit("操作成功:登录成功"));
                    signUpSuccess();
                    //disconnect(toBeanComServer, SIGNAL(readyRead), 0, 0);
                }
                else if (data == "Verification(false)") {
                    bui.inputError->append(QString::fromLocal8Bit("操作失败:账号与密码不匹配"));
                    //disconnect(toBeanComServer, SIGNAL(readyRead), 0, 0);
                }
                });
            //
            bui.inputPassword->clear();
            signUpSuccess();
            //bui.inputAccount->clear();
            //
        }
        });
    connect(bui.finishSignIn, &QPushButton::clicked, [=]() {
        QString accounts = bui.inputAccounts->text();
        QString password1 = bui.inputPasswords->text();
        QString password2 = bui.inputPasswordsa->text();
        if (accounts.isEmpty() || password1.isEmpty() || password2.isEmpty()) {
            bui.inputError->append(QString::fromLocal8Bit("操作失败:用户名与密码不得为空"));
        }
        else if (password1 != password2) {
            bui.inputError->append(QString::fromLocal8Bit("操作失败:密码与确认密码内容不同"));
        }
        else if (!((accounts.length() <= 16 || accounts.length() >= 3) ? true : false)) {
            bui.inputError->append(QString::fromLocal8Bit("操作失败:用户名长度不可接受(只允许 3~16 个字符)"));
        }
        else if (!((password1.length() <= 16 || password1.length() >= 8) ? true : false)) {
            bui.inputError->append(QString::fromLocal8Bit("操作失败:密码长度不可接受(只允许 8~16 个字符)"));
        }
        else {
            toBeanComServer = new QTcpSocket(this);
            toBeanComServer->abort();
            toBeanComServer->connectToHost("127.0.0.1", 6666);
            QString signInMessage;
            signInMessage =
                "@SIGNIN//<<" +
                bui.inputAccounts->text() +
                ">+<" +
                bui.inputPasswords->text() +
                ">>?";
            qDebug() << bui.inputAccounts->text() + bui.inputPasswords->text();
            QByteArray sendMessage = signInMessage.toLocal8Bit();
            toBeanComServer->write(sendMessage);
            //
            bui.inputError->append(QString::fromLocal8Bit("操作成功:请求已发送至 BeancomServer"));
            //
            connect(toBeanComServer, &QTcpSocket::readyRead, [=]() {
                QString data = toBeanComServer->readAll();
                qDebug() << data;
                if (data == "Verification(true)") {
                    bui.inputError->append(QString::fromLocal8Bit("操作成功:注册成功"));
                    signInSuccess();
                }
                else if (data == "Verification(false)") {
                    bui.inputError->append(QString::fromLocal8Bit("操作失败:BeanComServer驳回请求"));
                    //disconnect(toBeanComServer, SIGNAL(readyRead), 0, 0);
                }
                });
            //bui.inputAccounts->clear();
            //bui.inputPasswords->clear();
            bui.inputPasswordsa->clear();
        }
        });
}

//注册成功
void BeanComUI::signInSuccess() {
    bui.inputAccount->clear();
    bui.inputPassword->clear();
    bui.inputAccounts->clear();
    bui.inputPasswords->clear();
    bui.inputPasswordsa->clear();
    bui.inputError->clear();
    toBeanComServer->close();
    toBeanComServer->disconnectFromHost();
    disconnect(toBeanComServer, SIGNAL(readyRead), 0, 0);
    //bui.beanComSignUp->hide();
    bui.signInWidget->hide();
    bui.signUpWidget->show();
}

//登录成功
void BeanComUI::signUpSuccess() {
    bui.inputAccount->clear();
    bui.inputPassword->clear();
    bui.inputAccounts->clear();
    bui.inputPasswords->clear();
    bui.inputPasswordsa->clear();
    bui.inputError->clear();
    client->close();
    client->disconnectFromHost();
    disconnect(toBeanComServer, SIGNAL(readyRead), 0, 0);
    bui.beanComSignUp->hide();
    BTalkingStart();
}

void BeanComUI::BTalkingStart() {
    bui.btalking1->show();
    bui.btalking2->hide();
    toBeanComServer = new QTcpSocket(this);
    toBeanComServer->abort();
    toBeanComServer->connectToHost("127.0.0.1", 6666);
    connect(bui.bsendButton, &QPushButton::clicked, [=]() {
        BSendMessage();
        });
    connect(toBeanComServer, &QTcpSocket::readyRead, [=]() {
        BReceivingMessage();
        });
}

void BeanComUI::BSendMessage() {
    QString sendMessages = bui.btalking_send->toPlainText();
    get_information();
    QString ip = strIpAddress;
    QString mac = strMacAddress;
}

void BeanComUI::BReceivingMessage() {

}

//TOOLS
bool BeanComUI::fileWrite(QString path, QString s1) {
    QFile f(path);
    //如果不加QIODevice::Append，每次写入都会覆盖原文本
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        qDebug() << "Open failed.";
        return 0;
    }
    QTextStream txtOutput(&f);
    txtOutput << s1;
    f.close();
    return 1;
}

QString BeanComUI::fileRead(QString path) {
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Open failed.";
        return -1;
    }
    QTextStream txtInput(&f);
    QString lineStr;
    while (!txtInput.atEnd())
    {
        lineStr = txtInput.readLine();
        qDebug() << lineStr;
    }

    f.close();
    return lineStr;
}

bool BeanComUI::makeDir(QString path) {
    QDir dir;
    if (!dir.exists(path)) {
        dir.mkdir(path);
        return 0;
    }
    return 1;
}
