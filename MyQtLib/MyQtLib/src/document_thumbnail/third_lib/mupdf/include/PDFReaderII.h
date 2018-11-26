#ifndef _PDF_IUM_READER_H_
#define _PDF_IUM_READER_H_

#include <cstddef>

#ifdef PDF_IUM_READER_API extern "C" _declspec(dllexport)   
#else  
#define PDF_IUM_READER_API extern "C" _declspec(dllexport)  
#endif  

//加载
PDF_IUM_READER_API bool  PDFReader_Loadpdf(const char* filename);
//关闭
 PDF_IUM_READER_API void  PDFReader_Closepdf(const char* filename);
//加载某个page
PDF_IUM_READER_API char* PDFReader_GetPage(const char* filename, int page, int& width, int& height, ptrdiff_t& format);
//获取总页数
PDF_IUM_READER_API  int  PDFReader_GetPageCount(const char* filename);
//获取下一页该渲染的页
PDF_IUM_READER_API  char*  PDFReader_GetNextPage(const char* filename, int &page, int& width, int& height, ptrdiff_t& format);
//获取上一页该渲染的页
PDF_IUM_READER_API  char*  PDFReader_GetLastPage(const char* filename, int &page, int& width, int& height, ptrdiff_t& format);
//设置当前页
PDF_IUM_READER_API void  PDFReader_SetCurrentPage(const char* filename, int page);
#endif
