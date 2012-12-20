#ifndef SPRITE_H
#define SPRITE_H

#include <QGraphicsPixmapItem>

class Sprite : public QGraphicsPixmapItem
{
public:
    Sprite(QGraphicsItem* parent = 0, QGraphicsScene* scene = 0);
    Sprite(QPixmap& pixmap, QGraphicsItem* parent = 0, QGraphicsScene* scene = 0);

    Sprite(QString& file, QGraphicsItem* parent = 0, QGraphicsScene* scene = 0);

    /**
     * @brief setZValue
     * @param z : Is diffrent with cocos2d-x/cocos2d-iphone..
     */
    void setZValue(qreal z);

protected:
    /**
     * @brief init
     * - init the necessarily data
     */
    void init();

    /**
     * @brief paint
     * - draw rect around the sprite
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // SPRITE_H
