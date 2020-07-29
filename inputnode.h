#ifndef INPUTNODE_H
#define INPUTNODE_H
#include"node.h"

class InputNode:public Node
{
public:
    InputNode();
    InputNode(QPointF lc,double wd,double h);
    virtual void SetShape() override;
    virtual int GetType() override;
    virtual void BindToText(QGraphicsScene *qgs) override;
    ~InputNode();
};

#endif // INPUTNODE_H
