#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_cdocumentthumbnaildemo.h"

class QLabel;
class CDownloadNetData;
class CDocumentThumbnailDemo : public QMainWindow
{
    Q_OBJECT

public:
    CDocumentThumbnailDemo(QWidget *parent = Q_NULLPTR);
    ~CDocumentThumbnailDemo();

public:
    // ≤‚ ‘Àı¬‘Õº
    void testThumbnail();

public slots:
    void slotOnTextBtnClick();
    void slotOnImageBtnClick();
    void slotOnPDFBtnClick();
    void slotOnNetImageBtnClick();

    void slotDownloadFinish();

private:
    Ui::CDocumentThumbnailDemoClass ui;
    QLabel*                         m_pLabel;
    CDownloadNetData*               m_pDownLoadNetData;
};
