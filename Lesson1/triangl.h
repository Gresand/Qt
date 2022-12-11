#ifndef TRIANGL_H
#define TRIANGL_H

#include <QDialog>
#include "QtMath"
#include <QDoubleValidator>

namespace Ui {
class Triangl;
}

class Triangl : public QDialog
{
    Q_OBJECT

public:
    explicit Triangl(QWidget *parent = nullptr);
    ~Triangl();
    void inputCapability();
private slots:

    void on_answer_clicked();


    void on_SideA_textChanged(const QString &arg1);

    void on_SideB_textChanged(const QString &arg1);

    void on_Corner_textChanged(const QString &arg1);

private:
    Ui::Triangl *ui;
    QDoubleValidator m_doubleValidator;
    QDoubleValidator cornerValidator;
};

#endif // TRIANGL_H
