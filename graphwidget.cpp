#include "graphwidget.h"

#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include <QWheelEvent>
#include <QApplication>
#include <QUrl>

#include "sprite.h"
#include "config.h"
#include "Debug.h"

GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent)
    , m_scene(new QGraphicsScene())
    , m_scaleFactor(1)
    , m_pressed(false)
{
    QSettings settings(Config::config(), Config::format());
    int w = settings.value(Config::editorw, Config::w).toReal();
    int h = settings.value(Config::editorh, Config::h).toReal();

    this->setScene(m_scene);
    this->setSceneRect(0,0,w,h);

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

    // mouse rect
    m_mouseRectItem.setRect(0,0,1,1);
    m_mouseRectItem.setBrush(QBrush(QColor(200,200,200,100)));
    m_mouseRectItem.hide();
    m_mouseRectItem.setZValue(100);
    m_scene->addItem(&m_mouseRectItem);

    // controller
    m_controllerItem.setRect(0,0,100,100);
    m_controllerItem.setBrush(QBrush(QColor(255,0,0,100)));
    m_controllerItem.hide();
    m_controllerItem.setZValue(100);
    m_scene->addItem(&m_controllerItem);
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

/**
 * @brief GraphWidget::mousePressEvent
 * @param event
 *
 * - Operation of object is like folder on windows/mac/..
 */
void GraphWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QGraphicsItem *item = itemAt(event->pos());

        m_prePos = event->posF();
        m_pressed = true;
        if (item) {
            // add child if pressed ctrl, otherwise set the selected
            // item as selected items
            if (event->modifiers() == Qt::ControlModifier) {
                if (!m_selectItems.contains(item)) {
                    m_selectItems.append(item);
                }

            } else {
                if (!m_selectItems.contains(item)) {
                    m_selectItems.clear();
                    m_selectItems.append(item);
                }
            }
        } else {
            // clear selected itmes and show mouse rect

            // clear
            m_selectItems.clear();

            // show rect
            m_mouseStartPoint = mapToScene(event->pos());
            m_mouseRectItem.setRect(m_mouseRectItem.x()
                                    , m_mouseRectItem.y(),1,1);
        }
    }
    QGraphicsView::mousePressEvent(event);
}

void GraphWidget::mouseReleaseEvent(QMouseEvent * event)
{
    m_pressed = false;

    // select the items which in the mouse rect
    if (m_mouseRectItem.isVisible()) {
        QList<QGraphicsItem*> list = m_mouseRectItem.collidingItems();

        // todo: ctrl - select
        if (event->modifiers() == Qt::ControlModifier) {
//            QSet<QGraphicsItem*> ret = (list.toSet() | m_selectItems.toSet())
//                    - (list.toSet() - m_selectItems.toSet());
//            list = ret.toList();
        }
        m_selectItems = list;
    }

    m_mouseRectItem.hide();
    QGraphicsView::mouseReleaseEvent(event);
}

void GraphWidget::mouseMoveEvent(QMouseEvent *event)
{
    // move items if there are, otherwise show mouse rect
    if (m_pressed) {
        if (m_selectItems.count()) {
            foreach (QGraphicsItem* it, m_selectItems) {
                QPointF delta = event->posF() - m_prePos;
                it->setPos(delta + it->pos());
            }
            m_prePos =event->posF();
        } else {
            QPointF p = mapToScene(event->pos());
            showMouseRect(m_mouseStartPoint.toPoint(), p.toPoint());
        }
    }

    QGraphicsView::mouseMoveEvent(event);
}

void GraphWidget::keyReleaseEvent(QKeyEvent *event)
{
    // delete sprite
    if (event->key() == Qt::Key_Delete) {
        qDeleteAll(m_selectItems);
        m_selectItems.clear();
    }

    QGraphicsView::keyReleaseEvent(event);
}

void GraphWidget::paintEvent(QPaintEvent * event)
{
    QGraphicsView::paintEvent(event);
}

void GraphWidget::dragEnterEvent(QDragEnterEvent *event)
{
    event->accept();
}

void GraphWidget::dragMoveEvent(QDragMoveEvent *event)
{
    event->accept();
}

void GraphWidget::dropEvent(QDropEvent *event)
{
    if (m_scene) {
        QUrl url = event->mimeData()->urls().at(0);
        QString file = url.toLocalFile();
        QPixmap pixmap(file);
        if (!pixmap.isNull()) {
            Sprite *sprite = new Sprite(QPixmap(url.toLocalFile()));
            sprite->setPos(mapToScene(event->pos()));
            m_scene->addItem(sprite);
        } if (file.endsWith(".pshs")) {

        } else if (file.endsWith(".plist")) {

        }
    }
}

void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    QGraphicsView::drawBackground(painter, rect);

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
}

void GraphWidget::showMouseRect(QPoint start, QPoint end)
{
    int x = start.x();
    int y = start.y();
    int w = end.x() - start.x();
    int h = end.y() - start.y();

    if (w < 0) x = end.x();
    if (h < 0) y = end.y();

    m_mouseRectItem.show();
    m_mouseRectItem.setRect(x,y, abs(w),abs(h));
}

void GraphWidget::hideControllerItem()
{
    m_controllerItem.hide();
}

void GraphWidget::showControllerItem(QPointF pos)
{
    m_controllerItem.show();
    m_controllerItem.setPos(pos);
}

void GraphWidget::showControllerItem(QPoint pos)
{
    m_controllerItem.show();
    m_controllerItem.setPos(pos);
}
