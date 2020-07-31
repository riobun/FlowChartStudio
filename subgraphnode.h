#ifndef SUBGRAPHNODE_H
#define SUBGRAPHNODE_H
#include "node.h"
#include "QGraphicsLineItem"
class SubgraphNode:public Node
{
public:
    SubgraphNode();
    SubgraphNode(QPointF lc,double wd,double h);
    SubgraphNode(QPointF lc,double wd);
    virtual void SetShape() override;
    virtual int GetType() override;
    virtual void Paint(QGraphicsScene *qgs) override;
    virtual void Remove(QGraphicsScene *qgs) override;
    virtual void ChangeZValue(bool isSelected) override;
    ~SubgraphNode();
    
    void OpenSubGraph();
    
private:
    QVector<QGraphicsLineItem*> subShape;
};

#endif // SUBGRAPHNODE_H
