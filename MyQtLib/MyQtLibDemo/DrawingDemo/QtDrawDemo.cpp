#include "QtDrawDemo.h"
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QScrollBar>
#include <QGraphicsDropShadowEffect>
#include <QDebug>
#include "CCenterWidget.h"
#include "CDrawingWidget.h"
#include "CShape.h"
#include "CommonDefine.h"

namespace
{
    const char* const kszText = "asdlfkjalkfjalkfjlakjsflkajdflajsdfklafalkj \
        0130142348-134-13413187981791793085r719203579123ajflkjasdl;fja;ldfjafd \
KFLAJDFL;JKAOWIQJEFOIQJWEFOIJQWEFJQOIEFJIOQJEWFILQWJEFILQJFELJFE;WJFQEFJKQ;FJQ;FJEQ \
fojqwijfoqwifeojqweifjqiowej234134123091i3ir190irfjefoqj weojfasdlfkjalkfjalkfjlakjsflkajdflajsdfklafalkj \
        0130142348-134-13413187981791793085r719203579123ajflkjasdl;fja;ldfjafd \
KFLAJDFL;JKAOWIQJEFOIQJWEFOIJQWEFJQOIEFJIOQJEWFILQWJEFILQJFELJFE;WJFQEFJKQ;FJQ;FJEQ \
fojqwijfoqwifeojqweifjqiowej234134123091i3ir190irfjefoqjweojfasdlfkjalkfjalkfjlakjsflkajdflajsdfklafalkj \
        0130142348-134-13413187981791793085r719203579123ajflkjasdl;fja;ldfjafd \
KFLAJDFL;JKAOWIQJEFOIQJWEFOIJQWEFJQOIEFJIOQJEWFILQWJEFILQJFELJFE;WJFQEFJKQ;FJQ;FJEQ \
fojqwijfoqwifeojqweifjqiowej234134123091i3ir190irfjefoqjweojf";
}

static QColor GetColorByString(const QString& str, bool bBrush)
{
    if (str.isNull() || str.isEmpty())
    {
        return bBrush ? Qt::NoBrush : Qt::black;
    }

    if ("red" == str.toLower())
    {
        return Qt::red;
    }
    else if ("blue" == str.toLower())
    {
        return Qt::blue;
    }
    else if ("green" == str.toLower())
    {
        return Qt::green;
    }
    else if ("gray" == str.toLower())
    {
        return Qt::gray;
    }
    else if ("white" == str.toLower())
    {
        return Qt::white;
    }
    else if ("yellow" == str.toLower())
    {
        return Qt::yellow;
    }
    else
    {
        return Qt::black;
    }
}

QtDrawDemo::QtDrawDemo(QWidget *parent)
    : QWidget(parent)
    , m_pTestWgt(NULL)
    , m_pRect(NULL)
    , m_pPen(NULL)
{
    ui.setupUi(this);

    //QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    ////shadow_effect->setOffset(5);
    //shadow_effect->setOffset(-5, 5);
    //shadow_effect->setColor(Qt::red);
    //shadow_effect->setBlurRadius(8);
    ////ui->frame_main->setGraphicsEffect(shadow_effect);
    //setGraphicsEffect(shadow_effect);

    resize(1024, 500);

    m_pTestWgt = new CCenterWidget(ui.wgtCenter);
    if (NULL != m_pTestWgt)
    {
        ui.wgtCenter->installEventFilter(m_pTestWgt);

        // init attribute
        m_pTestWgt->SetFillBrush(GetColorByString(ui.fillColor->text(), true));
        m_pTestWgt->SetLineColor(GetColorByString(ui.lineColor->text(), false));
        int width = ui.lineWidth->text().toInt();
        m_pTestWgt->SetLineWidth(width);

        m_pTestWgt->SetShadow(ui.shadow->isChecked());
        m_pTestWgt->SetSawtooth(!ui.sawtooth->isChecked());
        m_pTestWgt->SetRoundCorner(ui.round->isChecked());

        ui.textEdit->hide();
        ui.plainTextEdit->hide();
    }
    else
    {
        ui.wgtCenter->setStyleSheet("QWidget#wgtCenter { background-color : #00ff00; }");
        ui.textEdit->setText(kszText);
        ui.plainTextEdit->setPlainText(kszText);

        // 背景透明，文本颜色
        QPalette pl = ui.textEdit->palette();
        pl.setBrush(QPalette::Base, QBrush(QColor(255, 0, 0, 0)));
        pl.setColor(QPalette::Text, Qt::black);
        QPen pen;
        QFont font;
        font.setItalic(true);
        font.setBold(true);
        font.setUnderline(true);
        font.setPixelSize(22);
        //QPainter painter(ui.textEdit);
        //painter.setFont(font);
        ui.textEdit->setFont(font);
        ui.textEdit->setPalette(pl);

        // 滚动条隐藏
        ui.textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        //ui.textEdit->verticalScrollBar()->setFixedWidth(1);
        //ui.textEdit->verticalScrollBar()->hide();

        ui.textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        //ui.textEdit->horizontalScrollBar()->setFixedHeight(1);
        //ui.textEdit->horizontalScrollBar()->hide();

        ui.textEdit->setAcceptRichText(false);

        ui.textEdit->setText(QString::fromLocal8Bit("在此输入"));
        ui.textEdit->selectAll();

        ui.textEdit->setFocus();

        // 去边框
        ui.textEdit->setStyleSheet("QTextEdit#textEdit { background:transparent; border: 2px dashed black }");
        //ui.textEdit->setStyleSheet("QTextEdit#textEdit { background:transparent; border: dashed black }");
        //ui.textEdit->setStyleSheet("QTextEdit#textEdit { background:transparent; border: none; }");

        //ui.textEdit->setDisabled(true);

        //ui.textEdit->resize(24, 42);
        connect(ui.textEdit->document(), SIGNAL(contentsChanged()), this, SLOT(slotTextAreaChanged()));
        ui.textEdit->setLineWrapMode(QTextEdit::NoWrap);

        connect(ui.textEdit, SIGNAL(selectionChanged()), this, SLOT(slotTextSelectChanged()));

    }

    {
        //m_pRect = new CDrawingWidget(ui.wgtCenter);
        //m_pRect = new CDrawingWidget(m_pTestWgt);
        if (NULL != m_pRect)
        {
            ui.wgtCenter->installEventFilter(m_pRect);
            m_pTestWgt->installEventFilter(m_pRect);
            //m_pRect->resize(ui.wgtCenter->size());
            m_pRect->SetDrawingType(DRAWING_TYPE_RECT);
        }

        //m_pPen = new CDrawingWidget(ui.wgtCenter);
        if (NULL != m_pPen)
        {
            ui.wgtCenter->installEventFilter(m_pPen);
            //m_pPen->resize(ui.wgtCenter->size());
            m_pPen->SetDrawingType(DRAWING_TYPE_PEN);
            //m_pPen->hide();
        }
    }

    ui.labelStatus->setText("Drawing Rect!!!");

    connect(ui.btnRect, SIGNAL(clicked()), this, SLOT(slotOnRectClick()));
    connect(ui.btnSquare, SIGNAL(clicked()), this, SLOT(slotOnSquareClick()));
    connect(ui.btnEllipse, SIGNAL(clicked()), this, SLOT(slotOnEllipseClick()));
    connect(ui.btnCircle, SIGNAL(clicked()), this, SLOT(slotOnCircleClick()));
    connect(ui.btnArrow, SIGNAL(clicked()), this, SLOT(slotOnArrowClick()));
    connect(ui.btnPen, SIGNAL(clicked()), this, SLOT(slotOnFreeClick()));
    connect(ui.btnUse, SIGNAL(clicked()), this, SLOT(slotOnUseClick()));
    connect(ui.btnMouse, SIGNAL(clicked()), this, SLOT(slotOnMouseClick()));
    connect(ui.btnText, SIGNAL(clicked()), this, SLOT(slotOnTextClick()));
}

void QtDrawDemo::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    QPen pen(Qt::red, 5);
    CShape::DrawArrow(painter, pen, QPointF(0, 0), QPointF(500, 700));
    QWidget::paintEvent(event);
}

void QtDrawDemo::mousePressEvent(QMouseEvent * event)
{
    QWidget::mousePressEvent(event);
}

void QtDrawDemo::mouseMoveEvent(QMouseEvent * event)
{
    QWidget::mouseMoveEvent(event);
}

void QtDrawDemo::mouseReleaseEvent(QMouseEvent * event)
{
    QWidget::mouseReleaseEvent(event);
}

void QtDrawDemo::slotOnRectClick()
{
    ui.labelStatus->setText("Drawing Rect!!!");
    if (NULL != m_pTestWgt)
    {
        m_pTestWgt->SetDrawType(DRAWING_TYPE_RECT);
    }
    if (NULL != m_pRect)
    {
        m_pRect->raise();
    }
}

void QtDrawDemo::slotOnSquareClick()
{
    ui.labelStatus->setText("Drawing Square!!!");
    if (NULL != m_pTestWgt)
    {
        m_pTestWgt->SetDrawType(DRAWING_TYPE_SQUARE);
    }
}

void QtDrawDemo::slotOnCircleClick()
{
    ui.labelStatus->setText("Drawing Circle!!!");
    if (NULL != m_pTestWgt)
    {
        m_pTestWgt->SetDrawType(DRAWING_TYPE_CIRCLE);
    }
}

void QtDrawDemo::slotOnEllipseClick()
{
    ui.labelStatus->setText("Drawing Ellipse!!!");
    if (NULL != m_pTestWgt)
    {
        m_pTestWgt->SetDrawType(DRAWING_TYPE_ELLIPE);
    }
}

void QtDrawDemo::slotOnArrowClick()
{
    ui.labelStatus->setText("Drawing Arrow!!!");
    if (NULL != m_pTestWgt)
    {
        m_pTestWgt->SetDrawType(DRAWING_TYPE_ARROW);
    }
}

void QtDrawDemo::slotOnFreeClick()
{
    ui.labelStatus->setText("Pen Drawing!!!");
    if (NULL != m_pTestWgt)
    {
        m_pTestWgt->SetDrawType(DRAWING_TYPE_PEN);
    }
    if (NULL != m_pPen)
    {
        m_pPen->raise();
    }
}

void QtDrawDemo::slotOnUseClick()
{
    if (NULL != m_pTestWgt)
    {
        m_pTestWgt->SetFillBrush(GetColorByString(ui.fillColor->text(), true));
        m_pTestWgt->SetLineColor(GetColorByString(ui.lineColor->text(), false));
        int width = ui.lineWidth->text().toInt();
        m_pTestWgt->SetLineWidth(width);

        m_pTestWgt->SetShadow(ui.shadow->isChecked());
        m_pTestWgt->SetSawtooth(ui.sawtooth->isChecked());
        m_pTestWgt->SetRoundCorner(ui.round->isChecked());
    }
}

void QtDrawDemo::slotOnMouseClick()
{
    ui.labelStatus->setText("Mouse Op!!!");
    if (NULL != m_pTestWgt)
    {
        m_pTestWgt->SetDrawType(DRAWING_TYPE_MAX);
    }
}

void QtDrawDemo::slotOnTextClick()
{
    ui.labelStatus->setText("Draw Text!!!");
    if (NULL != m_pTestWgt)
    {
        m_pTestWgt->SetDrawType(DRAWING_TYPE_TEXT);
    }
}

void QtDrawDemo::slotTextAreaChanged()
{
    QTextDocument *document = qobject_cast<QTextDocument*>(sender());
    document->adjustSize();
    if (document)
    {
        QTextEdit *editor = qobject_cast<QTextEdit*>(document->parent()->parent());
        if (editor)
        {
            int newwidth = document->size().width() +10;//10
            int newheight = document->size().height() + 10;// +20;//20

            qDebug() << "=-==-==== pre doc size: " << document->size()
                << ", edit: " << editor->size()
                << ", new W: " << newwidth << ", H: " << newheight;
            if (newwidth != editor->width())
            {
                editor->setFixedWidth(newwidth);
            }
            if (newheight != editor->height())
            {
                editor->setFixedHeight(newheight);
            }
        }
    }
}

void QtDrawDemo::slotTextSelectChanged()
{
    qDebug() << "=-==-==== $$$$$$$$$$$$$$$$$$$$$$$$$$$$$K$$$$$$$$$$$$$$$";
    disconnect(ui.textEdit, SIGNAL(selectionChanged()), this, SLOT(slotTextSelectChanged()));
}

