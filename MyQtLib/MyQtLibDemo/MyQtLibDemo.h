#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MyQtLibDemo.h"

class MyQtLibDemo : public QMainWindow
{
    Q_OBJECT

public:
    MyQtLibDemo(QWidget *parent = Q_NULLPTR);

private:
    Ui::MyQtLibDemoClass ui;
};
