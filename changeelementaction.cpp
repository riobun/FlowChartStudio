#include "changeelementaction.h"
#include "mainwindow.h"
#include "text.h"
#include "node.h"
#include "arrow.h"

void onArrowSelected(Arrow* arrow, bool isSelected);

ChangeElementAction::ChangeElementAction(void* element, ElementShape shape, bool isCreated) :
    isCreated(isCreated), shape(shape), element(element) {}

void ChangeElementAction::Do()
{
    auto window = MainWindow::instance();
    auto scene = window->scene();
    if (isNode(shape))
    {
        auto node = static_cast<Node*>(element);
        if (isCreated)
        {
            auto item = node->getNodeItem();
            connect(item, &NodeItem::Selected, this, &ChangeElementAction::onNodeSelected);
            connect(item, &NodeItem::NewLocation, this, &ChangeElementAction::onNodeMoved);
            node->Paint(scene);
            MainWindow::instance()->graph()->addNode(node);
            MainWindow::instance()->graph()->addNode(node,MainWindow::instance()->index_tab(),shape);
        }
        else
        {
            auto arrows = node->getArrows();
            foreach (auto arrow, arrows)
            {
                arrow->removeArrow();
                auto action = new ChangeElementAction(arrow, ElementShape::Arrow, false);
                action->Do();
               }
            node->Remove(scene);
            MainWindow::instance()->graph()->removeNode(node);
            MainWindow::instance()->selectedNodes()->remove(node->GetID());
        }
    }
    else if (shape == ElementShape::Text)
    {
        auto text = static_cast<Text*>(element);
        if (isCreated)
        {
            auto parent = text->parent;
            if (parent) parent->content = text;
            window->graph()->addText(text);
            text->putup_text(scene);
            connect(text, &Text::Selected, this, &ChangeElementAction::onTextSelected);
            text->build_text(text->get_text_color(), text->get_text_font());
        }
        else
        {
            auto parent = text->parent;
            if (parent) parent->content = nullptr;
            window->graph()->removeText(text);
            window->selectedTexts()->removeAll(text);
            text->delete_text(scene);
        }
    }
    else if (shape == ElementShape::Arrow)
    {
        auto arrow = static_cast<Arrow*>(element);
        if (isCreated)
        {
            arrow->myStartItem->GetNode()->ConnectAsSource(arrow);
            arrow->myEndItem->GetNode()->ConnectAsSource(arrow);
            arrow->setZValue(-100.0);
            arrow->s = onArrowSelected;
            MainWindow::instance()->scene()->addItem(arrow);
            arrow->updatePosition();
            MainWindow::instance()->graph()->addArrow(arrow);
        }
        else
        {
            MainWindow::instance()->graph()->removeArrow(arrow);
            MainWindow::instance()->scene()->removeItem(arrow);
            MainWindow::instance()->selectedArrows()->remove(arrow->GetID());
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
    auto selectedTexts = MainWindow::instance()->selectedTexts();
    if (isSelected)
    {
        selectedTexts->append(text);
    }
    else
    {
        selectedTexts->removeAll(text);
        if (text->get_text_all() == "")
        {
            (new ChangeElementAction(text, ElementShape::Text, false))->Do();
        }
    }
}

void onArrowSelected(Arrow* arrow, bool isSelected)
{
    auto selectedArrows = MainWindow::instance()->selectedArrows();
    if (isSelected)
    {
        selectedArrows->insert(arrow->GetID(), arrow);
    }
    else
    {
        selectedArrows->remove(arrow->GetID());
    }
}
