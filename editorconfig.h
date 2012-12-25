#ifndef EDITORCONFIG_H
#define EDITORCONFIG_H

#include <QWidget>

namespace Ui {
class EditorConfig;
}

class EditorConfig : public QWidget
{
    Q_OBJECT
    
public:
    explicit EditorConfig(QWidget *parent = 0);
    ~EditorConfig();
    
private:
    Ui::EditorConfig *ui;
};

#endif // EDITORCONFIG_H
