#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include <QRectF>
#include <QHash>

QT_BEGIN_NAMESPACE
class QGraphicsScene;
QT_END_NAMESPACE

class GraphWidget : public QGraphicsView
{
    Q_OBJECT
public:
    enum DeviceType { iPhone480x320 = 1
                      , iPhone960x640
                    };

    explicit GraphWidget(QWidget *parent = 0);

    void scaleBy(double factor);
    void zoomIn();
    void zoomOut();

    void setUpright(bool yes, DeviceType type);

protected:
    void init();

    virtual void wheelEvent(QWheelEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

    virtual void keyReleaseEvent(QKeyEvent *event);

    virtual void drawBackground(QPainter *painter, const QRectF &rect);
    virtual void drawForeground(QPainter *painter, const QRectF &rect);

protected:
    QGraphicsScene* m_scene;

    QRectF m_rect;
    bool m_pressed;
    qreal m_scaleFactor;
    QPointF m_prePos;
    QGraphicsItem *m_selectItem;
    QVector<QGraphicsItem*> m_selectItems;

    QPixmap m_bgFrame;

    // for show background frame
    QHash<DeviceType, QString> m_frames;
    QHash<DeviceType, QString> m_framevs;
    QHash<DeviceType, QPoint>   m_framePoint;
    QHash<DeviceType, QPoint>   m_framevPoint;
    QPoint              m_frameStartPoint;
};

#endif // GRAPHWIDGET_H
