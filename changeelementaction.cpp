#include "changeelementaction.h"
#include "mainwindow.h"
#include "text.h"
#include "node.h"

ChangeElementAction::ChangeElementAction(void* element, ElementShape shape, bool isCreated) :
    isCreated(isCreated), shape(shape), element(element) {}

void ChangeElementAction::Do()
{
    auto scene = MainWindow::instance()->scene();
    if (shape == ElementShape::Text)
    {
        auto text = static_cast<Text*>(element);
        if (isCreated)
        {
            text->putup_text(scene);
            text->build_text( QColor(), QFont());
        }
        else
        {
            text->delete_text(scene);
        }
    }
    else if (shape == ElementShape::Diamond || shape == ElementShape::Rectangle)
    {
        auto node = static_cast<Node*>(element);
        if (isCreated)
        {
            auto item = node->getNodeItem();
            connect(item, &NodeItem::Selected, this, &ChangeElementAction::onNodeSelected);
            node->Paint(scene);
        }
        else
        {
            node->Remove(scene);
        }
    }
}

void ChangeElementAction::Undo()
{
    ChangeElementAction(element, shape, !isCreated).Do();
}

void ChangeElementAction::onNodeSelected(Node* node, bool isSelected)
{
    auto selectedNodes = MainWindow::instance()->selectedNodes();
    if (isSelected)
    {
        selectedNodes->insert(node->GetID(), node);
    }
    else
    {
        selectedNodes->remove(node->GetID());
    }
}
