#pragma once

#include <QtWidgets/QWidget>
#include <QPainterPath>
#include "ui_QtDrawDemo.h"

class testWidget;
class CDrawingWidget;
class CCenterWidget;
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

private:
    Ui::QtDrawDemoClass ui;

    QPoint                  m_pointStart;
    QPoint                  m_pointCur;
    QPainterPath            m_painterPath;
    QPixmap                 pix, tempPix;
    QImage                  img;
    CCenterWidget*          m_pTestWgt;
    bool isDrawing;
};
