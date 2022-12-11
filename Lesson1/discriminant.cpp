#include "discriminant.h"
#include "ui_discriminant.h"
#include "QtMath"


Discriminant::Discriminant(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Discriminant),
    m_doubleValidator(-1000, 1000, 3, this)
{
    m_doubleValidator.setLocale(QLocale::English);
    ui->setupUi(this);
    ui->memberA->setValidator(&m_doubleValidator);
    ui->memberB->setValidator(&m_doubleValidator);
    ui->memberC->setValidator(&m_doubleValidator);
    ui->DButton->setEnabled(false);
}

Discriminant::~Discriminant()
{
    delete ui;
}

void Discriminant::inputСapability()
{
    if ((ui->memberA->text() != "") && (ui->memberB->text() != "") && (ui->memberC->text() != ""))
    {
        ui->DButton->setEnabled(true);
    }
    else
    {
        ui->DButton->setEnabled(false);
    }
}

void Discriminant::on_memberA_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    Discriminant::inputСapability();
}


void Discriminant::on_memberB_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    Discriminant::inputСapability();
}


void Discriminant::on_memberC_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    Discriminant::inputСapability();
}


void Discriminant::on_DButton_clicked()
{
    double a,b,c,d,x1,x2;
    a = ui->memberA->text().toDouble();
    b = ui->memberB->text().toDouble();
    c = ui->memberC->text().toDouble();
    d = qPow(b,2) - 4 * a * c;
    if(a == 0)
    {
        x1 = (-c)/b;
        ui->answer->setText("а = 0, корень один X = " + QString::number(x1));
    }
    else if (d > 0) // Условие при дискриминанте больше нуля
      {
        x1 = ((-b) - qSqrt(d)) / (2 * a);
        x2 = ((-b) + qSqrt(d)) / (2 * a);
        ui->answer->setText("Х1 = " + QString::number(x1) + "Х2 = " + QString::number(x2));
      }
    else if (d == 0) // Условие для дискриминанта равного нулю
      {
        x1 = -(b / (2 * a));
        ui->answer->setText("Дискриминант равен нулю, корень один X = " + QString::number(x1));
      }
    else if (d < 0) // Условие при дискриминанте меньше нуля
      {
        ui->answer->setText("Решения нет");
      }
}

