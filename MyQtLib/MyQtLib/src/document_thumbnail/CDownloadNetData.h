#pragma once
#include <QObject>
#include "myqtlib_global.h"

class QUrl;
class CDownloadNetDataPrivate;

class MYQTLIB_EXPORT CDownloadNetData : public QObject
{
    Q_OBJECT

public:
    CDownloadNetData(QObject* parent = NULL);
    ~CDownloadNetData();

public:
    bool downloadData(const QUrl& urlNet);

signals:
    // œ¬‘ÿΩ· ¯–≈∫≈
    void sigDownloadFinish();

private slots:
    void slotDownloadFinish();
    void slotReadyRead();

private:
    CDownloadNetDataPrivate     &m;
};

