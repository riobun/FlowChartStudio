#include "outputnode.h"

OutputNode::OutputNode()
{

}
OutputNode:: OutputNode(QPointF lc,double wd,double h):Node(lc,wd,h)
{


}
OutputNode::~OutputNode()
{
    delete shape;
    delete subShape;
}
void OutputNode::Paint(QGraphicsScene *qgs)
{
    Node::Paint(qgs);
    qgs->addItem(subShape);
}

void OutputNode::Remove(QGraphicsScene *qgs)
{
    Node::Remove(qgs);
    qgs->removeItem(subShape);
}

void OutputNode::ChangeZValue(bool isSelected)
{
    Node::ChangeZValue(isSelected);
    subShape->setZValue(shape->zValue());
}
void OutputNode::SetShape()
{
    QPolygonF polygon;
    polygon<<QPointF(location.x()+width/2,location.y()-height/2)<<QPointF(location.x(),location.y()-height/2);
    polygon<<QPoint(location.x()-width/2,location.y());
    polygon<<QPointF(location.x(),location.y()+height/2)<<QPointF(location.x()+width/2,location.y()+height/2);
    shape->setPolygon(polygon);
    double k=0.8;
    subShape->setRect(location.x()+width/4-k*width/4,location.y()-k*height/2,k*width/2,k*height);
}
void OutputNode::SetFrameColor(const QColor &qc)
{
    Node::SetFrameColor(qc);
    QPen pen=shape->pen();
    pen.setColor(frameColor);
    subShape->setPen(pen);
}
int OutputNode::GetType()
{
    return 5;
}
