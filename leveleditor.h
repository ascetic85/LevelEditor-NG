#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include <QWidget>
#include "ui_leveleditor.h"

QT_BEGIN_NAMESPACE
class QFileSystemModel;
QT_END_NAMESPACE

class LevelEditor : public QWidget
{
    Q_OBJECT

public:
    explicit LevelEditor(QWidget *parent = 0);

    ~LevelEditor();

    void setUseOpenGL();

    void scale(qreal f);

private slots:
    void on_resToolButton_clicked();

private:
    Ui::LevelEditor *ui;
    QFileSystemModel *m_fileModel;
};

#endif // LEVELEDITOR_H
