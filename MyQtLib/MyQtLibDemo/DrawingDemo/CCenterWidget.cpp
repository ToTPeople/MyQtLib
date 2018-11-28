#include "CCenterWidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QCursor>
#include <QDebug>
#include "CommonDefine.h"
#include "CShape.h"
#include "CDrawingWidget.h"
#include "CTextWidget.h"


namespace
{
//#define TEST_DRAWING_ONLY           // 仅测试绘制接口
}

class CCenterWidgetPrivate
{
    friend CCenterWidget;

public:
    CCenterWidgetPrivate()
        : bShadow(false)
        , bRound(false)
        , bSawTooth(false)
        , nLineWidth(1)
        , colorLine(Qt::black)
        , brushFill(Qt::NoBrush)
        , eDrawType(DRAWING_TYPE_RECT)
#ifndef TEST_DRAWING_ONLY
        , tmpDrawingWgt(NULL)
        , tmpTextWgt(NULL)
#endif
    {}

    ~CCenterWidgetPrivate()
    {
#ifndef TEST_DRAWING_ONLY
        if (NULL != tmpDrawingWgt)
        {
            delete tmpDrawingWgt;
            tmpDrawingWgt = NULL;
        }
#endif
    }

private:
    void SetLineWidth(int width)
    {
        if (width < 1)
        {
            return;
        }
        nLineWidth = width;
    }
    void SetType(DrawingType eType)
    {
        if (eType > DRAWING_TYPE_MAX || eType < DRAWING_TYPE_NONE)
        {
            return;
        }

        eDrawType = eType;
    }
#ifndef TEST_DRAWING_ONLY
    void PreparePainterDevice(CCenterWidget* pCenterWgt)
    {
        if (NULL == pCenterWgt)
        {
            return;
        }

        // 处理前一个画纸
        if (NULL != tmpDrawingWgt && !tmpDrawingWgt->HadDrawGraphics())
        {
            tmpDrawingWgt->deleteLater();
            tmpDrawingWgt = NULL;
        }
        if (NULL != tmpTextWgt && !tmpTextWgt->hadEdit())
        {
            if (DRAWING_TYPE_TEXT == eDrawType)
            {
                return;
            }
            else if (!tmpTextWgt->hadEdit())
            {
                tmpTextWgt->deleteLater();
                tmpTextWgt = NULL;
            }
        }

        if (DRAWING_TYPE_TEXT == eDrawType)
        {
            //tmpTextWgt = new CTextWidget(pCenterWgt);
            //if (NULL != tmpTextWgt)
            //{
            //    pCenterWgt->installEventFilter(tmpTextWgt);
            //    //tmpTextWgt->move(QCursor::pos());
            //    tmpTextWgt->resize(QSize(125, 70)); // 调整大小
            //    tmpTextWgt->show();
            //}
        }
        // 准备新画纸
        else if (eDrawType > DRAWING_TYPE_NONE && eDrawType < DRAWING_TYPE_MAX)
        {
            tmpDrawingWgt = new CDrawingWidget(pCenterWgt);
            if (NULL != tmpDrawingWgt)
            {
                QObject::connect(tmpDrawingWgt, SIGNAL(sigDrawingFinished()), pCenterWgt, SLOT(slotDrawingFinished()));
                pCenterWgt->installEventFilter(tmpDrawingWgt);
                {
                    tmpDrawingWgt->SetDrawingType(eDrawType);
                    tmpDrawingWgt->SetFillBrush(brushFill);
                    tmpDrawingWgt->SetSawtooth(bSawTooth);
                    tmpDrawingWgt->SetShadow(bShadow);
                    tmpDrawingWgt->SetRoundCorner(bRound);
                    tmpDrawingWgt->SetLineColor(colorLine);
                    tmpDrawingWgt->SetLineWidth(nLineWidth);
                }
                //qDebug() << "------------ size: " << pCenterWgt->size();
                tmpDrawingWgt->resize(pCenterWgt->size());
                tmpDrawingWgt->show();
            }
        }
    }
#endif

private:
    bool            bShadow;        // 阴影
    bool            bRound;         // 圆角
    bool            bSawTooth;      // 锯齿
    int             nLineWidth;     // 线宽
    QColor          colorLine;      // 线颜色
    QBrush          brushFill;      // 图形填充色
    DrawingType     eDrawType;      // 绘制类型

private:
    QImage          img;            // 绘制载体
    QImage          tmpImg;         // 双缓冲临时使用
    QPoint          m_pointCur;     // 绘制终点
    QPoint          m_pointStart;   // 绘制起点
    bool            isDrawing;

#ifndef TEST_DRAWING_ONLY
private:
    CDrawingWidget* tmpDrawingWgt;  // 处于绘制状态时创建
    CTextWidget*    tmpTextWgt;
#endif
};

CCenterWidget::CCenterWidget(QWidget* parent /*= NULL*/)
    : QWidget(parent)
    , m(*new CCenterWidgetPrivate())
{
#ifdef TEST_DRAWING_ONLY
    m.img = QImage(size(), QImage::Format_RGBA8888);
    m.img.fill(QColor(0, 0, 0, 0));
#else
    m.PreparePainterDevice(this);
#endif
}


CCenterWidget::~CCenterWidget()
{
    delete &m;
}

void CCenterWidget::paintEvent(QPaintEvent * event)
{
#ifdef TEST_DRAWING_ONLY
    QWidget::paintEvent(event);

    QPainter painter(this);

    QPen pen(m.colorLine, m.nLineWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    QImage &drawImg = (DRAWING_TYPE_PEN == m.eDrawType) ? m.img
        : (m.isDrawing ? (m.tmpImg=m.img, m.tmpImg) : m.img);

    QPainter painterImage(&drawImg);
    painterImage.setPen(pen);

    switch (m.eDrawType)
    {
    case DRAWING_TYPE_RECT:
        CShape::DrawGraphics(painterImage, pen, m.brushFill, m.m_pointStart, m.m_pointCur
            , m.bRound ? CShape::SHAPE_ROUND_RECT : CShape::SHAPE_RECT, !m.bSawTooth, m.bShadow);
        break;
    case DRAWING_TYPE_SQUARE:
        CShape::DrawGraphics(painterImage, pen, m.brushFill, m.m_pointStart, m.m_pointCur
            , m.bRound ? CShape::SHAPE_ROUND_SQUARE : CShape::SHAPE_SQUARE, !m.bSawTooth, m.bShadow);
        break;
    case DRAWING_TYPE_CIRCLE:
        CShape::DrawGraphics(painterImage, pen, m.brushFill, m.m_pointStart, m.m_pointCur
            , CShape::SHAPE_CIRCLE, !m.bSawTooth, m.bShadow);
        break;
    case DRAWING_TYPE_ELLIPE:
        CShape::DrawGraphics(painterImage, pen, m.brushFill, m.m_pointStart, m.m_pointCur
            , CShape::SHAPE_ELLIPSE, !m.bSawTooth, m.bShadow);
        break;
    case DRAWING_TYPE_ARROW:
        CShape::DrawArrow(painterImage, pen, m.m_pointStart, m.m_pointCur, !m.bSawTooth);
        break;
    case DRAWING_TYPE_PEN:
    {
        painterImage.setRenderHint(QPainter::Antialiasing, !m.bSawTooth);
        painterImage.drawLine(m.m_pointStart, m.m_pointCur);
        m.m_pointStart = m.m_pointCur;
    }
        break;
    default:
        break;
    }

    painter.setRenderHint(QPainter::Antialiasing, !m.bSawTooth);
    painter.drawImage(0, 0, drawImg);
    if (!m.isDrawing)
    {
        m.m_pointStart = m.m_pointCur;
    }
#else
    QWidget::paintEvent(event);
#endif
}

void CCenterWidget::resizeEvent(QResizeEvent * event)
{
#ifdef TEST_DRAWING_ONLY
    m.img = m.img.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
#endif
    QWidget::resizeEvent(event);
}

bool CCenterWidget::eventFilter(QObject * target, QEvent * event)
{
    if (NULL != event && QEvent::Resize == event->type() && NULL != target)
    {
        if (target->inherits("QWidget") && target == parent())
        {
            QWidget* pP = static_cast<QWidget*>(target);
            if (NULL != pP)
            {
                resize(pP->size());
            }
        }
    }

    return QWidget::eventFilter(target, event);
}

void CCenterWidget::mousePressEvent(QMouseEvent * event)
{
#ifdef TEST_DRAWING_ONLY
    if (NULL != event && underMouse())
    {
        m.m_pointCur = m.m_pointStart = event->pos();
        m.isDrawing = true;
    }
#else
    if (DRAWING_TYPE_TEXT == m.eDrawType)
    {
        bool bNeedCreate = true;
        if (NULL != m.tmpTextWgt)
        {
            bNeedCreate = false;
            if (!m.tmpTextWgt->underMouse())
            {
                if (!m.tmpTextWgt->hadEdit())
                {
                    m.tmpTextWgt->deleteLater();
                    m.tmpTextWgt = NULL;
                }
                else
                {
                    bNeedCreate = true;
                }
            }
        }
        if (bNeedCreate)
        {
            QList<CTextWidget*> listTextWgt = this->findChildren<CTextWidget*>();
            QList<CTextWidget*>::iterator it = listTextWgt.begin();
            for (; it != listTextWgt.end(); ++it)
            {
                if (NULL != *it && (*it)->geometry().contains(event->pos()))
                {
                    bNeedCreate = false;
                    break;
                }
            }

            if (bNeedCreate)
            {
                m.tmpTextWgt = new CTextWidget(this);
                if (NULL != m.tmpTextWgt)
                {
                    this->installEventFilter(m.tmpTextWgt);
                    m.tmpTextWgt->resize(QSize(125, 70)); // 调整大小
                    m.tmpTextWgt->move(event->pos());
                    m.tmpTextWgt->show();
                }
            }
        }
    }
#endif

    QWidget::mousePressEvent(event);
}

void CCenterWidget::mouseMoveEvent(QMouseEvent * event)
{
#ifdef TEST_DRAWING_ONLY
    if (NULL != event)
    {
        m.m_pointCur = event->pos();
        update();
    }
#endif
    QWidget::mouseMoveEvent(event);
}

void CCenterWidget::mouseReleaseEvent(QMouseEvent * event)
{
#ifdef TEST_DRAWING_ONLY
    m.isDrawing = false;
    update();
#endif
    QWidget::mouseReleaseEvent(event);
}

void CCenterWidget::SetLineWidth(int width)
{
    m.SetLineWidth(width);
    update();
#ifndef TEST_DRAWING_ONLY
    if (NULL != m.tmpDrawingWgt)
    {
        m.tmpDrawingWgt->SetLineWidth(width);
    }
    if (NULL != m.tmpTextWgt)
    {
        m.tmpTextWgt->SetFontSize(width);
    }
#endif
}

void CCenterWidget::SetLineColor(const QColor & colorL)
{
    m.colorLine = colorL;
    update();
#ifndef TEST_DRAWING_ONLY
    if (NULL != m.tmpDrawingWgt)
    {
        m.tmpDrawingWgt->SetLineColor(colorL);
    }
    if (NULL != m.tmpTextWgt)
    {
        m.tmpTextWgt->SetTextColor(colorL);
    }
#endif
}

void CCenterWidget::SetFillBrush(const QBrush & brushF)
{
    m.brushFill = brushF;
    update();
#ifndef TEST_DRAWING_ONLY
    if (NULL != m.tmpDrawingWgt)
    {
        m.tmpDrawingWgt->SetFillBrush(brushF);
    }
#endif
}

void CCenterWidget::SetShadow(bool bSet)
{
    m.bShadow = bSet;
    update();
#ifndef TEST_DRAWING_ONLY
    if (NULL != m.tmpDrawingWgt)
    {
        m.tmpDrawingWgt->SetShadow(bSet);
    }
#endif
}

void CCenterWidget::SetSawtooth(bool bSet)
{
    m.bSawTooth = bSet;
    update();
#ifndef TEST_DRAWING_ONLY
    if (NULL != m.tmpDrawingWgt)
    {
        m.tmpDrawingWgt->SetSawtooth(bSet);
    }
#endif
}

void CCenterWidget::SetRoundCorner(bool bSet)
{
    m.bRound = bSet;
    update();
#ifndef TEST_DRAWING_ONLY
    if (NULL != m.tmpDrawingWgt)
    {
        m.tmpDrawingWgt->SetRoundCorner(bSet);
    }
#endif
}

void CCenterWidget::SetDrawType(int eType)
{
    m.SetType((DrawingType)eType);
#ifndef TEST_DRAWING_ONLY
    m.PreparePainterDevice(this);
#endif
}

void CCenterWidget::slotDrawingFinished()
{
#ifndef TEST_DRAWING_ONLY
    m.PreparePainterDevice(this);
#endif
}
