#include "advanceclone.h"
#include "ui_advanceclone.h"

AdvanceClone::AdvanceClone(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdvanceClone)
{
    ui->setupUi(this);
}

AdvanceClone::~AdvanceClone()
{
    delete ui;
}

void AdvanceClone::on_makeclone_clicked()
{
    emit autoCopy(QPoint(ui->x->value(), ui->y->value()), ui->copies->value());
}

void AdvanceClone::on_checkBox_clicked(bool checked)
{
    emit manualCopy(checked, QSize(ui->width->value(), ui->height->value()));
}
