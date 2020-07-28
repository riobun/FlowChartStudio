#ifndef SUBGRAPHNODE_H
#define SUBGRAPHNODE_H
#include "node.h"

class SubgraphNode:public Node
{
public:
    SubgraphNode();
    SubgraphNode(QPointF lc,double wd);
    virtual void SetHeight(double h) override;
    virtual void SetWidth(double wd) override;
    virtual void SetShape() override;
    virtual int GetType() override;
    ~SubgraphNode();
};

#endif // SUBGRAPHNODE_H
