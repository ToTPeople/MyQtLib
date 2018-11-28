#include "CTextWidget.h"
#include <QResizeEvent>
#include <QTextEdit>
#include <QScrollBar>
#include <QPalette>
#include <QFile>
#include <QDebug>
#include "ui_Widget.h"
#include "CDragStretch.h"


namespace
{
    const char* const kszTextEditNormalEdge = "QTextEdit#drawingTextEdit { background:transparent; border: 2px dashed black }";
    const char* const kszTextEditNoneEdge = "QTextEdit#drawingTextEdit { background:transparent; border: 2px dashed rgba(0,0,0,0) }";
}

class CTextWidgetPrivate
{
    friend CTextWidget;

    typedef enum
    {
        TEXT_STATE_EDITING,           // 编辑状态
        TEXT_STATE_SHOW,              // 显示状态
        TEXT_STATE_MOVE_STRETCH,      // 移动、拉伸状态
    } TextState;

public:
    CTextWidgetPrivate(QWidget* pWgt);

public:
    /// 初始化
    void Init(QWidget* pWgt);
    /// 更新TextEdit状态：边框、可编辑态
    void ChangedTextState();

public:
    CDragStretch*   m_pDragStretch;     // 拖动、拉伸封装类
    QTextEdit*      m_pTextEdt;
    Ui::widget      ui;
    bool            hasEdit;            // 是否编辑过
    TextState       eTextState;         // 当前文本状态
private:
    int             nFontSize;          // 字体大小
    QString         textFamily;         // 字体类型
    bool            bBold;
    bool            bItalic;
    bool            bUnderLine;
    QColor          colorText;
    int             nAlign;
    bool            bFixW;              // 宽度是否固定
};

CTextWidgetPrivate::CTextWidgetPrivate(QWidget* pWgt)
    : m_pTextEdt(NULL)
    , m_pDragStretch(NULL)
    , hasEdit(false)
    , eTextState(TEXT_STATE_EDITING)
    , nFontSize(20)
    , textFamily("")
    , bBold(false)
    , bItalic(false)
    , bUnderLine(false)
    , colorText(Qt::black)
    , nAlign(Qt::AlignLeft)
    , bFixW(false)
{
    ui.setupUi(pWgt);
    {
        ui.wgtBottom->hide();
        ui.wgtBottomLeft->hide();
        ui.wgtBottomRight->hide();
        ui.wgtLeft->hide();
        ui.wgtRight->hide();
        ui.wgtTop->hide();
        ui.wgtTopLeft->hide();
        ui.wgtTopRight->hide();
    }
    Init(pWgt);
}

void CTextWidgetPrivate::Init(QWidget* pWgt)
{
    if (NULL == pWgt)
    {
        return;
    }

    m_pDragStretch = new CDragStretch(pWgt);
    if (NULL != m_pDragStretch)
    {
        m_pDragStretch->SetRightWidget(ui.wgtRight);
        ui.wgtRight->installEventFilter(pWgt);
        m_pDragStretch->SetUseBlock(EDGE_CORNER_RIGHT);
    }

    m_pTextEdt = new QTextEdit(pWgt);
    if (NULL == m_pTextEdt)
    {
        return;
    }

    m_pTextEdt->setObjectName(QStringLiteral("drawingTextEdit"));
    ui.hCenterDrawingLayout->addWidget(m_pTextEdt);

    // 文本颜色
    QPalette pl = m_pTextEdt->palette();
    pl.setColor(QPalette::Text, colorText);
    m_pTextEdt->setPalette(pl);
    // 粗体、下划线、字体大小、斜体
    QFont font;
    font.setItalic(bItalic);
    font.setBold(bBold);
    font.setUnderline(bUnderLine);
    font.setPointSize(nFontSize);
    m_pTextEdt->setFont(font);

    // 滚动条隐藏
    m_pTextEdt->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pTextEdt->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // 只处理文本（不处理富文本）
    m_pTextEdt->setAcceptRichText(false);

    m_pTextEdt->setText(QString::fromLocal8Bit("在此输入"));
    m_pTextEdt->selectAll();

    m_pTextEdt->setFocus();

    // 背景透明，去边框
    m_pTextEdt->setStyleSheet(kszTextEditNormalEdge);

    QObject::connect(m_pTextEdt->document(), SIGNAL(contentsChanged()), pWgt, SLOT(slotTextAreaChanged()));
    m_pTextEdt->setLineWrapMode(QTextEdit::NoWrap);     // 创建时宽度、高度都可调整

    QObject::connect(m_pTextEdt, SIGNAL(selectionChanged()), pWgt, SLOT(slotTextSelectChanged()));
}

void CTextWidgetPrivate::ChangedTextState()
{
    if (NULL == m_pTextEdt)
    {
        return;
    }
    // 编辑
    if (TEXT_STATE_EDITING == eTextState)
    {
        m_pTextEdt->setEnabled(true);
        m_pTextEdt->setFocus();
    }
    else
    {
        m_pTextEdt->setEnabled(false);
    }

    // 边框
    if (TEXT_STATE_SHOW == eTextState)
    {
        m_pTextEdt->setStyleSheet(kszTextEditNoneEdge);
    }
    else
    {
        m_pTextEdt->setStyleSheet(kszTextEditNormalEdge);
    }
}

CTextWidget::CTextWidget(QWidget* parent /*= NULL*/)
    : QWidget(parent)
    , m(*new CTextWidgetPrivate(this))
{
    QFile file(":/drawing/src/drawing/Resources/qss/default.css");
    if (file.open(QFile::ReadOnly))
    {
        setStyleSheet(file.readAll());
        file.close();
    }
}


CTextWidget::~CTextWidget()
{
    delete &m;
}

bool CTextWidget::hadEdit()
{
    return m.hasEdit;
}

void CTextWidget::SetFontSize(int nFontSize)
{
    if (nFontSize == m.nFontSize)
    {
        return;
    }

    if (nFontSize < 1)
    {
        nFontSize = 1;
    }
    m.nFontSize = nFontSize;
    if (NULL != m.m_pTextEdt)
    {
        m.m_pTextEdt->setFontPointSize(nFontSize);
    }
}

void CTextWidget::SetFamily(const QString & strFamily)
{
    if (strFamily.isNull() || strFamily.isEmpty() || strFamily == m.textFamily)
    {
        return;
    }

    m.textFamily = strFamily;
    if (NULL != m.m_pTextEdt)
    {
        m.m_pTextEdt->setFontFamily(strFamily);
    }
}

void CTextWidget::SetBold(bool bBold)
{
    if (bBold == m.bBold)
    {
        return;
    }
    m.bBold = bBold;
    if (NULL != m.m_pTextEdt)
    {
        QFont font = m.m_pTextEdt->font();
        font.setBold(bBold);
        m.m_pTextEdt->setFont(font);
    }
}

void CTextWidget::SetItalic(bool bItalic)
{
    if (bItalic == m.bItalic)
    {
        return;
    }
    m.bItalic = bItalic;
    if (NULL != m.m_pTextEdt)
    {
        m.m_pTextEdt->setFontItalic(bItalic);
    }
}

void CTextWidget::SetUnderLine(bool bUnderLine)
{
    if (bUnderLine == m.bUnderLine)
    {
        return;
    }
    m.bUnderLine = bUnderLine;
    if (NULL != m.m_pTextEdt)
    {
        m.m_pTextEdt->setFontUnderline(bUnderLine);
    }
}

void CTextWidget::SetTextColor(const QColor & colorText)
{
    if (colorText == m.colorText)
    {
        return;
    }
    m.colorText = colorText;
    if (NULL != m.m_pTextEdt)
    {
        QPalette pal = m.m_pTextEdt->palette();
        pal.setColor(QPalette::Text, colorText);
        m.m_pTextEdt->setPalette(pal);
    }
}

void CTextWidget::SetAlignment(int nAlign)
{
    if (nAlign == m.nAlign)
    {
        return;
    }
    m.nAlign = nAlign;
    if (NULL != m.m_pTextEdt)
    {
        m.m_pTextEdt->setAlignment((Qt::AlignmentFlag)nAlign);
    }
}

void CTextWidget::mousePressEvent(QMouseEvent * event)
{
    if (CTextWidgetPrivate::TEXT_STATE_EDITING != m.eTextState)
    {
        m.eTextState = CTextWidgetPrivate::TEXT_STATE_MOVE_STRETCH;
        if (NULL != m.m_pDragStretch)
        {
            m.m_pDragStretch->ProcessMousePress(event);
            m.m_pDragStretch->ShowUseBlock();
        }
        m.ChangedTextState();
    }
    QWidget::mousePressEvent(event);
}

void CTextWidget::mouseMoveEvent(QMouseEvent * event)
{
    if (CTextWidgetPrivate::TEXT_STATE_MOVE_STRETCH == m.eTextState)
    {
        if (NULL != m.m_pDragStretch)
        {
            m.m_pDragStretch->ProcessMouseMove(event);
        }
    }
    QWidget::mouseMoveEvent(event);
}

void CTextWidget::mouseReleaseEvent(QMouseEvent * event)
{
    if (CTextWidgetPrivate::TEXT_STATE_MOVE_STRETCH == m.eTextState)
    {
        if (NULL != m.m_pDragStretch)
        {
            m.m_pDragStretch->ProcessMouseRelease(event);
        }
    }
    QWidget::mouseReleaseEvent(event);
}

void CTextWidget::mouseDoubleClickEvent(QMouseEvent * event)
{
    if (CTextWidgetPrivate::TEXT_STATE_EDITING != m.eTextState)
    {
        if (NULL != m.m_pDragStretch)
        {
            m.m_pDragStretch->ProcessMouseRelease(event);
            m.m_pDragStretch->HideUseBlock();
        }
        m.eTextState = CTextWidgetPrivate::TEXT_STATE_EDITING;
        m.ChangedTextState();
    }
    QWidget::mouseDoubleClickEvent(event);
}

bool CTextWidget::eventFilter(QObject * target, QEvent * event)
{
    if (NULL != target && NULL != event && target == parent())
    {
        if (QEvent::MouseButtonPress == event->type() && !underMouse())
        {
            if (CTextWidgetPrivate::TEXT_STATE_SHOW != m.eTextState)
            {
                m.eTextState = CTextWidgetPrivate::TEXT_STATE_SHOW;
                if (NULL != m.m_pDragStretch)
                {
                    m.m_pDragStretch->HideUseBlock();
                }
                m.ChangedTextState();
                m.m_pTextEdt->setLineWrapMode(QTextEdit::WidgetWidth);
                m.bFixW = true;
            }
        }
    }
    else if (m.ui.wgtRight == target)
    {
        if (NULL != m.m_pDragStretch)
        {
            m.m_pDragStretch->UpdateCursorStatus();
        }
    }

    return QWidget::eventFilter(target, event);
}

void CTextWidget::resizeEvent(QResizeEvent * event)
{
    if (NULL != m.m_pTextEdt)
    {
        QTextDocument *document = m.m_pTextEdt->document();
        if (document)
        {
            QTextEdit *editor = m.m_pTextEdt;
            if (event->size().height() != document->size().height() + 30)
            {
                int nExtend = 10;
                int newheight = document->size().height() + nExtend;

                editor->resize(editor->width(), newheight);
                resize(event->size().width(), newheight + 20);
            }
        }
    }

    QWidget::resizeEvent(event);
}

void CTextWidget::slotTextAreaChanged()
{
    QTextDocument *document = qobject_cast<QTextDocument*>(sender());
    if (!m.bFixW)
    {
        document->adjustSize();
    }
    if (document)
    {
        QTextEdit *editor = qobject_cast<QTextEdit*>(document->parent()->parent());
        if (editor)
        {
            int nExtend = 10;
            int newwidth = m.bFixW ? editor->width() : document->size().width() + nExtend;
            int newheight = document->size().height() + nExtend;

            editor->resize(newwidth, newheight);
            resize(m.bFixW ? width() : newwidth + 20, newheight + 20);
        }
    }
}

void CTextWidget::slotTextSelectChanged()
{
    m.hasEdit = true;
    QObject::disconnect(m.m_pTextEdt, SIGNAL(selectionChanged()), this, SLOT(slotTextSelectChanged()));
}
