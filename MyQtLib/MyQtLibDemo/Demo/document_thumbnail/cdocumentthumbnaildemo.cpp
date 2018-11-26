#include "cdocumentthumbnaildemo.h"
#include <QLabel>
#include <QDebug>
#include <QFile>
#include <QTextCodec>
#include <QUrl>
#include "CThumbnailUtil.h"
#include "FileUtil.h"
#include "CDownloadNetData.h"

namespace
{
    // 以下路径适用于Windows平台，VS2017 IDE（其他平台、其他IDE需要调整路径）
#define TEST_WORD
    // 路径前缀
    const char* const kszPrePath = "";
    // text
    const char* const kszTxt = "./Resources/document/33.txt";
    const char* const kszTxtZh = "./Resources/document/我本.txt";
    // image
    const char* const kszImageJpgZh = "./Resources/images/水.jpg";
    // pdf
    const char* const kszPdfZh = "./Resources/document/01-事业部介绍-2018.pdf";
    const char* const kszPdfEn = "./Resources/document/test.pdf";
}

CDocumentThumbnailDemo::CDocumentThumbnailDemo(QWidget *parent)
    : QMainWindow(parent)
    , m_pLabel(NULL)
    , m_pDownLoadNetData(NULL)
{
    ui.setupUi(this);

    m_pLabel = ui.label;

    connect(ui.btnText, SIGNAL(clicked()), this, SLOT(slotOnTextBtnClick()));
    connect(ui.btnImg, SIGNAL(clicked()), this, SLOT(slotOnImageBtnClick()));
    connect(ui.btnPDF, SIGNAL(clicked()), this, SLOT(slotOnPDFBtnClick()));
    connect(ui.btnNet, SIGNAL(clicked()), this, SLOT(slotOnNetImageBtnClick()));

    m_pDownLoadNetData = new CDownloadNetData();
    if (NULL != m_pDownLoadNetData)
    {
        connect(m_pDownLoadNetData, SIGNAL(sigDownloadFinish()), this, SLOT(slotDownloadFinish()));
    }
}

CDocumentThumbnailDemo::~CDocumentThumbnailDemo()
{
    if (NULL != m_pDownLoadNetData)
    {
        delete m_pDownLoadNetData;
        m_pDownLoadNetData = NULL;
    }
}

static void openFileByExt(const char* pFilePath)
{
    if (NULL == pFilePath)
    {
        return;
    }
    QString filePath = QString::fromLocal8Bit(pFilePath);
    if (filePath.isNull() || filePath.isEmpty())
    {
        return;
    }

    if (filePath.endsWith(".pdf"))
    {
        FileUtil::OpenPdfFile(pFilePath);
    }
    else
    {
        FileUtil::openTxtFile(pFilePath);
    }
}

void CDocumentThumbnailDemo::testThumbnail()
{
    if (NULL == m_pLabel)
    {
        return;
    }
    QImage img;

    // text file
    {
        img = CThumbnailUtil::getTextThumbnail(kszTxtZh, 300, 200);
        if (!img.isNull()) {
            m_pLabel->setPixmap(QPixmap::fromImage(img));
        }
    }
    // image
    {
        //img = CThumbnailUtil::getPictureThumbnail("./Resources/images/bell.png", 100, 70);          // png
        //img = CThumbnailUtil::getPictureThumbnail("./Resources/images/phone.jpg", 100, 70);         // jpg
        //img = CThumbnailUtil::getPictureThumbnail(kszImageJpgZh, 100, 70);         // big jpg
        //img = CThumbnailUtil::getPictureThumbnail("./Resources/images/water.jpg", 100, 70);         // big jpg
        //img = CThumbnailUtil::getPictureThumbnail("./Resources/images/loading_rect.gif", 100, 70);      // gif
        /*if (!img.isNull()) {
            m_pLabel->setPixmap(QPixmap::fromImage(img));
        }*/
    }
    // network image
    {
        //QUrl urlImg("http://10.8.116.155/bg_256.ico");
        //CDownloadNetData *pD = new CDownloadNetData();
        //if (NULL != pD) {
        //    pD->downloadData(urlImg);
        //    connect(pD, SIGNAL(sigDownloadFinish()), this, SLOT(slotFinish()));
        //    // need to delete pD
        //}
    }
    // pdf
    {
        //QImage img = CThumbnailUtil::getPdfThumbnail(kszPdfEn, 300, 200);
        /*QImage img = CThumbnailUtil::getPdfThumbnail(kszPdfZh, 300, 200);
        m_pLabel->setPixmap(QPixmap::fromImage(img));*/
    }
}

void CDocumentThumbnailDemo::slotOnTextBtnClick()
{
    if (NULL == m_pLabel)
    {
        return;
    }
    QImage img;

    // text file
    {
        img = CThumbnailUtil::getTextThumbnail(kszTxtZh, 300, 200);
        if (!img.isNull()) {
            m_pLabel->setPixmap(QPixmap::fromImage(img));
        }
    }
}

void CDocumentThumbnailDemo::slotOnImageBtnClick()
{
    if (NULL == m_pLabel)
    {
        return;
    }
    QImage img;

    // image
    //img = CThumbnailUtil::getPictureThumbnail("./Resources/images/bell.png", 100, 70);          // png
    //img = CThumbnailUtil::getPictureThumbnail("./Resources/images/phone.jpg", 100, 70);         // jpg
    img = CThumbnailUtil::getPictureThumbnail(kszImageJpgZh, 100, 70);         // big jpg
    //img = CThumbnailUtil::getPictureThumbnail("./Resources/images/water.jpg", 100, 70);         // big jpg
    //img = CThumbnailUtil::getPictureThumbnail("./Resources/images/loading_rect.gif", 100, 70);      // gif
    if (!img.isNull())
    {
        m_pLabel->setPixmap(QPixmap::fromImage(img));
    }
}

void CDocumentThumbnailDemo::slotOnPDFBtnClick()
{
    if (NULL == m_pLabel)
    {
        return;
    }

    // PFD file
    QImage img = CThumbnailUtil::getPdfThumbnail(kszPdfZh, 300, 200);
    m_pLabel->setPixmap(QPixmap::fromImage(img));
}

void CDocumentThumbnailDemo::slotOnNetImageBtnClick()
{
    if (NULL == m_pLabel || NULL == m_pDownLoadNetData)
    {
        return;
    }
    if (QFile::exists("./Resources/download/bg_256.ico"))
    {
        QImage img = CThumbnailUtil::getPictureThumbnail("./Resources/download/bg_256.ico", 200, 100);
        if (img.isNull())
        {
            return;
        }

        m_pLabel->setPixmap(QPixmap::fromImage(img));
        return;
    }

    QUrl urlImg("http://10.8.116.155/bg_256.ico");
    m_pDownLoadNetData->downloadData(urlImg);
}

void CDocumentThumbnailDemo::slotDownloadFinish()
{
    if (NULL == m_pLabel)
    {
        return;
    }

    QImage img = CThumbnailUtil::getPictureThumbnail("./Resources/download/bg_256.ico", 200, 100);
    if (img.isNull())
    {
        return;
    }

    m_pLabel->setPixmap(QPixmap::fromImage(img));
}
