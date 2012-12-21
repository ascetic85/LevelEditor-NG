#ifndef SPRITE_H
#define SPRITE_H

#include <QGraphicsPixmapItem>
#include <QObject>


class Sprite :  public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_ENUMS(FocusLevel)
//    Q_PROPERTY(QString title READ title WRITE setTitle USER true)
    Q_PROPERTY(FocusLevel focusLevel READ focusLevel WRITE setFocusLevel)

public:
    enum FocusLevel { None, SelectAndFocus, SelectNoFocus };

    Sprite(QGraphicsItem* parent = 0, QGraphicsScene* scene = 0);
    Sprite(QPixmap& pixmap, QGraphicsItem* parent = 0, QGraphicsScene* scene = 0);

    Sprite(QString& file, QGraphicsItem* parent = 0, QGraphicsScene* scene = 0);

    /**
     * @brief setZValue
     * @param z : --Is diffrent with cocos2d-x/cocos2d-iphone..--
     */
    void setZValue(qreal z);

    /// property function
    FocusLevel focusLevel();
    void setFocusLevel(Sprite::FocusLevel level);

    /// property function end ///

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

protected:
    /// property
    FocusLevel m_focusLevel;
    /// property end
};

#endif // SPRITE_H
