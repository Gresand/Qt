#ifndef WORKTEXT_H
#define WORKTEXT_H

#include <QDialog>

namespace Ui {
class worktext;
}

class worktext : public QDialog
{
    Q_OBJECT

public:
    explicit worktext(QWidget *parent = nullptr);
    ~worktext();

private slots:
    void on_addButton_clicked();

    void on_leftTE_modificationChanged(bool arg1);

    void on_leftTE_textChanged();

    void on_rightTE_modificationChanged(bool arg1);

    void on_rightTE_textChanged();

    void on_swapButton_clicked();

    void on_htmlButton_clicked();

private:
    Ui::worktext *ui;
};

#endif // WORKTEXT_H
