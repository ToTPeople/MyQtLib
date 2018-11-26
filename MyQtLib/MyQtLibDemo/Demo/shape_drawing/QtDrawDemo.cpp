#include "QtDrawDemo.h"
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>
#include <QDebug>
#include "CShape.h"
#include "testWidget.h"
#include "CCenterWidget.h"
#include "CDrawingWidget.h"


static QColor GetColorByString(const QString& str, bool bBrush)
{
    if (str.isNull() || str.isEmpty())
    {
        return bBrush ? Qt::NoBrush : Qt::black;
    }

    if ("red" == str.toLower())
    {
        return Qt::red;
    }
    else if ("blue" == str.toLower())
    {
        return Qt::blue;
    }
    else if ("green" == str.toLower())
    {
        return Qt::green;
    }
    else if ("gray" == str.toLower())
    {
        return Qt::gray;
    }
    else if ("white" == str.toLower())
    {
        return Qt::white;
    }
    else if ("yellow" == str.toLower())
    {
        return Qt::yellow;
    }
    else
    {
        return Qt::black;
    }
}

QtDrawDemo::QtDrawDemo(QWidget *parent)
    : QWidget(parent)
    , m_pointStart(QPoint(0, 0))
    , m_pointCur(QPoint(0, 0))
    , isDrawing(false)
{
    //setWindowFlags(Qt::FramelessWindowHint);
    //setAttribute(Qt::WA_TranslucentBackground);
    ui.setupUi(this);

    //QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    ////shadow_effect->setOffset(5);
    //shadow_effect->setOffset(-5, 5);
    //shadow_effect->setColor(Qt::red);
    //shadow_effect->setBlurRadius(8);
    ////ui->frame_main->setGraphicsEffect(shadow_effect);
    //setGraphicsEffect(shadow_effect);

    //pix = new QPixmap(size());
    //setFixedSize(1024, 700);
    resize(1024, 500);
    pix = QPixmap(size());
    pix.fill(Qt::white);

    img = QImage(size(), QImage::Format_RGBA8888);
    img.fill(Qt::blue);
    img.fill(QColor(0, 0, 0, 0));

    m_pTestWgt = new CCenterWidget(this);
    m_pTestWgt->resize(ui.wgtCenter->size());

    ui.vLayout->removeWidget(ui.wgtCenter);
    ui.vLayout->insertWidget(1, m_pTestWgt);

    {
        // init attribute
        m_pTestWgt->SetFillBrush(GetColorByString(ui.fillColor->text(), true));
        m_pTestWgt->SetLineColor(GetColorByString(ui.lineColor->text(), false));
        int width = ui.lineWidth->text().toInt();
        m_pTestWgt->SetLineWidth(width);

        m_pTestWgt->SetShadow(ui.shadow->isChecked());
        m_pTestWgt->SetSawtooth(!ui.sawtooth->isChecked());
        m_pTestWgt->SetRoundCorner(ui.round->isChecked());

        connect(ui.btnRect, SIGNAL(clicked()), this, SLOT(slotOnRectClick()));
        connect(ui.btnSquare, SIGNAL(clicked()), this, SLOT(slotOnSquareClick()));
        connect(ui.btnEllipse, SIGNAL(clicked()), this, SLOT(slotOnEllipseClick()));
        connect(ui.btnCircle, SIGNAL(clicked()), this, SLOT(slotOnCircleClick()));
        connect(ui.btnArrow, SIGNAL(clicked()), this, SLOT(slotOnArrowClick()));
        connect(ui.btnPen, SIGNAL(clicked()), this, SLOT(slotOnFreeClick()));
        connect(ui.btnUse, SIGNAL(clicked()), this, SLOT(slotOnUseClick()));
    }
}

void QtDrawDemo::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);

    //CShape::DrawGraphics(painter, QPen(QColor(123, 0, 0), 2), Qt::NoBrush

    //if (isDrawing)     //如果正在绘图
    //{
    //    tempPix = pix;    //将以前pix中的内容复制到tempPix中，这样实现了交互绘图
    //    QPainter pp(&tempPix);
    //    pp.setPen(QPen(QColor(0, 160, 230), 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    //    pp.setRenderHint(QPainter::Antialiasing, true);
    //    //pp.drawRect(x, y, w, h);
    //    pp.drawLine(m_pointStart, m_pointCur);
    //    painter.drawPixmap(0, 0, tempPix);
    //}
    //else
    {
        QPen pen(QColor(0, 50, 100), 5);
        //CShape::DrawArrow(painter, pen, QPointF(0, 0), QPointF(100, 200));
        if (0)
        {
            QPainter pp(&pix);
            //pp.drawRect(x, y, w, h);

            pp.setPen(QPen(QColor(0, 160, 230), 20, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            pp.setRenderHint(QPainter::Antialiasing, true);
            pp.drawLine(m_pointStart, m_pointCur);
            painter.drawPixmap(0, 0, pix);

            m_pointStart = m_pointCur;
        }
        else if (0)
        {
            QPainter pp(&img);

            pp.setPen(QPen(QColor(0, 160, 230), 20, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            pp.setRenderHint(QPainter::Antialiasing, true);
            pp.drawLine(m_pointStart, m_pointCur);
            painter.drawImage(0, 0, img);

            m_pointStart = m_pointCur;
        }
        else if (0)
        {
           /* QPainter pp(&m_pTestWgt->img);

            pp.setPen(QPen(QColor(0, 160, 230), 20, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            pp.setRenderHint(QPainter::Antialiasing, true);
            pp.drawLine(m_pointStart, m_pointCur);*/
            //painter.drawImage(0, 0, img);

            m_pointStart = m_pointCur;
        }
        else if (0)
        {
            QColor color(255, 160, 90);
            /// 带阴影椭圆
            //CShape::DrawGraphics(painter, pen, color, m_pointStart, m_pointCur, CShape::SHAPE_ELLIPSE, true, true, true);
            /// 带阴影圆
            CShape::DrawGraphics(painter, pen, color, m_pointStart, m_pointCur, CShape::SHAPE_CIRCLE , true, true);
            /// 带阴影圆角矩形
            //CShape::DrawGraphics(painter, pen, color, m_pointStart, m_pointCur, CShape::SHAPE_ROUND_RECT, true, true);
            /// 带阴影矩形
            //CShape::DrawGraphics(painter, pen, color, m_pointStart, m_pointCur, CShape::SHAPE_RECT, true, true);
            /// 带阴影方形
            //CShape::DrawGraphics(painter, pen, color, m_pointStart, m_pointCur, CShape::SHAPE_SQUARE, true, true);
            /// 带阴影圆角方形
            //CShape::DrawGraphics(painter, pen, color, m_pointStart, m_pointCur, CShape::SHAPE_ROUND_SQUARE, true, true);
        }
    }
}

void QtDrawDemo::mousePressEvent(QMouseEvent * event)
{
    if (NULL != event)
    {
        m_pointCur = m_pointStart = event->pos();
        isDrawing = true;
    }

    QWidget::mousePressEvent(event);
}

void QtDrawDemo::mouseMoveEvent(QMouseEvent * event)
{
    if (NULL != event)
    {
        m_pointCur = event->pos();
        update();
    }
    QWidget::mouseMoveEvent(event);
}

void QtDrawDemo::mouseReleaseEvent(QMouseEvent * event)
{
    isDrawing = false;
    QWidget::mouseReleaseEvent(event);
}

void QtDrawDemo::slotOnRectClick()
{
    m_pTestWgt->SetDrawType(CCenterWidget::DRAW_TYPE_RECT);
}

void QtDrawDemo::slotOnSquareClick()
{
    m_pTestWgt->SetDrawType(CCenterWidget::DRAW_TYPE_SQUARE);
}

void QtDrawDemo::slotOnCircleClick()
{
    m_pTestWgt->SetDrawType(CCenterWidget::DRAW_TYPE_CIRCLE);
}

void QtDrawDemo::slotOnEllipseClick()
{
    m_pTestWgt->SetDrawType(CCenterWidget::DRAW_TYPE_ELLIPE);
}

void QtDrawDemo::slotOnArrowClick()
{
    m_pTestWgt->SetDrawType(CCenterWidget::DRAW_TYPE_ARROW);
}

void QtDrawDemo::slotOnFreeClick()
{
    m_pTestWgt->SetDrawType(CCenterWidget::DRAW_TYPE_PEN);
}

void QtDrawDemo::slotOnUseClick()
{
    m_pTestWgt->SetFillBrush(GetColorByString(ui.fillColor->text(), true));
    m_pTestWgt->SetLineColor(GetColorByString(ui.lineColor->text(), false));
    int width = ui.lineWidth->text().toInt();
    m_pTestWgt->SetLineWidth(width);

    m_pTestWgt->SetShadow(ui.shadow->isChecked());
    m_pTestWgt->SetSawtooth(ui.sawtooth->isChecked());
    m_pTestWgt->SetRoundCorner(ui.round->isChecked());
}

