#include <QMouseEvent>

#include "flowchartview.h"
#include "mainwindow.h"
#include "rectangle.h"
#include "diamond.h"
#include "text.h"
#include "changeelementaction.h"


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
            auto text = new Text(point, 100.0, 50.0);
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
