#ifndef WALL_H
#define WALL_H
#include "gameitem.h"
#include <QSize>
#include <cstring>

class Wall : public GameItem
{
public:
    Wall(QGraphicsScene *s, QPointF pos, QSize scale);
    bool canBeTouched[4];
};

#endif // WALL_H
