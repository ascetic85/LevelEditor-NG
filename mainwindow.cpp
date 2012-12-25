#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "config.h"
#include "gridconfig.h"
#include "editorconfig.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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

void MainWindow::on_actionGrid_triggered()
{
    GridConfig config(this);
    connect(&config, SIGNAL(gridChanged(int)), ui->levelEditor, SLOT(showGrid(int)));
    config.exec();
}


void MainWindow::on_actionOption_triggered()
{
    EditorConfig config(this);
    config.exec();
}
