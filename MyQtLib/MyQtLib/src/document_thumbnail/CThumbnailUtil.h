#pragma once
#include <QImage>
#include "myqtlib_global.h"


class MYQTLIB_EXPORT CThumbnailUtil
{
public:
    // 读取创建文本缩略图，默认拉伸到指定大小
    static QImage getTextThumbnail(const char* pFileName, int nTargetWidth = -1, int nTargetHeight = -1, int nScaleMode = 0);

    // 获取图片缩略图
    static QImage getPictureThumbnail(const char* pFileName, int nTargetWidth = -1, int nTargetHeight = -1, int nScaleMode = 0);

    // 获取PDF首页缩略图
    static QImage getPdfThumbnail(const char* pFile, int nTargetWidth = -1, int nTargetHeight = -1, int nScaleMode = 0);
    
private:
    CThumbnailUtil();
    ~CThumbnailUtil();
};

