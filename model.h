#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QFileSystemModel>

class Model : public QFileSystemModel
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = 0);
    
};

#endif // MODEL_H
