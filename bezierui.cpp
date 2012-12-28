#include "bezierui.h"
#include "ui_bezierui.h"

BezierUI::BezierUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BezierUI)
{
    ui->setupUi(this);
}

BezierUI::~BezierUI()
{
    delete ui;
}
