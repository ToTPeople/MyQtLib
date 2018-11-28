#pragma once
#include "myqtlib_global.h"

class QPainter;
class QPainterPath;
class QPoint;
class QPointF;
class QRect;
class QPen;
class QBrush;
class MYQTLIB_EXPORT CShape
{
public:
    /// 以矩形区域绘制的图形 类型
    typedef enum {
        SHAPE_NONE = 0x00,
        SHAPE_RECT,                     // 矩形
        SHAPE_ROUND_RECT,               // 圆角矩形
        SHAPE_SQUARE,                   // 正方形
        SHAPE_ROUND_SQUARE,             // 圆角正方形
        SHAPE_ELLIPSE,                  // 椭圆
        SHAPE_CIRCLE,                   // 圆
        SHAPE_MAX,
    } ShapeType;

public:
    /// 根据【图形】矩形区域 绘制阴影
    static void DrawShadowByShape(QPainter & painter, QPen pen, QRect& rc, ShapeType eType, bool bInternal = false, bool bAntialiasing = true, int shadowWidth = 10);
    /// 画给定方框 【图形】 外部阴影( 【图形】 大小不变，阴影在方框外侧)
    static void DrawExternalShadowByShape(QPainter& painter, QPen pen, const QPoint& topLeftPoint, const QPoint& bottomRightPoint, ShapeType eType, bool bAntialiasing = true, int shadowWidth = 10);
    /// 画给定方框 【图形】 阴影( 【图形】 会缩小，阴影在方框内侧)
    static void DrawInternalShadowByShape(QPainter& painter, QPen pen, const QPoint& topLeftPoint, const QPoint& bottomRightPoint, ShapeType eType, bool bAntialiasing = true, int shadowWidth = 10);

public:
    /// 跟随鼠标绘制；使用QPaintPath，画多些就会卡，建议自己实现
    static void DrawByMousePos(QPainter& painter, QPainterPath& painterPath, QPen pen, QPoint& st, QPoint& en, bool bAntialiasing = true);

    /// 画->(箭头)
    static void DrawArrow(QPainter& painter, QPen pen, QPointF st, QPointF en, bool bAntialiasing = true);

    /// 根据 【图形】类型 绘制
    static void DrawGraphics(QPainter& painter, QPen pen, QBrush brush, const QPoint& topLeftPoint, const QPoint& bottomRightPoint, ShapeType eType, bool bAntialiasing = true, bool bWithShadow = false, bool bInternal = false, int shadowWidth = 10);

private:
    CShape();
    ~CShape();
};

