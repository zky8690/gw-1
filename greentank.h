#ifndef GREENTANK_H
#define GREENTANK_H
#include "tank.h"
#include <QKeyEvent>
#include "greenbullet.h"
#include <QDebug>
#include <QSoundEffect>

class Greentank : public Tank
{
public:
    Greentank(QGraphicsScene *s, QPointF pos, QSize scale);
    void advance(int phase);
};

#endif // GREENTANK_H
