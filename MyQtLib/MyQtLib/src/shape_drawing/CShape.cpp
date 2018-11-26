#include "CShape.h"
#include <QPainter>
#include <math.h>

static QRect AdjustPosition(const QPoint &st, const QPoint &en, CShape::ShapeType eType)
{
    QRect rc;
    if (st == en)
    {
        rc.setTopLeft(st);
        rc.setBottomRight(en);
        return rc;
    }
    bool bEquilateral = false;
    if (CShape::SHAPE_SQUARE == eType || CShape::SHAPE_ROUND_SQUARE == eType
        || CShape::SHAPE_CIRCLE == eType)
    {
        bEquilateral = true;
    }

    int x = en.x() - st.x();
    int y = en.y() - st.y();
    int width = (x > 0) ? x : -x;
    int height = (y > 0) ? y : -y;
    int nMin = (width > height) ? height : width;
    QPoint newSt = st;
    QPoint newEn = en;


    if (x < 0)
    {
        if (y < 0)
        {
            if (bEquilateral)
            {
                newEn.setX(en.x() + width - nMin);
                newEn.setY(en.y() + height - nMin);
            }
            rc.setTopLeft(newEn);
            rc.setBottomRight(newSt);
        }
        else
        {
            if (bEquilateral)
            {
                newEn.setX(en.x() + width - nMin);
                newEn.setY(en.y() - (height - nMin));
            }
            rc.setTopRight(newSt);
            rc.setBottomLeft(newEn);
        }
    }
    else
    {
        if (y < 0)
        {
            if (bEquilateral)
            {
                newEn.setX(en.x() - (width - nMin));
                newEn.setY(en.y() + height - nMin);
            }
            rc.setBottomLeft(newSt);
            rc.setTopRight(newEn);
        }
        else
        {
            if (bEquilateral)
            {
                newEn.setX(en.x() - (width - nMin));
                newEn.setY(en.y() - (height - nMin));
            }
            rc.setTopLeft(newSt);
            rc.setBottomRight(newEn);
        }
    }

    return rc;
}

static QRect AdjustPosition(const QPoint &st, const QPoint &en)
{
    AdjustPosition(st, en, CShape::SHAPE_NONE);
}

static bool IsShapeTypeValid(CShape::ShapeType eType)
{
    if (CShape::SHAPE_NONE >= eType || eType >= CShape::SHAPE_MAX)
    {
        return false;
    }
    return true;
}

static void DrawByShape(QPainter& painter, QRect rc, CShape::ShapeType eType)
{
    if (!IsShapeTypeValid(eType))
    {
        return;
    }

    switch (eType)
    {
    case CShape::SHAPE_RECT:
    case CShape::SHAPE_SQUARE:
        painter.drawRect(rc);
        break;
    case CShape::SHAPE_ROUND_RECT:
    case CShape::SHAPE_ROUND_SQUARE:
        painter.drawRoundRect(rc);
        break;
    case CShape::SHAPE_ELLIPSE:
    case CShape::SHAPE_CIRCLE:
        painter.drawEllipse(rc);
        break;
    default:
        break;
    }
}

void CShape::DrawShadowByShape(QPainter & painter, QPen pen, QRect & rc, ShapeType eType, bool bInternal, bool bAntialiasing, int shadowWidth)
{
    if (!IsShapeTypeValid(eType))
    {
        return;
    }

    painter.setRenderHint(QPainter::Antialiasing, bAntialiasing);

    // 画阴影
    if (shadowWidth <= 0)
    {
        shadowWidth = 5;
    }
    QPen shadowPen(pen);
    shadowPen.setWidth(1);
    painter.setPen(shadowPen);
    //painter.setPen(QPen(QColor(255, 0, 0), shadowWidth, Qt::DotLine));

    // 设置画刷颜色
    painter.setBrush(Qt::NoBrush);
    QColor color(0, 0, 0, 50);
    int ellipseWidth = pen.width() / 2;
    int total = 150;
    int step = total / sqrt(shadowWidth);
    QRect rcDraw;
    for (int i = 0; i < shadowWidth; ++i)
    {
        color.setAlpha(total - sqrt(i) * step);
        painter.setPen(color);
        if (bInternal)
        {
            rcDraw.setRect(rc.x() + (shadowWidth - i), rc.y() + (shadowWidth - i)
                , rc.width() - (shadowWidth - i) * 2, rc.height() - (shadowWidth - i) * 2);
        }
        else
        {
            rcDraw.setRect(rc.x() - i - ellipseWidth, rc.y() - i - ellipseWidth
                , rc.width() + (i + ellipseWidth) * 2, rc.height() + (i + ellipseWidth) * 2);
        }

        DrawByShape(painter, rcDraw, eType);
    }

    if (bInternal)
    {
        rc.setRect(rc.x() + shadowWidth + ellipseWidth, rc.y() + shadowWidth + ellipseWidth
            , rc.width() - 2 * (shadowWidth + ellipseWidth)
            , rc.height() - 2 * (shadowWidth + ellipseWidth));

        //painter.setClipRect(rc);
    }
}

void CShape::DrawExternalShadowByShape(QPainter & painter, QPen pen, const QPoint & topLeftPoint, const QPoint & bottomRightPoint, ShapeType eType, bool bAntialiasing, int shadowWidth)
{
    if (topLeftPoint == bottomRightPoint)
    {
        return;
    }

    QRect rc = AdjustPosition(topLeftPoint, bottomRightPoint, eType);
    DrawShadowByShape(painter, pen, rc, eType, true, bAntialiasing, shadowWidth);
}

void CShape::DrawInternalShadowByShape(QPainter & painter, QPen pen, const QPoint & topLeftPoint, const QPoint & bottomRightPoint, ShapeType eType, bool bAntialiasing, int shadowWidth)
{
    if (topLeftPoint == bottomRightPoint)
    {
        return;
    }

    QRect rc = AdjustPosition(topLeftPoint, bottomRightPoint, eType);
    DrawShadowByShape(painter, pen, rc, eType, true, bAntialiasing, shadowWidth);
}

void CShape::DrawByMousePos(QPainter & painter, QPainterPath & painterPath, QPen pen, QPoint & st, QPoint & en, bool bAntialiasing /*= true*/)
{
    painter.setRenderHint(QPainter::Antialiasing, bAntialiasing);

    //QPen(QColor(0, 160, 230), 20, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)
    painter.setPen(pen);

    painterPath.moveTo(st);
    painterPath.lineTo(en);

    painter.drawPath(painterPath);

    painter.setRenderHint(QPainter::Antialiasing, !bAntialiasing);
    st = en;
}

//求箭头两点坐标
static void CalcVertexes(double start_x, double start_y, double end_x, double end_y, double& x1, double& y1, double& x2, double& y2)
{
    double arrow_lenght_ = 10;  //箭头长度，一般固定
    double arrow_degrees_ = 0.5;//箭头角度，一般固定

    double angle = atan2(end_y - start_y, end_x - start_x) + 3.1415926;//

    x1 = end_x + arrow_lenght_ * cos(angle - arrow_degrees_);//求得箭头点1坐标
    y1 = end_y + arrow_lenght_ * sin(angle - arrow_degrees_);
    x2 = end_x + arrow_lenght_ * cos(angle + arrow_degrees_);//求得箭头点2坐标
    y2 = end_y + arrow_lenght_ * sin(angle + arrow_degrees_);
}

void CShape::DrawArrow(QPainter & painter, QPen pen, QPointF st, QPointF en, bool bAntialiasing /*= true*/)
{
    painter.setRenderHint(QPainter::Antialiasing, bAntialiasing);
    painter.setPen(pen);

    double x1, y1, x2, y2; //箭头的两点坐标

    //求得箭头两点坐标
    CalcVertexes(st.x(), st.y(), en.x(), en.y(), x1, y1, x2, y2);

    painter.drawLine(st, en);//绘制线段
    painter.drawLine(en.x(), en.y(), x1, y1);//绘制箭头一半
    painter.drawLine(en.x(), en.y(), x2, y2);//绘制箭头另一半

    painter.setRenderHint(QPainter::Antialiasing, !bAntialiasing);
}

void CShape::DrawGraphics(QPainter & painter, QPen pen, QBrush brush, const QPoint & topLeftPoint, const QPoint & bottomRightPoint, ShapeType eType, bool bAntialiasing, bool bWithShadow, bool bInternal, int shadowWidth)
{
    // judge shape type valid
    if (!IsShapeTypeValid(eType))
    {
        return;
    }

    if (topLeftPoint == bottomRightPoint)
    {
        return;
    }

    QRect rc = AdjustPosition(topLeftPoint, bottomRightPoint, eType);

    painter.setRenderHint(QPainter::Antialiasing, bAntialiasing);

    // draw shadow
    if (bWithShadow)
    {
        DrawShadowByShape(painter, pen, rc, eType, bInternal, bAntialiasing, shadowWidth);
    }

    // draw graphics
    painter.setPen(pen);
    painter.setBrush(brush);
    DrawByShape(painter, rc, eType);
}

CShape::CShape()
{
}


CShape::~CShape()
{
}
