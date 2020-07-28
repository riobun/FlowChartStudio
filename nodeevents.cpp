#include <QMenu>

#include "nodeevents.h"
#include "changeelementaction.h"
#include "mainwindow.h"
#include "groupaction.h"
#include "arrow.h"


void NodeEvents::contextMenuEvent(Node* node, QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;
    auto deleteAction = menu.addAction("删除");
    deleteAction->setShortcut(QKeySequence::Delete);
    auto subGraphAction = menu.addAction("生成子图");
    auto cutAction = menu.addAction("剪切");
    cutAction->setShortcut(QKeySequence::Cut);
    auto copyAction = menu.addAction("复制");
    copyAction->setShortcut(QKeySequence::Copy);
    auto selectedAction = menu.exec(event->screenPos());
    if (selectedAction == deleteAction)
    {
        deleteElemets();
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
    else if (selectedAction == copyAction)
    {
        auto graph = MainWindow::instance()->cutGraph;
        graph->clear();
        foreach (auto node, *MainWindow::instance()->selectedNodes())
        {
            graph->addNode(node);
        }
        foreach (auto text, *MainWindow::instance()->selectedTexts())
        {
            graph->addText(text);
        }
        foreach (auto arrow, *MainWindow::instance()->selectedArrows())
        {
            graph->addArrow(arrow);
        }
    }
    else if (selectedAction == cutAction)
    {
        auto graph = MainWindow::instance()->cutGraph;
        auto scene = MainWindow::instance()->scene();
        graph->clear();
        auto action = new GroupAction();
        foreach (auto node, *MainWindow::instance()->selectedNodes())
        {
            graph->addNode(node);
            *action << new ChangeElementAction(node, ElementShape::Rectangle, false);
        }
        foreach (auto text, *MainWindow::instance()->selectedTexts())
        {
            graph->addText(text);
            *action << new ChangeElementAction(text, ElementShape::Text, false);
        }
        foreach (auto arrow, *MainWindow::instance()->selectedArrows())
        {
            graph->addArrow(arrow);
            arrow->removeArrow();
            *action << new ChangeElementAction(arrow, ElementShape::Arrow, false);
        }
        action->Do();
    }
}

void NodeEvents::deleteElemets()
{
    auto action = new GroupAction;
    foreach (auto node, *MainWindow::instance()->selectedNodes())
    {
        *action << new ChangeElementAction(node, ElementShape::Rectangle, false);
    }
    foreach (auto text, *MainWindow::instance()->selectedTexts())
    {
        *action << new ChangeElementAction(text, ElementShape::Text, false);
    }
    foreach (auto arrow, *MainWindow::instance()->selectedArrows())
    {
        arrow->removeArrow();
        *action << new ChangeElementAction(arrow, ElementShape::Arrow, false);
    }
    action->Do();
}

void NodeEvents::mousePressEvent(Node* node, QGraphicsSceneMouseEvent *event)
{

}

void NodeEvents::mouseReleaseEvent(Node* node, QGraphicsSceneMouseEvent *event)
{

}
