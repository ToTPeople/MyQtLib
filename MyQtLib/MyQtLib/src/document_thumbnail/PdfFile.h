#pragma once
#include <cstddef>
#include <QString>

class PdfFilePrivate;
class PdfFile
{
public:
    PdfFile(const QString& strFileName);
    ~PdfFile();

public:
    //获取指定页数据
    char* GetPage(int page, int& width, int& height, ptrdiff_t& format);
    //获取总页数
    int  GetPageCount();
    //获取下一页该渲染的页
    char* GetNextPage(int &page, int& width, int& height, ptrdiff_t& format);
    //获取上一页该渲染的页
    char* GetLastPage(int &page, int& width, int& height, ptrdiff_t& format);
    //设置当前页
    void  SetCurrentPage(int page);

private:
    PdfFilePrivate&         m;
};

