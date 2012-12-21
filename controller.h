#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QGraphicsRectItem>

class Controller : public QGraphicsRectItem
{
public:
    explicit Controller(QGraphicsItem* parent = 0, QGraphicsScene* scene = 0);
    
};

#endif // CONTROLLER_H
