#pragma once
#include <QImage>
#include "myqtlib_global.h"


class MYQTLIB_EXPORT CThumbnailUtil
{
public:
    // ��ȡ�����ı�����ͼ��Ĭ�����쵽ָ����С
    static QImage getTextThumbnail(const char* pFileName, int nTargetWidth = -1, int nTargetHeight = -1, int nScaleMode = 0);

    // ��ȡͼƬ����ͼ
    static QImage getPictureThumbnail(const char* pFileName, int nTargetWidth = -1, int nTargetHeight = -1, int nScaleMode = 0);

    // ��ȡPDF��ҳ����ͼ
    static QImage getPdfThumbnail(const char* pFile, int nTargetWidth = -1, int nTargetHeight = -1, int nScaleMode = 0);
    
private:
    CThumbnailUtil();
    ~CThumbnailUtil();
};

