#pragma once
#include <QRect>

class QPainter;
class CEffects
{
public:
    // 边框阴影效果
    void PaintShadow(QPainter& painter, int width, int height, int shadow_width);
    // 圆角效果
    void PaintRound(QPainter& painter, QRect rc, int xRnd, int yRnd);

private:
    CEffects();
    ~CEffects();
};

