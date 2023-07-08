#include "greenbullet.h"



Greenbullet::Greenbullet(QGraphicsScene *s, QPointF pos, qreal _d) :Bullet(":/img/bulletGreen.png",s,pos, _d)
{
    ++ this->cnt;
    this->setData(2, "Green");
}
Greenbullet::~Greenbullet() {
    -- this->cnt;
}
