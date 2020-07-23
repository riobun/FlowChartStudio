#ifndef CHANGEELEMENTACTION_H
#define CHANGEELEMENTACTION_H

#include "action.h"
#include "elementshape.h"
#include "node.h"


class ChangeElementAction : public Action
{
    Q_OBJECT

public:
    ChangeElementAction(void* element, ElementShape shape, bool isCreated);

    void Do() override;
    void Undo() override;
private slots:
    void onNodeSelected(Node* node, bool isSelected);
private:
    bool isCreated;
    ElementShape shape;
    void* element;
};

#endif // CHANGEELEMENTACTION_H
