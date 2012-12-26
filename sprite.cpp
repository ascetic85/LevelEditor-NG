#include "sprite.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QKeyEvent>

#include "Debug.h"


class PointCtl : public QObject, public QGraphicsRectItem
{
public:
    PointCtl(QGraphicsItem* parent = 0, QGraphicsScene *scene = 0)
        : QGraphicsRectItem(parent, scene)
    {
//        setAcceptedMouseButtons(Qt::NoButton);
    }


Q_SIGNALS:
    void offset(QPointF);
};

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

Sprite::FocusLevel Sprite::focusLevel()
{
    return m_focusLevel;
}

void Sprite::setFocusLevel(Sprite::FocusLevel level)
{
    m_focusLevel = level;
}

void Sprite::init()
{
    setCacheMode(QGraphicsItem::ItemCoordinateCache);
    m_focusLevel = Sprite::None;
}

void Sprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsPixmapItem::paint(painter, option, widget);

    // draw rect
    if (m_focusLevel == Sprite::None) {
        painter->setPen(QPen(Qt::red));
        painter->drawRect(this->pixmap().rect());
    } else if (m_focusLevel == Sprite::SelectAndFocus) {


    } else if (m_focusLevel == Sprite::SelectNoFocus) {

    }
}

void Sprite::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_prePos = event->pos().toPoint();
}

void Sprite::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPoint delta = event->pos().toPoint() - m_prePos;
    setPos(pos()+delta);
}

void Sprite::mouseReleaseEvent(QGraphicsSceneMouseEvent * /*event*/)
{
    ungrabMouse();
}
