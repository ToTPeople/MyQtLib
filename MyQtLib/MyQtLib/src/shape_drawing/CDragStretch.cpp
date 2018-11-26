#include "CDragStretch.h"
#include <QWidget>
#include <QMouseEvent>


class CDragStretchPrivate
{
    friend CDragStretch;

public:
    typedef enum
    {
        RESIZE_TYPE_NONE = 0x00,        // ��
        RESIZE_TYPE_H,                  // ˮƽ����
        RESIZE_TYPE_V,                  // ��ֱ����
        RESIZE_TYPE_VH,                 // ˮƽ����ֱ ͬʱ����
        RESIZE_TYPE_MAX
    } ResizeWidgetType;

public:
    CDragStretchPrivate(QWidget* pWgt);

public:
    // ��¼�߿�����״̬
    void UpdateDragStretchStatus(QMouseEvent* event);
    // ���ñ߿����������״
    void SetCursorStyle();

public:
    QWidget*            m_pShowWidget;          // ��ʾ�ؼ�
    QWidget*            m_pRightWidget;         // �Ҳ�ؼ�
    QWidget*            m_pBottomWidget;        // �ײ�ؼ�
    QWidget*            m_pBottomRightWidget;   // ���½ǿؼ�

public:
    ResizeWidgetType    eResizeType;            // ��������
    bool                bMoveWnd;               // �Ƿ��ƶ�QWidget
    QPoint              offPoint;               // QWidgetƫ����
    QSize               rightBottomSize;        // ���������ʱ���ұ� �� �ײ� �� ���½� ���
    float               fRatio;                 // �ȱ������죬����ֵ
};

CDragStretchPrivate::CDragStretchPrivate(QWidget* pWgt)
    : m_pShowWidget(pWgt)
    , m_pRightWidget(NULL)
    , m_pBottomWidget(NULL)
    , m_pBottomRightWidget(NULL)
    , eResizeType()
    , bMoveWnd(false)
    , offPoint(QPoint(0, 0))
    , fRatio(1.0)
{}

void CDragStretchPrivate::UpdateDragStretchStatus(QMouseEvent* event)
{
    if (NULL == m_pShowWidget || NULL == event)
    {
        return;
    }

    QPoint pos = event->pos();
    if (NULL != m_pBottomRightWidget && m_pBottomRightWidget->underMouse())
    {
        m_pShowWidget->setCursor(Qt::SizeFDiagCursor);
        eResizeType = RESIZE_TYPE_VH;
        rightBottomSize.setWidth(m_pShowWidget->width() - pos.x());
        rightBottomSize.setHeight(m_pShowWidget->height() - pos.y());
    }
    else if (NULL != m_pRightWidget && m_pRightWidget->underMouse())
    {
        m_pShowWidget->setCursor(Qt::SizeHorCursor);
        eResizeType = RESIZE_TYPE_H;
        rightBottomSize.setWidth(m_pShowWidget->width() - pos.x());
    }
    else if (NULL != m_pBottomWidget && m_pBottomWidget->underMouse())
    {
        m_pShowWidget->setCursor(Qt::SizeVerCursor);
        eResizeType = RESIZE_TYPE_V;
        rightBottomSize.setHeight(m_pShowWidget->height() - pos.y());
    }
    else
    {
        m_pShowWidget->setCursor(Qt::ArrowCursor);
        bMoveWnd = true;
        offPoint = event->globalPos() - m_pShowWidget->pos(); // record mouse press off size
    }
}

void CDragStretchPrivate::SetCursorStyle()
{
    if (NULL == m_pShowWidget)
    {
        return;
    }

    if (NULL != m_pBottomWidget && m_pBottomWidget->underMouse())
    {
        m_pShowWidget->setCursor(Qt::SizeVerCursor);
    }
    else if (NULL != m_pRightWidget && m_pRightWidget->underMouse())
    {
        m_pShowWidget->setCursor(Qt::SizeHorCursor);
    }
    else if (NULL != m_pBottomRightWidget && m_pBottomRightWidget->underMouse())
    {
        m_pShowWidget->setCursor(Qt::SizeFDiagCursor);
    }
    else
    {
        m_pShowWidget->setCursor(Qt::ArrowCursor);
    }
}

CDragStretch::CDragStretch(QWidget* pWgt)
    : m(*new CDragStretchPrivate(pWgt))
{
}


CDragStretch::~CDragStretch()
{
    delete& m;
}

void CDragStretch::SetStretchRatio(float fRatio)
{
    m.fRatio = fRatio;
    if (m.fRatio < 0.001)
    {
        m.fRatio = 1.0;
    }
}

void CDragStretch::UpdateCursorStatus()
{
    m.SetCursorStyle();
}

void CDragStretch::SetRightWidget(QWidget * pWgt)
{
    m.m_pRightWidget = pWgt;
}

void CDragStretch::SetBottomWidget(QWidget * pWgt)
{
    m.m_pBottomWidget = pWgt;
}

void CDragStretch::SetBottomRightWidget(QWidget * pWgt)
{
    m.m_pBottomRightWidget = pWgt;
}

void CDragStretch::ProcessMousePress(QMouseEvent * event)
{
    if (NULL == event || NULL == m.m_pShowWidget || !m.m_pShowWidget->underMouse())
    {
        return ;
    }

    m.UpdateDragStretchStatus(event);
}

void CDragStretch::ProcessMouseMove(QMouseEvent * event)
{
    if (NULL == event || NULL == m.m_pShowWidget)
    {
        return;
    }

    QSize sizeWgt = m.m_pShowWidget->size();
    int width = sizeWgt.width();
    int height = sizeWgt.height();
    if (m.bMoveWnd)
    {
        QPoint point = event->globalPos() - m.offPoint;
        m.m_pShowWidget->move(point);
    }
    else if (CDragStretchPrivate::RESIZE_TYPE_VH == m.eResizeType)
    {
        QPoint curPos = event->pos();
        if (curPos.x() < 1) curPos.setX(2);
        if (curPos.y() < 1) curPos.setY(2);
        // y��̶���x��ȱ����仯
        int nNewHeight = curPos.y() + m.rightBottomSize.height();
        int nNewWidth = nNewHeight * m.fRatio;
        m.m_pShowWidget->resize(nNewWidth, nNewHeight);
    }
    else if (CDragStretchPrivate::RESIZE_TYPE_H == m.eResizeType)
    {
        QPoint curPos = event->pos();
        if (curPos.x() < 1) curPos.setX(2);
        int nNewWidth = curPos.x() + m.rightBottomSize.width();
        m.m_pShowWidget->resize(nNewWidth, height);
        m.fRatio = 1.0 * nNewWidth / height;
    }
    else if (CDragStretchPrivate::RESIZE_TYPE_V == m.eResizeType)
    {
        QPoint curPos = event->pos();
        if (curPos.y() < 1) curPos.setY(2);
        int nNewHeight = curPos.y() + m.rightBottomSize.height();
        m.m_pShowWidget->resize(width, nNewHeight);
        m.fRatio = 1.0 * width / nNewHeight;
    }
}

void CDragStretch::ProcessMouseRelease(QMouseEvent * event)
{
    m.bMoveWnd = false;
    m.eResizeType = CDragStretchPrivate::RESIZE_TYPE_NONE;
    m.SetCursorStyle();
}
