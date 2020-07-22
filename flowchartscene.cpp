#include "flowchartscene.h"

FlowChartScene::FlowChartScene()
{

}

void FlowChartScene::keyPressEvent(QKeyEvent *event)
{

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
}

void FlowChartScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
    if (rect)
    {
        QPointF size = event->scenePos() - selectLeftTop;
        QPointF position = selectLeftTop + size / 2;
        if (size.rx() < 0) size.rx() = -size.rx();
        if (size.ry() < 0) size.ry() = -size.ry();
        rect->SetWidth(size.rx());
        rect->SetHeight(size.ry());
        rect->SetLocation(position - selectLeftTop / 2);
    }
}

void FlowChartScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);
    if (rect)
    {

        rect->Remove(this);
        rect = nullptr;
    }
}
