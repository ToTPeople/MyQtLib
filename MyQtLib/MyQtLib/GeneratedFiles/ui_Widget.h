/********************************************************************************
** Form generated from reading UI file 'Widget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_widget
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *wgtLeftBar;
    QVBoxLayout *verticalLayout;
    QWidget *wgtTopLeft;
    QSpacerItem *verticalSpacer;
    QWidget *wgtLeft;
    QSpacerItem *verticalSpacer_2;
    QWidget *wgtBottomLeft;
    QWidget *wgtCenter;
    QVBoxLayout *verticalLayout_2;
    QWidget *wgtTopBar;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QWidget *wgtTop;
    QSpacerItem *horizontalSpacer_2;
    QWidget *wgtCenterDrawing;
    QWidget *wgtBottomBar;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QWidget *wgtBottom;
    QSpacerItem *horizontalSpacer_4;
    QWidget *wgtRightBar;
    QVBoxLayout *verticalLayout_3;
    QWidget *wgtTopRight;
    QSpacerItem *verticalSpacer_3;
    QWidget *wgtRight;
    QSpacerItem *verticalSpacer_4;
    QWidget *wgtBottomRight;

    void setupUi(QWidget *widget)
    {
        if (widget->objectName().isEmpty())
            widget->setObjectName(QStringLiteral("widget"));
        widget->resize(400, 300);
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        wgtLeftBar = new QWidget(widget);
        wgtLeftBar->setObjectName(QStringLiteral("wgtLeftBar"));
        wgtLeftBar->setMinimumSize(QSize(5, 15));
        wgtLeftBar->setMaximumSize(QSize(5, 16777215));
        verticalLayout = new QVBoxLayout(wgtLeftBar);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        wgtTopLeft = new QWidget(wgtLeftBar);
        wgtTopLeft->setObjectName(QStringLiteral("wgtTopLeft"));
        wgtTopLeft->setMinimumSize(QSize(5, 5));
        wgtTopLeft->setMaximumSize(QSize(5, 5));

        verticalLayout->addWidget(wgtTopLeft);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        wgtLeft = new QWidget(wgtLeftBar);
        wgtLeft->setObjectName(QStringLiteral("wgtLeft"));
        wgtLeft->setMinimumSize(QSize(5, 5));
        wgtLeft->setMaximumSize(QSize(5, 5));

        verticalLayout->addWidget(wgtLeft);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        wgtBottomLeft = new QWidget(wgtLeftBar);
        wgtBottomLeft->setObjectName(QStringLiteral("wgtBottomLeft"));
        wgtBottomLeft->setMinimumSize(QSize(5, 5));
        wgtBottomLeft->setMaximumSize(QSize(5, 5));

        verticalLayout->addWidget(wgtBottomLeft);


        horizontalLayout->addWidget(wgtLeftBar);

        wgtCenter = new QWidget(widget);
        wgtCenter->setObjectName(QStringLiteral("wgtCenter"));
        wgtCenter->setMinimumSize(QSize(0, 40));
        verticalLayout_2 = new QVBoxLayout(wgtCenter);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        wgtTopBar = new QWidget(wgtCenter);
        wgtTopBar->setObjectName(QStringLiteral("wgtTopBar"));
        wgtTopBar->setMinimumSize(QSize(0, 5));
        wgtTopBar->setMaximumSize(QSize(16777215, 5));
        horizontalLayout_2 = new QHBoxLayout(wgtTopBar);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        wgtTop = new QWidget(wgtTopBar);
        wgtTop->setObjectName(QStringLiteral("wgtTop"));
        wgtTop->setMinimumSize(QSize(5, 5));
        wgtTop->setMaximumSize(QSize(5, 5));

        horizontalLayout_2->addWidget(wgtTop);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_2->addWidget(wgtTopBar);

        wgtCenterDrawing = new QWidget(wgtCenter);
        wgtCenterDrawing->setObjectName(QStringLiteral("wgtCenterDrawing"));
        wgtCenterDrawing->setMinimumSize(QSize(0, 20));

        verticalLayout_2->addWidget(wgtCenterDrawing);

        wgtBottomBar = new QWidget(wgtCenter);
        wgtBottomBar->setObjectName(QStringLiteral("wgtBottomBar"));
        wgtBottomBar->setMinimumSize(QSize(0, 5));
        wgtBottomBar->setMaximumSize(QSize(16777215, 5));
        horizontalLayout_3 = new QHBoxLayout(wgtBottomBar);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        wgtBottom = new QWidget(wgtBottomBar);
        wgtBottom->setObjectName(QStringLiteral("wgtBottom"));
        wgtBottom->setMinimumSize(QSize(5, 5));
        wgtBottom->setMaximumSize(QSize(5, 5));

        horizontalLayout_3->addWidget(wgtBottom);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        verticalLayout_2->addWidget(wgtBottomBar);


        horizontalLayout->addWidget(wgtCenter);

        wgtRightBar = new QWidget(widget);
        wgtRightBar->setObjectName(QStringLiteral("wgtRightBar"));
        wgtRightBar->setMinimumSize(QSize(5, 15));
        wgtRightBar->setMaximumSize(QSize(5, 16777215));
        verticalLayout_3 = new QVBoxLayout(wgtRightBar);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        wgtTopRight = new QWidget(wgtRightBar);
        wgtTopRight->setObjectName(QStringLiteral("wgtTopRight"));
        wgtTopRight->setMinimumSize(QSize(5, 5));
        wgtTopRight->setMaximumSize(QSize(5, 5));

        verticalLayout_3->addWidget(wgtTopRight);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);

        wgtRight = new QWidget(wgtRightBar);
        wgtRight->setObjectName(QStringLiteral("wgtRight"));
        wgtRight->setMinimumSize(QSize(5, 5));
        wgtRight->setMaximumSize(QSize(5, 5));

        verticalLayout_3->addWidget(wgtRight);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_4);

        wgtBottomRight = new QWidget(wgtRightBar);
        wgtBottomRight->setObjectName(QStringLiteral("wgtBottomRight"));
        wgtBottomRight->setMinimumSize(QSize(5, 5));
        wgtBottomRight->setMaximumSize(QSize(5, 5));

        verticalLayout_3->addWidget(wgtBottomRight);


        horizontalLayout->addWidget(wgtRightBar);


        retranslateUi(widget);

        QMetaObject::connectSlotsByName(widget);
    } // setupUi

    void retranslateUi(QWidget *widget)
    {
        widget->setWindowTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class widget: public Ui_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
