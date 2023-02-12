#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include <QLineEdit>
#include <QPushButton>

#include "downloader.h"
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    downloader* dl;
    QProgressBar* ppb;
    QLineEdit* txt;
    QPushButton* btn;
    void showPic(const QString&);
    QLabel* lbl;
    QLabel* lbl1;
    QLabel* lbl2;
    QLabel* lbl3;
    QLabel* lbl4;
    QLabel* lbl5;
    int i = 0;
private slots:
    void slotGo();
    void slotError();
    void slotDownloadProgress(qint64, qint64);
    void slotDone(const QUrl&, const QByteArray&);
};
#endif // MAINWINDOW_H
