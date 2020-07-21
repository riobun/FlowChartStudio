#include "deleteelementaction.h"
#include "addelementaction.h"
#include "mainwindow.h"
#include "rectangle.h"
#include "diamond.h"

DeleteElementAction::DeleteElementAction(Node* node, bool isAdded) : Action(isAdded), node(node)
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

void DeleteElementAction::Do()
{
    auto scene = MainWindow::instance()->scene();
    node->Remove(scene);
}

void DeleteElementAction::Undo()
{
    AddElementAction(shape, point, size, false).Do();
}
