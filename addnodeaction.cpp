#include <QGraphicsScene>

#include "mainwindow.h"
#include "addnodeaction.h"
#include "deletenodeaction.h"
#include "rectangle.h"
#include "diamond.h"
#include "text.h"


AddNodeAction::AddNodeAction(ElementShape shape, QPointF point, QSizeF size, bool isAdded) :
    Action(isAdded), shape(shape), point(point), size(size)
{

}

void AddNodeAction::Do()
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

void AddNodeAction::Undo()
{
    DeleteNodeAction(node, false).Do();
}
