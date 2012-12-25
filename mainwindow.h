#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_actionOpenGL_triggered();

    void on_actionReset_triggered();

    void on_actionGrid_triggered();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
