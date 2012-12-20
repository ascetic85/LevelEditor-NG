#include "graphwidget.h"

#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include <QWheelEvent>
#include <QApplication>

#include "sprite.h"

#include "Debug.h"

GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent)
    , m_scene(new QGraphicsScene())
    , m_scaleFactor(1)
    , m_selectItem(NULL)
{
    int w(480);
    int h(320);

    this->setScene(m_scene);
    this->setSceneRect(0,0,w,h);

    QGraphicsTextItem* t = m_scene->addText("Scene here");
    t->setPos(w/2, h/2);

    QPolygonF polygon;
    polygon << QPointF(0, 0) << QPointF(w, h);
    m_scene->addPolygon(polygon);

    m_scene->addRect(0,0,w,h, QPen(Qt::red, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin));

    Sprite *sprite = new Sprite(QPixmap("resource/1.png"), 0, m_scene);
    sprite->setPos(100, 100);

#if 0
    QGraphicsPixmapItem* pix = m_scene->addPixmap(QPixmap("resource/1.png"));
    pix->setPos(100,100);

    pix->setRotation(80);

    QGraphicsPixmapItem* pix2 = new QGraphicsPixmapItem(QPixmap("resource/1.png")
                                                        , pix, m_scene);

    pix2->setPos(10, 10);
    pix2->setZValue(1);

    pix2->rotate(-90);

    pix2 = new QGraphicsPixmapItem(QPixmap("resource/1.png")
                                                        , pix2, m_scene);

    pix2->setPos(30, 30);
    pix2->setZValue(0);
#endif
}

void GraphWidget::scaleBy(double factor)
{
    scale(factor, factor);
}

void GraphWidget::zoomIn()
{
    scaleBy(1.1);
}

void GraphWidget::zoomOut()
{
    scaleBy(1.0 / 1.1);
}

void GraphWidget::wheelEvent(QWheelEvent *event)
{
    if (event->modifiers() == Qt::ControlModifier)
     {
         scaleBy(std::pow(4.0 / 3.0, (-event->delta() / 240.0)));
     }
     else
     {
         QGraphicsView::wheelEvent(event);
     }
}

void GraphWidget::mousePressEvent(QMouseEvent *event)
{
//    Debug() << Q_FUNC_INFO << event->pos();
    m_pressed = true;
    m_prePos = event->posF();

    QGraphicsItem *item = itemAt(event->pos());
    if (item) {
        m_selectItem = item;
    }
}

void GraphWidget::mouseReleaseEvent(QMouseEvent */*event*/)
{
//    Debug() << Q_FUNC_INFO << event->pos();
    m_pressed = false;

    m_selectItem = NULL;
}

void GraphWidget::mouseMoveEvent(QMouseEvent *event)
{
//    Debug() << Q_FUNC_INFO << event->pos() << this->mapToScene(event->pos());

    if (m_selectItem) {
        QPointF delta = event->posF() - m_prePos + m_selectItem->pos();
        m_prePos = event->posF();
        m_selectItem->setPos(delta);
    }
}

