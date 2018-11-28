#pragma once

class QPainter;
class QPen;
class QFont;
class QPointF;
class QString;
class QPixmap;
class QImage;
class QPicture;

/// �ı�����
void DrawingText(QPainter& painter, QPointF st, const QString& text, bool bAntialiasing = true);
void DrawingText(QPainter& painter, QPointF st, const QString& text, QFont font, QPen pen, bool bAntialiasing = true);

/// ͼƬ����
void DrawingPixmap(QPainter& painter, QPointF st, const QPixmap& pix, bool bAntialiasing = true);
void DrawingPixmap(QPainter& painter, QPen pen, QPointF st, const QPixmap& pix, bool bAntialiasing = true);

void DrawingImage(QPainter& painter, QPointF st, const QImage& img, bool bAntialiasing = true);
void DrawingImage(QPainter& painter, QPen pen, QPointF st, const QImage& img, bool bAntialiasing = true);

void DrawingPicture(QPainter& painter, QPointF st, const QPicture& pic, bool bAntialiasing = true);
void DrawingPicture(QPainter& painter, QPen pen, QPointF st, const QPicture& pic, bool bAntialiasing = true);
