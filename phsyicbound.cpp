#include "phsyicbound.h"
#include "ui_phsyicbound.h"

PhsyicBound::PhsyicBound(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PhsyicBound)
{
    ui->setupUi(this);
}

PhsyicBound::~PhsyicBound()
{
    delete ui;
}
