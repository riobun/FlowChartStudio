#ifndef ACTION_H
#define ACTION_H

#include <QObject>

class Action : public QObject
{
    Q_OBJECT
public:
    explicit Action(QObject *parent = nullptr);

    virtual void Do() = 0;
    virtual void Undo() = 0;

signals:

};

#endif // ACTION_H
