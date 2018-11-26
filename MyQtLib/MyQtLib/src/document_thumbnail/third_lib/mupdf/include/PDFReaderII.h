#ifndef _PDF_IUM_READER_H_
#define _PDF_IUM_READER_H_

#include <cstddef>

#ifdef PDF_IUM_READER_API extern "C" _declspec(dllexport)   
#else  
#define PDF_IUM_READER_API extern "C" _declspec(dllexport)  
#endif  

//����
PDF_IUM_READER_API bool  PDFReader_Loadpdf(const char* filename);
//�ر�
 PDF_IUM_READER_API void  PDFReader_Closepdf(const char* filename);
//����ĳ��page
PDF_IUM_READER_API char* PDFReader_GetPage(const char* filename, int page, int& width, int& height, ptrdiff_t& format);
//��ȡ��ҳ��
PDF_IUM_READER_API  int  PDFReader_GetPageCount(const char* filename);
//��ȡ��һҳ����Ⱦ��ҳ
PDF_IUM_READER_API  char*  PDFReader_GetNextPage(const char* filename, int &page, int& width, int& height, ptrdiff_t& format);
//��ȡ��һҳ����Ⱦ��ҳ
PDF_IUM_READER_API  char*  PDFReader_GetLastPage(const char* filename, int &page, int& width, int& height, ptrdiff_t& format);
//���õ�ǰҳ
PDF_IUM_READER_API void  PDFReader_SetCurrentPage(const char* filename, int page);
#endif
