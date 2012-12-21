#include "watcher.h"

//class UpdateListener : public FW::FileWatchListener
//{
//public:
//    UpdateListener() {}
//    void handleFileAction(FW::WatchID watchid, const FW::String& dir, const FW::String& filename,
//        FW::Action action)
//    {
////        std::cout << "DIR (" << dir + ") FILE (" + filename + ") has event " << action << std::endl;
//    }
//};

//// create the file watcher object
//FW::FileWatcher fileWatcher;

//// add a watch to the system
//FW::WatchID watchID = fileWatcher.addWatch("E:/suren", new UpdateListener(), true);

//std::cout << "Press ^C to exit demo" << std::endl;

//// loop until a key is pressed
//while(1)
//{
//    fileWatcher.update();
//}

Watcher::Watcher(QObject *parent) :
    QObject(parent)
{
}

void Watcher::addPath(QString & /*path*/ )
{
}
