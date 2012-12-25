#include "editorconfig.h"
#include "ui_editorconfig.h"

EditorConfig::EditorConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditorConfig)
{
    ui->setupUi(this);
    setWindowTitle(tr("Game Configure"));
}

EditorConfig::~EditorConfig()
{
    delete ui;
}

void EditorConfig::on_buttonBox_accepted()
{
    accept();
}

void EditorConfig::on_buttonBox_rejected()
{
    reject();
}
