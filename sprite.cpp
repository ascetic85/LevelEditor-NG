#include "sprite.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

#include "Debug.h"

Sprite::Sprite(QGraphicsItem* parent, QGraphicsScene* scene)
    : QGraphicsPixmapItem(parent, scene)
{
    init();
}

Sprite::Sprite(QPixmap &pixmap, QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsPixmapItem(pixmap, parent, scene)
{
    init();
}

Sprite::Sprite(QString &file, QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsPixmapItem(QPixmap(file), parent, scene)
{
    init();
}

void Sprite::setZValue(qreal z)
{
    QGraphicsPixmapItem::setZValue(z);
}

void Sprite::init()
{
    setCacheMode(QGraphicsItem::ItemCoordinateCache);
}

void Sprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsPixmapItem::paint(painter, option, widget);

    // draw rect
    painter->setPen(QPen(Qt::red));
    painter->drawRect(this->pixmap().rect());
}
