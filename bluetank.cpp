#include "bluetank.h"




Bluetank::Bluetank(QGraphicsScene *s, QPointF pos, QSize scale) : Tank(":/img/tank_blue.png",s,pos,scale)
{
    this->setData(2, QString("Blue"));
}


void Bluetank::advance(int phase) {
    Tank::advance(phase);
    //()<<this->tanktimer->remainingTime();
    if (this->KeyPressed[4] && this->tanktimer->remainingTime() <= 0 && Bluebullet::cnt < 5) {
        if(music)
        {
            QSoundEffect* sound = new QSoundEffect();
            sound->setVolume((float)qitayinliang / 100);
            sound->setSource(QUrl::fromLocalFile(":/music/shoot.wav"));
            sound->play();
        }

        Bluebullet * bullet = new Bluebullet(this->scene, this->mapToScene(0, 0), this->pixmap.height() / 2 + this->speed);
        bullet->setRotation(this->rotation());
        //bullet->setPos(bullet->mapToScene(0, +bullet->pixmap.height() / 2 + 1));

        tanktimer->start(200);
    }
}
