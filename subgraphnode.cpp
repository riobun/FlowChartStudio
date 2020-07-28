#include "subgraphnode.h"
#include <math.h>

SubgraphNode::SubgraphNode()
{

}
SubgraphNode:: SubgraphNode(QPointF lc,double wd):Node(lc,wd,sqrt(3)*wd/2)
{


}
SubgraphNode::~SubgraphNode()
{
    delete shape;
}

void SubgraphNode::SetHeight(double h)
{
    width=2*h/sqrt(3);
    height=h;
    SetShape();
}
void SubgraphNode::SetWidth(double wd)
{
    width=wd;
    height=sqrt(3)*wd/2;
    SetShape();
}
void SubgraphNode::SetShape()
{
    QPolygonF polygon;
    polygon<<QPointF(location.x()-width/2,location.y()+height/2)<<QPointF(location.x()+width/2,location.y()+height/2);
    polygon<<QPointF(location.x(),location.y()-height/2);
    shape->setPolygon(polygon);
}
int SubgraphNode::GetType()
{
    return 5;
}
