#ifndef BLUEBULLET_H
#define BLUEBULLET_H
#include "bullet.h"

class Bluebullet :public Bullet
{
public:
    Bluebullet(QGraphicsScene *s, QPointF pos, qreal _d);
    static int cnt;
    ~Bluebullet();
};



#endif // BLUEBULLET_H
