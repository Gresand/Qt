#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "discriminant.h"
#include "triangl.h"
#include "worktext.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_solutionButton_clicked();

private:
    Ui::MainWindow *ui;
    double a;
    double b;
    double c;
    double d;
    double x1;
    double x2;
    Discriminant* D;
    Triangl* T;
    worktext* w;
};
#endif // MAINWINDOW_H
