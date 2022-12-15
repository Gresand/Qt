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

void MainWindow::on_choice_clicked()
{
    if (ui->specSymbol->isChecked())
    {
        MainWindow::setEnabled(false);
        parse = new parsetext;
        parse->exec();
        delete parse;
    }
    else if (ui->language->isChecked())
    {
        MainWindow::setEnabled(false);
        l = new language;
        l->exec();
        delete l;
    }
    else if (ui->tableWithNet->isChecked())
    {
        MainWindow::setEnabled(false);
        tw = new TableWithNew;
        tw->exec();
        delete tw;
    }
    MainWindow::setEnabled(true);
}

