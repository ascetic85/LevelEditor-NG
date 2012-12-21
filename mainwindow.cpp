#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "config.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Config::defaultSettings();

    ui->setupUi(this);
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
