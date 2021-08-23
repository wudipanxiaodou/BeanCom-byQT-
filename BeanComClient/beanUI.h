#ifndef UI_FIRST_H
#define UI_FIRST_H
#include <QtCore/QLocale>
#include <QtGui/QIcon>
#include<ui_BeanComUI.h>
#include<QtWidgets>
#include"BeanComUIRewrites.h"
//#include"BeanComUI.h"
QT_BEGIN_NAMESPACE
class beanUI :public Ui_BeanComUIClass
{
private:
	//UI
public:
	//控件
	QColor widget_color;
	QColor tab_color, text_color, control_color, left_color;
	QColor dock_color, dock_widget_color, dock_control_color;
	QColor tab_widget_color[7];
	QWidget* centralWidget;
	QTabWidget* tabwidget;
	QWidget* connect, * talking, * file, * activities, * set;
	BeanComEdit* talking_send, * talking_seceive, * TalkingMessageWidget, * Control;
	QWidget* leftSetupBeanCom;
	QWidget* mainTextWidget;
	QPushButton* send_button, * controlButton, * getImformation;
	QPushButton* logButton, * Account, * connectServerButton;
	BeanComEdit* macNumberLabel, * ipNumberLabel;
	QLineEdit* inputServerIP, * inputServerHost;
	QPushButton* beanTalking;
	QLineEdit* inputAccount, * inputPassword;
	QLineEdit* inputAccounts, * inputPasswords, * inputPasswordsa;
	QPushButton* signUpButton, * signInButton;
	QPushButton* finishSignUp, * finishSignIn;
	QWidget* signUpWidget, * signInWidget;
	QRadioButton* passwordVisual, * passwordVisuals;
	BeanComEdit* inputError;
	QWidget* btalking1, * btalking2;
	BeanComEdit* btalking_send, * btalking_seceive;
	QWidget* BFriends;
	QPushButton* bsendButton;
	//主窗口构造
	QVBoxLayout* vlayout_left;
	QVBoxLayout* vlayout_right;
	QWidget* mainLeftWidget;
	QWidget* mainRightWidget;
	QVBoxLayout* hlayout_all;
	QWidget* mainWindowWidget;
	QHBoxLayout* vlayout_up;
	QHBoxLayout* vlayout_down;
	QWidget* mainUpWidget;
	QWidget* mainDownWidget;
	QDockWidget* dock;
	QDockWidget* dock_beancom;
	QDockWidget* BeanComControl;
	QDockWidget* beanComSignUp;
public:
	void Setup_ALL(QMainWindow* ui);
	void Setup_TAB(QMainWindow* ui);
	void Setup_BUTTON_1(QMainWindow* ui);
	void Setup_CONNECT_WIDGET(QMainWindow* ui);
	void Setup_TALKING_WIDGET(QMainWindow* ui);
	void Setup_FILE_WIDGET(QMainWindow* ui);
	void Setup_ACTIVITIES_WIDGET(QMainWindow* ui);
	void Setup_SET_WIDGET(QMainWindow* ui);
	void Setup_MAINTEXTWIDGET(QMainWindow* ui);
	void Setup_DOCK(QMainWindow* ui);
	void Setup_DOCK_BEANCOM(QMainWindow* ui);
	void Setup_DOCK_CONTROL(QMainWindow* ui);
	void Setup_SETUP_BEANCOM(QMainWindow* ui);
	void Setup_Sign(QMainWindow* ui);
public:

};
#endif
