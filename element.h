#ifndef ELEMENT_H
#define ELEMENT_H

#include <QObject>

#include "elementshape.h"

class Scene;

class Element : public QObject
{
    Q_OBJECT

public:
    static Element* create(ElementShape shape);

private:
    Element(Scene* scene, ElementShape shape);

private:
    Scene* _scene;
    ElementShape _shape;
};

#endif // ELEMENT_H
