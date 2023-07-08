#ifndef BULLET_H
#define BULLET_H
#include "gameitem.h"
#include <QString>
#include <QTimer>
#include <QGraphicsObject>
#include <QList>
#include <QSize>
#include <vector>
#include <algorithm>
#include "MyConstants.h"
#include "wall.h"
#include <QSoundEffect>
#define eps 1e-6

using namespace std;

class Bullet : public GameItem
{
    Q_OBJECT
public:
    Bullet(QString File,QGraphicsScene *s, QPointF pos, qreal distance);
    virtual ~Bullet();
    QTimer *timer;
    QTimer *boretimer;
    void advance(int phase);
    qreal speed;
    QSoundEffect* sound;
public slots:
    void Disappear(void);
};

#endif // BULLET_H
