#include "flowchartscene.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QMapIterator>
#include "mainwindow.h"
#include "node.h"
#include "changeelementaction.h"
#include "diamond.h"
#include "arrow.h"
#include <QMenu>
#include "groupaction.h"
#include "subgraphnode.h"
#include "inputnode.h"
#include "outputnode.h"


FlowChartScene::FlowChartScene()
{

}

void FlowChartScene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Control)
    {
        isCtrlDown = true;
    }
}

void FlowChartScene::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Control)
    {
        isCtrlDown = false;
    }
}

void FlowChartScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::MouseButton::LeftButton)
    {
        auto window = MainWindow::instance();
        auto shape = window->nextAddedShape();
        auto point = event->scenePos();
        if (shape == ElementShape::Text)
        {
            auto text = new Text(point);
            auto action = new ChangeElementAction(text, ElementShape::Text, true);
            action->Do();
        }
        else if (shape == ElementShape::Diamond)
        {
            auto diamond = new Diamond(point, 100.0, 50.0);
            auto action = new ChangeElementAction(diamond, ElementShape::Diamond, true);
            action->Do();
        }
        else if (shape == ElementShape::Rectangle)
        {
            auto rectangle = new Rectangle(point, 100.0, 50.0);
            auto action = new ChangeElementAction(rectangle, ElementShape::Rectangle, true);
            action->Do();
        }
        else if (shape == ElementShape::Arrow)
        {
            lineFrom = window->graph->searchNode(point);
            if (lineFrom)
            {
                fromLinePosition = lineFrom->GetLocation();
                line = new QGraphicsLineItem(QLineF(fromLinePosition, fromLinePosition));
                line->setPen(QPen(window->lineColor, 2));
                addItem(line);
            }
            window->setNextAddedShape(ElementShape::Unknown);
            return;
        }
        else if (shape == ElementShape::SubGraph)
        {
            auto subgraph = new SubgraphNode(point, 100.0);
            auto action = new ChangeElementAction(subgraph, ElementShape::SubGraph, true);
            action->Do();
        }
        else if (shape == ElementShape::Input)
        {
            auto input = new InputNode(point, 100.0, 50.0);
            auto action = new ChangeElementAction(input, ElementShape::Input, true);
            action->Do();
        }
        else if (shape == ElementShape::Output)
        {
            auto output = new OutputNode(point, 100.0, 50.0);
            auto action = new ChangeElementAction(output, ElementShape::Output, true);
            action->Do();
        }
        window->setNextAddedShape(ElementShape::Unknown);
    }
    else if (event->button() == Qt::MouseButton::RightButton)
    {
        return;
    }
    QGraphicsScene::mousePressEvent(event);
    if (!event->isAccepted())
    {
        MainWindow::instance()->setNextAddedShape(ElementShape::Unknown);
        selectLeftTop = event->scenePos();
        rect = new Rectangle(event->scenePos(), 1, 1);
        rect->getNodeItem()->setZValue(-1000);
        rect->Paint(this);
    }
    keyDownPosition = event->scenePos();
}

void FlowChartScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (line)
    {
        auto toPosition = event->scenePos();
        line->setLine(QLineF(fromLinePosition, toPosition));
    }
    else if (rect)
    {
        QPointF size = event->scenePos() - selectLeftTop;
        QPointF position = (selectLeftTop + event->scenePos()) / 2;
        if (size.rx() < 0)
        {
            size.rx() = -size.rx();
        }
        if (size.ry() < 0)
        {
            size.ry() = -size.ry();
        }
        rect->SetWidth(size.rx());
        rect->SetHeight(size.ry());
        rect->SetLocation(position);
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void FlowChartScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);
    if (rect)
    {
        auto nodes = MainWindow::instance()->graph->searchNodes(rect);
        foreach (auto node, nodes)
        {
            node->getNodeItem()->SetSelected(true);
        }
        auto texts = MainWindow::instance()->graph->searchTexts(rect);
        foreach (auto text, texts)
        {
            text->getTextItem()->SetSelected(true);
        }
        rect->Remove(this);
        delete rect;
        rect = nullptr;
    }
    if (line)
    {
        auto to = MainWindow::instance()->graph->searchNode(event->scenePos());
        if (to)
        {
            auto arrow = new Arrow(lineFrom->getNodeItem(),to->getNodeItem());
            auto action = new ChangeElementAction(arrow, ElementShape::Arrow, true);
            action->Do();
        }
        MainWindow::instance()->scene()->removeItem(line);
        delete line;
        line = nullptr;
    }
}

void FlowChartScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QGraphicsScene::contextMenuEvent(event);
    if (!event->isAccepted())
    {
        QMenu menu;
        auto pasteAction = menu.addAction("粘贴");
        pasteAction->setShortcut(QKeySequence::Paste);
        auto selectedAction = menu.exec(event->screenPos());
        if (selectedAction == pasteAction)
        {
            pasteElements();
        }
    }
}

void FlowChartScene::pasteElements()
{
    auto action = new GroupAction();
    auto graph = MainWindow::instance()->cutGraph;
    QMap<Node*, Node*> nodes;
    foreach (auto node, graph->getNodes())
    {
        Node* newNode;
        ElementShape shape;
        if (dynamic_cast<Rectangle*>(node))
        {
            newNode = new Rectangle(node->GetLocation(), node->GetWidth(), node->GetHeight());
            shape = ElementShape::Rectangle;
        }
        else if (dynamic_cast<Diamond*>(node))
        {
            newNode = new Diamond(node->GetLocation(), node->GetWidth(), node->GetHeight());
            shape = ElementShape::Diamond;
        }
        else if (dynamic_cast<SubgraphNode*>(node))
        {
            newNode = new SubgraphNode(node->GetLocation(), node->GetWidth());
            shape = ElementShape::SubGraph;
        }
        else if (dynamic_cast<InputNode*>(node))
        {
            newNode = new InputNode(node->GetLocation(), node->GetWidth(), node->GetHeight());
            shape = ElementShape::Input;
        }
        else if (dynamic_cast<OutputNode*>(node))
        {
            newNode = new OutputNode(node->GetLocation(), node->GetWidth(), node->GetHeight());
            shape = ElementShape::Output;
        }
        *action << new ChangeElementAction(newNode, shape, true);
        nodes.insert(node, newNode);
    }
    foreach (auto text, graph->getTexts())
    {
        auto newText = new Text(text->get_text_location());
        *action << new ChangeElementAction(newText, ElementShape::Text, true);
    }
    foreach (auto arrow, graph->getArrows())
    {
        auto newArrow = new Arrow(nodes[arrow->startItem()->GetNode()]->getNodeItem(),
                nodes[arrow->endItem()->GetNode()]->getNodeItem());
        *action << new ChangeElementAction(newArrow, ElementShape::Arrow, true);
    }
    action->Do();
    graph->clear();
}
