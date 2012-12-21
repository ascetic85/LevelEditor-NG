#include "graphwidget.h"

#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include <QWheelEvent>
#include <QApplication>

#include "sprite.h"
#include "config.h"

#include "Debug.h"

GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent)
    , m_scene(new QGraphicsScene())
    , m_scaleFactor(1)
    , m_selectItem(NULL)
{
    QSettings settings(Config::config(), Config::format());
    int w = settings.value(Config::editorw, Config::w).toReal();
    int h = settings.value(Config::editorh, Config::h).toReal();

    this->setScene(m_scene);
    this->setSceneRect(0,0,w,h);

    QGraphicsTextItem* t = m_scene->addText("Scene here");
    t->setPos(w/2, h/2);

    QPolygonF polygon;
    polygon << QPointF(0, 0) << QPointF(w, h);
    m_scene->addPolygon(polygon);

    init();
//    m_scene->addRect(0,0,w,h, QPen(Qt::red, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin));

    setUpright(false, iPhone480x320);
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

void GraphWidget::setUpright(bool yes, DeviceType type)
{
    if (yes) {
        m_bgFrame.load(m_frames.value(type));
        m_frameStartPoint = m_framePoint.value(type);
    }
    else {
        m_bgFrame.load(m_framevs.value(type));
        m_frameStartPoint = m_framevPoint.value(type);
    }
}

void GraphWidget::init()
{
    m_frames.insert(iPhone480x320, "resource/4frame.png");
    m_frames.insert(iPhone960x640, "resource/fframe@2x.png");

    m_framevs.insert(iPhone480x320, "resource/4frame-v.png");
    m_framevs.insert(iPhone960x640, "resource/fframe@2x-v.png");

    m_framePoint.insert(iPhone480x320, QPoint(0,0));
    m_framePoint.insert(iPhone480x320, QPoint(0,0));

    m_framevPoint.insert(iPhone480x320, QPoint(-119,-23));
    m_framevPoint.insert(iPhone960x640, QPoint(0,0));

    //
    m_mouseRectItem.setRect(0,0,1,1);
    m_mouseRectItem.setBrush(QBrush(QColor(200,200,200,100)));
    m_mouseRectItem.hide();
    m_mouseRectItem.setZValue(100);
    m_scene->addItem(&m_mouseRectItem);
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

    QGraphicsView::wheelEvent(event);
}

void GraphWidget::mousePressEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton) {
        QGraphicsItem *item = itemAt(event->pos());
        m_pressed = true;
        m_prePos = event->posF();

        m_mouseStartPoint = mapToScene(event->pos());
        m_mouseRectItem.setRect(m_mouseRectItem.x(), m_mouseRectItem.y(),1,1);

        if (event->modifiers() == Qt::ControlModifier) {
            if (item && !m_selectItems.contains(item)) {
                m_selectItems.append(item);
            } else {
                m_mouseRectItem.show();
            }
        }
        else {
            if (item) {
                m_selectItem = item;
            } else {
                m_mouseRectItem.show();
            }
        }
    }

    // just for test, add sprite
    else if (event->button() == Qt::RightButton && event->modifiers() == Qt::NoModifier) {
        Sprite *sprite = new Sprite(QString("resource/1.png"), 0, m_scene);
        sprite->setPos(mapToScene(event->pos()));
    }

    QGraphicsView::mousePressEvent(event);
}

void GraphWidget::mouseReleaseEvent(QMouseEvent * event)
{
    m_pressed = false;

    m_selectItem = NULL;

    m_mouseRectItem.hide();
    QGraphicsView::mouseReleaseEvent(event);
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

        // draw mouse rect
        QPointF p = mapToScene(event->pos());
        showMouseRect(m_mouseStartPoint.toPoint(), p.toPoint());
    }

    QGraphicsView::mouseMoveEvent(event);
}

void GraphWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Control) {
        Debug() << "Clear all selected items";
        m_selectItems.clear();
    }

    QGraphicsView::keyReleaseEvent(event);
}

void GraphWidget::paintEvent(QPaintEvent * event)
{
    QGraphicsView::paintEvent(event);
}

void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    QGraphicsView::drawBackground(painter, rect);

//    painter->setPen(QPen(Qt::red));
//    painter->drawEllipse(100,100,100,100);

    if (!m_bgFrame.isNull()) {
        painter->drawPixmap(m_frameStartPoint, m_bgFrame);
    }
}

void GraphWidget::drawForeground(QPainter *painter, const QRectF &rect)
{
    QGraphicsView::drawForeground(painter, rect);

    // view rect
    painter->setPen(QPen(Qt::red));
    painter->drawRect(sceneRect());

#if 0
    // draw coor
    QPoint offset(-5,-5);
    painter->setPen(QPen(QBrush(Qt::red), 3));
    painter->drawLine(sceneRect().bottomLeft()+offset, offset);
    painter->drawLine(sceneRect().bottomLeft()-offset, sceneRect().bottomRight()-offset);
#endif
}

void GraphWidget::showMouseRect(QPoint start, QPoint end)
{
    int x = start.x();
    int y = start.y();
    int w = end.x() - start.x();
    int h = end.y() - start.y();

    if (w < 0) x = end.x();
    if (h < 0) y = end.y();

    m_mouseRectItem.setRect(x,y, abs(w),abs(h));
}
