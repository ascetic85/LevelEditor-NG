#ifndef SUPPORTINGCODE_H
#define SUPPORTINGCODE_H

#include <QWidget>

namespace Ui {
class SupportingCode;
}

class SupportingCode : public QWidget
{
    Q_OBJECT
    
public:
    explicit SupportingCode(QWidget *parent = 0);
    ~SupportingCode();
    
private:
    Ui::SupportingCode *ui;
};

#endif // SUPPORTINGCODE_H
