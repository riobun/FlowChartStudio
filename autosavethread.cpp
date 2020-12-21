#include "autosavethread.h"

AutoSaveThread* AutoSaveThread::_instance;

AutoSaveThread::AutoSaveThread(QObject *parent) : QThread(parent)
{
    _instance = this;
}

AutoSaveThread* AutoSaveThread::instance()
{
    return _instance;
}

void AutoSaveThread::run()
{
    while (true)
    {
        QThread::sleep(10);
        emit autoSave();
    }
}
