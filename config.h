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
const QString KeyDel = "shortcut/del";
const QString KeyLeft = "shortcut/left";
const QString KeyRight = "shortcut/right";
const QString KeyTop = "shortcut/top";
const QString KeyBottom = "shortcut/bottom";
const QString KeyCopy = "shortcut/c";
const QString KeyCopyModifiers = "shortcut/ctrl";
const QString KeyPaste = "shortcut/v";
const QString KeyPasteModifers = "shortcut/ctrl";
const QString ShortcutKey = "shortcut/file";
const QString ShortcutFile = "shortcut.kms";

QSettings::Format format();

QString config();

void defaultSettings();

}
#endif // CONFIG_H
