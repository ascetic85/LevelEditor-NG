#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QRectF>
#include <QHash>

QT_BEGIN_NAMESPACE
class QGraphicsScene;
QT_END_NAMESPACE

#include "controller.h"

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


public Q_SLOTS:
    /**
     * @brief alignment
     */
    void alignment(Qt::Alignment alig);

    /**
     * @brief copy and paste selected items
     */
    void copyAndPasteSelectedItem();

    /**
     * @brief delete selected items
     */
    void deleteSelectedItem();

protected:
    void init();

    virtual void wheelEvent(QWheelEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

    virtual void keyReleaseEvent(QKeyEvent *event);

    virtual void paintEvent(QPaintEvent *event);

    virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void dragMoveEvent(QDragMoveEvent *event);
    virtual void dropEvent(QDropEvent *event);


    /**
     * @brief draw the iphone frame
     * @param painter
     * @param rect
     */
    virtual void drawBackground(QPainter *painter, const QRectF &rect);

    /**
     * @brief draw the view rect & the mouse select rect
     * @param painter
     * @param rect
     */
    virtual void drawForeground(QPainter *painter, const QRectF &rect);

    // custom function
    void showMouseRect(QPoint start, QPoint end);

    void hideControllerItem();
    void showControllerItem(QPointF pos);
    void showControllerItem(QPoint pos);


    void alignmentTop();
    void alignmentBottom();
    void alignmentLeft();
    void alignmentRight();


protected:
    QGraphicsScene*             m_scene;
    QGraphicsRectItem           m_mouseRectItem;
    Controller                  m_controllerItem;

    QRectF                      m_rect;
    bool                        m_pressed;
    qreal                       m_scaleFactor;
    QPointF                     m_prePos;
    QList<QGraphicsItem*>       m_selectItems;
    QGraphicsItem*              m_aligmentItem;

    QPixmap                     m_bgFrame;

    // for show background frame
    QHash<DeviceType, QString>  m_frames;
    QHash<DeviceType, QString>  m_framevs;
    QHash<DeviceType, QPoint>   m_framePoint;
    QHash<DeviceType, QPoint>   m_framevPoint;
    QPoint                      m_frameStartPoint;

    // for show mouse rect
    QPointF                     m_mouseStartPoint;
};

#endif // GRAPHWIDGET_H
