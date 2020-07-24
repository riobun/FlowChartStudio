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
            lineFrom->ConnectAsSource(arrow);
            to->ConnectAsDestination(arrow);
            arrow->setZValue(-100.0);
            MainWindow::instance()->scene()->addItem(arrow);
            arrow->updatePosition();
        }
        MainWindow::instance()->scene()->removeItem(line);
        delete line;
        line = nullptr;
    }
}
