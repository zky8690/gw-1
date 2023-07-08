#ifndef GAMEVIEW_H
#define GAMEVIEW_H
#include <QGraphicsView>
#include <QWidget>
#include <string>
#include "gamescene.h"
#include <QBrush>
#include <QPixmap>
#include <iostream>
#include <fstream>
#include "MyConstants.h"

using namespace std;

class GameView : public QGraphicsView
{
    Q_OBJECT
public:
    GameView(QWidget * p);
    GameScene *scene;
signals:
    void nextloop(void);
public slots:
    void vDestroy(void);
};

#endif // GAMEVIEW_H
