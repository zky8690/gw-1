#ifndef BLUETANK_H
#define BLUETANK_H
#include "tank.h"
#include <QKeyEvent>
#include "bluebullet.h"
#include <QTimer>
#include <QDebug>
#include <QSoundEffect>

class Bluetank : public Tank
{
public:
    Bluetank(QGraphicsScene *s, QPointF pos, QSize scale);
    void advance(int phase);
};

#endif // BLUETANK_H
