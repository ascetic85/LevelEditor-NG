#ifndef CONFIG_H
#define CONFIG_H

#include <QtGlobal>
#include <QSettings>

// property

namespace Config {

const QString editorw = "editor/width";
const QString editorh = "editor/height";
const qreal w = 480;
const qreal h = 320;


// for shortcut
const QString key_del = "shortcut/del";
const QString key_left = "shortcut/left";
const QString key_right = "shortcut/right";
const QString key_top = "shortcut/top";
const QString key_bottom = "shortcut/bottom";
const Qt::Key Del = Qt::Key_Delete;
const Qt::Key Left = Qt::Key_L;
const Qt::Key Right = Qt::Key_R;
const Qt::Key Top = Qt::Key_T;
const Qt::Key Bottom = Qt::Key_B;


QSettings::Format format();

QString config();

void defaultSettings();

}
#endif // CONFIG_H
