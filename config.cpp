#include "config.h"

#include <QApplication>
#include <QFile>

namespace Config {

QSettings::Format format()
{
    #if defined(Q_OS_WIN) || defined(Q_OS_WIN32)
        return QSettings::IniFormat;
    #else
        return QSettings::NativeFormat;
    #endif
}

QString config()
{
    return qApp->applicationDirPath()+"/config.ini";
}

void defaultSettings()
{
    if (!QFile::exists(Config::config()))
    {
        QSettings settings(Config::config(), Config::format());
        settings.setValue("editor/opengl", false);

        settings.sync();
    }
}


} // namespace Config
