#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include <QWidget>
#include "ui_leveleditor.h"

class LevelEditor : public QWidget
{
    Q_OBJECT

public:
    explicit LevelEditor(QWidget *parent = 0)
        : QWidget(parent)
        , ui(new Ui::LevelEditor() )
    {
        ui->setupUi(this);
    }

    ~LevelEditor() { delete ui; }

private:
    Ui::LevelEditor *ui;
};

#endif // LEVELEDITOR_H
