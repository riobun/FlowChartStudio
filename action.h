#ifndef ACTION_H
#define ACTION_H

#include <QObject>

class Action : public QObject
{
    Q_OBJECT
public:
    explicit Action(QObject *parent = nullptr);

    void virtual Do();
    void virtual Undo();

signals:

};

#endif // ACTION_H
