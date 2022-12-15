#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <QDialog>
#include <QMessageBox>
#include <QStandardItemModel>

namespace Ui {
class language;
}

class language : public QDialog
{
    Q_OBJECT

public:
    explicit language(QWidget *parent = nullptr);
    ~language();

private slots:
    void on_addBut_clicked();

    void on_delButton_clicked();

    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_checkBox_clicked(bool checked);

private:
    Ui::language *ui;
    QStandardItemModel* model;
};

#endif // LANGUAGE_H
