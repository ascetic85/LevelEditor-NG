#ifndef EDITORCONFIG_H
#define EDITORCONFIG_H

#include <QDialog>

namespace Ui {
class EditorConfig;
}

class EditorConfig : public QDialog
{
    Q_OBJECT
    
public:
    explicit EditorConfig(QWidget *parent = 0);
    ~EditorConfig();
    
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::EditorConfig *ui;
};

#endif // EDITORCONFIG_H
