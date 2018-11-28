#pragma once
#include <QWidget>
#include "myqtlib_global.h"

class CDrawingWidgetPrivate;
class QLabel;
class MYQTLIB_EXPORT CDrawingWidget : public QWidget
{
    Q_OBJECT
public:
    CDrawingWidget(QWidget* parent = NULL);
    ~CDrawingWidget();

public:
    /// 设置画线宽度
    void SetLineWidth(int width);
    /// 设置画线颜色
    void SetLineColor(const QColor& colorL);
    /// 设置图形内部填充色
    void SetFillBrush(const QBrush& brushF);
    /// 设置图形是否有阴影（线、箭头无此属性，设置不起作用）
    void SetShadow(bool bSet);
    /// 设置是否有锯齿
    void SetSawtooth(bool bSet);
    /// 设置圆角
    void SetRoundCorner(bool bSet);
    /// 设置绘制图形类型(enum DrawingType)
    void SetDrawingType(int eType);

    /// 是否有绘制图形
    bool HadDrawGraphics();

public:
    virtual void paintEvent(QPaintEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
    virtual bool eventFilter(QObject *target, QEvent *event);

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

signals:
    void sigDrawingFinished();


private:
    CDrawingWidgetPrivate&      m;
};

