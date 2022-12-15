#include "parsetext.h"
#include "ui_parsetext.h"

parsetext::parsetext(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::parsetext)
{
    ui->setupUi(this);
    *tc = ui->plainTextEdit->textCursor();
    ui->plainTextEdit->setTextCursor(*tc);
}

parsetext::~parsetext()
{
    delete ui;
}

void parsetext::on_plainTextEdit_textChanged()
{
    QString str = ui->plainTextEdit->toPlainText();
    if (flagc)
    {
        tc->setPosition(posc);
        ui->plainTextEdit->setTextCursor(*tc);
        flagc = false;
    }
    qint32 pos = 0;
    while(1)
    {
        qint32 fnd = str.indexOf("#@", pos);
        if (fnd == -1) return;
        pos = fnd + 1;
        int r = str.indexOf("&^", fnd);
        int space = str.indexOf(" ",fnd);
        if ((r<space || space == -1) && r != -1)
        {
            if (str.sliced(fnd + 2, r - fnd - 2) == "RUB")
            {
                *tc = ui->plainTextEdit->textCursor();
                posc = fnd + 1;
                flagc = true;
                str.insert(r+2, "₽");
                str.remove(fnd,7);
                ui->plainTextEdit->setPlainText(str);
            }
            if (str.sliced(fnd + 2, r - fnd - 2) == "EUR")
            {
                *tc = ui->plainTextEdit->textCursor();
                posc = fnd + 1;
                flagc = true;
                str.insert(r+2, "€");
                str.remove(fnd,7);
                ui->plainTextEdit->setPlainText(str);
            }
            if (str.sliced(fnd + 2, r - fnd - 2) == "PRO")
            {
                *tc = ui->plainTextEdit->textCursor();
                posc = fnd + 1;
                flagc = true;
                str.insert(r+2, "‰");
                str.remove(fnd,7);
                ui->plainTextEdit->setPlainText(str);
            }
            if (str.sliced(fnd + 2, r - fnd - 2) == "COO")
            {
                *tc = ui->plainTextEdit->textCursor();
                posc = fnd + 1;
                flagc = true;
                str.insert(r+2, "©");
                str.remove(fnd,7);
                ui->plainTextEdit->setPlainText(str);
            }
            if (str.sliced(fnd + 2, r - fnd - 2) == "ROO")
            {
                *tc = ui->plainTextEdit->textCursor();
                posc = fnd + 1;
                flagc = true;
                str.insert(r+2, "®");
                str.remove(fnd,7);
                ui->plainTextEdit->setPlainText(str);
            }
        }
    }
}

