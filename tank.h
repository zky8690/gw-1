#ifndef TANK_H
#define TANK_H
#include "gameitem.h"
#include <QRandomGenerator>
#include <QString>
#include <QSize>
#include <QList>
#include <cstring>
#include <QPointF>
#include <QLineF>
#include "bullet.h"
#include <QtMath>
#include <QDebug>
#include <QSoundEffect>
#include "MyConstants.h"
#include <QTimer>

class Tank : public GameItem
{
    Q_OBJECT
public:
    Tank(QString File,QGraphicsScene *s, QPointF pos, QSize scale);
    void advance(int phase);
    bool KeyPressed[5];
    qreal speed, rotatespeed = 90;
    QTimer *tanktimer;
    int isDying;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    QSoundEffect* sound;
signals:
    void ImDead(void);
};

#endif // TANK_H
