#include "customproperties.h"
#include "ui_customproperties.h"

#include <QHeaderView>
#include <QTableWidget>

CustomProperties::CustomProperties(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomProperties)
{
    ui->setupUi(this);
}

CustomProperties::~CustomProperties()
{
    delete ui;
}
