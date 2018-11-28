#pragma once
#include "CommonDefine.h"

class QMouseEvent;
class QWidget;
/**
  ���ܣ�����϶�������QWidget��
  ʵ�֣�9���񲼾֣����ܱ�QWidget��ӽ������ڲ�ʵ�ֹ������졢�϶��߼�
  < >------------< >
   |              |
   | �ڲ���ʾ���� |
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
    /// �ȱ�������ʱ�������������
    void SetStretchRatio(float fRatio);
    /// �������״̬
    void UpdateCursorStatus();
    /// �����ܱ�8�����ÿ�
    void SetUseBlock(EdgeCornerType_E eType);
    /// ��ʾ�ܱ����ÿ�
    void ShowUseBlock();
    /// �����ܱ����ÿ�
    void HideUseBlock();

    /// ����9����QWidget
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

