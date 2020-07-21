#include <QGraphicsScene>

#include "mainwindow.h"
#include "addelementaction.h"
#include "rectangle.h"
#include "diamond.h"
#include "text.h"


AddElementAction::AddElementAction(ElementShape shape, QPointF point) : shape(shape), point(point)
{

}

void AddElementAction::Do()
{
    auto window = MainWindow::instance();
    scene = window->scene();
    if (shape == ElementShape::Rectangle)
    {
        node = new Rectangle(point, 100.0, 50.0);
        node->Paint(scene);
    }
    else if (shape == ElementShape::Diamond)
    {
        node = new Diamond(point, 100.0, 50.0);
        node->Paint(scene);
    }
    else if (shape == ElementShape::Text)
    {
        auto text = new Text(point.toPoint(), 100.0, 50.0);
        text->build_text(scene, QColor(), QFont());
    }
}

void AddElementAction::Undo()
{
    if (node != nullptr)
    {
        node->Remove(scene);
    }
}
