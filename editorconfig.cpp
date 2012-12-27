#include "editorconfig.h"
#include "ui_editorconfig.h"

#include <QFile>
#include <QFileInfo>
#include "config.h"
#include "Debug.h"

const QString kSection("section");
const QString kData("data");
const QString kName("name");
const QString kShortcut("shortcut");
const QString kLabel("lable");
const QString kKey("key");

const int kLabelIndex (1);
const int kKeyIndex (2);

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
                if (name == kSection) {
                    readSection();
                }
            } else if (m_xml.isEndElement()) {
                if (name == kData) {
                    break;
                }
            }
        }
    }

    ui->commandList->expandAll();
}

void EditorConfig::readSection()
{
    QString topName = m_xml.attributes().value(kName).toString();
    QTreeWidgetItem *top = new QTreeWidgetItem(QStringList()<<topName);
    ui->commandList->addTopLevelItem(top);

    while (!m_xml.atEnd()) {
        m_xml.readNext();

        QString name = m_xml.name().toString();
        if (m_xml.isStartElement()) {
            if (name == kShortcut) {
                QTreeWidgetItem* item = new QTreeWidgetItem(readShortcut());
                top->addChild(item);
            }
        } else if (m_xml.isEndElement()) {
            if (name == kSection) {
                break;
            }
        }
    }
}

QStringList EditorConfig::readShortcut()
{
    QStringList list;
    list.append(m_xml.attributes().value(kName).toString());
    while (!m_xml.atEnd()) {
        m_xml.readNext();

        QString name = m_xml.name().toString();
        if (m_xml.isStartElement()) {
            list.append(m_xml.readElementText());
        } else if (m_xml.isEndElement()) {
            if (name == kShortcut) {
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
    ui->keySequence->setText(ui->commandList->currentItem()->text(kKeyIndex));
}

void EditorConfig::on_resetButton_clicked()
{
    ui->keySequence->setText("");
}

void EditorConfig::onKeySequnenceChanged(QString text)
{
    if (ui->commandList->currentItem()->text(kLabelIndex).isEmpty())
        ui->commandList->currentItem()->setText(kLabelIndex, "");
    ui->commandList->currentItem()->setText(kKeyIndex, text);
}

void EditorConfig::on_applyButton_clicked()
{
    // save command list (tree)
    QSettings settings(Config::config(), Config::format());
    QFile file(settings.value(Config::ShortcutKey, Config::ShortcutFile).toString());

    if (file.open(QIODevice::WriteOnly|QIODevice::Text)) {
        QXmlStreamWriter writer;
        writer.setDevice(&file);
        writer.setAutoFormatting(true);
        writer.writeStartDocument();

        writer.writeStartElement(kData);
        int cnt = ui->commandList->topLevelItemCount();
        for (int i = 0; i < cnt; ++i) {
            QTreeWidgetItem *top = ui->commandList->topLevelItem(i);
            // write section
            writer.writeStartElement(kSection);
            writer.writeAttribute(kName, top->text(0));

            // shortcut
            int shortcutCnt = top->childCount();
            for (int j = 0; j < shortcutCnt; ++j) {
                QTreeWidgetItem *shortcutItem = top->child(j);
                // write shortcut
                writer.writeStartElement(kShortcut);
                writer.writeAttribute(kName, shortcutItem->text(0));

                // label
                if (!shortcutItem->text(kLabelIndex).isEmpty())
                    writer.writeTextElement(kLabel, shortcutItem->text(kLabelIndex));

                // key
                if (!shortcutItem->text(kKeyIndex).isEmpty())
                    writer.writeTextElement(kKey, shortcutItem->text(kKeyIndex));

                // shortcut end
                writer.writeEndElement();
            }
            writer.writeEndElement();
        }
        writer.writeEndElement();

        writer.writeEndDocument();
    }

}
