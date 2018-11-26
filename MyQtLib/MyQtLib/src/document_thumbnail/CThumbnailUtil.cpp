#include "CThumbnailUtil.h"
#include <cstddef>
#include <QFile>
#include <QLabel>
#include <QImage>
#include <QMovie>
#include <QDebug>
#include <QTextCodec>
#include "FileUtil.h"
#include "PdfFile.h"

namespace
{
    const int g_nTextReadChars = 1024;      // �ı��ļ���ȡ�ı��ַ�����
}


QImage CThumbnailUtil::getTextThumbnail(const char* pFileName, int nTargetWidth, int nTargetHeight, int nScaleMode)
{
    QImage img;

    // ���ļ�����ȡ����
    QFile* pFile = FileUtil::openTxtFile(pFileName);
    if (NULL == pFile)
    {
        return img;
    }

    // op(ͨ��QLabel��ͼ��ȡ)
    QLabel* pLabel = new QLabel();
    if (NULL == pLabel)
    {
        return img;
    }
    pLabel->setText(pFile->read(g_nTextReadChars));
    pLabel->adjustSize();
    img = pLabel->grab().toImage();
    if (nTargetWidth <= 0 || nTargetWidth <= 0)
    {
        return img;
    }

    // ����mode����
    if (nScaleMode <= 0)
    {
        img = img.scaled(nTargetWidth, nTargetHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        return img;
    }

    // ����scale����

    return img;
}

QImage CThumbnailUtil::getPictureThumbnail(const char* pFileName, int nTargetWidth, int nTargetHeight, int nScaleMode)
{
    QImage img;
    if (NULL == pFileName || 0 == strlen(pFileName))
    {
        return img;
    }

    QString strFileName = QString::fromLocal8Bit(pFileName);
    if (!img.load(strFileName))
    {
        return img;
    }

    if (nTargetHeight <= 0 || nTargetWidth <= 0)
    {
        return img;
    }

    // ����mode scale
    if (nScaleMode <= 0)
    {
        img = img.scaled(nTargetWidth, nTargetHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        return img;
    }

    // ����scale����

    return img;
}

static void releasePdfFile(PdfFile* pPdfFile)
{
    if (NULL != pPdfFile)
    {
        delete pPdfFile;
        pPdfFile = NULL;
    }
}

QImage CThumbnailUtil::getPdfThumbnail(const char* pFile, int nTargetWidth, int nTargetHeight, int nScaleMode)
{
    QImage img;
    if (NULL == pFile)
    {
        return img;
    }
    
    PdfFile* pPdfFile = FileUtil::OpenPdfFile(pFile);
    if (NULL == pPdfFile)
    {
        return img;
    }

    int nWidth, nHeight;
    ptrdiff_t format;
    int nPage = 0;
    char* buffer = pPdfFile->GetPage(nPage, nWidth, nHeight, format);
    if (NULL == buffer)
    {
        releasePdfFile(pPdfFile);
        return img;
    }

    QImage ii = QImage((uchar*)buffer, nWidth, nHeight, format, QImage::Format_RGB888);
    img = ii.copy();

    releasePdfFile(pPdfFile);

    if (nTargetHeight <= 0 || nTargetWidth <= 0)
    {
        return img;
    }

    // ����mode scale
    if (nScaleMode <= 0)
    {
        img = img.scaled(nTargetWidth, nTargetHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        return img;
    }

    // ����scale����

    return img;
}

CThumbnailUtil::CThumbnailUtil()
{
}


CThumbnailUtil::~CThumbnailUtil()
{
}
