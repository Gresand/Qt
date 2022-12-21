#include "mainwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    keyboard = new Keyboard;
    connect(ui->open_2, SIGNAL(triggered()), this, SLOT(open()));
    connect(ui->save, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->exit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->help, SIGNAL(triggered()), this, SLOT(help()));
    connect(ui->openRead,SIGNAL(triggered()), this, SLOT(openOnlyRead()));
    connect(ui->english, SIGNAL(triggered()), this, SLOT(changeLanguageUS()));
    connect(ui->russian, SIGNAL(triggered()), this, SLOT(changeLanguageRU()));

    list << "Ctrl+O" << "Ctrl+S" << "F1" << "Ctrl+Q";
    connect(this, SIGNAL(sendToKeyboard(QStringList)), keyboard, SLOT(getList(QStringList)));
    emit sendToKeyboard(list);
    helpKey = new QShortcut(this);
    helpKey->setKey(Qt::Key_F1);
    openKey = new QShortcut(this);
    openKey->setKey(Qt::CTRL | Qt::Key_O);
    saveKey = new QShortcut(this);
    saveKey->setKey(Qt::CTRL | Qt::Key_S);
    quitKey = new QShortcut(this);
    quitKey->setKey(Qt::CTRL | Qt::Key_Q);

    connect(helpKey, SIGNAL(activated()), this, SLOT(help()));
    connect(openKey, SIGNAL(activated()), this, SLOT(open()));
    connect(saveKey, SIGNAL(activated()), this, SLOT(save()));
    connect(quitKey, SIGNAL(activated()), this, SLOT(close()));
    connect(ui->keysetting, SIGNAL(triggered()), keyboard, SLOT(show()));
}

MainWindow::~MainWindow()
{
    delete keyboard;
    delete ui;
}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
    QMainWindow::changeEvent(event);
}

void MainWindow::open() {
    ui->textEdit->setReadOnly(false);
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

void MainWindow::openOnlyRead()
{
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
        ui->textEdit->setReadOnly(true);
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

void MainWindow::changeLanguageUS()
{
    if (translator.load(":/QtLanguage_en_US.qm"))
    {
        qApp->installTranslator(&translator);
    }
}

void MainWindow::changeLanguageRU()
{
    qApp->removeTranslator(&translator);
}
