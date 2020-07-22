#include "flowchartscene.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

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
        QPointF position = (selectLeftTop + event->scenePos()) / 2;
        if (size.rx() < 0)
        {
            size.rx() = -size.rx();
            //position.rx() -= event->scenePos().rx() / 2;
        }
        //else position.rx() -= selectLeftTop.rx() / 2;
        if (size.ry() < 0)
        {
            size.ry() = -size.ry();
            //position.ry() -= event->scenePos().ry() / 2;
        }
        //else position.ry() -= selectLeftTop.ry() / 2;
        rect->SetWidth(size.rx());
        rect->SetHeight(size.ry());
        rect->SetLocation(position);
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
