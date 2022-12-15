#include "tablewithnew.h"
#include "ui_tablewithnew.h"
#include <QStringList>
TableWithNew::TableWithNew(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TableWithNew)
{
    ui->setupUi(this);
    newLineNumber = new QLineEdit(QString::number(row + 1));
    newLineName = new QLineEdit;
    newLineName->setInputMask("nnnnnnnnnnnnnnnnnnnn;_");
    newLineName->setText("Laptop FX506QM");
    newLineIP = new QLineEdit;
    newLineIP->setInputMask("009.009.009.009;_");
    newLineIP->setText("192.168.10.1");
    newLineMAC = new QLineEdit;
    newLineMAC->setInputMask("HH:HH:HH:HH:HH:HH;_");
    newLineMAC->setText("ff:ff:ff:ff:ff:ff");
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectItems);
    ui->tableWidget->setColumnWidth(0,50);
    ui->tableWidget->setColumnWidth(1,150);
    QStringList mystrlist;
    mystrlist << "id" << "Имя компьютера" << "IP адрес" << "MAC адрес";
    ui->tableWidget->setHorizontalHeaderLabels(mystrlist);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->insertRow(row);
    ui->tableWidget->setCellWidget(row, col, newLineNumber); col = col + 1;
    ui->tableWidget->setCellWidget(row, col, newLineName); col = col + 1;
    ui->tableWidget->setCellWidget(row, col, newLineIP); col = col + 1;
    ui->tableWidget->setCellWidget(row, col, newLineMAC); col = col + 1;
}

TableWithNew::~TableWithNew()
{
    delete ui;
}

void TableWithNew::on_add_clicked()
{
    row = ui->tableWidget->rowCount();
    col = 0;
    newLineNumber = new QLineEdit(QString::number(row + 1));
    newLineNumber->setInputMask("999;___");
    newLineName = new QLineEdit;
    newLineName->setInputMask("nnnnnnnnnnnnnnnnnnnn;_");
    newLineIP = new QLineEdit;
    newLineIP->setInputMask("009.009.009.009;_");
    newLineMAC = new QLineEdit;
    newLineMAC->setInputMask("HH:HH:HH:HH:HH:HH;_");
    ui->tableWidget->insertRow(row);
    ui->tableWidget->setCellWidget(row, col, newLineNumber); col = col + 1;
    ui->tableWidget->setCellWidget(row, col, newLineName); col = col + 1;
    ui->tableWidget->setCellWidget(row, col, newLineIP); col = col + 1;
    ui->tableWidget->setCellWidget(row, col, newLineMAC); col = col + 1;
    if (!ui->deleterow->isEnabled())
        ui->deleterow->setEnabled(true);
}


void TableWithNew::on_deleterow_clicked()
{
    qDebug() << row;
    if (ui->tableWidget->rowCount() > 1)
    {
        qDebug() << row;
        row = ui->tableWidget->currentRow();
        ui->tableWidget->removeRow(row);
        row = ui->tableWidget->rowCount();
        qDebug() << row;
    }
    else
    {
        qDebug() << row;
        msg = new QMessageBox();
        msg->setWindowTitle("Ошибка");
        msg->setText("Нет строк, которые можно удалить");
        msg->exec();
        delete msg;
        ui->deleterow->setEnabled(false);
    }
}
void TableWithNew::on_tableWidget_cellActivated(int rows, int column)
{
    QWidget* f = ui->tableWidget->cellWidget(rows,column);
    f->setStyleSheet("background: yellow");
    ui->tableWidget->setCellWidget(rows,column, f);
}

