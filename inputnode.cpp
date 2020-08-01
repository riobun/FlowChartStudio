#include "inputnode.h"


InputNode::InputNode()
{
    subShape.resize(3);
    subShape[0]=new QGraphicsLineItem();
    subShape[1]=new QGraphicsLineItem();
    subShape[2]=new QGraphicsLineItem();
}
InputNode:: InputNode(QPointF lc,double wd,double h):Node(lc,wd,h)
{
    subShape.resize(3);
    subShape[0]=new QGraphicsLineItem();
    subShape[1]=new QGraphicsLineItem();
    subShape[2]=new QGraphicsLineItem();

}
InputNode::~InputNode()
{
    delete shape;
    delete subShape[0];
    delete subShape[1];
    delete subShape[2];
}
void InputNode::Paint(QGraphicsScene *qgs)
{
    Node::Paint(qgs);
    qgs->addItem(subShape[0]);
    qgs->addItem(subShape[1]);
    qgs->addItem(subShape[2]);
}
void InputNode::Remove(QGraphicsScene *qgs)
{
    Node::Remove(qgs);
    qgs->removeItem(subShape[0]);
    qgs->removeItem(subShape[1]);
    qgs->removeItem(subShape[2]);
}

void InputNode::ChangeZValue(bool isSelected)
{
    Node::ChangeZValue(isSelected);
    subShape[0]->setZValue(shape->zValue());
    subShape[1]->setZValue(shape->zValue());
    subShape[2]->setZValue(shape->zValue());
}
void InputNode::SetShape()
{
    QPolygonF polygon;
    polygon<<QPointF(location.x()-width/2,location.y()-height/2)<<QPointF(location.x(),location.y()-height/2);
    polygon<<QPoint(location.x()+width/2,location.y());
    polygon<<QPointF(location.x(),location.y()+height/2)<<QPointF(location.x()-width/2,location.y()+height/2);
    shape->setPolygon(polygon);
    double k1=0.8,k2=0.4,k3=0.5;
    subShape[0]->setLine(location.x()-width/4,location.y()-k1*height/2,location.x()-width/4,location.y()+k1*height/2);
    subShape[1]->setLine(location.x()-width/4-k2*width/4,location.y()-0.8*height/2,location.x()-width/4+k2*width/4,location.y()-0.8*height/2);
    subShape[2]->setLine(location.x()-width/4-k3*width/4,location.y()+0.8*height/2,location.x()-width/4+k3*width/4,location.y()+0.8*height/2);
}

void InputNode::SetFrameColor(const QColor &qc)
{
    Node::SetFrameColor(qc);
    QPen pen=shape->pen();
    pen.setColor(frameColor);
    subShape[0]->setPen(pen);
    subShape[1]->setPen(pen);
    subShape[2]->setPen(pen);
}
int InputNode::GetType()
{
    return 4;
}
