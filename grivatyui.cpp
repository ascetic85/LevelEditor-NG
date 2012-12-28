#include "grivatyui.h"
#include "ui_grivatyui.h"

GrivatyUI::GrivatyUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GrivatyUI)
{
    ui->setupUi(this);
}

GrivatyUI::~GrivatyUI()
{
    delete ui;
}
