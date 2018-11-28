#pragma once

#include <QtWidgets/QWidget>
#include <QPainterPath>
#include "ui_QtDrawDemo.h"

class CDrawingWidget;
class CCenterWidget;
class CDrawingWidget;
class QtDrawDemo : public QWidget
{
    Q_OBJECT

public:
    QtDrawDemo(QWidget *parent = Q_NULLPTR);

public:
    virtual void paintEvent(QPaintEvent *event);

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

public slots:
    void slotOnRectClick();
    void slotOnSquareClick();
    void slotOnCircleClick();
    void slotOnEllipseClick();
    void slotOnArrowClick();
    void slotOnFreeClick();
    void slotOnUseClick();
    void slotOnMouseClick();
    void slotOnTextClick();

    void slotTextAreaChanged();
    void slotTextSelectChanged();

private:
    Ui::QtDrawDemoClass ui;
    CCenterWidget*          m_pTestWgt;
    CDrawingWidget*         m_pPen;
    CDrawingWidget*         m_pRect;
};
