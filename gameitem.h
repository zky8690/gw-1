#ifndef GAMEITEM_H
#define GAMEITEM_H
#include <QGraphicsItem>
#include <QPixmap>
#include <QString>
#include <QPointF>
#include <QGraphicsScene>
#include <QRectF>
#include <QPainter>
#include <QSize>
#include <QVariant>
#include <vector>
#include <algorithm>

class GameItem : public QGraphicsObject
{
public:
    GameItem(QString FILE, QGraphicsScene *s, QPointF pos, int m = 0);
    GameItem(QString FILE, QGraphicsScene *s, QPointF pos, QSize scale, int m = 0);
    QPixmap pixmap;
    QGraphicsScene *scene;
    int mode;

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
};

#endif // GAMEITEM_H
