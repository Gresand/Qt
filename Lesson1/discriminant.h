#ifndef DISCRIMINANT_H
#define DISCRIMINANT_H

#include <QDialog>
#include <QDoubleValidator>

namespace Ui {
class Discriminant;
}

class Discriminant : public QDialog
{
    Q_OBJECT

public:
    explicit Discriminant(QWidget *parent = nullptr);
    ~Discriminant();
    void inputСapability();
private slots:
    void on_memberA_textChanged(const QString &arg1);

    void on_memberB_textChanged(const QString &arg1);

    void on_memberC_textChanged(const QString &arg1);

    void on_DButton_clicked();

private:
    Ui::Discriminant *ui;
    QDoubleValidator m_doubleValidator;
};

#endif // DISCRIMINANT_H
