#include "MyQtLibDemo.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyQtLibDemo w;
    w.show();
    return a.exec();
}
