#ifndef GRIVATYUI_H
#define GRIVATYUI_H

#include <QWidget>

namespace Ui {
class GrivatyUI;
}

class GrivatyUI : public QWidget
{
    Q_OBJECT
    
public:
    explicit GrivatyUI(QWidget *parent = 0);
    ~GrivatyUI();
    
private:
    Ui::GrivatyUI *ui;
};

#endif // GRIVATYUI_H
