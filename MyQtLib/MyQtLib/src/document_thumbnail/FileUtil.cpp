#include "FileUtil.h"
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QTextCodec>
#include "PdfFile.h"
#include "PDFReaderII.h"


// 处理包含中文名称文件
static QString getFileName(const char* pFileName)
{
    if (NULL == pFileName || 0 == strlen(pFileName))
    {
        return QString("");
    }

    QTextCodec* pCodec = QTextCodec::codecForName("GBK");
    return (NULL == pCodec) ? QString("") : (pCodec->toUnicode(pFileName));
}

QFile * FileUtil::openTxtFile(const char* pFileName, int nMode /*= QFile::ReadOnly*/)
{
    QString strFile = getFileName(pFileName);
    if (strFile.isNull() || strFile.isEmpty())
    {
        return nullptr;
    }

    QFile* pFile = new QFile(strFile);
    if (nullptr != pFile)
    {
        if (!pFile->open((QFile::OpenMode)nMode))
        {
            delete pFile;
            pFile = nullptr;
        }
    }

    return pFile;
}

bool FileUtil::closeFile(QFile * file)
{
    if (nullptr == file)
    {
        return false;
    }

    file->close();
    delete file;
    file = nullptr;
    return true;
}

PdfFile * FileUtil::OpenPdfFile(const char* pFileName)
{
    QString strFile = getFileName(pFileName);
    if (strFile.isNull() || strFile.isEmpty())
    {
        return nullptr;
    }

    if (!PDFReader_Loadpdf(strFile.toUtf8().data()))
    {
        return nullptr;
    }

    return (new PdfFile(strFile));
}

FileUtil::FileUtil()
{
}


FileUtil::~FileUtil()
{
}

