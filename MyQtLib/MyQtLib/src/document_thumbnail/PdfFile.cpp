#include "PdfFile.h"
#include "PDFReaderII.h"


class PdfFilePrivate
{
    friend PdfFile;

    QString       fileName;

    PdfFilePrivate(const QString& strFileName)
        : fileName(strFileName)
    {}
};

PdfFile::PdfFile(const QString& strFileName)
    : m(*new PdfFilePrivate(strFileName))
{
}


PdfFile::~PdfFile()
{
    if (!m.fileName.isEmpty())
    {
        PDFReader_Closepdf(m.fileName.toUtf8().data());
    }
    delete &m;
}

char * PdfFile::GetPage(int page, int & width, int & height, ptrdiff_t & format)
{
    if (m.fileName.isEmpty())
    {
        return nullptr;
    }

    return PDFReader_GetPage(m.fileName.toUtf8().data(), page, width, height, format);
}

int PdfFile::GetPageCount()
{
    if (m.fileName.isEmpty())
    {
        return 0;
    }

    return PDFReader_GetPageCount(m.fileName.toUtf8().data());
}

char * PdfFile::GetNextPage(int & page, int & width, int & height, ptrdiff_t & format)
{
    if (m.fileName.isEmpty())
    {
        return nullptr;
    }

    return PDFReader_GetNextPage(m.fileName.toUtf8().data(), page, width, height, format);
}

char * PdfFile::GetLastPage(int & page, int & width, int & height, ptrdiff_t & format)
{
    if (m.fileName.isEmpty())
    {
        return nullptr;
    }
    return PDFReader_GetLastPage(m.fileName.toUtf8().data(), page, width, height, format);
}

void PdfFile::SetCurrentPage(int page)
{
    if (m.fileName.isEmpty())
    {
        return;
    }

    PDFReader_SetCurrentPage(m.fileName.toUtf8().data(), page);
}
