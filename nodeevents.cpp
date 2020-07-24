#include <QMenu>

#include "nodeevents.h"
#include "changeelementaction.h"
#include "mainwindow.h"


void NodeEvents::contextMenuEvent(Node* node, QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;
    auto deleteAction = menu.addAction("删除");
    deleteAction->setShortcut(QKeySequence::Delete);
    auto subGraphAction = menu.addAction("生成子图");
    auto selectedAction = menu.exec(event->screenPos());
    if (selectedAction == deleteAction)
    {
        foreach (auto node, *MainWindow::instance()->selectedNodes())
        {
            auto action = new ChangeElementAction(node, ElementShape::Rectangle, false);
            action->Do();
        }
    }
    else if (selectedAction == subGraphAction)
    {
        QVector<Node*> nodes;
        foreach (auto node, *MainWindow::instance()->selectedNodes())
        {
            nodes.append(node);
        }
        QVector<Text*> texts;
        QVector<Graph*> graphs;
        new Graph(nodes, texts, graphs);
    }
}

void NodeEvents::mousePressEvent(Node* node, QGraphicsSceneMouseEvent *event)
{

}

void NodeEvents::mouseReleaseEvent(Node* node, QGraphicsSceneMouseEvent *event)
{

}
