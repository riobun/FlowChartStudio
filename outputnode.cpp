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
}

void OutputNode::SetShape()
{
    QPolygonF polygon;
    polygon<<QPointF(location.x()+width/2,location.y()-height/2)<<QPointF(location.x(),location.y()-height/2);
    polygon<<QPoint(location.x()-width/2,location.y());
    polygon<<QPointF(location.x(),location.y()+height/2)<<QPointF(location.x()+width/2,location.y()+height/2);
    shape->setPolygon(polygon);
}
void OutputNode::BindToText(QGraphicsScene *qgs)
{
    Node::BindToText(qgs);
    content->change_content("out");
}
int OutputNode::GetType()
{
    return 4;
}
