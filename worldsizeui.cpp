#include "worldsizeui.h"
#include "ui_worldsizeui.h"

WorldSizeUI::WorldSizeUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorldSizeUI)
{
    ui->setupUi(this);
}

WorldSizeUI::~WorldSizeUI()
{
    delete ui;
}
