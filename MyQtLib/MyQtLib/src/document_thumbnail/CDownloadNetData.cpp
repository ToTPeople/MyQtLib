#include "CDownloadNetData.h"
#include <QtNetwork/QNetworkReply>
#include <QFile>
#include <QFileInfo>
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QMessageBox>


namespace {
    const char* const kszNetworkDataSavePre = "./Resources/download/";
}

class CDownloadNetDataPrivate {
    friend CDownloadNetData;

public:
    CDownloadNetDataPrivate();

public:
    QNetworkAccessManager   m_netAccessMgr;
    QNetworkReply*          m_pReply;
    QFile*                  m_pFile;
    QUrl                    m_url;
};

CDownloadNetDataPrivate::CDownloadNetDataPrivate()
    : m_pReply(NULL)
    , m_pFile(NULL)
{
}


CDownloadNetData::CDownloadNetData(QObject* parent /*= NULL*/)
    : QObject(parent)
    , m(*new CDownloadNetDataPrivate())
{
}


CDownloadNetData::~CDownloadNetData()
{
    delete &m;
}

bool CDownloadNetData::downloadData(const QUrl & urlNet)
{
    m.m_url = urlNet;
    QFileInfo info(urlNet.path());
    QString fileName(info.fileName());
    if (fileName.isEmpty()) {
        return false;
    }
    m.m_pFile = new QFile(kszNetworkDataSavePre + fileName);
    if (NULL == m.m_pFile || !m.m_pFile->open(QIODevice::WriteOnly)) {
        if (NULL != m.m_pFile) {
            /*QMessageBox::information(pWgt, tr("HTTP"),
                tr("Unable to save the file %1: %2.")
                .arg(fileName).arg(m.m_pFile->errorString()));*/
            delete m.m_pFile;
            m.m_pFile = NULL;
        }
        return false;
    }
    qDebug() << "url: " << urlNet;

    // request
    m.m_pReply = m.m_netAccessMgr.get(QNetworkRequest(urlNet));
    if (NULL == m.m_pReply) {
        delete m.m_pFile;
        m.m_pFile = NULL;
        return false;
    }

    QObject::connect(m.m_pReply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    QObject::connect(m.m_pReply, SIGNAL(finished()), this, SLOT(slotDownloadFinish()));

    return true;
}

void CDownloadNetData::slotReadyRead()
{
    if (NULL != m.m_pFile && NULL != m.m_pReply) {
        m.m_pFile->write(m.m_pReply->readAll());
    }
}

void CDownloadNetData::slotDownloadFinish()
{
    if (NULL != m.m_pFile) {
        m.m_pFile->flush();
        m.m_pFile->close();
        delete m.m_pFile;
        m.m_pFile = NULL;
    }
    if (NULL != m.m_pReply) {
        delete m.m_pReply;
        m.m_pReply = NULL;
    }
    emit sigDownloadFinish();
}
