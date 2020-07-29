#include "subgraphnode.h"
#include <math.h>

SubgraphNode::SubgraphNode()
{
     subShape.resize(2);
     subShape[0]=new QGraphicsLineItem();
     subShape[1]=new QGraphicsLineItem();
}
SubgraphNode:: SubgraphNode(QPointF lc,double wd,double h):Node(lc,wd,h)
{
    subShape.resize(2);
    subShape[0]=new QGraphicsLineItem();
    subShape[1]=new QGraphicsLineItem();
}
SubgraphNode:: SubgraphNode(QPointF lc,double wd):Node(lc,wd,wd)
{
    subShape.resize(2);
    subShape[0]=new QGraphicsLineItem();
    subShape[1]=new QGraphicsLineItem();
}
SubgraphNode::~SubgraphNode()
{
    delete shape;
}

void SubgraphNode::Paint(QGraphicsScene *qgs)
{
    SetShape();
    shape->setVisible(true);
    shape->setFlags(QGraphicsItem::ItemIsSelectable);
    SetBackgroundColor(backgroundColor);
    SetFrameColor(frameColor);
    qgs->addItem(shape);
    qgs->addItem(subShape[0]);
    qgs->addItem(subShape[1]);
}

void SubgraphNode::SetShape()
{
    QPolygonF polygon;
    polygon<<QPointF(location.x()-width/2,location.y()-height/2)<<QPointF(location.x()+width/2,location.y()-height/2);
    polygon<<QPointF(location.x()+width/2,location.y()+height/2)<<QPointF(location.x()-width/2,location.y()+height/2);
    shape->setPolygon(polygon);
    double k=0.8;
    subShape[0]->setLine(location.x(),location.y()-k*height/2,location.x(),location.y()+k*height/2);
    subShape[1]->setLine(location.x()-k*width/2,location.y(),location.x()+k*width/2,location.y());
}

void SubgraphNode::Remove(QGraphicsScene *qgs)
{
    Node::Remove(qgs);
    qgs->removeItem(subShape[0]);
    qgs->removeItem(subShape[1]);
}
void SubgraphNode::ChangeZValue(bool isSelected)
{
    Node::ChangeZValue(isSelected);
    subShape[0]->setZValue(shape->zValue());
    subShape[1]->setZValue(shape->zValue());
}
int SubgraphNode::GetType()
{
    return 5;
}
