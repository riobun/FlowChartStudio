#include "nodeitem.h"
#include "nodeevents.h"
#include "node.h"

void NodeItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(isSelected)
    {
        node->SetLocation(event->pos());
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
    if(contains(event->pos()))
    {
        isSelected=true;
        NodeEvents::mousePressEvent(node, event);
    }


}

void NodeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(isSelected)
    {
       NodeEvents::mouseReleaseEvent(node, event);
    }
    isSelected=false;
}

void NodeItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    NodeEvents::contextMenuEvent(node, event);
}
