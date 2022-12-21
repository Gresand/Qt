#include "keyboard.h"
#include "ui_keyboard.h"

#include <QApplication>

Keyboard::Keyboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Keyboard)
{
    ui->setupUi(this);
}

Keyboard::~Keyboard()
{
    delete ui;
}

void Keyboard::on_pushButton_clicked()
{
    delete stringListModel;
    list << "Ctrl+O" << "Ctrl+S" << "F1" << "Ctrl+Q";
    stringListModel = new QStringListModel(list);
    ui->listView->setModel(stringListModel);
}

void Keyboard::getList(QStringList strList)
{
    stringListModel = new QStringListModel(strList);
    ui->listView->setModel(stringListModel);
}
