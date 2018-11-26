#pragma once
#include <QRect>

class QPainter;
class CEffects
{
public:
    // �߿���ӰЧ��
    void PaintShadow(QPainter& painter, int width, int height, int shadow_width);
    // Բ��Ч��
    void PaintRound(QPainter& painter, QRect rc, int xRnd, int yRnd);

private:
    CEffects();
    ~CEffects();
};

