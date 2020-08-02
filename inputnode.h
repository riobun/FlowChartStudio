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
    virtual void Paint(QGraphicsScene *qgs) override;
    virtual void Remove(QGraphicsScene *qgs) override;
    virtual void ChangeZValue(bool isSelected) override;
    virtual void SetFrameColor(const QColor &qc) override;
    ~InputNode();
protected:
     QVector<QGraphicsLineItem*> subShape;
};

#endif // INPUTNODE_H
