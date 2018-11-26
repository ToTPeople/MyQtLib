#include "CEffects.h"
#include <QPainter>


static int min_value(int x, int y)
{
    return (x < y ? x : y);
}

static int max_value(int x, int y)
{
    return (x < y ? y : x);
}

/**
  ���ã��߿���ӰЧ��
  ԭ��ʹ��alpha�������
  ����ʵ�֣�9����
  ���գ�https://blog.csdn.net/luoyayun361/article/details/65428939
  http://blog.sina.com.cn/s/blog_a6fb6cc90101eoop.html
  http://blog.sina.com.cn/s/blog_a6fb6cc90101eoc7.html
  ˵����QGraphicsDropShadowEffect���ã�����2������ӰЧ��
*/
void CEffects::PaintShadow(QPainter & painter, int width, int height, int shadow_width)
{
    if (shadow_width <= 0 || width <= 0 || height <= 0)
    {
        return;
    }

    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(shadow_width, shadow_width, width - 2* shadow_width, height - 2* shadow_width);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(Qt::white));
    QColor color(0, 0, 0, 50);
    for (int i = 0; i < shadow_width; ++i)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(shadow_width - i, shadow_width - i, width - (shadow_width - i) * 2, height - (shadow_width - i) * 2);
        color.setAlpha(150 - sqrt(i) * 50);
        painter.setPen(color);
        painter.drawPath(path);
    }

    // ��������QPainter��������
    painter.setClipRect(shadow_width, shadow_width, width - 2 * shadow_width, height - 2 * shadow_width);
}

/**
  ���ã��߿�Բ��Ч��
  ԭ������QPainter�ӿ�ֱ�ӻ���
  ���գ�https://blog.csdn.net/xuxunjie147/article/details/80609035
  https://www.cnblogs.com/xj626852095/p/3648101.html
  ˵����������ʾ���򣨼򵥡��ֱ������ӿؼ���ʾ���򣬵��ӿؼ��԰�ԭ����ʾ������ʾ����ʵ�ʲ����ܿ����ӿؼ���ʾ~~~~
*/
void CEffects::PaintRound(QPainter & painter, QRect rc, int xRnd, int yRnd)
{
    if (xRnd <= 0 && yRnd <= 0)
    {
        return;
    }

    painter.setRenderHint(QPainter::Antialiasing, true);

    {
        // ������ʾ���򣨼򵥡��ֱ������ӿؼ���ʾ���򣬵��ӿؼ��԰�ԭ����ʾ������ʾ��
        QRegion region;
        region += rc.adjusted(xRnd, 0, -xRnd, 0);
        region += rc.adjusted(0, yRnd, 0, -yRnd);

        QRect coner = QRect(rc.topLeft(), QSize(xRnd * 2, yRnd * 2));
        region += QRegion(coner, QRegion::Ellipse);

        coner.moveTopRight(rc.topRight());
        region += QRegion(coner, QRegion::Ellipse);

        coner.moveBottomLeft(rc.bottomLeft());
        region += QRegion(coner, QRegion::Ellipse);

        coner.moveBottomRight(rc.bottomRight());
        region += QRegion(coner, QRegion::Ellipse);

        //QWidget->setMask(region);
    }

    painter.drawRoundRect(rc, xRnd, yRnd);
}

CEffects::CEffects()
{
}


CEffects::~CEffects()
{
}
