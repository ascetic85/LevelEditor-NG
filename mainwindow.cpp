#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->levelEditor->setUseOpenGL();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpenGL_triggered()
{
}

void MainWindow::on_actionReset_triggered()
{
    ui->levelEditor->scale(1.0);
}
