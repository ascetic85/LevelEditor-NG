#ifndef CUSTOMPROPERTIES_H
#define CUSTOMPROPERTIES_H

#include <QWidget>

namespace Ui {
class CustomProperties;
}

class CustomProperties : public QWidget
{
    Q_OBJECT
    
public:
    explicit CustomProperties(QWidget *parent = 0);
    ~CustomProperties();
    
private:
    Ui::CustomProperties *ui;
};

#endif // CUSTOMPROPERTIES_H
