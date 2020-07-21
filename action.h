#ifndef ACTION_H
#define ACTION_H

#include <QObject>

class Action : public QObject
{
    Q_OBJECT
public:
    explicit Action(QObject *parent = nullptr);

signals:

};

#endif // ACTION_H
