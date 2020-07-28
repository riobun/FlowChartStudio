#ifndef OUTPUTNODE_H
#define OUTPUTNODE_H
#include "node.h"

class OutputNode:public Node
{
public:
    OutputNode();
    OutputNode(QPointF lc,double wd,double h);
    virtual void SetShape() override;
    virtual int GetType() override;
    ~OutputNode();
};

#endif // OUTPUTNODE_H
