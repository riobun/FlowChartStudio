
#include <QMenu>

#include "textevents.h"
#include "changeelementaction.h"
#include "mainwindow.h"


void NodeEvents::contextMenuEvent(Text* text, QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;
    auto deleteAction = menu.addAction("删除");
    deleteAction->setShortcut(QKeySequence::Delete);
    auto selectedAction = menu.exec(event->screenPos());
    if (selectedAction == deleteAction)
    {
        auto action = new ChangeElementAction(text, ElementShape::Rectangle, false);
        action->Do();
    }
}

void NodeEvents::mousePressEvent(Text* text, QGraphicsSceneMouseEvent *event)
{

}

void NodeEvents::mouseReleaseEvent(Text* text, QGraphicsSceneMouseEvent *event)
{

}
© 202
