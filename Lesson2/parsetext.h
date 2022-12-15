#ifndef PARSETEXT_H
#define PARSETEXT_H

#include <QDialog>
#include <QTextCursor>

namespace Ui {
class parsetext;
}

class parsetext : public QDialog
{
    Q_OBJECT

public:
    explicit parsetext(QWidget *parent = nullptr);
    ~parsetext();

private slots:
    void on_plainTextEdit_textChanged();

private:
    Ui::parsetext *ui;
    QTextCursor* tc = new QTextCursor;
    bool flagc = false;
    qint32 posc = 0;
};

#endif // PARSETEXT_H
