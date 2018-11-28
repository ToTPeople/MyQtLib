#pragma once
#include <qwidget.h>
#include "myqtlib_global.h"

class QColor;
class CTextWidgetPrivate;
class MYQTLIB_EXPORT CTextWidget : public QWidget
{
    Q_OBJECT
public:
    CTextWidget(QWidget* parent = NULL);
    ~CTextWidget();

public:
    /// �Ƿ��б༭��
    bool hadEdit();
    /// ���ñ༭���ԣ������С���������͡����塢б�塢�»��ߡ��ı���ɫ�����뷽ʽ
    void SetFontSize(int nFontSize);
    void SetFamily(const QString& strFamily);
    void SetBold(bool bBold);
    void SetItalic(bool bItalic);
    void SetUnderLine(bool bUnderLine);
    void SetTextColor(const QColor& colorText);
    void SetAlignment(int nAlign);

public:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);

    virtual bool eventFilter(QObject *target, QEvent *event);

    virtual void resizeEvent(QResizeEvent *event);

public slots:
    /// �ı���ʾ����仯�ۺ���
    void slotTextAreaChanged();
    /// ѡ���ı��仯�ۺ���
    void slotTextSelectChanged();

private:
    CTextWidgetPrivate&     m;
};

