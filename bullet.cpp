#include "bullet.h"

Bullet::Bullet(QString File,QGraphicsScene *s, QPointF pos, qreal distance) : GameItem(File,s,pos,QSize(unit / 4,unit / 3),1), speed(2.6 * unit)
{
    setData(0, QVariant(QString("Bullet")));
    timer = new QTimer;
    timer->start(10000);
    this->connect(timer, SIGNAL(timeout()), this, SLOT(Disappear()));
    boretimer = new QTimer(this);
    boretimer->setSingleShot(true);
    boretimer->start((distance + this->pixmap.height() / 2 + 1) * 1000 / speed);
    this->setData(1, boretimer->isActive());
    sound = new QSoundEffect;
    sound->setSource(QUrl::fromLocalFile(":/music/bong_003.wav"));
}

Bullet::~Bullet() {
    timer->stop();
    delete timer;
    delete boretimer;
    sound->stop();
}
void Bullet::Disappear() {
    this->hide();
    delete this;
}

void Bullet::advance(int phase) {
    this->setPos(this->mapToScene(0, -speed / fps));
    this->setData(1, boretimer->isActive());
    auto itemslist = this->collidingItems();
    vector<int> sid;
    for (auto it = itemslist.begin(); it != itemslist.end(); ++ it) {
        if ((*it)->data(0) == "Wall") {
            QPointF bulletpos = this->mapToScene(0, 0);
            QPointF wallpos = (*it)->mapToScene(0, 0);
            QLineF line = QLineF(wallpos, bulletpos);
            Wall * w = (Wall*)(*it);
            if (line.angle() + eps <= 45 || line.angle() + eps >= 315) {
                qDebug()<<w->canBeTouched[3];
                if (w->canBeTouched[3])
                    sid.push_back(3);
            }
            else if (line.angle() + eps > 45 && line.angle() + eps <= 135) {
                qDebug()<<w->canBeTouched[0];
                if (w->canBeTouched[0])
                    sid.push_back(0);
            }
            else if (line.angle() + eps > 135 && line.angle() + eps <= 225) {
                qDebug()<<w->canBeTouched[2];
                if (w->canBeTouched[2])
                    sid.push_back(2);
            }
            else {
                qDebug()<<w->canBeTouched[1];
                if (w->canBeTouched[1])
                    sid.push_back(1);
            }
        }
    }
    sort(sid.begin(), sid.end());
    int total = unique(sid.begin(), sid.end()) - sid.begin();

    if (total >= 2) {
//        qDebug()<<sid[0]<<" "<<sid[1];

        if(music)
        {
            sound->setVolume((float)qitayinliang / 100);
            sound->play();
        }
        this->setRotation(this->rotation() + 180);
        this->setPos(this->mapToScene(0, -speed / fps));
    }
    else if (total > 0) { // total == 1
        if(music)
        {
            sound->setVolume((float)qitayinliang / 100);
            sound->play();
        }
        int side = sid[0];
        if (side == 1 && qCos(qDegreesToRadians(this->rotation())) < 0){
//            qDebug()<<1;
            return;
        }
        if (side == 0 && qCos(qDegreesToRadians(this->rotation())) > 0){
//            qDebug()<<1;
            return;
        }
        if (side == 2 && qSin(qDegreesToRadians(this->rotation())) < 0){
//            qDebug()<<1;
            return;
        }
        if (side == 3 && qSin(qDegreesToRadians(this->rotation())) > 0){
//            qDebug()<<1;
            return;
        }
        if (side == 0 || side == 1) {
            this->setRotation(180 - this->rotation());
            this->setPos(this->mapToScene(0, -speed / fps));
        }
        if (side == 2 || side == 3) {
            this->setRotation(-this->rotation());
            this->setPos(this->mapToScene(0, -speed / fps));
        }
    }

}
