#ifndef ROOTNODE_H
#define ROOTNODE_H

#include "node.h"

class RootNode: public Node
{
public:
    RootNode();
    RootNode(QPointF lc,double wd,double h);
    ~RootNode();

    virtual void Paint(QGraphicsScene *qgs) override;
    virtual void SetShape() override;
    virtual void Remove(QGraphicsScene *qgs) override;
    virtual void ChangeZValue(bool isSelected) override;
    virtual void SetFrameColor(const QColor &qc) override;
    virtual int GetType() override;
    virtual void SetThickness(double nt) override;

protected:
    QVector<QGraphicsLineItem*> subShape;
};

#endif // ROOTNODE_H
