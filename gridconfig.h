#ifndef GRIDCONFIG_H
#define GRIDCONFIG_H

#include <QDialog>

namespace Ui {
class GridConfig;
}

class GridConfig : public QDialog
{
    Q_OBJECT
    
public:
    explicit GridConfig(QWidget *parent = 0);
    ~GridConfig();

    void setGridNumber(int n);

public Q_SLOTS:
    virtual void accept();

Q_SIGNALS:
    void gridChanged(int);

private slots:
    void on_lineEdit_returnPressed();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::GridConfig *ui;
    int m_num;
};

#endif // GRIDCONFIG_H
