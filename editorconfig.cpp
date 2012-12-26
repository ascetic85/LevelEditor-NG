#include "editorconfig.h"
#include "ui_editorconfig.h"

#include <QFile>
#include <QFileInfo>
#include "config.h"
#include "Debug.h"

EditorConfig::EditorConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditorConfig)
{
    ui->setupUi(this);
#ifdef Q_OS_MAC
    setWindowTitle(tr("Preference"));
#else
    setWindowTitle(tr("Option"));
#endif
    init();
}

EditorConfig::~EditorConfig()
{
    delete ui;
}

void EditorConfig::init()
{
    parseXML();

    // command list
    QTreeWidgetItem *sceneItem = new QTreeWidgetItem(QStringList()<<"Scene");
    ui->commandList->addTopLevelItem(sceneItem);

    QList<QStringList> commands;
    commands << (QStringList()<<"1"<<"2"<<"3");
    commands << (QStringList()<<"3"<<"2"<<"1");
    foreach (QStringList it, commands) {
        sceneItem->addChild(new QTreeWidgetItem(it));
    }


    ui->commandList->expandAll();
}

void EditorConfig::parseXML()
{
    m_xml.clear();

    QSettings settings(Config::config(), Config::format());
    QFile xml(settings.value(Config::ShortcutKey, Config::ShortcutFile).toString());


    if (xml.open(QIODevice::ReadOnly)) {
        m_xml.addData(xml.readAll());
        QXmlStreamReader &reader = m_xml;
        reader.readNext();

        QStringList parent;
        QList<QStringList> commands;
        QStringList value;
        while (!reader.atEnd())
        {
            if(reader.isStartElement())
            {
                if(reader.name() == "parent")
                {
//                    Debug() << "parent" << reader.attributes().value("name");
                    parent.append(reader.attributes().value("parent").toString());
                }
                else if(reader.name() == "shortcut")
                {
//                    Debug() << reader.attributes().value("name");
                    value.append(reader.attributes().value("name").toString());
                }
                else if (reader.name() == "label") {
//                    Debug() << "label" << reader.readElementText();
                    value.append(reader.readElementText());
                }
                else if (reader.name() == "key") {
//                    Debug() << "key" << reader.readElementText();
                    value.append(reader.readElementText());
                }
            }
            else if(reader.isEndElement())
            {
                if(reader.name() == "parent")
                {
                    Debug() << __LINE__ << "parent end" << value;
                    commands.append(value);
                    value.clear();
//                     message_map->insert(std::make_pair(message->GetMsgPhone(), message));
                }
            }
            reader.readNext();
        }
    }
}

void EditorConfig::on_buttonBox_accepted()
{
    accept();
}

void EditorConfig::on_buttonBox_rejected()
{
    reject();
}

void EditorConfig::on_commandList_clicked(const QModelIndex &index)
{

}
