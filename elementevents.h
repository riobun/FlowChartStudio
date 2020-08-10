#ifndef ELEMENTEVENTS_H
#define ELEMENTEVENTS_H

#include <QObject>

class ElementEvents : public QObject
{
    Q_OBJECT
public:
    explicit ElementEvents(QObject *parent = nullptr);

signals:

};

#endif // ELEMENTEVENTS_H
