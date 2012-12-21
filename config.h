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

QSettings::Format format();

QString config();

void defaultSettings();

}
#endif // CONFIG_H
