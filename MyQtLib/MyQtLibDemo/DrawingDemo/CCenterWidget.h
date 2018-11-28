#pragma once
#include <qwidget.h>

class CCenterWidgetPrivate;
class QColor;
class QBrush;
class QImage;
class QMouseEvent;
/**
  �����࣬���ƻ��壬�ṩ���Ƶ�����
*/
class CCenterWidget : public QWidget
{
    Q_OBJECT

public:
    CCenterWidget(QWidget* parent = NULL);
    ~CCenterWidget();

    virtual void paintEvent(QPaintEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
    virtual bool eventFilter(QObject *target, QEvent *event);

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

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

    /// ���û������� (enum DrawingType)
    void SetDrawType(int eType);

public slots:
    void slotDrawingFinished();

private:
    CCenterWidgetPrivate&       m;
};

