#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->action, SIGNAL(triggered()), this, SLOT(open()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open() {
    QString fileName = QFileDialog::getOpenFileName(this,
    tr("Открыть файл"), "",
    tr("Текстовые файлы (*.html);"));
    if (fileName != "")
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, tr("Ошибка"), tr("Не могу открыть файл"));
            return;
        }
        QTextStream in(&file);
        QString str = in.readAll();
        QString forUser = "Погода: ";
        QString weatherstr = str.mid(str.indexOf("weather-temp\">"), (str.indexOf("weather-temp\">") - str.indexOf("°")));
        weatherstr = weatherstr.sliced(weatherstr.indexOf(">") + 1);
        weatherstr = weatherstr.first(weatherstr.indexOf("°"));
        forUser += weatherstr + "\nКурс доллара: ";
        QString coursestr = str.mid(str.indexOf("rate__currency svelte-ov6yem\">", 40), 40);
        str = str.remove(str.indexOf("rate__currency svelte-ov6yem\">"), 40);
        coursestr = coursestr.sliced(coursestr.indexOf(">") + 1);
        coursestr = coursestr.first(coursestr.indexOf("<"));
        forUser += coursestr;
        QString coursestrEuro = str.mid(str.indexOf("rate__currency svelte-ov6yem\">", 40), 40);
        coursestrEuro = coursestrEuro.sliced(coursestrEuro.indexOf(">") + 1);
        coursestrEuro = coursestrEuro.first(coursestrEuro.indexOf("<"));
        forUser += "\nКурс евро: " + coursestrEuro;
        ui->textEdit->setText(forUser);
        file.close();
    }
}
