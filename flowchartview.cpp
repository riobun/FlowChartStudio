#include <QMouseEvent>

#include "flowchartview.h"
#include "mainwindow.h"
#include "rectangle.h"
#include "diamond.h"
#include "text.h"
#include "addelementaction.h"
#include "addtextaction.h"


FlowChartView::FlowChartView(QWidget *parent) : QGraphicsView(parent)
{

}

void FlowChartView::mousePressEvent(QMouseEvent *event)
{
    auto window = MainWindow::instance();
    auto shape = window->nextAddedShape();
    auto button = event->button();
    if (button == Qt::MouseButton::LeftButton)
    {
        auto rawPoint = event->localPos();
        auto point = mapToScene(rawPoint.toPoint());
        if (shape == ElementShape::Text)
        {
            auto action = new AddTextAction(point);
            action->Do();
        }
        else if (shape != ElementShape::Unknown)
        {
            auto action = new AddElementAction(shape, point, QSizeF(100, 50));
            action->Do();
        }
        window->setNextAddedShape(ElementShape::Unknown);
        mousePressedPoint = point;
    }
    else if (button == Qt::MouseButton::RightButton)
    {

    }
    QGraphicsView::mousePressEvent(event);
}

void FlowChartView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
}
