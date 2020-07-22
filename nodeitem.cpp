#include "nodeitem.h"
#include "nodeevents.h"
#include "node.h"
#include "QKeyEvent"
#include "QDebug"
void NodeItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(isFocus)
    {
        isMoved=true;
        if(event->modifiers()==Qt::ShiftModifier&&isResized)
        {
              QPointF pos = event->pos();
              double nw=sqrt(pow(node->GetLocation().x() - pos.x(), 2)),nh=sqrt(pow(node->GetLocation().y() - pos.y(), 2));
              node->SetHeight(nh*2);
              node->SetWidth(nw*2);
        }
        else
        {
            node->SetLocation(node->GetLocation()+event->pos()-event->lastPos());
        }
    }
}

void NodeItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

}

void NodeItem::keyPressEvent(QKeyEvent *event)
{

}

void NodeItem::keyReleaseEvent(QKeyEvent *event)
{


}


void NodeItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
     SetSelected(true);
     if(event->button()==Qt::MouseButton::LeftButton)
     {
         isFocus=true;
         lastWidth=node->GetWidth();
         lastHeight=node->GetHeight();
         lastLocation=node->GetLocation();
         if(event->modifiers()==Qt::ShiftModifier)
         {
             isResized=true;
         }
    }
}

void NodeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(isFocus)
    {
        if(isMoved)
        {
            if(isResized)
            {
                 emit NewSize(node,lastWidth,lastHeight);
            }
            else
            {
                 emit NewLocation(node,lastLocation);
            }
        }
    }
    isMoved=false;
    isFocus=false;
    isResized=false;
}

void NodeItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{

}
