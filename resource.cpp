#include "resource.h"
#include <QStringList>

Resource::Resource(QObject *parent) :
    QObject(parent)
{
}

void Resource::setResource(QString &dir)
{
    m_resDir = dir;
    if (m_resDir.endsWith("/"))
        m_resDir.remove(m_resDir.length()-1,1);
}

QString Resource::directory()
{
    return m_resDir;
}

QString Resource::file(QString id)
{
    QStringList f = id.split(":",  QString::SkipEmptyParts);

    QString ret = m_resDir;
    foreach (QString it, f) {
        ret += "/" + it;
    }

    return ret;
}
