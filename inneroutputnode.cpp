#include "inneroutputnode.h"


InnerOutputNode::InnerOutputNode()
{

}

InnerOutputNode::~InnerOutputNode()
{
    delete innerLine;
}
InnerOutputNode::InnerOutputNode(QPointF lc,double wd,double h):OutputNode(lc,wd,h) {};
void InnerOutputNode::Paint(QGraphicsScene *qgs)
{
    OutputNode::Paint(qgs);
    qgs->addItem(innerLine);
}
void InnerOutputNode::Remove(QGraphicsScene *qgs)
{
    OutputNode::Remove(qgs);
    qgs->removeItem(innerLine);
}

void InnerOutputNode::ChangeZValue(bool isSelected)
{
    OutputNode::ChangeZValue(isSelected);
    innerLine->setZValue(shape->zValue());
}
void InnerOutputNode::SetShape()
{
    OutputNode::SetShape();
    double k=0.6;
    innerLine->setLine(location.x()+width/4+k*width/4,location.y()-height/2,location.x()+width/4+k*width/4,location.y()+height/2);
}

void InnerOutputNode::SetFrameColor(const QColor &qc)
{
    OutputNode::SetFrameColor(qc);
    QPen pen=shape->pen();
    pen.setColor(frameColor);
    innerLine->setPen(pen);
}
int InnerOutputNode::GetType()
{
    return 8;
}
