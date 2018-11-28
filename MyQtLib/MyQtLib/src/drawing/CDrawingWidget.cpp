#include "CDrawingWidget.h"
#include <QPainter>
#include <QLabel>
#include <QMouseEvent>
#include <QFile>
#include <QDebug>
#include "ui_Widget.h"
#include "CShape.h"
#include "CommonDefine.h"
#include "CommonFunc.h"
#include "CDragStretch.h"

class CDrawingWidgetPrivate
{
    friend CDrawingWidget;

    typedef enum
    {
        WIDGET_STATE_DRAWING,           // 绘制状态
        WIDGET_STATE_SHOW,              // 显示状态
        WIDGET_STATE_EDITING,           // 编辑状态
    } WidgetState;

    CDrawingWidgetPrivate(CDrawingWidget* pWgt);

public:
    void hideRound();
    void showRound();
    void updatePos(const QPoint& pos);
    void SetLineWidth(int width);
    void SetType(DrawingType eType);

    QImage& GetImage();

public:
    QSize           wgt_size;
    Ui::widget      ui;
    WidgetState     wgtState;       // 当前处理状态

public:
    /// drawing
    bool            bShadow;        // 阴影
    bool            bRound;         // 圆角
    bool            bSawTooth;      // 锯齿
    int             nLineWidth;     // 线宽
    QColor          colorLine;      // 线颜色
    QBrush          brushFill;      // 图形填充色
    int             drawingType;    // 绘制类型
    QImage          originImg;          // 绘制完成后图像（供拉伸）
    QImage          img;                // 显示图像
    QImage          tmpImg;             // 双缓冲绘制临时图像
    QPoint          m_pointCur;
    QPoint          m_pointStart;
    bool            isLastPen;          // 绘制最后一笔
    QRect           afterDrawingPos;    // 绘制完成后位置
    bool            firstUpdatePos;
    bool            hadDrawGraphics;    // 是否有绘制图形
public:
    /// move and stretch
    CDragStretch*   m_pDragStretch;     // 拉伸、拖动封装类
};

CDrawingWidgetPrivate::CDrawingWidgetPrivate(CDrawingWidget* pWgt)
    : wgtState(WIDGET_STATE_DRAWING)
    , isLastPen(false)
    , m_pointCur(QPoint(0, 0))
    , m_pointStart(QPoint(0, 0))
    , drawingType(0)
    , m_pDragStretch(NULL)
    , afterDrawingPos(0, 0, 0, 0)
    , firstUpdatePos(true)
    , hadDrawGraphics(false)
    , bShadow(false)
    , bRound(false)
    , bSawTooth(false)
    , nLineWidth(1)
    , colorLine(Qt::black)
    , brushFill(Qt::NoBrush)
{
    ui.setupUi(pWgt);
    {
        ui.wgtBottom->hide();
        ui.wgtBottomLeft->hide();
        ui.wgtBottomRight->hide();
        ui.wgtLeft->hide();
        ui.wgtRight->hide();
        ui.wgtTop->hide();
        ui.wgtTopLeft->hide();
        ui.wgtTopRight->hide();
    }
    hideRound();

    img = QImage(pWgt->size(), QImage::Format_RGBA8888);
    img.fill(QColor(0, 0, 0, 0));
    originImg = img;

    m_pDragStretch = new CDragStretch(pWgt);
    if (NULL != m_pDragStretch)
    {
        m_pDragStretch->SetRightWidget(ui.wgtRight);
        m_pDragStretch->SetBottomWidget(ui.wgtBottom);
        m_pDragStretch->SetBottomRightWidget(ui.wgtBottomRight);

        ui.wgtRight->installEventFilter(pWgt);
        ui.wgtBottom->installEventFilter(pWgt);
        ui.wgtBottomRight->installEventFilter(pWgt);
    }
}

void CDrawingWidgetPrivate::hideRound()
{
    if (NULL != m_pDragStretch)
    {
        m_pDragStretch->HideUseBlock();
    }
}

void CDrawingWidgetPrivate::showRound()
{
    if (NULL != m_pDragStretch)
    {
        m_pDragStretch->ShowUseBlock();
    }
}

void CDrawingWidgetPrivate::updatePos(const QPoint& pos)
{
    if (WIDGET_STATE_DRAWING != wgtState)
    {
        return;
    }
    if (DRAWING_TYPE_PEN == drawingType && afterDrawingPos.contains(pos))
    {
        return;
    }

    if (firstUpdatePos)
    {
        afterDrawingPos.setTopLeft(pos);
        afterDrawingPos.setBottomRight(pos);
        firstUpdatePos = false;
        return;
    }

    if (DRAWING_TYPE_PEN == drawingType)
    {
        ExpandRegionByPos(afterDrawingPos, pos);
    }
    else
    {
        int eType = REGION_TYPE_RECT;
        if (DRAWING_TYPE_SQUARE == drawingType || DRAWING_TYPE_CIRCLE == drawingType)
        {
            eType = REGION_TYPE_SQUARE;
        }
        afterDrawingPos = CalRegionByPos(m_pointStart, pos, (RegionType_E)eType);
    }
    
}

void CDrawingWidgetPrivate::SetLineWidth(int width)
{
    if (width < 1)
    {
        return;
    }
    nLineWidth = width;
}
void CDrawingWidgetPrivate::SetType(DrawingType eType)
{
    if (eType > DRAWING_TYPE_MAX || eType < DRAWING_TYPE_NONE)
    {
        return;
    }

    drawingType = eType;
}

QImage& CDrawingWidgetPrivate::GetImage()
{
    if (WIDGET_STATE_DRAWING == wgtState && DRAWING_TYPE_PEN != drawingType)
    {
        tmpImg = img;
        return tmpImg;
    }

    return img;
}

CDrawingWidget::CDrawingWidget(QWidget* parent /*= NULL*/)
    : QWidget(parent)
    , m(*new CDrawingWidgetPrivate(this))
{
#ifdef BUILD_STATIC
    Q_INIT_RESOURCE(my_qt_lib); // 静态库时要设置
#endif
    QFile file(":/drawing/src/drawing/Resources/qss/default.css");
    if (file.open(QFile::ReadOnly))
    {
        setStyleSheet(file.readAll());
        file.close();
    }
}


CDrawingWidget::~CDrawingWidget()
{
    delete &m;
    qDebug() << "-=-=-===-=-=-=-=-= [~CDrawingWidget()] $$$$$$$$$$$$$$$$$$$$";
}

void CDrawingWidget::SetLineWidth(int width)
{
    m.SetLineWidth(width);
}

void CDrawingWidget::SetLineColor(const QColor & colorL)
{
    m.colorLine = colorL;
}

void CDrawingWidget::SetFillBrush(const QBrush & brushF)
{
    m.brushFill = brushF;
}

void CDrawingWidget::SetShadow(bool bSet)
{
    m.bShadow = bSet;
}

void CDrawingWidget::SetSawtooth(bool bSet)
{
    m.bSawTooth = bSet;
}

void CDrawingWidget::SetRoundCorner(bool bSet)
{
    m.bRound = bSet;
}

void CDrawingWidget::SetDrawingType(int eType)
{
    m.drawingType = eType;
}

bool CDrawingWidget::HadDrawGraphics()
{
    return m.hadDrawGraphics;
}

void CDrawingWidget::paintEvent(QPaintEvent * event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);

    QImage &drawImg = m.GetImage();
    if (CDrawingWidgetPrivate::WIDGET_STATE_DRAWING == m.wgtState || m.isLastPen)
    {
        m.isLastPen = false;
        QPen pen(m.colorLine, m.nLineWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        painter.setPen(pen);
        painter.setRenderHint(QPainter::Antialiasing, true);

        QPainter painterImage(&drawImg);
        painterImage.setPen(pen);

        switch (m.drawingType)
        {
        case DRAWING_TYPE_RECT:
            CShape::DrawGraphics(painterImage, pen, m.brushFill, m.m_pointStart, m.m_pointCur
                , m.bRound ? CShape::SHAPE_ROUND_RECT : CShape::SHAPE_RECT, !m.bSawTooth, m.bShadow, true);
            break;
        case DRAWING_TYPE_SQUARE:
            CShape::DrawGraphics(painterImage, pen, m.brushFill, m.m_pointStart, m.m_pointCur
                , m.bRound ? CShape::SHAPE_ROUND_SQUARE : CShape::SHAPE_SQUARE, !m.bSawTooth, m.bShadow, true);
            break;
        case DRAWING_TYPE_CIRCLE:
            CShape::DrawGraphics(painterImage, pen, m.brushFill, m.m_pointStart, m.m_pointCur
                , CShape::SHAPE_CIRCLE, !m.bSawTooth, m.bShadow, true);
            break;
        case DRAWING_TYPE_ELLIPE:
            CShape::DrawGraphics(painterImage, pen, m.brushFill, m.m_pointStart, m.m_pointCur
                , CShape::SHAPE_ELLIPSE, !m.bSawTooth, m.bShadow, true);
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
    }

    painter.drawImage(0, 0, drawImg);
    if (CDrawingWidgetPrivate::WIDGET_STATE_DRAWING != m.wgtState)
    {
        m.m_pointStart = m.m_pointCur;
    }
}

void CDrawingWidget::resizeEvent(QResizeEvent * event)
{
    m.img = m.originImg.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QWidget::resizeEvent(event);
}

bool CDrawingWidget::eventFilter(QObject * target, QEvent * event)
{
    if (NULL != target && NULL != event && target == parent())
    {
        if (QEvent::MouseButtonPress == event->type() && !underMouse())
        {
            if (CDrawingWidgetPrivate::WIDGET_STATE_EDITING == m.wgtState)
            {
                m.wgtState = CDrawingWidgetPrivate::WIDGET_STATE_SHOW;
                m.hideRound();
            }
        }
    }
    else if (m.ui.wgtBottom == target || m.ui.wgtRight == target || m.ui.wgtBottomRight == target)
    {
        if (NULL != m.m_pDragStretch)
        {
            m.m_pDragStretch->UpdateCursorStatus();
        }
    }

    return QWidget::eventFilter(target, event);
}

void CDrawingWidget::mousePressEvent(QMouseEvent * event)
{
    if (NULL == event || !underMouse())
    {
        return QWidget::mousePressEvent(event);
    }

    if (CDrawingWidgetPrivate::WIDGET_STATE_SHOW == m.wgtState)
    {
        m.wgtState = CDrawingWidgetPrivate::WIDGET_STATE_EDITING;
    }

    m.m_pointCur = m.m_pointStart = event->pos();
    m.updatePos(event->pos());

    if (CDrawingWidgetPrivate::WIDGET_STATE_EDITING == m.wgtState)
    {
        m.showRound();
        if (NULL != m.m_pDragStretch)
        {
            m.m_pDragStretch->ProcessMousePress(event);
        }
    }

    QWidget::mousePressEvent(event);
}

void CDrawingWidget::mouseMoveEvent(QMouseEvent * event)
{
    if (NULL != event)
    {
        m.m_pointCur = event->pos();
        if (CDrawingWidgetPrivate::WIDGET_STATE_DRAWING == m.wgtState)
        {
            m.updatePos(event->pos());
            m.hadDrawGraphics = true;
        }
        update();

        if (NULL != m.m_pDragStretch)
        {
            m.m_pDragStretch->ProcessMouseMove(event);
        }
    }
    QWidget::mouseMoveEvent(event);
}

void CDrawingWidget::mouseReleaseEvent(QMouseEvent * event)
{
    m.updatePos(event->pos());

    int pre = m.wgtState;
    if (CDrawingWidgetPrivate::WIDGET_STATE_DRAWING == m.wgtState)
    {
        m.wgtState = CDrawingWidgetPrivate::WIDGET_STATE_SHOW;
        m.isLastPen = true;
    }
    repaint();  // 最后一次绘制
    QWidget::mouseReleaseEvent(event);

    if (NULL != m.m_pDragStretch)
    {
        m.m_pDragStretch->ProcessMouseRelease(event);
    }

    if (CDrawingWidgetPrivate::WIDGET_STATE_SHOW == m.wgtState)
    {
        // 最后根据画笔宽度，修正区域
        int penWidth = m.nLineWidth;
        m.afterDrawingPos.setRect(m.afterDrawingPos.x() - penWidth / 2, m.afterDrawingPos.y() - penWidth / 2
            , m.afterDrawingPos.width() + penWidth, m.afterDrawingPos.height() + penWidth);
        /////////////////////////////
        m.originImg = QImage(m.afterDrawingPos.width(), m.afterDrawingPos.height(), QImage::Format_RGBA8888);
        m.originImg.fill(QColor(0, 0, 0, 0));
        qDebug() << "-=-=-=-=-=- pos: " << m.afterDrawingPos;

        if (NULL != m.m_pDragStretch)
        {
            float fRatio = m.afterDrawingPos.width() * 1.0 / m.afterDrawingPos.height();
            m.m_pDragStretch->SetStretchRatio(fRatio);
        }

        QPainter painter(&m.originImg);
        painter.begin(&m.originImg);
        painter.drawImage(QPoint(0, 0), m.img, m.afterDrawingPos);
        painter.end();
        setGeometry(m.afterDrawingPos);

        emit sigDrawingFinished();
    }
}

