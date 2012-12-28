#ifndef PHSYICBOUND_H
#define PHSYICBOUND_H

#include <QWidget>

namespace Ui {
class PhsyicBound;
}

class PhsyicBound : public QWidget
{
    Q_OBJECT
    
public:
    explicit PhsyicBound(QWidget *parent = 0);
    ~PhsyicBound();
    
private:
    Ui::PhsyicBound *ui;
};

#endif // PHSYICBOUND_H
