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
    /// ���û��߿��
    void SetLineWidth(int width);
    /// ���û�����ɫ
    void SetLineColor(const QColor& colorL);
    /// ����ͼ���ڲ����ɫ
    void SetFillBrush(const QBrush& brushF);
    /// ����ͼ���Ƿ�����Ӱ���ߡ���ͷ�޴����ԣ����ò������ã�
    void SetShadow(bool bSet);
    /// �����Ƿ��о��
    void SetSawtooth(bool bSet);
    /// ����Բ��
    void SetRoundCorner(bool bSet);
    /// ���û���ͼ������(enum DrawingType)
    void SetDrawingType(int eType);

    /// �Ƿ��л���ͼ��
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

