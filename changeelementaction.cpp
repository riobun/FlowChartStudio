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
    if (shape == ElementShape::Text)
    {
        auto text = static_cast<Text*>(element);
        if (isCreated)
        {
            text->putup_text(scene);
            window->graph()->addText(text);
            connect(text, &Text::Selected, this, &ChangeElementAction::onTextSelected);
            text->build_text(MainWindow::instance()->textColor, QFont());
        }
        else
        {
            window->graph()->removeText(text);
            window->selectedTexts()->removeAll(text);
            text->delete_text(scene);
        }
    }
    else if (shape == ElementShape::Diamond || shape == ElementShape::Rectangle ||
             shape == ElementShape::SubGraph || shape == ElementShape::Input ||
             shape == ElementShape::Output || shape==ElementShape::Arrownode)
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
            MainWindow::instance()->graph()->addNode(node);
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
            arrow->setArrowColor(MainWindow::instance()->lineColor);
            arrow->updatePosition();
            MainWindow::instance()->graph()->addArrow(arrow);
            arrow->s = onArrowSelected;
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
