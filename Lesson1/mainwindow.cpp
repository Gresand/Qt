#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_solutionButton_clicked()
{
    if(ui->discriminantButton->isChecked())
    {
        MainWindow::setEnabled(false);
        D = new Discriminant;
        D->exec();
        delete D;
    }
    else if (ui->triangleButton->isChecked())
    {
        MainWindow::setEnabled(false);
        T = new Triangl;
        T->exec();
        delete T;
    }
    else if(ui->textButton->isChecked())
    {
        MainWindow::setEnabled(false);
        w = new worktext;
        w->exec();
        delete w;
    }
    MainWindow::setEnabled(true);
}

