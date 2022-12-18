#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->open_2, SIGNAL(triggered()), this, SLOT(open()));
    connect(ui->save, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->exit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->help, SIGNAL(triggered()), this, SLOT(help()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open() {
    QString fileName = QFileDialog::getOpenFileName(this,
    tr("Открыть файл"), "",
    tr("Текстовые файлы (*.txt);;Файлы C++ (*.cpp *.h)"));
    if (fileName != "")
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, tr("Ошибка"), tr("Не могу открыть файл"));
            return;
        }
        QTextStream in(&file);
        ui->textEdit->setText(in.readAll());
        file.close();
    }
}

void MainWindow::save() {
    QString fileName = QFileDialog::getSaveFileName(this,
    tr("Сохранить файл"), "",
    tr("Текстовые файлы (*.txt);;Файлы C++ (*.cpp *.h)"));
    if (fileName != "")
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox msgBox; msgBox.setText("Не могу записать файл"); msgBox.exec();
        }
        else
        {
            QTextStream stream(&file);
            stream << ui->textEdit->toPlainText();
            stream.flush();
            file.close();
        }
    }
}

void MainWindow::help()
{
    Form* f = new Form;
    f->show();
}
