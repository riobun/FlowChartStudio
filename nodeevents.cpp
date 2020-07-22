#include <QMenu>

#include "nodeevents.h"
#include "changeelementaction.h"
#include "mainwindow.h"


void NodeEvents::contextMenuEvent(Node* node, QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;
    auto deleteAction = menu.addAction("删除");
    deleteAction->setShortcut(QKeySequence::Delete);
    auto selectedAction = menu.exec(event->screenPos());
    if (selectedAction == deleteAction)
    {
        auto action = new ChangeElementAction(node, ElementShape::Rectangle, false);
        action->Do();
    }
}

void NodeEvents::mousePressEvent(Node* node, QGraphicsSceneMouseEvent *event)
{

}

void NodeEvents::mouseReleaseEvent(Node* node, QGraphicsSceneMouseEvent *event)
{

}
