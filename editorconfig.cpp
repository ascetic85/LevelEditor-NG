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
    ui->commandList->expandAll();

    connect(ui->keySequence, SIGNAL(textChanged(QString))
            , this, SLOT(onKeySequnenceChanged(QString)));
}

void EditorConfig::parseXML()
{
    m_xml.clear();

    QSettings settings(Config::config(), Config::format());
    QFile file(settings.value(Config::ShortcutKey, Config::ShortcutFile).toString());

    if (file.open(QIODevice::ReadOnly|QIODevice::Text)) {
        QByteArray all = file.readAll();
        m_xml.addData(all);
        while (!m_xml.atEnd()) {
            m_xml.readNext();

            QString name = m_xml.name().toString();
            if (m_xml.isStartElement()) {
                if (name == "section") {
                    readSection();
                }
            } else if (m_xml.isEndElement()) {
                if (name == "data") {
                    break;
                }
            }
        }
    }

    ui->commandList->expandAll();
}

void EditorConfig::readSection()
{
    QString topName = m_xml.attributes().value("name").toString();
    QTreeWidgetItem *top = new QTreeWidgetItem(QStringList()<<topName);
    ui->commandList->addTopLevelItem(top);

    while (!m_xml.atEnd()) {
        m_xml.readNext();

        QString name = m_xml.name().toString();
        if (m_xml.isStartElement()) {
            if (name == "shortcut") {
                QTreeWidgetItem* item = new QTreeWidgetItem(readShortcut());
                top->addChild(item);
            }
        } else if (m_xml.isEndElement()) {
            if (name == "section") {
                break;
            }
        }
    }
}

QStringList EditorConfig::readShortcut()
{
    QStringList list;
    list.append(m_xml.attributes().value("name").toString());
    while (!m_xml.atEnd()) {
        m_xml.readNext();

        QString name = m_xml.name().toString();
        if (m_xml.isStartElement()) {
            list.append(m_xml.readElementText());
        } else if (m_xml.isEndElement()) {
            if (name == "shortcut") {
                break;
            }
        }
    }
    return list;
}

void EditorConfig::on_buttonBox_accepted()
{
    accept();
}

void EditorConfig::on_buttonBox_rejected()
{
    reject();
}

void EditorConfig::on_commandList_clicked(const QModelIndex & /*index*/)
{
    ui->keySequence->setText(ui->commandList->currentItem()->text(2));
}

void EditorConfig::on_resetButton_clicked()
{
    ui->keySequence->setText("");
}

void EditorConfig::onKeySequnenceChanged(QString text)
{
    ui->commandList->currentItem()->setText(2, text);
}
