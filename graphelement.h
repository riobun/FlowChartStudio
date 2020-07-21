#ifndef GRAPHELEMENT_H
#define GRAPHELEMENT_H
#include "text.h"
#include"QGraphicsScene"

class GraphElement
{
public:
    GraphElement();
    int GetID();
    virtual void BindToText(QGraphicsScene* qgs)=0;
protected:
    int id;
    Text* content=nullptr;
};

#endif // GRAPHELEMENT_H
