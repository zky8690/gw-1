#include "bluebullet.h"

Bluebullet::Bluebullet(QGraphicsScene *s, QPointF pos, qreal _d): Bullet(":/img/bulletBlue.png",s,pos, _d)
{
    ++ this->cnt;
    this->setData(2, QString("Blue"));
}
Bluebullet::~Bluebullet() {
    -- this->cnt;
}
