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
    /// 是否有编辑过
    bool hadEdit();
    /// 设置编辑属性：字体大小、字体类型、粗体、斜体、下划线、文本颜色、对齐方式
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
    /// 文本显示区域变化槽函数
    void slotTextAreaChanged();
    /// 选中文本变化槽函数
    void slotTextSelectChanged();

private:
    CTextWidgetPrivate&     m;
};

