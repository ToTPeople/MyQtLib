#include "CCenterWidget.h"
#include <QPainter>
#include <QMouseEvent>
#include "CShape.h"


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
        , eDrawType(CCenterWidget::DRAW_TYPE_RECT)
    {}

private:
    void SetLineWidth(int width)
    {
        if (width < 1)
        {
            return;
        }
        nLineWidth = width;
    }
    void SetType(CCenterWidget::DrawType eType)
    {
        if (eType >= CCenterWidget::DRAW_TYPE_MAX || eType < CCenterWidget::DRAW_TYPE_RECT)
        {
            return;
        }

        eDrawType = eType;
    }

    QImage& GetImage()
    {
        if (CCenterWidget::DRAW_TYPE_PEN == eDrawType || !isDrawing)
        {
            return img;
        }

        tmpImg = img;
        return tmpImg;
    }

private:
    bool            bShadow;
    bool            bRound;
    bool            bSawTooth;      // 锯齿
    int             nLineWidth;
    QColor          colorLine;
    QBrush          brushFill;
    CCenterWidget::DrawType     eDrawType;

public:
    QImage          img;
    QImage          tmpImg;
    QPoint          m_pointCur;
    QPoint          m_pointStart;
    bool            isDrawing;
};

CCenterWidget::CCenterWidget(QWidget* parent /*= NULL*/)
    : QWidget(parent)
    , m(*new CCenterWidgetPrivate())
{
    //setAutoFillBackground(true);
    //setAttribute(Qt::WA_TranslucentBackground);
    m.img = QImage(size(), QImage::Format_RGBA8888);
    m.img.fill(Qt::blue);
    m.img.fill(QColor(0, 0, 0, 0));
}


CCenterWidget::~CCenterWidget()
{
    delete &m;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void drawArrow(QPainter& painter)
{
    QPainterPath path;

    path.moveTo(10, 100);
    path.cubicTo(10, 100, 100, 10, 200, 70);
    path.lineTo(200, 50);
    path.lineTo(220, 80);
    path.lineTo(200, 110);
    path.lineTo(200, 90);
    path.cubicTo(200, 100, 100, 50, 50, 100);

    // draw
    QPen pen(QColor(255, 0, 0), 2);
    painter.setPen(pen);
    painter.drawPath(path);
}

static void drawPathText(QPainter& painter)
{
    //painter.setRenderHint(QPainter::TextAntialiasing, true);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QLinearGradient linearGrad(QPointF(200, 0), QPointF(1000, 0));
    linearGrad.setColorAt(0, Qt::black);
    linearGrad.setColorAt(1, Qt::white);

    QFont font("隶书", 120);
    font.setBold(true);

    QPainterPath textPath;
    QString strText = QObject::tr(QString::fromLocal8Bit("电子工业出版社").toUtf8().data());
    //QObject::tr("电子工业出版社")
    textPath.addText(200, 300, font, strText);

    painter.setBrush(linearGrad);
    painter.drawPath(textPath);

    //painter.setRenderHint(QPainter::TextAntialiasing, false);
    painter.setRenderHint(QPainter::Antialiasing, false);
}

static void drawText(QPainter& painter)
{
    painter.setRenderHint(QPainter::TextAntialiasing, false);
    //painter.setRenderHint(QPainter::TextAntialiasing, true);
    //painter.setRenderHint(QPainter::Antialiasing, true);

    QFont font("隶书", 120);
    font.setBold(true);

    QString strText = QObject::tr(QString::fromLocal8Bit("电子工业出版社").toUtf8().data());

    painter.setFont(font);

    painter.drawText(QPoint(200, 150), strText);

    //painter.setRenderHint(QPainter::TextAntialiasing, false);
    //painter.setRenderHint(QPainter::Antialiasing, false);
}

static void drawArcPieChord(QPainter& painter)
{
    painter.setRenderHint(QPainter::Antialiasing);

    int startAngle = 10 * 16;
    int spanAngle = 160 * 16;
    int width = 900;
    int height = 700;
    painter.drawArc(10, 10, width, height, startAngle, spanAngle);

    width = 400;
    height = 500;
    painter.drawPie(50, 50, width, height, startAngle, spanAngle);

    painter.drawChord(350, 50, width, height, startAngle, 180 * 16);

    painter.drawEllipse(50, 500, width, height);

    painter.setRenderHint(QPainter::Antialiasing, false);
}

static void drawByMousePos(QPainter& painter, QPainterPath& painterPath, QPoint& st, QPoint& en)
{
    painter.setRenderHint(QPainter::Antialiasing, true);
    //painter.setRenderHint(QPainter::HighQualityAntialiasing, true);

    // 设置画笔颜色、宽度
    int width = 20;
    painter.setPen(QPen(QColor(0, 160, 230), width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    painterPath.moveTo(st);
    painterPath.lineTo(en);
    QPoint ct1 = st;// (en - st) / 3;
    QPoint ct2 = en;// (en - st) * 2 / 3;
    //painterPath.cubicTo(ct1, ct2, en);
    //painterPath.addEllipse(QRect(st, en));
    //painter.drawPolyline();

    //painterPath.addPolygon(QPolygonF(en));

    painter.drawPath(painterPath);

    painter.setRenderHint(QPainter::Antialiasing, false);
    st = en;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CCenterWidget::paintEvent(QPaintEvent * event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);

    QPen pen(m.colorLine, m.nLineWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    QImage &drawImg = (CCenterWidget::DRAW_TYPE_PEN == m.eDrawType) ? m.img 
        : (m.isDrawing ? (m.tmpImg=m.img, m.tmpImg) : m.img);

    QPainter painterImage(&drawImg);
    painterImage.setPen(pen);

    switch (m.eDrawType)
    {
    case DRAW_TYPE_RECT:
        CShape::DrawGraphics(painterImage, pen, m.brushFill, m.m_pointStart, m.m_pointCur
            , m.bRound ? CShape::SHAPE_ROUND_RECT : CShape::SHAPE_RECT, !m.bSawTooth, m.bShadow);
        break;
    case DRAW_TYPE_SQUARE:
        CShape::DrawGraphics(painterImage, pen, m.brushFill, m.m_pointStart, m.m_pointCur
            , m.bRound ? CShape::SHAPE_ROUND_SQUARE : CShape::SHAPE_SQUARE, !m.bSawTooth, m.bShadow);
        break;
    case DRAW_TYPE_CIRCLE:
        CShape::DrawGraphics(painterImage, pen, m.brushFill, m.m_pointStart, m.m_pointCur
            , CShape::SHAPE_CIRCLE, !m.bSawTooth, m.bShadow);
        break;
    case DRAW_TYPE_ELLIPE:
        CShape::DrawGraphics(painterImage, pen, m.brushFill, m.m_pointStart, m.m_pointCur
            , CShape::SHAPE_ELLIPSE, !m.bSawTooth, m.bShadow);
        break;
    case DRAW_TYPE_ARROW:
        CShape::DrawArrow(painterImage, pen, m.m_pointStart, m.m_pointCur, !m.bSawTooth);
        break;
    case DRAW_TYPE_PEN:
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
}

void CCenterWidget::resizeEvent(QResizeEvent * event)
{
    m.img = m.img.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

void CCenterWidget::mousePressEvent(QMouseEvent * event)
{
    if (NULL != event && underMouse())
    {
        m.m_pointCur = m.m_pointStart = event->pos();
        m.isDrawing = true;
    }

    QWidget::mousePressEvent(event);
}

void CCenterWidget::mouseMoveEvent(QMouseEvent * event)
{
    if (NULL != event)
    {
        m.m_pointCur = event->pos();
        update();
    }
    QWidget::mouseMoveEvent(event);
}

void CCenterWidget::mouseReleaseEvent(QMouseEvent * event)
{
    m.isDrawing = false;
    update();
    QWidget::mouseReleaseEvent(event);
}

void CCenterWidget::SetLineWidth(int width)
{
    m.SetLineWidth(width);
    update();
}

void CCenterWidget::SetLineColor(const QColor & colorL)
{
    m.colorLine = colorL;
    update();
}

void CCenterWidget::SetFillBrush(const QBrush & brushF)
{
    m.brushFill = brushF;
    update();
}

void CCenterWidget::SetShadow(bool bSet)
{
    m.bShadow = bSet;
    update();
}

void CCenterWidget::SetSawtooth(bool bSet)
{
    m.bSawTooth = bSet;
    update();
}

void CCenterWidget::SetRoundCorner(bool bSet)
{
    m.bRound = bSet;
    update();
}

void CCenterWidget::SetDrawType(DrawType eType)
{
    m.SetType(eType);
}

QImage & CCenterWidget::GetImage()
{
    return m.img;
}
