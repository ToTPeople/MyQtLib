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
    /// �Ծ���������Ƶ�ͼ�� ����
    typedef enum {
        SHAPE_NONE = 0x00,
        SHAPE_RECT,                     // ����
        SHAPE_ROUND_RECT,               // Բ�Ǿ���
        SHAPE_SQUARE,                   // ������
        SHAPE_ROUND_SQUARE,             // Բ��������
        SHAPE_ELLIPSE,                  // ��Բ
        SHAPE_CIRCLE,                   // Բ
        SHAPE_MAX,
    } ShapeType;

public:
    /// ���ݡ�ͼ�Ρ��������� ������Ӱ
    static void DrawShadowByShape(QPainter & painter, QPen pen, QRect& rc, ShapeType eType, bool bInternal = false, bool bAntialiasing = true, int shadowWidth = 10);
    /// ���������� ��ͼ�Ρ� �ⲿ��Ӱ( ��ͼ�Ρ� ��С���䣬��Ӱ�ڷ������)
    static void DrawExternalShadowByShape(QPainter& painter, QPen pen, const QPoint& topLeftPoint, const QPoint& bottomRightPoint, ShapeType eType, bool bAntialiasing = true, int shadowWidth = 10);
    /// ���������� ��ͼ�Ρ� ��Ӱ( ��ͼ�Ρ� ����С����Ӱ�ڷ����ڲ�)
    static void DrawInternalShadowByShape(QPainter& painter, QPen pen, const QPoint& topLeftPoint, const QPoint& bottomRightPoint, ShapeType eType, bool bAntialiasing = true, int shadowWidth = 10);

public:
    /// ���������ƣ�ʹ��QPaintPath������Щ�ͻῨ�������Լ�ʵ��
    static void DrawByMousePos(QPainter& painter, QPainterPath& painterPath, QPen pen, QPoint& st, QPoint& en, bool bAntialiasing = true);

    /// ��->(��ͷ)
    static void DrawArrow(QPainter& painter, QPen pen, QPointF st, QPointF en, bool bAntialiasing = true);

    /// ���� ��ͼ�Ρ����� ����
    static void DrawGraphics(QPainter& painter, QPen pen, QBrush brush, const QPoint& topLeftPoint, const QPoint& bottomRightPoint, ShapeType eType, bool bAntialiasing = true, bool bWithShadow = false, bool bInternal = false, int shadowWidth = 10);

private:
    CShape();
    ~CShape();
};

