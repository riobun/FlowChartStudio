#include "node.h"
#include"arrow.h"

Node::Node(){}
Node::Node(QPointF lc,double w,double h):location(lc),width(w),height(h)
{

}

Node::~Node()
{

}
double Node::GetWidth()
{
    return width;
}

double Node::GetHeight()
{
    return height;
}

QColor Node::GetBackgroundColor()
{
    return backgroundColor;
}

QColor Node::GetFrameColor()
{
    return frameColor;
}
QPointF Node::GetLocation()
{
    return location;
}

void Node::ConnectAsSource(Arrow *ar)
{
    sourceArrows[ar->GetID()]=ar;
}

void Node::ConnectAsDestination(Arrow *ar)
{
    destinationArrows[ar->GetID()]=ar;
}

void Node::DisconnectAsSource(Arrow *ar)
{
    sourceArrows.remove(ar->GetID());
}

void Node::DisconnectAsDestination(Arrow *ar)
{
    destinationArrows.remove(ar->GetID());
}

QVector<Arrow*> Node::getArrows()
{
    QVector<Arrow*> vec;
    foreach (auto arrow, sourceArrows)
    {
        vec.append(arrow);
    }
    foreach (auto arrow, destinationArrows)
    {
        vec.append(arrow);
    }
    return vec;
}

