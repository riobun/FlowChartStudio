#include "rectangleitem.h"
#include "nodeevents.h"

/*
void RectangleItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

}

void RectangleItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void RectangleItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}

void RectangleItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

}

void RectangleItem::keyPressEvent(QKeyEvent *event)
{

}

void RectangleItem::keyReleaseEvent(QKeyEvent *event)
{

}
*/

void RectangleItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    NodeEvents::contextMenuEvent(node, event);
}
