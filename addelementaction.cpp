#include <QGraphicsScene>

#include "mainwindow.h"
#include "addelementaction.h"
#include "deleteelementaction.h"
#include "rectangle.h"
#include "diamond.h"
#include "text.h"


AddElementAction::AddElementAction(ElementShape shape, QPointF point, QSizeF size, bool isAdded) :
    Action(isAdded), shape(shape), point(point), size(size)
{

}

void AddElementAction::Do()
{
    auto scene = MainWindow::instance()->scene();
    if (shape == ElementShape::Rectangle)
    {
        node = new Rectangle(point, size.rwidth(), size.height());
        node->Paint(scene);
    }
    else if (shape == ElementShape::Diamond)
    {
        node = new Diamond(point, size.rwidth(), size.height());
        node->Paint(scene);
    }
}

void AddElementAction::Undo()
{
    DeleteElementAction(node, false).Do();
}
