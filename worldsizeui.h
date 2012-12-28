#ifndef WORLDSIZEUI_H
#define WORLDSIZEUI_H

#include <QWidget>

namespace Ui {
class WorldSizeUI;
}

class WorldSizeUI : public QWidget
{
    Q_OBJECT
    
public:
    explicit WorldSizeUI(QWidget *parent = 0);
    ~WorldSizeUI();
    
private:
    Ui::WorldSizeUI *ui;
};

#endif // WORLDSIZEUI_H
