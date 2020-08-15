#ifndef OUTPUTNODE_H
#define OUTPUTNODE_H
#include "node.h"
class SubgraphNode;
class InnerOutputNode;
class OutputNode:public Node
{
public:
    OutputNode();
    OutputNode(QPointF lc,double wd,double h);
    virtual void SetShape() override;
    virtual int GetType() override;
    virtual void Paint(QGraphicsScene *qgs) override;
    virtual void Remove(QGraphicsScene *qgs) override;
    virtual void ChangeZValue(bool isSelected) override;
    virtual void SetFrameColor(const QColor &qc) override;
    virtual void SetThickness(double nt) override;
    ~OutputNode();
protected:
    QGraphicsEllipseItem* subShape=new QGraphicsEllipseItem();
    QMap<int,InnerOutputNode*> relatedInner;

};

#endif // OUTPUTNODE_H
