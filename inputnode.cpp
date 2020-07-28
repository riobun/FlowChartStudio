#include "inputnode.h"


InputNode::InputNode()
{

}
InputNode:: InputNode(QPointF lc,double wd,double h):Node(lc,wd,h)
{


}
InputNode::~InputNode()
{
    delete shape;
}

void InputNode::SetShape()
{
    QPolygonF polygon;
    polygon<<QPointF(location.x()-width/2,location.y()-height/2)<<QPointF(location.x(),location.y()-height/2);
    polygon<<QPoint(location.x()+width/2,location.y());
    polygon<<QPointF(location.x(),location.y()+height/2)<<QPointF(location.x()-width/2,location.y()+height/2);
    shape->setPolygon(polygon);
}
int InputNode::GetType()
{
    return 1;
}
