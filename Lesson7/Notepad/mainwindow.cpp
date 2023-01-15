#include "mainwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QMdiSubWindow>
#include <QTextEdit>
#include <QFont>

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
    connect(ui->readOnly,SIGNAL(triggered()), this, SLOT(openOnlyRead()));
    connect(ui->english, SIGNAL(triggered()), this, SLOT(changeLanguageUS()));
    connect(ui->russian, SIGNAL(triggered()), this, SLOT(changeLanguageRU()));

    connect(this, SIGNAL(sendToKeyboard(QStringList)), keyboard, SLOT(getList(QStringList)));

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

    connect(keyboard, &Keyboard::Changed, [this](QStringList changed_list)
    {
    openKey->setKey(changed_list[0]);
    saveKey->setKey(changed_list[1]);
    helpKey->setKey(changed_list[2]);
    quitKey->setKey(changed_list[3]);
    });

    connect(ui->dark, SIGNAL(triggered()), this, SLOT(on_dark_clicked()));
    connect(ui->light, SIGNAL(triggered()), this, SLOT(on_light_clicked()));
    ui->russian->setEnabled(false);
    ui->light->setEnabled(false);
    connect(ui->widget, SIGNAL(path(QFileInfo)), this, SLOT(changePath(QFileInfo)));

    ui->mdiArea->addSubWindow(new QTextEdit(this));
    connect(ui->newDoc, SIGNAL(triggered()), this, SLOT(newD()));
    connect(ui->printDoc, SIGNAL(triggered()), this, SLOT(printD()));

    //Урок 7
    tcf = new QTextCharFormat;
    //Коннекты кнопок в меню по очереди (копирование формата, вставка, выравнивание, шрифты)
    connect(ui->copyFT, SIGNAL(triggered()), this, SLOT(copyFText()));
    connect(ui->setFT, SIGNAL(triggered()), this, SLOT(setFText()));
    ui->setFT->setEnabled(false);
    connect(ui->onLeft, SIGNAL(triggered()), this, SLOT(setTextLeft()));
    connect(ui->onCenter, SIGNAL(triggered()), this, SLOT(setTextCenter()));
    connect(ui->onRight, SIGNAL(triggered()), this, SLOT(setTextRight()));
    connect(ui->font, SIGNAL(triggered()), this, SLOT(setFont()));
}

MainWindow::~MainWindow()
{
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
    QMdiSubWindow* subWindow = ui->mdiArea->activeSubWindow();
    QWidget* widg = subWindow->widget();
    QTextEdit* edit = (QTextEdit*)widg;
    edit->setReadOnly(false);
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
        edit->setText(in.readAll());
        edit->setWindowTitle(fileName);
        ui->lineEdit->setText(fileName);
        file.close();
    }
}

void MainWindow::openOnlyRead()
{
    QMdiSubWindow* subWindow = ui->mdiArea->activeSubWindow();
    QWidget* widg = subWindow->widget();
    QTextEdit* edit = (QTextEdit*)widg;
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
        edit->setText(in.readAll());
        edit->setReadOnly(true);
        ui->lineEdit->setText(fileName);
        file.close();
    }
}

void MainWindow::save()
{

    QMdiSubWindow* subWindow = ui->mdiArea->activeSubWindow();
    QWidget* widg = subWindow->widget();
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
            QTextEdit* edit = (QTextEdit*)widg;
            stream << edit->toPlainText();
            stream.flush();
            ui->lineEdit->setText(fileName);
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
    ui->russian->setEnabled(true);
    if (translator.load(":/QtLanguage_en_US.qm"))
    {
        qApp->installTranslator(&translator);
    }
    ui->english->setEnabled(false);
}

void MainWindow::changeLanguageRU()
{
    ui->english->setEnabled(true);
    qApp->removeTranslator(&translator);
    ui->russian->setEnabled(false);
}

void MainWindow::newD()
{
    QTextEdit* newtxt = new QTextEdit(this);
    ui->mdiArea->addSubWindow(newtxt);
    newtxt->show();
}

void MainWindow::on_dark_clicked()
{
    ui->light->setEnabled(true);
    QPalette darkPalette;

    darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    qApp->setPalette(darkPalette);
    ui->dark->setEnabled(false);
}

void MainWindow::on_light_clicked()
{
    ui->light->setEnabled(false);
    qApp->setPalette(style()->standardPalette());
    ui->dark->setEnabled(true);
}

void MainWindow::changePath(QFileInfo fileInfo)
{
    if (fileInfo.fileName() == ".")
    {
        ui->lineEdit->setText("C:/");
    }
    else
        ui->lineEdit->setText(fileInfo.absoluteFilePath());
}

void MainWindow::printD()
{
    QPrinter printer;
    QPrintDialog dlg(&printer);
    dlg.setWindowTitle("На печать");
    if (dlg.exec() != QDialog::Accepted) return;
    QMdiSubWindow* subWindow = ui->mdiArea->activeSubWindow();
    QWidget* widg = subWindow->widget();
    QTextEdit* edit = (QTextEdit*)widg;
    edit->print(&printer);
}

//Реализация слотов копирования и применения формата текста к выделенному фрагменту
void MainWindow::copyFText()
{
    QMdiSubWindow* subWindow = ui->mdiArea->activeSubWindow();
    QWidget* widg = subWindow->widget();
    QTextEdit* edit = (QTextEdit*)widg;
    *tcf = edit->textCursor().charFormat();
    ui->setFT->setEnabled(true);
}

void MainWindow::setFText()
{
    QMdiSubWindow* subWindow = ui->mdiArea->activeSubWindow();
    QWidget* widg = subWindow->widget();
    QTextEdit* edit = (QTextEdit*)widg;
    edit->textCursor().setCharFormat(*tcf);
}

//Реализация слотов положения текста построчно, можно выделять несколько строк и выравнивать
void MainWindow::setTextLeft()
{
    QMdiSubWindow* subWindow = ui->mdiArea->activeSubWindow();
    QWidget* widg = subWindow->widget();
    QTextEdit* edit = (QTextEdit*)widg;
    edit->setAlignment(Qt::AlignLeft);
}

void MainWindow::setTextCenter()
{
    QMdiSubWindow* subWindow = ui->mdiArea->activeSubWindow();
    QWidget* widg = subWindow->widget();
    QTextEdit* edit = (QTextEdit*)widg;
    edit->setAlignment(Qt::AlignCenter);
}

void MainWindow::setTextRight()
{
    QMdiSubWindow* subWindow = ui->mdiArea->activeSubWindow();
    QWidget* widg = subWindow->widget();
    QTextEdit* edit = (QTextEdit*)widg;
    edit->setAlignment(Qt::AlignRight);
}

//Реализация слотов изменения шрифта
void MainWindow::setFont()
{
    QMdiSubWindow* subWindow = ui->mdiArea->activeSubWindow();
    QWidget* widg = subWindow->widget();
    QTextEdit* edit = (QTextEdit*)widg;
    QFont font = edit->textCursor().charFormat().font();
    QFontDialog fntDlg(font, this);
    bool ok = true;
    font = fntDlg.getFont(&ok, this);
    if (ok)
    {
        QTextCharFormat fmt;
        fmt.setFont(font);
        edit->textCursor().setCharFormat(fmt);
    }
}
