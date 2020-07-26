#include "changeelementaction.h"
#include "mainwindow.h"
#include "text.h"
#include "node.h"

ChangeElementAction::ChangeElementAction(void* element, ElementShape shape, bool isCreated) :
    isCreated(isCreated), shape(shape), element(element) {}

void ChangeElementAction::Do()
{
    auto window = MainWindow::instance();
    auto scene = window->scene();
    if (shape == ElementShape::Text)
    {
        auto text = static_cast<Text*>(element);
        if (isCreated)
        {
            text->putup_text(scene);
            window->graph->addText(text);
            auto item = text->get_item();
            connect(item, &TextItem::Selected, this, &ChangeElementAction::onTextSelected);
            text->build_text( QColor(), QFont());
        }
        else
        {
            window->graph->removeText(text);
            text->delete_text(scene);
        }
    }
    else if (shape == ElementShape::Diamond || shape == ElementShape::Rectangle)
    {
        auto node = static_cast<Node*>(element);
        if (isCreated)
        {
            node->SetFrameColor(window->bdColor);
            node->SetBackgroundColor(window->fillColor);
            auto item = node->getNodeItem();
            connect(item, &NodeItem::Selected, this, &ChangeElementAction::onNodeSelected);
            connect(item, &NodeItem::NewLocation, this, &ChangeElementAction::onNodeMoved);
            node->Paint(scene);
            MainWindow::instance()->graph->addNode(node);
        }
        else
        {
            node->Remove(scene);
            MainWindow::instance()->graph->removeNode(node);
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

void ChangeElementAction::onNodeMoved(Node* node, QPointF oldPosition)
{

}

void ChangeElementAction::onTextSelected(Text* text, bool isSelected)
{

}
