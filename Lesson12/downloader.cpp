#include "downloader.h"

#include <QNetworkReply>

downloader::downloader(QObject *parent)
    : QObject{parent}
{
    pnam = new QNetworkAccessManager(this);
    picknam = new QNetworkAccessManager(this);
    connect(pnam, SIGNAL(finished(QNetworkReply*)), this, SLOT(slotFinished(QNetworkReply*)));
    connect(picknam, SIGNAL(finished(QNetworkReply*)), this, SLOT(pickFinished(QNetworkReply*)));
}

void downloader::download(const QString &url)
{
    QString urlText;
    urlText += "https://yandex.ru/images/search?text=";
    urlText += url;
    QNetworkRequest reques(urlText);
    QNetworkReply* reply = pnam->get(reques);
//    connect(reply, SIGNAL(downloadProgress(qint64,qint64)), this, SIGNAL(downloadProgress(qint64,qint64)));
}

void downloader::downloadPick(const QUrl &urlText)
{
    QNetworkRequest reques(urlText);
    QNetworkReply* replyPick = picknam->get(reques);
    connect(replyPick, SIGNAL(downloadProgress(qint64,qint64)), this, SIGNAL(downloadProgress(qint64,qint64)));
}

void downloader::slotFinished(QNetworkReply *reply)
{
    if(reply->error() != QNetworkReply::NetworkError::NoError)
    {
        emit error();
    }
    else
    {
        QString data = QString::fromUtf8(reply->readAll());
        data = data.mid(data.lastIndexOf(".jpg"));
        data = data.mid(data.indexOf("<img"));
        QStringList imageSrcList;
        for (int i = 0; i < 10; ++i)
        {
            QString tempInList;
            data = data.mid(data.indexOf("src=\"") + 5);
            tempInList = "https:";
            tempInList += data.mid(0, data.indexOf("\""));
            tempInList = tempInList.remove(tempInList.indexOf("amp"), 4);
            tempInList = tempInList.remove(tempInList.indexOf("amp"), 4);
            imageSrcList.append(tempInList);
            downloadPick(tempInList);
        }
//        emit done(reply->url(), reply->readAll());
    }
    reply->deleteLater();
}

void downloader::pickFinished(QNetworkReply *replyPick)
{
    if(replyPick->error() != QNetworkReply::NetworkError::NoError)
    {
        emit error();
    }
    else
    {
        emit done(replyPick->url(), replyPick->readAll());
    }
    replyPick->deleteLater();
}
