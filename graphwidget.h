#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include <QRectF>

QT_BEGIN_NAMESPACE
class QGraphicsScene;
QT_END_NAMESPACE

class GraphWidget : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphWidget(QWidget *parent = 0);

    void scaleBy(double factor);
    void zoomIn();
    void zoomOut();

protected:
    virtual void wheelEvent(QWheelEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

    virtual void keyReleaseEvent(QKeyEvent *event);

    virtual void drawForeground(QPainter *painter, const QRectF &rect);

protected:
    QGraphicsScene* m_scene;

    QRectF m_rect;
    bool m_pressed;
    qreal m_scaleFactor;
    QPointF m_prePos;
    QGraphicsItem *m_selectItem;
    QVector<QGraphicsItem*> m_selectItems;
};

#endif // GRAPHWIDGET_H
