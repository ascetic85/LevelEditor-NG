#include "gridconfig.h"
#include "ui_gridconfig.h"


GridConfig::GridConfig(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GridConfig)
    , m_num(0)
{
    ui->setupUi(this);

    QRegExp regx("[0-9]+$");
    QValidator *validator = new QRegExpValidator(regx, ui->lineEdit );
    ui->lineEdit->setValidator(validator);
}

GridConfig::~GridConfig()
{
    delete ui;
}

void GridConfig::setGridNumber(int n)
{
    m_num = n;
}

void GridConfig::accept()
{
    int n = ui->lineEdit->text().toInt();
    if (n != m_num) {
        m_num = n;
        emit gridChanged(m_num);
    }

    QDialog::accept();
}

void GridConfig::on_lineEdit_returnPressed()
{
    accept();
}

void GridConfig::on_buttonBox_accepted()
{
    accept();
}

void GridConfig::on_buttonBox_rejected()
{
    reject();
}
