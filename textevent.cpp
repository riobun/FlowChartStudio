
#include <QMenu>

#include "textevent.h"
#include "changeelementaction.h"
#include "mainwindow.h"


void TextEvents::contextMenuEvent(Text* text, QGraphicsSceneContextMenuEvent *event)
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

void TextEvents::mousePressEvent(Text* text, QGraphicsSceneMouseEvent *event)
{

}

void TextEvents::mouseReleaseEvent(Text* text, QGraphicsSceneMouseEvent *event)
{

}
© 202
