#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new myScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    //Обработчик приближения на колесике
    QPoint numDegrees = event->angleDelta() / 8;
    if (numDegrees.ry() > 0)
        ui->graphicsView->scale(1.1, 1.1);
    else
        ui->graphicsView->scale(1/1.1, 1/1.1);
    event->accept();


}

//Обработчик приближения на "+" и "-"
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Plus)
        ui->graphicsView->scale(1.1, 1.1);
    else if (event->key() == Qt::Key_Minus)
        ui->graphicsView->scale(1/1.1, 1/1.1);
    event->accept();
}
