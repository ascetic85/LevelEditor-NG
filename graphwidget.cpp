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

//    m_scene->addRect(0,0,w,h, QPen(Qt::red, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin));
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
    if (event->button() == Qt::LeftButton) {
        QGraphicsItem *item = itemAt(event->pos());
        m_pressed = true;
        m_prePos = event->posF();

        if (event->modifiers() == Qt::ControlModifier) {
            if (item && !m_selectItems.contains(item)) {
                m_selectItems.append(item);
            }
        }
        else {
            if (item) {
                m_selectItem = item;
            }
        }
    }

    // just for test, add sprite
    else if (event->button() == Qt::RightButton && event->modifiers() == Qt::NoModifier) {
        Sprite *sprite = new Sprite(QString("resource/1.png"), 0, m_scene);
        sprite->setPos(event->pos());
    }
}

void GraphWidget::mouseReleaseEvent(QMouseEvent * /*event*/)
{
    m_pressed = false;

    m_selectItem = NULL;
}

void GraphWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_pressed) {
        // for one
        if (m_selectItem) {
            QPointF delta = event->posF() - m_prePos + m_selectItem->pos();
            m_prePos = event->posF();
            m_selectItem->setPos(delta);
        }

        // for some
        if (event->modifiers() == Qt::ControlModifier && !m_selectItems.isEmpty()) {
            foreach (QGraphicsItem* it, m_selectItems) {
                QPointF delta = event->posF() - m_prePos + it->pos();
                it->setPos(delta);
            }
            m_prePos = event->posF();
        }
    }
}

void GraphWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Control) {
        Debug() << "Clear all selected items";
        m_selectItems.clear();
    }
}

void GraphWidget::drawForeground(QPainter *painter, const QRectF &rect)
{
    QGraphicsView::drawForeground(painter, rect);

    painter->setPen(QPen(Qt::red));
    painter->drawRect(sceneRect());
}


