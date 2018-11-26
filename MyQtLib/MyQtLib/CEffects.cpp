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
  作用：边框阴影效果
  原理：使用alpha渐变绘制
  其他实现：9宫格
  参照：https://blog.csdn.net/luoyayun361/article/details/65428939
  http://blog.sina.com.cn/s/blog_a6fb6cc90101eoop.html
  http://blog.sina.com.cn/s/blog_a6fb6cc90101eoc7.html
  说明：QGraphicsDropShadowEffect试用，仅能2边有阴影效果
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

    // 重新设置QPainter绘制区域
    painter.setClipRect(shadow_width, shadow_width, width - 2 * shadow_width, height - 2 * shadow_width);
}

/**
  作用：边框圆角效果
  原理：调用QPainter接口直接绘制
  参照：https://blog.csdn.net/xuxunjie147/article/details/80609035
  https://www.cnblogs.com/xj626852095/p/3648101.html
  说明：设置显示区域（简单、粗暴控制子控件显示区域，但子控件仍按原来显示区域显示）。实际并不能控制子控件显示~~~~
*/
void CEffects::PaintRound(QPainter & painter, QRect rc, int xRnd, int yRnd)
{
    if (xRnd <= 0 && yRnd <= 0)
    {
        return;
    }

    painter.setRenderHint(QPainter::Antialiasing, true);

    {
        // 设置显示区域（简单、粗暴控制子控件显示区域，但子控件仍按原来显示区域显示）
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
