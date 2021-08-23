#pragma once
#include<QtWidgets>
//ÖØÐ´QLineEdit
class BeanComEdit : public QTextEdit
{
	Q_OBJECT

public:
	BeanComEdit(QWidget* parent = 0);
	~BeanComEdit();
protected:
	//½¹µãº¯Êý
	void setFocus(Qt::FocusReason reason);
	void focusInEvent(QFocusEvent* e);
	void focusOutEvent(QFocusEvent* e);
};
