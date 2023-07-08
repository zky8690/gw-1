#include "greentank.h"

Greentank::Greentank(QGraphicsScene *s, QPointF pos, QSize scale) : Tank(":/img/tank_green.png",s,pos,scale)
{
    this->setData(2, QString("Green"));
}

void Greentank::advance(int phase) {
    Tank::advance(phase);
    if (this->KeyPressed[4] && this->tanktimer->remainingTime() <= 0 && Greenbullet::cnt < 5) {
        if(music)
        {
            QSoundEffect* sound = new QSoundEffect();
            sound->setVolume((float)qitayinliang / 100);
            sound->setSource(QUrl::fromLocalFile(":/music/shoot.wav"));
            sound->play();
        }

        Greenbullet * bullet = new Greenbullet(this->scene, this->mapToScene(0, 0), this->pixmap.height() / 2 + this->speed);
        bullet->setRotation(this->rotation());
        //bullet->setPos(bullet->mapToScene(0, +bullet->pixmap.height() / 2 + 1));

        tanktimer->start(200);
    }
}
