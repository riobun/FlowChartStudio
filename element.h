#ifndef ELEMENT_H
#define ELEMENT_H

#include <QObject>

class Element : public QObject
{
    Q_OBJECT
public:
    explicit Element(QObject *parent = nullptr);

signals:

};

#endif // ELEMENT_H
