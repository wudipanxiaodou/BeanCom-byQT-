#pragma once
#include<QtWidgets>
//��дQLineEdit
class BeanComEdit : public QTextEdit
{
	Q_OBJECT

public:
	BeanComEdit(QWidget* parent = 0);
	~BeanComEdit();
protected:
	//���㺯��
	void setFocus(Qt::FocusReason reason);
	void focusInEvent(QFocusEvent* e);
	void focusOutEvent(QFocusEvent* e);
};
