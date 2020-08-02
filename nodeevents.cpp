#include <QMenu>

#include "nodeevents.h"
#include "changeelementaction.h"
#include "mainwindow.h"
#include "groupaction.h"
#include "arrow.h"
#include "subgraphnode.h"


void NodeEvents::contextMenuEvent(Node* node, QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;
    auto deleteAction = menu.addAction("删除");
    deleteAction->setShortcut(QKeySequence::Delete);
    QAction* subGraphAction;
    if (dynamic_cast<SubgraphNode*>(node))
    {
        subGraphAction = menu.addAction("打开子图");
    }
    auto cutAction = menu.addAction("剪切");
    cutAction->setShortcut(QKeySequence::Cut);
    auto copyAction = menu.addAction("复制");
    copyAction->setShortcut(QKeySequence::Copy);
    auto selectedAction = menu.exec(event->screenPos());
    if (selectedAction == deleteAction)
    {
        deleteElemets();
    }
    else if (selectedAction && selectedAction == subGraphAction)
    {
        auto sgnode = static_cast<SubgraphNode*>(node);
        sgnode->OpenSubGraph();
    }
    else if (selectedAction == copyAction)
    {
        copyElements(node);
    }
    else if (selectedAction == cutAction)
    {
        cutElements(node);
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

void NodeEvents::cutElements(Node* node)
{
    auto graph = MainWindow::instance()->cutGraph;
    auto scene = MainWindow::instance()->scene();
    graph->clear();
    graph->node = node;
    auto action = new GroupAction();
    /*foreach (auto node, *MainWindow::instance()->selectedNodes())
    {
        if (!graph->node) graph->node = node;
        foreach (auto arrow, node->getSourceArrows())
        {
            graph->addArrow(arrow);
        }
    }*/
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
        *action << new ChangeElementAction(arrow, ElementShape::Arrow, false);
    }
    action->Do();
}

void NodeEvents::copyElements(Node* node)
{
    auto graph = MainWindow::instance()->cutGraph;
    graph->clear();
    graph->node = node;
    /*foreach (auto node, *MainWindow::instance()->selectedNodes())
    {
        if (!graph->node) graph->node = node;
        foreach (auto arrow, node->getSourceArrows())
        {
            graph->addArrow(arrow);
        }
    }*/
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

void NodeEvents::mousePressEvent(Node* node, QGraphicsSceneMouseEvent *event)
{

}

void NodeEvents::mouseReleaseEvent(Node* node, QGraphicsSceneMouseEvent *event)
{

}

void NodeEvents::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    foreach (auto node, *MainWindow::instance()->selectedNodes())
    {
        node->SetLocation(node->GetLocation()+event->pos()-event->lastPos());
        Text* text=node->content;
        if(text)
        {
            text->move_text(text->get_text_location()+event->pos()-event->lastPos());
        }
    }
    foreach (auto text, *MainWindow::instance()->selectedTexts())
    {
        text->move_text((text->get_text_location()+event->pos()-event->lastPos()));
    }
}

void NodeEvents::selectAll()
{
    auto graph = MainWindow::instance()->graph();
    foreach (auto node, graph->getNodes())
    {
        node->getNodeItem()->SetSelected(true);
    }
    foreach (auto arrow, graph->getArrows())
    {
        arrow->setSelected(true);
    }
    foreach (auto text, graph->getTexts())
    {
        text->setSelected(true);
    }
}

void NodeEvents::scaleNodes(Node* node, QGraphicsSceneMouseEvent *event)
{
    QPointF pos = event->pos();
    double nw=sqrt(pow(node->GetLocation().x() - pos.x(), 2)),nh=sqrt(pow(node->GetLocation().y() - pos.y(), 2));
    double cw = nw * 2 - node->GetWidth(), ch = nh * 2 - node->GetHeight();
    foreach (auto node, *MainWindow::instance()->selectedNodes())
    {
        node->SetHeight(node->GetHeight() + ch);
        node->SetWidth(node->GetWidth() + cw);
        foreach (auto arrow, node->getArrows())
        {
            arrow->update();
        }
    }
}
