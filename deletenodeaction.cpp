#include "deletenodeaction.h"
#include "addnodeaction.h"
#include "mainwindow.h"
#include "rectangle.h"
#include "diamond.h"

DeleteNodeAction::DeleteNodeAction(Node* node, bool isAdded) : Action(isAdded), node(node)
{
    point = node->GetLocation();
    size = QSizeF(node->GetWidth(), node->GetHeight());
    if (dynamic_cast<Rectangle*>(node))
    {
        shape = ElementShape::Rectangle;
    }
    else if (dynamic_cast<Diamond*>(node))
    {
        shape = ElementShape::Diamond;
    }
}

void DeleteNodeAction::Do()
{
    auto scene = MainWindow::instance()->scene();
    node->Remove(scene);
}

void DeleteNodeAction::Undo()
{
    AddNodeAction(shape, point, size, false).Do();
}
