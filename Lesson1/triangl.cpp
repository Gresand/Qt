#include "triangl.h"
#include "ui_triangl.h"


Triangl::Triangl(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Triangl),
    m_doubleValidator(0, 1000, 3, this),
    cornerValidator(1,178, 6, this)
{
    ui->setupUi(this);
    m_doubleValidator.setLocale(QLocale::English);
    cornerValidator.setLocale(QLocale::English);
    ui->SideA->setValidator(&m_doubleValidator);
    ui->SideB->setValidator(&m_doubleValidator);
    ui->Corner->setValidator(&cornerValidator);
}

Triangl::~Triangl()
{
    delete ui;
}

void Triangl::inputCapability()
{
    if((ui->Corner->text() != "") && (ui->SideA->text() != "") && (ui->SideB->text() != ""))
        ui->answer->setEnabled(true);
    else
        ui->answer->setEnabled(false);
}


void Triangl::on_SideA_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    Triangl::inputCapability();
}


void Triangl::on_SideB_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    Triangl::inputCapability();
}


void Triangl::on_Corner_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    Triangl::inputCapability();
}

void Triangl::on_answer_clicked()
{
    double a;
    double b;
    double c;
    double answer;
    a = ui->SideA->text().toDouble();
    b = ui->SideB->text().toDouble();
    c = ui->Corner->text().toDouble();
    if (ui->grad->isChecked())
    {
        answer = qSqrt(qPow(a,2) + qPow(b,2) - 2 * a * b * qCos(qDegreesToRadians(c)));
        ui->labelAnswer->setText("Ответ:" + QString::number(answer));
    }
    else if (ui->rad->isChecked())
    {
        answer = qSqrt(qPow(a,2) + qPow(b,2) - 2 * a * b * qCos(c));
        ui->labelAnswer->setText("Ответ:" + QString::number(answer));
    }
}



