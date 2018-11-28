#include "MyQtLibDemo.h"
#include <QtWidgets/QApplication>
#include "QtDrawDemo.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    //MyQtLibDemo w;
    //w.show();
    if (1)
    {
        /// drawing demo
        QtDrawDemo *w = new QtDrawDemo();
        w->show();
    }


    return a.exec();
}
