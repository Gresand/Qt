#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "parsetext.h"
#include "tablewithnew.h"
#include "language.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void changeText(QString &str);

private slots:

    void on_choice_clicked();

private:
    Ui::MainWindow *ui;
    parsetext *parse;
    TableWithNew *tw;
    language* l;
};
#endif // MAINWINDOW_H
