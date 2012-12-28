#ifndef ADVANCECLONE_H
#define ADVANCECLONE_H

#include <QWidget>

namespace Ui {
class AdvanceClone;
}

class AdvanceClone : public QWidget
{
    Q_OBJECT
    
public:
    explicit AdvanceClone(QWidget *parent = 0);
    ~AdvanceClone();

Q_SIGNALS:
    void autoCopy(QPoint p, int copies);

    void manualCopy(bool activeManualCopy, QSize size);

private slots:
    void on_makeclone_clicked();

    void on_checkBox_clicked(bool checked);

private:
    Ui::AdvanceClone *ui;
};

#endif // ADVANCECLONE_H
