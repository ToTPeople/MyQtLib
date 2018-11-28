/********************************************************************************
** Form generated from reading UI file 'MyQtLibDemo.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYQTLIBDEMO_H
#define UI_MYQTLIBDEMO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyQtLibDemoClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MyQtLibDemoClass)
    {
        if (MyQtLibDemoClass->objectName().isEmpty())
            MyQtLibDemoClass->setObjectName(QStringLiteral("MyQtLibDemoClass"));
        MyQtLibDemoClass->resize(600, 400);
        menuBar = new QMenuBar(MyQtLibDemoClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        MyQtLibDemoClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MyQtLibDemoClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MyQtLibDemoClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(MyQtLibDemoClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MyQtLibDemoClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MyQtLibDemoClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MyQtLibDemoClass->setStatusBar(statusBar);

        retranslateUi(MyQtLibDemoClass);

        QMetaObject::connectSlotsByName(MyQtLibDemoClass);
    } // setupUi

    void retranslateUi(QMainWindow *MyQtLibDemoClass)
    {
        MyQtLibDemoClass->setWindowTitle(QApplication::translate("MyQtLibDemoClass", "MyQtLibDemo", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MyQtLibDemoClass: public Ui_MyQtLibDemoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYQTLIBDEMO_H
