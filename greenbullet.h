#ifndef GREENBULLET_H
#define GREENBULLET_H
#include "bullet.h"

class Greenbullet : public Bullet
{
public:
    Greenbullet(QGraphicsScene *s, QPointF pos, qreal _d);
    static int cnt;
    ~Greenbullet();
};



#endif // GREENBULLET_H
