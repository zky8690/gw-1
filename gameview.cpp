#include "gameview.h"

GameView::GameView(QWidget * p) : QGraphicsView(p)
{
    QSize siz(m * unit + 5, n * unit + 5);
    this->grabKeyboard();
    this->setFixedSize(siz);
    scene = new GameScene();
    scene->setSceneRect(0, 0, this->width() - 2, this->height() - 2);
    this->setScene(scene);
    this->connect(scene,SIGNAL(EndGame()),this,SLOT(vDestroy()));

}

void GameView::vDestroy(void)
{
    emit nextloop();
    delete this;
}


