#include "gameitem.h"

GameItem::GameItem(QString FILE, QGraphicsScene *s, QPointF pos, int m) : scene(s), mode(m)
{
    this->pixmap.load(FILE);
    s->addItem(this);
    this->setPos(pos);
}

GameItem::GameItem(QString FILE, QGraphicsScene *s, QPointF pos, QSize scale, int m) : scene(s), mode(m) {
    this->pixmap.load(FILE);
    this->pixmap = pixmap.scaled(scale, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    s->addItem(this);
    this->setPos(pos);
}

QRectF GameItem::boundingRect() const {
    if (mode == 0) {
        return QRectF(0, 0, this->pixmap.width(), this->pixmap.height());
    }
    else {
        return QRectF(-this->pixmap.width() / 2, -this->pixmap.height() / 2, this->pixmap.width(), this->pixmap.height());
    }
}

void GameItem::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) {
    if (mode == 0) {
        painter->drawPixmap(QRect(0, 0, this->pixmap.width(), this->pixmap.height()), this->pixmap);
    }
    else {
        painter->drawPixmap(QRect(-this->pixmap.width() / 2, -this->pixmap.height() / 2, this->pixmap.width(), this->pixmap.height()), this->pixmap);
    }
}
