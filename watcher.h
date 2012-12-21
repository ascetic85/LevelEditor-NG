#ifndef WATCHER_H
#define WATCHER_H

#include <QObject>
#include "FileWatcher/FileWatcher.h"



class Watcher : public QObject
{
    Q_OBJECT
public:
    explicit Watcher(QObject *parent = 0);
    
    void addPath(QString& path);

protected:

    FW::FileWatcher *m_watcher;
    
};

#endif // WATCHER_H
