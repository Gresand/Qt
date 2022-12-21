#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QKeyEvent>
#include <QEvent>
#include <QSharedPointer>

#include "form.h"
#include "keyboard.h"

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
    void open();
    void openOnlyRead();
    void save();
    void help();
    void changeLanguageUS();
    void changeLanguageRU();
private:
    Ui::MainWindow *ui;
    QTranslator translator;
    Keyboard* keyboard;
    QShortcut* openKey;
    QShortcut* saveKey;
    QShortcut* helpKey;
    QShortcut* quitKey;
    QStringList list;
};
#endif // MAINWINDOW_H
