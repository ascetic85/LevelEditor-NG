#ifndef EDITORCONFIG_H
#define EDITORCONFIG_H

#include <QDialog>
#include <QModelIndex>
#include <QXmlStreamReader>

namespace Ui {
class EditorConfig;
}

class EditorConfig : public QDialog
{
    Q_OBJECT
    
public:
    explicit EditorConfig(QWidget *parent = 0);
    ~EditorConfig();
    
protected:
    void init();

    void parseXML();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_commandList_clicked(const QModelIndex &index);

private:
    Ui::EditorConfig *ui;

    QXmlStreamReader m_xml;
};

#endif // EDITORCONFIG_H
