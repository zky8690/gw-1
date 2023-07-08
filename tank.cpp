#include "tank.h"
using namespace std;

Tank::Tank(QString File,QGraphicsScene *s, QPointF pos, QSize scale) : GameItem(File, s, pos, scale, 1), isDying(0)
{
    this->setData(0, QVariant(QString("Tank")));
    setRotation(QRandomGenerator::global()->bounded(360.0));
    speed = 2 * this->pixmap.width();
    memset(this->KeyPressed, 0, sizeof KeyPressed);
    tanktimer = new QTimer(this);
    tanktimer->setSingleShot(true);

    sound = new QSoundEffect;
    sound->setSource(QUrl::fromLocalFile(":/music/bomb.wav"));
}

void Tank::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if (isDying > 0) {
        int order = isDying / (int)(fps / 10) + 1;
        QString str = ":/img/explosion/explosion" + QString::number(order) + ".png";
        this->pixmap.load(str);
        //qDebug()<<isDying<<" "<<order<<" "<<str;
        isDying++;
    }

    painter->drawPixmap(QRect(-this->pixmap.width() / 2, -this->pixmap.height() / 2, this->pixmap.width(), this->pixmap.height()), this->pixmap);
}



void Tank::advance(int phase) {
    if (isDying / (int)(fps / 10) + 1 == 6) {
        this->hide();
        this->scene->removeItem(this);
        return;
    }
    if (isDying > 0) {
        this->scene->update();
        emit ImDead();
        return;
    }

    auto itemslist = this->collidingItems();
    vector<int> sid;
    for (auto it = itemslist.begin(); it != itemslist.end(); ++ it) {
        if ((*it)->data(0) == "Bullet" && ((*it)->data(1) == false || (*it)->data(2) != this->data(2))) {
            isDying = 1;
            if(music)
            {
                sound->setVolume((float)qitayinliang / 100);
                sound->play();
            }
            Bullet *tmp = (Bullet*) (*it);
            tmp->Disappear();
            return;
        }
        if ((*it)->data(0) == "Wall") {
            QPointF tankpos = this->mapToScene(0, 0);
            QPointF wallpos = (*it)->mapToScene(0, 0);
            QLineF line = QLineF(wallpos, tankpos);
            if (line.angle() <= 45 || line.angle() >= 315) {
                sid.push_back(3);
            }
            else if (line.angle() > 45 && line.angle() <= 135) {
                sid.push_back(0);
            }
            else if (line.angle() > 135 && line.angle() <= 225) {
                sid.push_back(2);
            }
            else {
                sid.push_back(1);
            }
        }
    }
    sort(sid.begin(),sid.end());
    int total = unique(sid.begin(),sid.end()) - sid.begin();
    if (this->KeyPressed[2]) {
        this->setRotation(this->rotation() - this->rotatespeed / fps);
    }
    if (this->KeyPressed[3]) {
        this->setRotation(this->rotation() + this->rotatespeed / fps);
    }
    QPointF tankpos = this->mapToScene(0, 0);
    qreal mu = 0.5;
    int side = -1;
    if (this->KeyPressed[0]) {
        if (total >= 2)
        {
            int side1 = sid[0];
            int side2 = sid[1];

            if (qCos(qDegreesToRadians(this->rotation())) < 0 && qSin(qDegreesToRadians(this->rotation())) < 0) //side = -2是为了进入墙角倒车的判断
            {
                if (side1 == 1 && side2 == 3){side = 3;}
                if (side1 == 0 && side2 == 2){side = 0;}
                if (side1 == 1 && side2 == 2){side = -2;}
            }
            else if (qCos(qDegreesToRadians(this->rotation())) < 0 && qSin(qDegreesToRadians(this->rotation())) > 0)
            {
                if (side1 == 1 && side2 == 2){side = 2;}
                if (side1 == 0 && side2 == 3){side = 0;}
                if (side1 == 1 && side2 == 3){side = -2;}
            }
            else if (qCos(qDegreesToRadians(this->rotation())) > 0 && qSin(qDegreesToRadians(this->rotation())) < 0)
            {
                if (side1 == 1 && side2 == 2){side = 1;}
                if (side1 == 0 && side2 == 3){side = 3;}
                if (side1 == 0 && side2 == 2){side = -2;}
            }
            else if (qCos(qDegreesToRadians(this->rotation())) > 0 && qSin(qDegreesToRadians(this->rotation())) > 0)
            {
                if (side1 == 0 && side2 == 2){side = 2;}
                if (side1 == 1 && side2 == 3){side = 1;}
                if (side1 == 0 && side2 == 3){side = -2;}
            }
            else if (side1 == side2){side = side1;}
            if (side == -1)
            {
                return;
            }
        }
        else if (total == 1)
        {
            side = sid[0];

        }
        if (side == 0 && qCos(qDegreesToRadians(this->rotation())) < 0) {
            tankpos.setX(tankpos.x() + speed * mu * qSin(qDegreesToRadians(this->rotation())) / fps);
            this->setPos(tankpos);
        }
        else if (side == 1 && qCos(qDegreesToRadians(this->rotation())) > 0) {
            tankpos.setX(tankpos.x() + speed * mu * qSin(qDegreesToRadians(this->rotation())) / fps);
            this->setPos(tankpos);
        }
        else if (side == 2 && qSin(qDegreesToRadians(this->rotation())) > 0) {
            tankpos.setY(tankpos.y() - speed * mu * qCos(qDegreesToRadians(this->rotation())) / fps);
            this->setPos(tankpos);
        }
        else if (side == 3 && qSin(qDegreesToRadians(this->rotation())) < 0) {
            tankpos.setY(tankpos.y() - speed * mu * qCos(qDegreesToRadians(this->rotation())) / fps);
            this->setPos(tankpos);
        }
        else {
            this->setPos(mapToScene(0, -speed / fps));
        }

    }
    if (this->KeyPressed[1]) {
        if (total >= 2)
        {
            int side1 = sid[0];
            int side2 = sid[1];
            //qDebug()<<side1<<" "<<side2;
            //qDebug()<<qCos(qDegreesToRadians(this->rotation()))<<" "<<qSin(qDegreesToRadians(this->rotation()));
            if (qCos(qDegreesToRadians(this->rotation())) > 0 && qSin(qDegreesToRadians(this->rotation())) > 0) //side = -2是为了进入墙角倒车的判断
            {
                if (side1 == 1 && side2 == 3){side = 3;}
                if (side1 == 0 && side2 == 2){side = 0;}
                if (side1 == 1 && side2 == 2) {side = -2;}
            }
            else if (qCos(qDegreesToRadians(this->rotation())) > 0 && qSin(qDegreesToRadians(this->rotation())) < 0)
            {
                if (side1 == 1 && side2 == 2){side = 2;}
                if (side1 == 0 && side2 == 3){side = 0;}
                if (side1 == 1 && side2 == 3){side = -2;}
            }
            else if (qCos(qDegreesToRadians(this->rotation())) < 0 && qSin(qDegreesToRadians(this->rotation())) > 0)
            {
                if (side1 == 1 && side2 == 2){side = 1;}
                if (side1 == 0 && side2 == 3){side = 3;}
                if (side1 == 0 && side2 == 2){side = -2;}

            }
            else if (qCos(qDegreesToRadians(this->rotation())) < 0 && qSin(qDegreesToRadians(this->rotation())) < 0)
            {
                if (side1 == 0 && side2 == 2){side = 2;}
                if (side1 == 1 && side2 == 3){side = 1;}
                if (side1 == 0 && side2 == 3){side = -2;}
            }
            else if (side1 == side2){side = side1;}
            if (side == -1)
            {
                return;
            }
        }
        else if (total == 1)
        {
            side = sid[0];

        }
        if (side == 0 && qCos(qDegreesToRadians(this->rotation())) > 0) {
            tankpos.setX(tankpos.x() - speed * mu * qSin(qDegreesToRadians(this->rotation())) / fps);
            this->setPos(tankpos);
        }
        else if (side == 1 && qCos(qDegreesToRadians(this->rotation())) < 0) {
            tankpos.setX(tankpos.x() - speed * mu * qSin(qDegreesToRadians(this->rotation())) / fps);
            this->setPos(tankpos);
        }
        else if (side == 2 && qSin(qDegreesToRadians(this->rotation())) < 0) {
            tankpos.setY(tankpos.y() + speed * mu * qCos(qDegreesToRadians(this->rotation())) / fps);
            this->setPos(tankpos);
        }
        else if (side == 3 && qSin(qDegreesToRadians(this->rotation())) > 0) {
            tankpos.setY(tankpos.y() + speed * mu * qCos(qDegreesToRadians(this->rotation())) / fps);
            this->setPos(tankpos);
        }
        else {
            this->setPos(mapToScene(0, speed / fps));
        }
    }

}
