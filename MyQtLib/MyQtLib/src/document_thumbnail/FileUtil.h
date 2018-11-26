#pragma once
#include <QFile>
#include "myqtlib_global.h"


class PdfFile;
class MYQTLIB_EXPORT FileUtil
{
public:
    // text�ı��ļ���ȡ
    static QFile* openTxtFile(const char* pFileName, int nMode = QFile::ReadOnly);
    static bool closeFile(QFile* file);

    // ��pdf�ĵ�
    static PdfFile* OpenPdfFile(const char* pFileName);

private:
    FileUtil();
    ~FileUtil();
};

