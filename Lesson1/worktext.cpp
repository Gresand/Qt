#include "worktext.h"
#include "ui_worktext.h"

worktext::worktext(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::worktext)
{
    ui->setupUi(this);
}

worktext::~worktext()
{
    delete ui;
}

void worktext::on_addButton_clicked()
{
        QString str = ui->leftTE->toPlainText();
        ui->rightTE->setPlainText(str);
        ui->addButton->setEnabled(false);
        ui->swapButton->setEnabled(false);
}

void worktext::on_leftTE_modificationChanged(bool arg1)
{
    Q_UNUSED(arg1)
    ui->addButton->setEnabled(true);
}

void worktext::on_leftTE_textChanged()
{
    ui->addButton->setEnabled(true);
}


void worktext::on_rightTE_modificationChanged(bool arg1)
{
    Q_UNUSED(arg1)
    ui->swapButton->setEnabled(true);
}


void worktext::on_rightTE_textChanged()
{
    ui->swapButton->setEnabled(true);
}


void worktext::on_swapButton_clicked()
{
    ui->leftTE->document()->clear();
    QString str = ui->rightTE->toPlainText();
    ui->leftTE->setPlainText(str);
    ui->swapButton->setEnabled(false);
    ui->addButton->setEnabled(false);
}


void worktext::on_htmlButton_clicked()
{
    ui->leftTE->appendHtml("<font color='red'>Hello</font>");
    ui->rightTE->appendHtml("<font color='red'>I Got It</font>");
}

