#include "rootnode.h"

RootNode::RootNode()
{
    subShape.resize(2);
    subShape[0]=new QGraphicsLineItem();
    subShape[1]=new QGraphicsLineItem();
}

RootNode::RootNode(QPointF lc,double wd,double h): Node(lc,wd,h)
{
    subShape.resize(2);
    subShape[0]=new QGraphicsLineItem();
    subShape[1]=new QGraphicsLineItem();
}

RootNode::~RootNode()
{
    delete shape;
    delete subShape[0];
    delete subShape[1];
}

void RootNode::Paint(QGraphicsScene *qgs)
{
    Node::Paint(qgs);
    qgs->addItem(subShape[0]);
    qgs->addItem(subShape[1]);
}

void RootNode::SetShape()
{
    QPolygonF polygon;
    polygon<<QPointF(location.x()-width/2,location.y()-height/2)<<QPointF(location.x()+width/2,location.y()-height/2);
    polygon<<QPointF(location.x()+width/2,location.y()+height/2)<<QPointF(location.x()-width/2,location.y()+height/2);
    shape->setPolygon(polygon);
    double k=0.8;
    subShape[0]->setLine(location.x(),location.y()-k*height/2,location.x(),location.y()+k*height/2);
    subShape[1]->setLine(location.x()-k*width/2,location.y(),location.x()+k*width/2,location.y());
}

void RootNode::Remove(QGraphicsScene *qgs)
{
    Node::Remove(qgs);
    qgs->removeItem(subShape[0]);
    qgs->removeItem(subShape[1]);
}

void RootNode::ChangeZValue(bool isSelected)
{
    Node::ChangeZValue(isSelected);
    subShape[0]->setZValue(shape->zValue());
    subShape[1]->setZValue(shape->zValue());
}

void RootNode::SetFrameColor(const QColor &qc)
{
    Node::SetFrameColor(qc);
    QPen pen=shape->pen();
    pen.setColor(frameColor);
    subShape[0]->setPen(pen);
    subShape[1]->setPen(pen);
}

int RootNode::GetType()
{
    return 6;
}

void RootNode::SetThickness(double nt)
{
    Node::SetThickness(nt);
    QPen pen=shape->pen();
    pen.setWidthF(nt);
    subShape[0]->setPen(pen);
    subShape[1]->setPen(pen);
}
