#ifndef BEZIERUI_H
#define BEZIERUI_H

#include <QWidget>

namespace Ui {
class BezierUI;
}

class BezierUI : public QWidget
{
    Q_OBJECT
    
public:
    explicit BezierUI(QWidget *parent = 0);
    ~BezierUI();
    
private:
    Ui::BezierUI *ui;
};

#endif // BEZIERUI_H
