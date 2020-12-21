#ifndef AUTOSAVETHREAD_H
#define AUTOSAVETHREAD_H

#include <QThread>

class AutoSaveThread : public QThread
{
    Q_OBJECT
public:
    static AutoSaveThread* instance();

    explicit AutoSaveThread(QObject *parent = nullptr);

protected:
    void run() override;

signals:
    void autoSave();

private:
    static AutoSaveThread* _instance;
};

#endif // AUTOSAVETHREAD_H
