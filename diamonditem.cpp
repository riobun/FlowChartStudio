#include "diamonditem.h"
#include "nodeevents.h"

/*
void DiamondItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

}



void DiamondItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

}



void DiamondItem::keyPressEvent(QKeyEvent *event)
{

}

void DiamondItem::keyReleaseEvent(QKeyEvent *event)
{

}
*/

void DiamondItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    NodeEvents::mousePressEvent(node, event);
}

void DiamondItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    NodeEvents::mouseReleaseEvent(node, event);
}

void DiamondItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    NodeEvents::contextMenuEvent(node, event);
}
