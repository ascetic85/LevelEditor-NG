#include "editorconfig.h"
#include "ui_editorconfig.h"

EditorConfig::EditorConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditorConfig)
{
    ui->setupUi(this);
}

EditorConfig::~EditorConfig()
{
    delete ui;
}
