#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QKeyEvent>
#include <QEvent>
#include <QSharedPointer>
#include <QMdiArea>
#include <QPrinter>
#include <QPrintDialog>

#include "form.h"
#include "keyboard.h"
#include "filemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    virtual void changeEvent(QEvent* event) override;

signals:
    void sendToKeyboard(QStringList strList);

private slots:

    //Слоты действий меню
    void open();
    void openOnlyRead();
    void save();
    void help();

    //Слоты изменения языка приложения
    void changeLanguageUS();
    void changeLanguageRU();

    //Слот нового документа
    void newD();

    //Слоты изменения темы редактора
    void on_dark_clicked();
    void on_light_clicked();

    //Слот работы с файловым менеджером
    void changePath(QFileInfo fileInfo);
    void printD();

    //Урок 7
    //Слоты изменения формата фрагмента текста
    void copyFText();
    void setFText();
    //Слоты положения текста
    void setTextLeft();
    void setTextCenter();
    void setTextRight();
    //Cлот диалога с шрифтами
    void setFont();
private:
    Ui::MainWindow *ui;
    QTranslator translator;
    Keyboard* keyboard;
    fileManager* f;
    QShortcut* openKey;
    QShortcut* saveKey;
    QShortcut* helpKey;
    QShortcut* quitKey;
    QMdiArea* area;

    QTextCharFormat* tcf;
};
#endif // MAINWINDOW_H
