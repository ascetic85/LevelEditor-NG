#include "supportingcode.h"
#include "ui_supportingcode.h"

SupportingCode::SupportingCode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SupportingCode)
{
    ui->setupUi(this);
}

SupportingCode::~SupportingCode()
{
    delete ui;
}
