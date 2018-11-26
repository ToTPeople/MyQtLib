#pragma once

class QMouseEvent;
class QWidget;
/**
  功能：鼠标拖动、拉伸QWidget类
  实现：9宫格布局，把周边QWidget添加进来，内部实现管理拉伸、拖动逻辑
  < >------------< >
   |              |
   | 内部显示区域 |
   |              |
  < >------------< >
*/
class CDragStretchPrivate;
class CDragStretch
{
public:
    CDragStretch(QWidget* pWgt);
    ~CDragStretch();

public:
    /// 等比例拉伸时，设置拉伸比例
    void SetStretchRatio(float fRatio);
    /// 更新鼠标状态
    void UpdateCursorStatus();

    /// 设置9宫格QWidget
    void SetRightWidget(QWidget* pWgt);
    void SetBottomWidget(QWidget* pWgt);
    void SetBottomRightWidget(QWidget* pWgt);

public:
    void ProcessMousePress(QMouseEvent * event);
    void ProcessMouseMove(QMouseEvent * event);
    void ProcessMouseRelease(QMouseEvent * event);

private:
    CDragStretchPrivate&        m;
};

