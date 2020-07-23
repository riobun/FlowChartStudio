#include "flowchartscene.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QMapIterator>
#include "mainwindow.h"
#include "node.h"

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
    QGraphicsScene::mousePressEvent(event);
    if (!event->isAccepted())
    {
        if (event->button() == Qt::MouseButton::LeftButton)
        {
            selectLeftTop = event->scenePos();
            rect = new Rectangle(event->scenePos(), 1, 1);
            rect->Paint(this);
        }
    }
    keyDownPosition = event->scenePos();
}

void FlowChartScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
    if (rect)
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
}

void FlowChartScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // 取消已经选中的节点。
    if (!isCtrlDown && keyDownPosition == event->scenePos())
    {
        foreach (auto node, *MainWindow::instance()->selectedNodes())
        {
            node->getNodeItem()->SetSelected(false);
        }
    }
    QGraphicsScene::mouseReleaseEvent(event);
    if (rect)
    {

        rect->Remove(this);
        rect = nullptr;
    }
}
