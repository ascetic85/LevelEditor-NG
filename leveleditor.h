#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include <QWidget>
#include "ui_leveleditor.h"

QT_BEGIN_NAMESPACE
class QFileSystemModel;
class QFileSystemWatcher;
class QSortFilterProxyModel;
QT_END_NAMESPACE

class Resource;
class Model;

class LevelEditor : public QWidget
{
    Q_OBJECT

public:
    explicit LevelEditor(QWidget *parent = 0);

    ~LevelEditor();

    void scale(qreal f);

public Q_SLOTS:
    /**
     * @brief show grid if @n > 1 & @n < 50
     * @param n
     */
    void showGrid(int n);


private Q_SLOTS:
    void on_resToolButton_clicked();

    /**
     * @brief onFilechanged
     * - file was modified, rename, remove
     *
     * Note that QFileSystemWatcher stops monitoring files once they have been
     * renamed or removed from disk, and directories once they have been removed
     * from disk.
     */
    void onFilechanged(QString file);

    /**
     * @brief onDirectoryChaned
     * - directory or its contents is modified or removed
     */
    void onDirectoryChaned(QString dir);

    void on_filter_textChanged(const QString &arg1);

    void on_toolClone_clicked();

    void on_toolDelete_clicked();

    void on_physicBoundToolButton_toggled(bool checked);

    void on_gravityToolButton_toggled(bool checked);

    void on_cloneToolButton_toggled(bool checked);

    void on_worldSizeToolButton_toggled(bool checked);

    void on_bezierToolButton_toggled(bool checked);

private:
    Ui::LevelEditor *ui;
    Model *m_fileModel;
    QFileSystemWatcher *m_watcher;
    Resource    *m_resource;
    QSortFilterProxyModel *m_proxyMode;
    QList<QToolButton*> m_buttons;
};

#endif // LEVELEDITOR_H
