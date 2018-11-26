#pragma once
#include <QFile>
#include "myqtlib_global.h"


class PdfFile;
class MYQTLIB_EXPORT FileUtil
{
public:
    // text文本文件读取
    static QFile* openTxtFile(const char* pFileName, int nMode = QFile::ReadOnly);
    static bool closeFile(QFile* file);

    // 打开pdf文档
    static PdfFile* OpenPdfFile(const char* pFileName);

private:
    FileUtil();
    ~FileUtil();
};

