#include "modQtDrawing.h"
#include <QPainter>


void DrawingText(QPainter & painter, QPointF st, const QString & text, bool bAntialiasing)
{
    painter.setRenderHint(QPainter::TextAntialiasing, bAntialiasing);
    painter.drawText(st, text);
}

void DrawingText(QPainter & painter, QPointF st, const QString & text, QFont font, QPen pen, bool bAntialiasing)
{
    painter.setPen(pen);
    painter.setFont(font);
    DrawingText(painter, st, text, bAntialiasing);
}

void DrawingPixmap(QPainter & painter, QPointF st, const QPixmap & pix, bool bAntialiasing)
{
    painter.setRenderHint(QPainter::SmoothPixmapTransform, bAntialiasing);
    painter.drawPixmap(st, pix);
}

void DrawingPixmap(QPainter & painter, QPen pen, QPointF st, const QPixmap & pix, bool bAntialiasing)
{
    painter.setPen(pen);
    DrawingPixmap(painter, st, pix, bAntialiasing);
}

void DrawingImage(QPainter & painter, QPointF st, const QImage & img, bool bAntialiasing)
{
    painter.setRenderHint(QPainter::SmoothPixmapTransform, bAntialiasing);
    painter.drawImage(st, img);
}

void DrawingImage(QPainter & painter, QPen pen, QPointF st, const QImage & img, bool bAntialiasing)
{
    painter.setPen(pen);
    DrawingImage(painter, st, img, bAntialiasing);
}

void DrawingPicture(QPainter & painter, QPointF st, const QPicture & pic, bool bAntialiasing)
{
    painter.setRenderHint(QPainter::SmoothPixmapTransform, bAntialiasing);
    painter.drawPicture(st, pic);
}

void DrawingPicture(QPainter & painter, QPen pen, QPointF st, const QPicture & pic, bool bAntialiasing)
{
    painter.setPen(pen);
    DrawingPicture(painter, st, pic, bAntialiasing);
}
