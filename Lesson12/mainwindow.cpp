#include "mainwindow.h"

#include <QGridLayout>
#include <QFile>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    dl = new downloader(this);
    ppb = new QProgressBar(this);
    txt = new QLineEdit(this);
    txt->setPlaceholderText("Enter a request \"cat\" or another ");
    btn = new QPushButton("Go", this);
    lbl = new QLabel;
    lbl1 = new QLabel;
    lbl2 = new QLabel;
    lbl3 = new QLabel;
    lbl4 = new QLabel;
    lbl5 = new QLabel;

    connect(btn, SIGNAL(clicked()), this, SLOT(slotGo()));
    connect(dl, SIGNAL(downloadProgress(qint64,qint64)),
            this, SLOT(slotDownloadProgress(qint64,qint64)));
    connect(dl, SIGNAL(done(const QUrl&,const QByteArray&)),
            this, SLOT(slotDone(const QUrl&,const QByteArray&)));

    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(lbl, 0, 0);
    layout->addWidget(lbl1, 0, 1);
    layout->addWidget(lbl2, 1, 0);
    layout->addWidget(lbl3, 1, 1);
    layout->addWidget(lbl4, 2, 0);
    layout->addWidget(lbl5, 2, 1);
    layout->addWidget(txt, 3, 0);
    layout->addWidget(btn, 3, 1);
    layout->addWidget(ppb, 4, 0, 1, 2);

    QWidget* wgt = new QWidget(this);
    setCentralWidget(wgt);
    wgt->setLayout(layout);
}

MainWindow::~MainWindow()
{
}

void MainWindow::showPic(const QString &path)
{
    QPixmap pix(path);
    pix = pix.scaled(pix.size());
    if (i == 0)
    {
        lbl->setPixmap(pix);
        lbl->setFixedSize(pix.size());
        lbl->show();
        ++i;
    }
    else if (i == 1)
    {
        lbl1->setPixmap(pix);
        lbl1->setFixedSize(pix.size());
        lbl1->show();
        ++i;
    }
    else if (i == 2)
    {
        lbl2->setPixmap(pix);
        lbl2->setFixedSize(pix.size());
        lbl2->show();
        ++i;
    }
    else if (i == 3)
    {
        lbl3->setPixmap(pix);
        lbl3->setFixedSize(pix.size());
        lbl3->show();
        ++i;
    }
    else if (i == 4)
    {
        lbl4->setPixmap(pix);
        lbl4->setFixedSize(pix.size());
        lbl4->show();
        ++i;
    } else if (i == 5)
    {
        lbl5->setPixmap(pix);
        lbl5->setFixedSize(pix.size());
        lbl5->show();
        i = 0;
    }
}

void MainWindow::slotGo()
{
    lbl->clear();
    lbl1->clear();
    lbl2->clear();
    lbl3->clear();
    lbl4->clear();
    lbl5->clear();
    dl->download(txt->text());
}

void MainWindow::slotError()
{
    QMessageBox::critical(this, "Error", "some wrong!");
}

void MainWindow::slotDownloadProgress(qint64 received, qint64 total)
{
    if(total <= 0)
    {
        slotError();
        return;
    }
    ppb->setValue(100 * received / total);
}

void MainWindow::slotDone(const QUrl &url, const QByteArray &ba)
{
    QFile file(url.path().section('/', -1));
    qDebug() << url;
    if(file.open(QIODevice::WriteOnly))
    {
        file.write(ba);
        file.close();
    }
    showPic(file.fileName());
}

