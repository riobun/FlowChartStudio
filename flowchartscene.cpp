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
#include "nodeevents.h"
#include "innerinputnode.h"
#include "inneroutputnode.h"


FlowChartScene::FlowChartScene()
{

}

FlowChartScene::~FlowChartScene()
{
    delete graph;
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
        if (isNode(shape))
        {
            Node* node;
            constexpr double width = 100;
            constexpr double height = 50;
            switch (shape)
            {
                case ElementShape::Input: node = new InputNode(point, width, height); break;
                case ElementShape::Output: node = new OutputNode(point, width, height); break;
                case ElementShape::Diamond: node = new Diamond(point, width, height); break;
                case ElementShape::SubGraph: node = new SubgraphNode(point, width); break;
                case ElementShape::Rectangle: node = new Rectangle(point, width, height); break;
                case ElementShape::InnerInput: node = new InnerInputNode(point, width, height); break;
                case ElementShape::InnerOutput: node = new InnerOutputNode(point, width, height); break;
                default: throw;
            }
            node->SetFrameColor(window->bdColor);
            node->SetBackgroundColor(window->fillColor);
            auto action = new ChangeElementAction(node, shape, true);
            action->Do();
        }
        else if (shape == ElementShape::Text)
        {
            auto text = new Text(point);
            text->reset_color(window->textColor);
            text->reset_font(QFont(window->fontFamily, window->fontSize));
            auto action = new ChangeElementAction(text, ElementShape::Text, true);
            action->Do();
        }
        else if (shape == ElementShape::Arrow)
        {
            lineFrom = window->graph()->searchNode(point);
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
        auto nodes = MainWindow::instance()->graph()->searchNodes(rect);
        foreach (auto node, nodes)
        {
            node->getNodeItem()->SetSelected(true);
        }
        auto texts = MainWindow::instance()->graph()->searchTexts(rect);
        foreach (auto text, texts)
        {
            text->getTextItem()->SetSelected(true);
        }
        auto arrows = MainWindow::instance()->graph()->searchArrows(rect);
        foreach (auto arrow,arrows)
        {
            arrow->setSelected(true);
        }
        rect->Remove(this);
        delete rect;
        rect = nullptr;
    }
    if (line)
    {
        auto to = MainWindow::instance()->graph()->searchNode(event->scenePos());
        if (to)
        {
            auto arrow = new Arrow(lineFrom->getNodeItem(),to->getNodeItem(),1);
            arrow->setArrowColor(MainWindow::instance()->lineColor);
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
        auto selectAllAction = menu.addAction("全选");
        selectAllAction->setShortcut(QKeySequence::SelectAll);
        auto selectedAction = menu.exec(event->screenPos());
        if (selectedAction == pasteAction)
        {
            pasteElements(event);
        }
        else if (selectedAction == selectAllAction)
        {
            NodeEvents::selectAll();
        }
    }
}

void FlowChartScene::pasteElements(QGraphicsSceneContextMenuEvent *event)
{
    auto action = new GroupAction();
    auto graph = MainWindow::instance()->cutGraph;
    QPointF offset;
    if (event && graph->node) offset = event->scenePos() - graph->node->GetLocation();
    else offset = QPointF();
    QMap<Node*, Node*> nodes;
    foreach (auto node, graph->getNodes())
    {
        Node* newNode;
        ElementShape shape;
        if (dynamic_cast<Rectangle*>(node))
        {
            newNode = new Rectangle(node->GetLocation() + offset, node->GetWidth(), node->GetHeight());
            shape = ElementShape::Rectangle;
        }
        else if (dynamic_cast<Diamond*>(node))
        {
            newNode = new Diamond(node->GetLocation() + offset, node->GetWidth(), node->GetHeight());
            shape = ElementShape::Diamond;
        }
        else if (dynamic_cast<SubgraphNode*>(node))
        {
            newNode = new SubgraphNode(node->GetLocation() + offset, node->GetWidth());
            shape = ElementShape::SubGraph;
        }
        else if (dynamic_cast<InputNode*>(node))
        {
            newNode = new InputNode(node->GetLocation() + offset, node->GetWidth(), node->GetHeight());
            shape = ElementShape::Input;
        }
        else if (dynamic_cast<OutputNode*>(node))
        {
            newNode = new OutputNode(node->GetLocation() + offset, node->GetWidth(), node->GetHeight());
            shape = ElementShape::Output;
        }
        newNode->SetFrameColor(node->GetFrameColor());
        newNode->SetBackgroundColor(node->GetBackgroundColor());
        *action << new ChangeElementAction(newNode, shape, true);
        nodes.insert(node, newNode);
    }
    foreach (auto text, graph->getTexts())
    {
        auto newText = new Text(text->get_text_location());
        newText->reset_font(text->get_text_font());
        *action << new ChangeElementAction(newText, ElementShape::Text, true);
    }
    foreach (auto arrow, graph->getArrows())
    {
        auto graph = MainWindow::instance()->graph();
        auto fromNode = nodes[arrow->startItem()->GetNode()];
        if (!fromNode)
        {
            fromNode = arrow->startItem()->GetNode();
            if (!graph->getNodes().contains(fromNode->GetID())) continue;
        }
        auto toNode = nodes[arrow->endItem()->GetNode()];
        if (!toNode)
        {
            toNode = arrow->endItem()->GetNode();
            if (!graph->getNodes().contains(toNode->GetID())) continue;
        }

        auto newArrow = new Arrow(fromNode->getNodeItem(), toNode->getNodeItem(), 1);
        newArrow->setArrowColor(arrow->getColor());
        *action << new ChangeElementAction(newArrow, ElementShape::Arrow, true);
    }
    action->Do();
    graph->clear();
}

void FlowChartScene::clearSelect()
{
    auto window = MainWindow::instance();
    window->selectedNodes()->clear();
    window->selectedTexts()->clear();
    window->selectedArrows()->clear();
    clearSelection();
}
