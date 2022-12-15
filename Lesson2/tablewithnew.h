#ifndef TABLEWITHNEW_H
#define TABLEWITHNEW_H

#include <QDialog>
#include <QLineEdit>
#include <QTableWidgetItem>
#include <QMessageBox>

namespace Ui {
class TableWithNew;
}

class TableWithNew : public QDialog
{
    Q_OBJECT

public:
    explicit TableWithNew(QWidget *parent = nullptr);
    ~TableWithNew();

private slots:
    void on_add_clicked();

    void on_deleterow_clicked();

    void on_tableWidget_cellActivated(int row, int column);

private:
    Ui::TableWithNew *ui;
    uint row = 0;
    uint col = 0;
    QLineEdit* newLineNumber;
    QLineEdit* newLineName;
    QLineEdit* newLineIP;
    QLineEdit* newLineMAC;
    QMessageBox* msg;
};

#endif // TABLEWITHNEW_H
