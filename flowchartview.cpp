#include <QMouseEvent>

#include "flowchartview.h"
#include "mainwindow.h"
#include "rectangle.h"
#include "diamond.h"
#include "text.h"


FlowChartView::FlowChartView(QWidget *parent) : QGraphicsView(parent)
{

}

void FlowChartView::mousePressEvent(QMouseEvent *event)
{
    auto window = MainWindow::instance();
    auto scene = window->scene();
    auto shape = window->nextAddedShape();
    auto button = event->button();
    if (button == Qt::MouseButton::LeftButton)
    {
        auto rawPoint = event->localPos();
        auto point = mapToScene(rawPoint.toPoint());
        if (shape == ElementShape::Rectangle)
        {
            auto rectangle = new Rectangle(point, 100.0, 50.0);
            rectangle->Paint(scene);
        }
        else if (shape == ElementShape::Diamond)
        {
            auto diamond = new Diamond(point, 100.0, 50.0);
            diamond->Paint(scene);
        }
        else if (shape == ElementShape::Text)
        {
            auto text = new Text(point.toPoint(), 100.0, 50.0);
            text->build_text(scene, QColor(), QFont());
        }
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
