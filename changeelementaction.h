#ifndef CHANGEELEMENTACTION_H
#define CHANGEELEMENTACTION_H

#include "action.h"
#include "elementshape.h"
#include "node.h"

class Scene;

class ChangeElementAction : public Action
{
    Q_OBJECT

public:
    ChangeElementAction(void* element, ElementShape shape, bool isCreated, Scene* Scene = nullptr);
    ~ChangeElementAction();

    void Do() override;
    void Undo() override;

private:
    bool isCreated;
    ElementShape shape;
    void* element;
};

#endif // CHANGEELEMENTACTION_H
