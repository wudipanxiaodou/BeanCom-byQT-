#include <beanUI.h>

//UI设计：最没技术含量的代码
//如果实在看不懂就删掉重写吧
//这里的东西真没什么实际价值

void beanUI::Setup_ALL(QMainWindow* ui)
{
    vlayout_left = new QVBoxLayout(ui);
    vlayout_right = new QVBoxLayout(ui);
    hlayout_all = new QVBoxLayout(ui);
    vlayout_up = new QHBoxLayout(ui);
    vlayout_down = new QHBoxLayout(ui);
    mainWindowWidget = new QWidget(ui);
    mainLeftWidget = new QWidget(ui);
    mainRightWidget = new QWidget(ui);
    mainDownWidget = new QWidget(ui);
    mainUpWidget = new QWidget(ui);
    widget_color = QColor(220, 220, 220);
    tab_color = QColor(211, 211, 211);
    dock_color = QColor(211, 211, 211);
    left_color = QColor(211, 211, 211);
    text_color = QColor(192, 192, 192);
    dock_widget_color = QColor(211, 211, 211);
    dock_control_color = QColor(211, 211, 211);
    tab_widget_color[0] = QColor(211, 211, 211);
    tab_widget_color[1] = QColor(211, 211, 211);
    tab_widget_color[2] = QColor(211, 211, 211);
    tab_widget_color[3] = QColor(211, 211, 211);
    tab_widget_color[4] = QColor(211, 211, 211);
    tab_widget_color[5] = QColor(211, 211, 211);
    tab_widget_color[6] = QColor(211, 211, 211);
    control_color = QColor(255, 255, 255);
    ui->setMinimumSize(2000, 1000);
    //ui->setWindowState(Qt::WindowMaximized);
    Setup_BUTTON_1(ui);
    //setup
    QPalette pal(ui->palette());
    pal.setColor(QPalette::Background, widget_color);
    ui->setAutoFillBackground(true);
    ui->setPalette(pal);
    //
    Setup_CONNECT_WIDGET(ui);
    Setup_TALKING_WIDGET(ui);
    Setup_FILE_WIDGET(ui);
    Setup_ACTIVITIES_WIDGET(ui);
    Setup_SET_WIDGET(ui);
    Setup_MAINTEXTWIDGET(ui);
    Setup_TAB(ui);
    Setup_DOCK(ui);
    Setup_DOCK_BEANCOM(ui);
    Setup_DOCK_CONTROL(ui);
    Setup_SETUP_BEANCOM(ui);
    //tab
    vlayout_down->setMargin(5);
    vlayout_left->setMargin(5);
    vlayout_right->setMargin(5);
    vlayout_up->setMargin(5);
    hlayout_all->setMargin(5);
    vlayout_left->addWidget(leftSetupBeanCom);
    vlayout_right->addWidget(tabwidget);
    mainLeftWidget->setLayout(vlayout_left);
    mainRightWidget->setLayout(vlayout_right);
    vlayout_down->addWidget(mainLeftWidget);
    vlayout_down->addWidget(mainRightWidget);
    vlayout_down->setStretchFactor(mainLeftWidget, 1);
    vlayout_down->setStretchFactor(mainRightWidget, 4);
    mainDownWidget->setLayout(vlayout_down);
    vlayout_up->addWidget(mainTextWidget);
    mainUpWidget->setLayout(vlayout_up);
    hlayout_all->addWidget(mainUpWidget);
    hlayout_all->addWidget(mainDownWidget);
    hlayout_all->setStretchFactor(mainDownWidget, 10);
    hlayout_all->setStretchFactor(mainUpWidget, 1);
    mainWindowWidget->setLayout(hlayout_all);
    ui->setCentralWidget(mainWindowWidget);
    BeanComControl->hide();
}

void beanUI::Setup_TAB(QMainWindow* ui)
{
    centralWidget = new QWidget(ui);
    tabwidget = new QTabWidget(centralWidget);
    tabwidget->addTab(connect, QString::fromLocal8Bit("talking"));
    tabwidget->addTab(talking, QString::fromLocal8Bit("picture"));
    tabwidget->addTab(file, QString::fromLocal8Bit("file"));
    tabwidget->addTab(activities, QString::fromLocal8Bit("activities"));
    tabwidget->addTab(set, QString::fromLocal8Bit("set"));
    //tabwidget->addTab(beancom, QString::fromLocal8Bit("beancom"));
    //tabwidget->addTab(server, QString::fromLocal8Bit("server"));
    QPalette pal(tabwidget->palette());
    pal.setColor(QPalette::Background, tab_color);
    tabwidget->setAutoFillBackground(true);
    tabwidget->setPalette(pal);
    const char* tab_name[7] = {
    " CONNECT "," BTALKING "," FILE "," ACTIVITIE "," SETUP "
    };
    tabwidget->setTabText(tabwidget->indexOf(connect), QString::fromLocal8Bit(tab_name[0]));
    tabwidget->setTabText(tabwidget->indexOf(talking), QString::fromLocal8Bit(tab_name[1]));
    tabwidget->setTabText(tabwidget->indexOf(file), QString::fromLocal8Bit(tab_name[2]));
    tabwidget->setTabText(tabwidget->indexOf(activities), QString::fromLocal8Bit(tab_name[3]));
    tabwidget->setTabText(tabwidget->indexOf(set), QString::fromLocal8Bit(tab_name[4]));
    //tabwidget->setTabText(tabwidget->indexOf(beancom), QString::fromLocal8Bit(tab_name[5]));
    //tabwidget->setTabText(tabwidget->indexOf(server), QString::fromLocal8Bit(tab_name[6]));

}

void beanUI::Setup_BUTTON_1(QMainWindow* ui) {

}
void beanUI::Setup_CONNECT_WIDGET(QMainWindow* ui) {
    connect = new QWidget(ui);
    QPalette pal(connect->palette());
    pal.setColor(QPalette::Background, tab_widget_color[0]);
    connect->setAutoFillBackground(true);
    connect->setPalette(pal);
    QWidget* up_widget = new QWidget(connect);
    QVBoxLayout* talking_widget = new QVBoxLayout(ui), * send_button_widget = new QVBoxLayout(ui);
    QHBoxLayout* UpWidgets = new QHBoxLayout(ui);
    talking_send = new BeanComEdit(connect);
    talking_seceive = new BeanComEdit(ui);
    TalkingMessageWidget = new BeanComEdit(ui);
    send_button = new QPushButton(QString::fromLocal8Bit("Send"));
    talking_seceive->setReadOnly(true);
    TalkingMessageWidget->setReadOnly(true);
    //talking_send->setFontPointSize(10);
    UpWidgets->addWidget(TalkingMessageWidget);
    UpWidgets->addWidget(talking_seceive);
    UpWidgets->setStretchFactor(TalkingMessageWidget, 1);
    UpWidgets->setStretchFactor(talking_seceive, 3);
    up_widget->setLayout(UpWidgets);
    talking_widget->addWidget(up_widget);
    talking_widget->addWidget(talking_send);
    talking_widget->setStretchFactor(up_widget, 6);
    talking_widget->setStretchFactor(talking_send, 1);
    send_button_widget->addWidget(send_button, 0, Qt::AlignRight | Qt::AlignBottom);
    connect->setLayout(talking_widget);
    talking_send->setLayout(send_button_widget);
}
void beanUI::Setup_TALKING_WIDGET(QMainWindow* ui) {
    //向导界面 
    talking = new QWidget(ui);
    btalking2 = new QWidget(talking);
    btalking2->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    QPalette pal(btalking2->palette());
    pal.setColor(QPalette::Background, Qt::white);
    btalking2->setAutoFillBackground(true);
    btalking2->setPalette(pal);
    QLabel* lable = new QLabel(btalking2);
    lable->setFixedSize(800, 200);
    lable->setText(QString::fromLocal8Bit("      欢迎使用BTalking"));
    lable->setFont(QFont("Microsoft YaHe", 20, QFont::Black));
    beanTalking = new QPushButton(btalking2);
    beanTalking->setFixedSize(400, 100);
    beanTalking->setText(QString::fromLocal8Bit("开始使用"));
    beanTalking->setFont(QFont("Microsoft YaHe", 15, QFont::Black));
    QVBoxLayout* pLayout = new QVBoxLayout();
    pLayout->addStretch();
    pLayout->addWidget(lable, 0, Qt::AlignCenter);
    pLayout->addWidget(beanTalking, 0, Qt::AlignCenter);
    pLayout->addStretch();
    btalking2->setLayout(pLayout);
    QHBoxLayout* layout2 = new QHBoxLayout();
    layout2->setSpacing(0);
    layout2->addWidget(btalking2);
    //btalking2->hide();
    talking->setLayout(layout2);
    //使用界面 
    btalking1 = new QWidget(talking);
    btalking1->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    QPalette pal2(btalking1->palette());
    pal2.setColor(QPalette::Background, tab_widget_color[0]);
    btalking1->setAutoFillBackground(true);
    btalking1->setPalette(pal2);
    btalking1->hide();
    layout2->addWidget(btalking1);
    QVBoxLayout* talking_widget = new QVBoxLayout(ui);
    QHBoxLayout* allWdgets = new QHBoxLayout(ui);
    QVBoxLayout* send_button_widget = new QVBoxLayout(ui);
    talking_widget->setSpacing(10);
    allWdgets->setSpacing(10);
    send_button_widget->setSpacing(10);
    btalking_send = new BeanComEdit();
    btalking_seceive = new BeanComEdit();
    BFriends = new QWidget();
    bsendButton = new QPushButton();
    bsendButton = new QPushButton(QString::fromLocal8Bit("Send"));
    btalking_seceive->setReadOnly(true);
    send_button_widget->addWidget(bsendButton, 0, Qt::AlignRight | Qt::AlignBottom);
    btalking_send->setLayout(send_button_widget);
    talking_widget->addWidget(btalking_seceive);
    talking_widget->addWidget(btalking_send);
    talking_widget->setStretchFactor(btalking_seceive, 6);
    talking_widget->setStretchFactor(btalking_send, 1);
    QWidget* rightWidget = new QWidget(btalking1);
    rightWidget->setLayout(talking_widget);
    allWdgets->addWidget(BFriends);
    allWdgets->addWidget(rightWidget);
    allWdgets->setStretchFactor(BFriends, 1);
    allWdgets->setStretchFactor(rightWidget, 4);
    btalking1->setLayout(allWdgets);
    Setup_Sign(ui);

}

void beanUI::Setup_Sign(QMainWindow* ui) {
    beanComSignUp = new QDockWidget(ui);
    beanComSignUp->setFloating(true);
    beanComSignUp->setFixedSize(1000, 700);
    beanComSignUp->hide();
    QPalette pal(beanComSignUp->palette());
    pal.setColor(QPalette::Background, QColor(231, 231, 231));
    beanComSignUp->setAutoFillBackground(true);
    beanComSignUp->setPalette(pal);
    QLabel* lable1 = new QLabel(beanComSignUp);
    lable1->setGeometry(10, 10, 200, 80);
    lable1->setText(QString::fromLocal8Bit("登录或注册"));
    lable1->setFont(QFont("Microsoft YaHe", 10, QFont::Black));
    signUpButton = new QPushButton(beanComSignUp);
    signUpButton->setGeometry(730, 550, 100, 50);
    signUpButton->setText(QString::fromLocal8Bit("登录"));
    signInButton = new QPushButton(beanComSignUp);
    signInButton->setGeometry(850, 550, 100, 50);
    signInButton->setText(QString::fromLocal8Bit("注册"));
    inputError = new BeanComEdit(beanComSignUp);
    inputError->setGeometry(20, 380, 650, 300);
    inputError->setReadOnly(true);
    QPalette pa(inputError->palette());
    pa.setColor(QPalette::Base, QColor(221, 221, 221));
    inputError->setAutoFillBackground(true);
    inputError->setPalette(pa);
    //登录
    signUpWidget = new QWidget(beanComSignUp);
    signUpWidget->setGeometry(10, 20, 800, 500);
    inputAccount = new QLineEdit(signUpWidget);
    inputAccount->setGeometry(10, 90, 500, 40);
    inputAccount->setPlaceholderText(QString::fromLocal8Bit("账号"));
    QPalette pal1(inputAccount->palette());
    pal1.setColor(QPalette::Base, QColor(211, 211, 211));
    inputAccount->setAutoFillBackground(true);
    inputAccount->setPalette(pal1);
    inputPassword = new QLineEdit(signUpWidget);
    inputPassword->setGeometry(10, 150, 500, 40);
    inputPassword->setPlaceholderText(QString::fromLocal8Bit("密码"));
    QPalette pal2(inputPassword->palette());
    pal2.setColor(QPalette::Base, QColor(211, 211, 211));
    inputPassword->setAutoFillBackground(true);
    inputPassword->setPalette(pal2);
    //signUpWidget->hide();
    finishSignUp = new QPushButton(signUpWidget);
    finishSignUp->setGeometry(10, 230, 150, 60);
    finishSignUp->setText(QString::fromLocal8Bit("完成登录"));
    passwordVisual = new QRadioButton(signUpWidget);
    passwordVisual->setGeometry(200, 240, 20, 20);
    QLabel* visualLable = new QLabel(signUpWidget);
    visualLable->setGeometry(230, 230, 250, 40);
    visualLable->setText(QString::fromLocal8Bit("密码可见"));
    //注册
    signInWidget = new QWidget(beanComSignUp);
    signInWidget->setGeometry(10, 20, 800, 500);
    inputAccounts = new QLineEdit(signInWidget);
    inputAccounts->setGeometry(10, 90, 500, 40);
    inputAccounts->setPlaceholderText(QString::fromLocal8Bit("账号"));
    QPalette pal3(inputAccounts->palette());
    pal3.setColor(QPalette::Base, QColor(211, 211, 211));
    inputAccounts->setAutoFillBackground(true);
    inputAccounts->setPalette(pal3);
    inputPasswords = new QLineEdit(signInWidget);
    inputPasswords->setGeometry(10, 150, 500, 40);
    inputPasswords->setPlaceholderText(QString::fromLocal8Bit("密码"));
    QPalette pal4(inputPasswords->palette());
    pal4.setColor(QPalette::Base, QColor(211, 211, 211));
    inputPasswords->setAutoFillBackground(true);
    inputPasswords->setPalette(pal4);
    inputPasswordsa = new QLineEdit(signInWidget);
    inputPasswordsa->setGeometry(10, 210, 500, 40);
    inputPasswordsa->setPlaceholderText(QString::fromLocal8Bit("确认密码"));
    QPalette pal5(inputPasswordsa->palette());
    pal5.setColor(QPalette::Base, QColor(211, 211, 211));
    inputPasswordsa->setAutoFillBackground(true);
    inputPasswordsa->setPalette(pal5);
    finishSignIn = new QPushButton(signInWidget);
    finishSignIn->setGeometry(10, 280, 150, 60);
    finishSignIn->setText(QString::fromLocal8Bit("完成注册"));
    signInWidget->hide();
    passwordVisuals = new QRadioButton(signInWidget);
    passwordVisuals->setGeometry(200, 290, 20, 20);
    QLabel* visualLables = new QLabel(signInWidget);
    visualLables->setGeometry(230, 280, 250, 40);
    visualLables->setText(QString::fromLocal8Bit("密码可见"));
}

void beanUI::Setup_FILE_WIDGET(QMainWindow* ui) {
    file = new QWidget(ui);
    QPalette pal(file->palette());
    pal.setColor(QPalette::Background, tab_widget_color[2]);
    file->setAutoFillBackground(true);
    file->setPalette(pal);
    QWidget* widget = new QWidget(file);
}
void beanUI::Setup_ACTIVITIES_WIDGET(QMainWindow* ui) {
    activities = new QWidget(ui);
    QPalette pal(activities->palette());
    pal.setColor(QPalette::Background, tab_widget_color[3]);
    activities->setAutoFillBackground(true);
    activities->setPalette(pal);
    QWidget* widget = new QWidget(activities);
}
void beanUI::Setup_SET_WIDGET(QMainWindow* ui) {
    set = new QWidget(ui);
    QPalette pal(set->palette());
    pal.setColor(QPalette::Background, tab_widget_color[4]);
    set->setAutoFillBackground(true);
    set->setPalette(pal);
    QWidget* widget = new QWidget(set);
}

void beanUI::Setup_MAINTEXTWIDGET(QMainWindow* ui)
{
    mainTextWidget = new QWidget(ui);
    QPalette pal(mainTextWidget->palette());
    pal.setColor(QPalette::Background, text_color);
    mainTextWidget->setAutoFillBackground(true);
    mainTextWidget->setPalette(pal);
    QWidget* widget = new QWidget(mainTextWidget);
    logButton = new QPushButton(QString::fromLocal8Bit("SignIn&Up"));
    Account = new QPushButton();
    QHBoxLayout* mainTextLayout1 = new QHBoxLayout(mainTextWidget);
    QHBoxLayout* mainTextLayout2 = new QHBoxLayout(mainTextWidget);
    //
    mainTextLayout1->addStretch();
    mainTextLayout1->addWidget(logButton, 0, Qt::AlignRight | Qt::AlignTop);
    mainTextWidget->setLayout(mainTextLayout1);
    mainTextLayout2->addStretch();
    mainTextLayout2->addWidget(Account, 0, Qt::AlignRight | Qt::AlignTop);
    mainTextWidget->setLayout(mainTextLayout2);
    logButton->hide();
    logButton->setFixedSize(QSize(200, 80));
    Account->hide();
    Account->setFixedSize(QSize(00, 80));
}

void beanUI::Setup_DOCK(QMainWindow* ui)
{
    dock = new QDockWidget(QString::fromLocal8Bit("Server"), centralWidget);
    dock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
    QPalette pal(dock->palette());
    pal.setColor(QPalette::Background, dock_color);
    dock->setAutoFillBackground(true);
    dock->setPalette(pal);
    ui->addDockWidget(Qt::RightDockWidgetArea, dock);
    QWidget* widget = new QWidget(dock);
}

void beanUI::Setup_DOCK_BEANCOM(QMainWindow* ui)
{
    dock_beancom = new QDockWidget(QString::fromLocal8Bit("BeanCom"), ui);
    dock_beancom->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    dock_beancom->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
    QPalette pal(dock_beancom->palette());
    pal.setColor(QPalette::Background, dock_color);
    dock_beancom->setAutoFillBackground(true);
    dock_beancom->setPalette(pal);
    ui->addDockWidget(Qt::BottomDockWidgetArea, dock_beancom);
    QWidget* widget = new QWidget(ui);
    dock_beancom->setWidget(widget);
    QHBoxLayout* layout = new QHBoxLayout(dock_beancom);
    layout->setMargin(2);
    controlButton = new QPushButton(QString::fromLocal8Bit("control"));
    controlButton->setFont(QFont("Microsoft YaHe", 8, QFont::Black));
    controlButton->setFixedSize(QSize(100, 50));
    getImformation = new QPushButton(QString::fromLocal8Bit("IP&MAC"));
    getImformation->setFont(QFont("Microsoft YaHe", 8, QFont::Black));
    getImformation->setFixedSize(QSize(100, 50));
    layout->addStretch();
    layout->addWidget(controlButton, 0, Qt::AlignRight | Qt::AlignTop);
    layout->addWidget(getImformation, 0, Qt::AlignRight | Qt::AlignTop);
    widget->setLayout(layout);
    QPalette pa2(widget->palette());
    pa2.setColor(QPalette::Background, QColor(
        (255 - dock_color.red()) / 2 + dock_color.red(),
        (255 - dock_color.green()) / 2 + dock_color.green(),
        (255 - dock_color.blue()) / 2 + dock_color.blue()));
    widget->setAutoFillBackground(true);
    widget->setPalette(pa2);
    macNumberLabel = new BeanComEdit(widget);
    ipNumberLabel = new BeanComEdit(widget);
    ipNumberLabel->setReadOnly(true);
    macNumberLabel->setReadOnly(true);
    QFont ft("Microsoft YaHe", 10, QFont::Black);
    macNumberLabel->setGeometry(20, 15, 400, 40);
    macNumberLabel->setText(QString::fromLocal8Bit("MAC: "));
    macNumberLabel->setFont(ft);
    //macNumberLabel->setFrameShape(QFrame::Box);
    macNumberLabel->setStyleSheet("border: 2px solid  #000000");
    ipNumberLabel->setGeometry(530, 15, 300, 40);
    ipNumberLabel->setText(QString::fromLocal8Bit("IP: "));
    ipNumberLabel->setFont(ft);
    //ipNumberLabel->setFrameShape(QFrame::Box);
    ipNumberLabel->setStyleSheet("border: 2px solid  #000000");
}

void beanUI::Setup_DOCK_CONTROL(QMainWindow* ui)
{
    BeanComControl = new QDockWidget(QString("BeanComControl"), dock_beancom);
    BeanComControl->setFeatures(QDockWidget::AllDockWidgetFeatures);
    BeanComControl->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
    QPalette pal(BeanComControl->palette());
    pal.setColor(QPalette::Background, dock_control_color);
    BeanComControl->setAutoFillBackground(true);
    BeanComControl->setPalette(pal);
    Control = new BeanComEdit(BeanComControl);
    QPalette pal2(Control->palette());
    pal2.setColor(QPalette::Base, control_color);
    Control->setAutoFillBackground(true);
    Control->setPalette(pal2);
    ui->addDockWidget(Qt::BottomDockWidgetArea, BeanComControl);
    BeanComControl->setWidget(Control);
}

void beanUI::Setup_SETUP_BEANCOM(QMainWindow* ui) {
    leftSetupBeanCom = new QWidget(ui);
    QPalette pal(leftSetupBeanCom->palette());
    pal.setColor(QPalette::Background, left_color);
    leftSetupBeanCom->setAutoFillBackground(true);
    leftSetupBeanCom->setPalette(pal);
    QLabel* text = new QLabel();
    QFont ft("Microsoft YaHe", 10, QFont::Black);
    text->setFont(ft);
    text->setText(QString::fromLocal8Bit("BeanCom Set"));
    QHBoxLayout* layout = new QHBoxLayout(leftSetupBeanCom);
    layout->addWidget(text, 0, Qt::AlignLeft | Qt::AlignTop);
    leftSetupBeanCom->setLayout(layout);
    inputServerHost = new QLineEdit(leftSetupBeanCom);
    inputServerHost->setGeometry(5, 100, 350, 50);
    //QLabel* inputHostText = new QLabel(leftSetupBeanCom);
    //inputHostText->setFont(QFont("Microsoft YaHe", 9, QFont::Black));
    //inputHostText->setText(QString::fromLocal8Bit("ServerHost :"));
    //inputHostText->setGeometry(5, 100, 250, 50);
    inputServerIP = new QLineEdit(leftSetupBeanCom);
    inputServerIP->setGeometry(5, 180, 350, 50);
    //QLabel* inputIPText = new QLabel(leftSetupBeanCom);
    //inputIPText->setFont(QFont("Microsoft YaHe", 9, QFont::Black));
    //inputIPText->setText(QString::fromLocal8Bit("ServerIP :"));
    //inputIPText->setGeometry(5, 180, 250, 50);
    inputServerIP->setPlaceholderText(QString::fromLocal8Bit("ServerIP"));
    inputServerHost->setPlaceholderText(QString::fromLocal8Bit("ServerHost"));
    connectServerButton = new QPushButton(leftSetupBeanCom);
    connectServerButton->setGeometry(5, 250, 200, 60);
    connectServerButton->setFont(QFont("Microsoft YaHe", 10, QFont::Black));
    connectServerButton->setText(QString::fromLocal8Bit("Connect"));
}

