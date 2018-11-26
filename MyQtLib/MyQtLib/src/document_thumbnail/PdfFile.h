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
    //��ȡָ��ҳ����
    char* GetPage(int page, int& width, int& height, ptrdiff_t& format);
    //��ȡ��ҳ��
    int  GetPageCount();
    //��ȡ��һҳ����Ⱦ��ҳ
    char* GetNextPage(int &page, int& width, int& height, ptrdiff_t& format);
    //��ȡ��һҳ����Ⱦ��ҳ
    char* GetLastPage(int &page, int& width, int& height, ptrdiff_t& format);
    //���õ�ǰҳ
    void  SetCurrentPage(int page);

private:
    PdfFilePrivate&         m;
};

