#include <BeanComUIRewrites.h>

BeanComEdit::BeanComEdit(QWidget* parent) :QTextEdit(parent)
{

}

BeanComEdit::~BeanComEdit()
{
    
}

void BeanComEdit::setFocus(Qt::FocusReason reason)
{
    repaint();
}

void BeanComEdit::focusInEvent(QFocusEvent* e)
{
    QTextEdit::focusInEvent(e);

}

void BeanComEdit::focusOutEvent(QFocusEvent* e)
{
    QTextEdit::focusInEvent(e);

}