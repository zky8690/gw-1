#ifndef GAMESCENE_H
#define GAMESCENE_H
#include <QGraphicsScene>
#include <iostream>
#include <fstream>
#include <string>
#include "wall.h"
#include <QPointF>
#include <QDebug>
#include <QSize>
#include "greentank.h"
#include "bluetank.h"
#include <QTimer>
#include <QKeyEvent>
#include "MyConstants.h"
#include "tank.h"
#include <QRandomGenerator>

using namespace std;

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GameScene();
    Greentank * tank_g;
    Bluetank * tank_b;
    QTimer * timer;
    QTimer * Endtimer;
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
//    void advance(void);
public slots:
    void Destroy(void);
    void Prepare_to_dieg(void);
     void Prepare_to_dieb(void);
signals:
    void EndGame(void);
};

#endif // GAMESCENE_H
