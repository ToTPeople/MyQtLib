/********************************************************************************
** Form generated from reading UI file 'QtDrawDemo.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTDRAWDEMO_H
#define UI_QTDRAWDEMO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtDrawDemoClass
{
public:
    QVBoxLayout *vLayout;
    QWidget *wgtTop;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QPushButton *btnRect;
    QPushButton *btnSquare;
    QPushButton *btnEllipse;
    QPushButton *btnCircle;
    QPushButton *btnArrow;
    QPushButton *btnPen;
    QPushButton *btnText;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *lineWidth;
    QLabel *label_3;
    QWidget *widget_9;
    QVBoxLayout *verticalLayout_8;
    QLineEdit *lineColor;
    QLabel *label_8;
    QWidget *widget_8;
    QVBoxLayout *verticalLayout_7;
    QLineEdit *fillColor;
    QLabel *label_7;
    QCheckBox *shadow;
    QCheckBox *round;
    QCheckBox *sawtooth;
    QPushButton *btnUse;
    QPushButton *btnMouse;
    QWidget *wgtCenter;
    QTextEdit *textEdit;
    QPlainTextEdit *plainTextEdit;
    QWidget *wgtStatus;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QLabel *labelStatus;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *QtDrawDemoClass)
    {
        if (QtDrawDemoClass->objectName().isEmpty())
            QtDrawDemoClass->setObjectName(QStringLiteral("QtDrawDemoClass"));
        QtDrawDemoClass->resize(633, 400);
        vLayout = new QVBoxLayout(QtDrawDemoClass);
        vLayout->setSpacing(6);
        vLayout->setContentsMargins(11, 11, 11, 11);
        vLayout->setObjectName(QStringLiteral("vLayout"));
        wgtTop = new QWidget(QtDrawDemoClass);
        wgtTop->setObjectName(QStringLiteral("wgtTop"));
        wgtTop->setMinimumSize(QSize(0, 100));
        wgtTop->setMaximumSize(QSize(16777215, 100));
        verticalLayout_2 = new QVBoxLayout(wgtTop);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(wgtTop);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(0, 40));
        widget->setMaximumSize(QSize(16777215, 40));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(30, 0));
        label->setMaximumSize(QSize(30, 16777215));

        horizontalLayout->addWidget(label);

        btnRect = new QPushButton(widget);
        btnRect->setObjectName(QStringLiteral("btnRect"));

        horizontalLayout->addWidget(btnRect);

        btnSquare = new QPushButton(widget);
        btnSquare->setObjectName(QStringLiteral("btnSquare"));

        horizontalLayout->addWidget(btnSquare);

        btnEllipse = new QPushButton(widget);
        btnEllipse->setObjectName(QStringLiteral("btnEllipse"));

        horizontalLayout->addWidget(btnEllipse);

        btnCircle = new QPushButton(widget);
        btnCircle->setObjectName(QStringLiteral("btnCircle"));

        horizontalLayout->addWidget(btnCircle);

        btnArrow = new QPushButton(widget);
        btnArrow->setObjectName(QStringLiteral("btnArrow"));

        horizontalLayout->addWidget(btnArrow);

        btnPen = new QPushButton(widget);
        btnPen->setObjectName(QStringLiteral("btnPen"));

        horizontalLayout->addWidget(btnPen);

        btnText = new QPushButton(widget);
        btnText->setObjectName(QStringLiteral("btnText"));

        horizontalLayout->addWidget(btnText);


        verticalLayout_2->addWidget(widget);

        widget_3 = new QWidget(wgtTop);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        horizontalLayout_2 = new QHBoxLayout(widget_3);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget_3);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(30, 0));
        label_2->setMaximumSize(QSize(30, 16777215));

        horizontalLayout_2->addWidget(label_2);

        widget_4 = new QWidget(widget_3);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        verticalLayout_3 = new QVBoxLayout(widget_4);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        lineWidth = new QLineEdit(widget_4);
        lineWidth->setObjectName(QStringLiteral("lineWidth"));

        verticalLayout_3->addWidget(lineWidth);

        label_3 = new QLabel(widget_4);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_3->addWidget(label_3);


        horizontalLayout_2->addWidget(widget_4);

        widget_9 = new QWidget(widget_3);
        widget_9->setObjectName(QStringLiteral("widget_9"));
        verticalLayout_8 = new QVBoxLayout(widget_9);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        lineColor = new QLineEdit(widget_9);
        lineColor->setObjectName(QStringLiteral("lineColor"));

        verticalLayout_8->addWidget(lineColor);

        label_8 = new QLabel(widget_9);
        label_8->setObjectName(QStringLiteral("label_8"));

        verticalLayout_8->addWidget(label_8);


        horizontalLayout_2->addWidget(widget_9);

        widget_8 = new QWidget(widget_3);
        widget_8->setObjectName(QStringLiteral("widget_8"));
        verticalLayout_7 = new QVBoxLayout(widget_8);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        fillColor = new QLineEdit(widget_8);
        fillColor->setObjectName(QStringLiteral("fillColor"));

        verticalLayout_7->addWidget(fillColor);

        label_7 = new QLabel(widget_8);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout_7->addWidget(label_7);


        horizontalLayout_2->addWidget(widget_8);

        shadow = new QCheckBox(widget_3);
        shadow->setObjectName(QStringLiteral("shadow"));

        horizontalLayout_2->addWidget(shadow);

        round = new QCheckBox(widget_3);
        round->setObjectName(QStringLiteral("round"));

        horizontalLayout_2->addWidget(round);

        sawtooth = new QCheckBox(widget_3);
        sawtooth->setObjectName(QStringLiteral("sawtooth"));

        horizontalLayout_2->addWidget(sawtooth);

        btnUse = new QPushButton(widget_3);
        btnUse->setObjectName(QStringLiteral("btnUse"));

        horizontalLayout_2->addWidget(btnUse);

        btnMouse = new QPushButton(widget_3);
        btnMouse->setObjectName(QStringLiteral("btnMouse"));

        horizontalLayout_2->addWidget(btnMouse);


        verticalLayout_2->addWidget(widget_3);


        vLayout->addWidget(wgtTop);

        wgtCenter = new QWidget(QtDrawDemoClass);
        wgtCenter->setObjectName(QStringLiteral("wgtCenter"));
        textEdit = new QTextEdit(wgtCenter);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(9, 118, 221, 103));
        plainTextEdit = new QPlainTextEdit(wgtCenter);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(9, 9, 564, 103));

        vLayout->addWidget(wgtCenter);

        wgtStatus = new QWidget(QtDrawDemoClass);
        wgtStatus->setObjectName(QStringLiteral("wgtStatus"));
        wgtStatus->setMinimumSize(QSize(0, 40));
        wgtStatus->setMaximumSize(QSize(16777215, 40));
        horizontalLayout_3 = new QHBoxLayout(wgtStatus);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_4 = new QLabel(wgtStatus);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_3->addWidget(label_4);

        labelStatus = new QLabel(wgtStatus);
        labelStatus->setObjectName(QStringLiteral("labelStatus"));

        horizontalLayout_3->addWidget(labelStatus);

        horizontalSpacer = new QSpacerItem(513, 19, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        vLayout->addWidget(wgtStatus);


        retranslateUi(QtDrawDemoClass);

        QMetaObject::connectSlotsByName(QtDrawDemoClass);
    } // setupUi

    void retranslateUi(QWidget *QtDrawDemoClass)
    {
        QtDrawDemoClass->setWindowTitle(QApplication::translate("QtDrawDemoClass", "QtDrawDemo", Q_NULLPTR));
        label->setText(QApplication::translate("QtDrawDemoClass", "\345\275\242\347\212\266", Q_NULLPTR));
        btnRect->setText(QApplication::translate("QtDrawDemoClass", "\351\225\277\346\226\271\345\275\242", Q_NULLPTR));
        btnSquare->setText(QApplication::translate("QtDrawDemoClass", "\346\255\243\346\226\271\345\275\242", Q_NULLPTR));
        btnEllipse->setText(QApplication::translate("QtDrawDemoClass", "\346\244\255\345\234\206", Q_NULLPTR));
        btnCircle->setText(QApplication::translate("QtDrawDemoClass", "\345\234\206", Q_NULLPTR));
        btnArrow->setText(QApplication::translate("QtDrawDemoClass", "\347\256\255\345\244\264", Q_NULLPTR));
        btnPen->setText(QApplication::translate("QtDrawDemoClass", "\351\232\217\346\204\217\347\224\273", Q_NULLPTR));
        btnText->setText(QApplication::translate("QtDrawDemoClass", "\346\226\207\346\234\254", Q_NULLPTR));
        label_2->setText(QApplication::translate("QtDrawDemoClass", "\345\261\236\346\200\247", Q_NULLPTR));
        lineWidth->setText(QApplication::translate("QtDrawDemoClass", "10", Q_NULLPTR));
        label_3->setText(QApplication::translate("QtDrawDemoClass", "\347\272\277\345\256\275/\345\255\227\344\275\223\345\244\247\345\260\217", Q_NULLPTR));
        lineColor->setText(QApplication::translate("QtDrawDemoClass", "white", Q_NULLPTR));
        label_8->setText(QApplication::translate("QtDrawDemoClass", "\347\272\277\350\211\262/\346\226\207\346\234\254\350\211\262", Q_NULLPTR));
        fillColor->setText(QApplication::translate("QtDrawDemoClass", "green", Q_NULLPTR));
        label_7->setText(QApplication::translate("QtDrawDemoClass", "\345\241\253\345\205\205\350\211\262", Q_NULLPTR));
        shadow->setText(QApplication::translate("QtDrawDemoClass", "\351\230\264\345\275\261", Q_NULLPTR));
        round->setText(QApplication::translate("QtDrawDemoClass", "\345\234\206\350\247\222", Q_NULLPTR));
        sawtooth->setText(QApplication::translate("QtDrawDemoClass", "\351\224\257\351\275\277", Q_NULLPTR));
        btnUse->setText(QApplication::translate("QtDrawDemoClass", "\345\272\224\347\224\250", Q_NULLPTR));
        btnMouse->setText(QApplication::translate("QtDrawDemoClass", "\351\274\240\346\240\207\346\223\215\344\275\234", Q_NULLPTR));
        label_4->setText(QApplication::translate("QtDrawDemoClass", "\347\212\266\346\200\201\357\274\232", Q_NULLPTR));
        labelStatus->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class QtDrawDemoClass: public Ui_QtDrawDemoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTDRAWDEMO_H
