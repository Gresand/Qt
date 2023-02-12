#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>

class downloader : public QObject
{
    Q_OBJECT
public:
    explicit downloader(QObject *parent = nullptr);
    void download(const QString&);
    void downloadPick(const QUrl&);
signals:
    void downloadProgress(qint64,qint64);
    void done(const QUrl&, const QByteArray&);
    void error();

private:
    QNetworkAccessManager* pnam;
    QNetworkAccessManager* picknam;
private slots:
    void slotFinished(QNetworkReply*);
    void pickFinished(QNetworkReply*);
};

#endif // DOWNLOADER_H
