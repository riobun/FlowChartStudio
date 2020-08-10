#ifndef ELEMENT_H
#define ELEMENT_H

#include <QObject>

#include "elementshape.h"

class Element : public QObject
{
    Q_OBJECT

protected:
    Element(ElementShape shape);

private:
    ElementShape _shape;
};

#endif // ELEMENT_H
