#include "myscene.h"

static int geomI = 0;

myScene::myScene(QObject *parent)
    : QGraphicsScene{parent}
{

}

void myScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //Отработка добавление элемента на левую кнопку мыши
    if (event->button() == Qt::LeftButton && !this->itemAt(event->scenePos(), {}))
    {
        It = new gItem(this);
        It->setPos(event->scenePos());
        this->addItem(It);
        if (geomI == 0)
        {
            It->setGeometry(geomI);
            geomI++;
            this->update();
        }
            else if (geomI == 1)
        {
            It->setGeometry(geomI);
            geomI++;
            this->update();
        }
        else if (geomI == 2)
        {
            It->setGeometry(geomI);
            geomI = 0;
            this->update();
        }
    }
    //Отработка перерисовки элементов (эллипс->квадрат->звезда) если нажимать на любой элемент
    //Удалено, но работает :)
//    else if (event->button() == Qt::LeftButton && this->itemAt(event->scenePos(), {}))
//    {
//        QGraphicsItem* pIt = this->itemAt(event->scenePos(),{});
//        gItem* castIt = (gItem*)(pIt);
//        if (castIt->getGeometry() == 0)
//        {
//            castIt->setGeometry(1);
//            this->update();
//        }
//            else if (castIt->getGeometry() == 1)
//        {
//            castIt->setGeometry(2);
//            this->update();
//        }
//        else if (castIt->getGeometry() == 2)
//        {
//            castIt->setGeometry(0);
//            this->update();
//        }
//    }
    //Отработка удаление на правую кнопку мыши
    if (event->button() == Qt::RightButton && this->itemAt(event->scenePos(), {}))
    {
        QGraphicsItem* pIt = this->itemAt(event->scenePos(),{});
        this->removeItem(pIt);
    }
    QGraphicsScene::mousePressEvent(event);
}

