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
    , m_aligmentItem(0)
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
        m_aligmentItem = item;

        m_prePos = event->posF();
        m_pressed = true;
        if (item) {
            // add child if pressed ctrl, otherwise set the selected
            // item as selected items
            if (event->modifiers() == Qt::ControlModifier) {
                if (!m_selectItems.contains(item)) {
                    m_selectItems.append(item);
                }
            }

            // copy
            else if (event->modifiers() == Qt::ShiftModifier) {
                QList<QGraphicsItem*> tmpList;
                foreach (QGraphicsItem* it, m_selectItems) {
                    Sprite* s = dynamic_cast<Sprite*> (it);
                    Sprite* news = new Sprite(s->pixmap());
                    news->setPos(s->pos());
                    tmpList.append(news);
                    m_scene->addItem(news);
                }
                m_selectItems = tmpList;
            }

            // show
            else {
                if (!m_selectItems.contains(item)) {
                    m_selectItems.clear();
                    m_selectItems.append(item);
                }
            }
        } else {
            // clear selected itmes and show mouse rect

            // clear
            m_selectItems.clear();
            m_aligmentItem = NULL;

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

void GraphWidget::copyAndPasteSelectedItem()
{
    foreach (QGraphicsItem* it, m_selectItems) {
        Sprite* s = dynamic_cast<Sprite*> (it);
        Sprite* news = new Sprite(s->pixmap());
        news->setPos(s->pos()+QPoint(10,10));
        m_scene->addItem(news);
    }
}

void GraphWidget::deleteSelectedItem()
{
    qDeleteAll(m_selectItems);
    m_selectItems.clear();
}

void GraphWidget::keyReleaseEvent(QKeyEvent *event)
{
    QSettings settings(Config::config(), Config::format());
    // delete sprite
    if (event->key() == settings.value(Config::KeyDel, Qt::Key_Delete)) {
        deleteSelectedItem();
    }

    //
    else if (event->key() == settings.value(Config::KeyTop, Qt::Key_T)) {
        alignmentTop();
    }

    else if (event->key() == settings.value(Config::KeyLeft, Qt::Key_L)) {
        alignmentLeft();
    }

    else if (event->key() == settings.value(Config::KeyRight, Qt::Key_R)) {
        alignmentRight();
    }

    else if (event->key() == settings.value(Config::KeyBottom, Qt::Key_B)) {
        alignmentBottom();
    }

    // copy / paste
    else if ((event->key() == settings.value(Config::KeyCopy, Qt::Key_C))
             && (event->modifiers() == settings.value(Config::KeyCopyModifiers, Qt::ControlModifier).toInt())) {
    }

    else if ((event->key() == settings.value(Config::KeyPaste, Qt::Key_V))
             && (event->modifiers() == settings.value(Config::KeyPasteModifers, Qt::ControlModifier).toInt())) {
        copyAndPasteSelectedItem();
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

void GraphWidget::alignment(Qt::Alignment alig)
{
    switch (alig) {
    case Qt::AlignLeft:
        alignmentLeft();
        break;

    case Qt::AlignRight:
        break;

    case Qt::AlignTop:
        alignmentLeft();
        break;

    case Qt::AlignBottom:
        break;

    default:
        break;
    }
}

/**
 * @brief 向上对齐
 */
void GraphWidget::alignmentTop()
{
    if (m_selectItems.count() && m_aligmentItem) {
        if (m_selectItems.contains(m_aligmentItem)) {
            foreach (QGraphicsItem* it, m_selectItems) {
                if (m_aligmentItem != it) {
                    it->setY(m_aligmentItem->y());
                }
            }
        }
    }
}

void GraphWidget::alignmentBottom()
{
    if (m_selectItems.count() && m_aligmentItem) {
        if (m_selectItems.contains(m_aligmentItem)) {
            int b = m_aligmentItem->y()+m_aligmentItem->boundingRect().size().height();
            // b = it.height+y
            foreach (QGraphicsItem* it, m_selectItems) {
                if (m_aligmentItem != it) {
                    int y = b - it->boundingRect().size().height();
                    it->setY(y);
                }
            }
        }
    }
}

/**
 * @brief 向左对齐
 */
void GraphWidget::alignmentLeft()
{
    if (m_selectItems.count() && m_aligmentItem) {
        if (m_selectItems.contains(m_aligmentItem)) {
            foreach (QGraphicsItem* it, m_selectItems) {
                if (m_aligmentItem != it) {
                    it->setX(m_aligmentItem->x());
                }
            }
        }
    }
}

void GraphWidget::alignmentRight()
{
    if (m_selectItems.count() && m_aligmentItem) {
        if (m_selectItems.contains(m_aligmentItem)) {
            int r = m_aligmentItem->x() + m_aligmentItem->boundingRect().size().width();
            //  r = it.width+x;
            foreach (QGraphicsItem* it, m_selectItems) {
                if (m_aligmentItem != it) {
                    int x =  r - it->boundingRect().size().width();
                    it->setX(x);
                }
            }
        }
    }
}
