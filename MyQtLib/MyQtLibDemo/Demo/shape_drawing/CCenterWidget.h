#pragma once
#include <qwidget.h>

class CCenterWidgetPrivate;
class QColor;
class QBrush;
class QImage;
class QMouseEvent;
class CCenterWidget : public QWidget
{
public:
    typedef enum
    {
        DRAW_TYPE_RECT = 0x00,
        DRAW_TYPE_SQUARE,
        DRAW_TYPE_CIRCLE,
        DRAW_TYPE_ELLIPE,
        DRAW_TYPE_ARROW,
        DRAW_TYPE_PEN,
        DRAW_TYPE_MAX
    } DrawType;

public:
    CCenterWidget(QWidget* parent = NULL);
    ~CCenterWidget();

    virtual void paintEvent(QPaintEvent *event);
    virtual void resizeEvent(QResizeEvent *event);

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

public:
    void SetLineWidth(int width);
    void SetLineColor(const QColor& colorL);
    void SetFillBrush(const QBrush& brushF);
    void SetShadow(bool bSet);
    void SetSawtooth(bool bSet);
    void SetRoundCorner(bool bSet);
    void SetDrawType(DrawType eType);

    QImage& GetImage();

private:
    CCenterWidgetPrivate&       m;
};

