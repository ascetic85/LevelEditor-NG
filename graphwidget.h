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

protected:
    QGraphicsScene* m_scene;

    QRectF m_rect;
};

#endif // GRAPHWIDGET_H
