#ifndef ELEMENT_H
#define ELEMENT_H

#include <QObject>

#include "elementshape.h"

class FlowChartScene;

class Element : public QObject
{
    Q_OBJECT

protected:
    Element(FlowChartScene* scene, ElementShape shape);

private:
    FlowChartScene* _scene;
    ElementShape _shape;
};

#endif // ELEMENT_H
