#include "BeanComUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BeanComUI w;
    w.show();
    return a.exec();
}
