#include "wall.h"

Wall::Wall(QGraphicsScene *s, QPointF pos, QSize scale) : GameItem(":/img/wall.png", s, pos, scale, 1)
{
    this->setData(0, QVariant(QString("Wall")));
    memset(canBeTouched,0,sizeof(canBeTouched));
}
