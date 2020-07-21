#ifndef CHANGEELEMENTACTION_H
#define CHANGEELEMENTACTION_H

#include "action.h"
#include "elementshape.h"


class ChangeElementAction : public Action
{
public:
    ChangeElementAction(void* element, ElementShape shape, bool isCreated);

    void Do() override;
    void Undo() override;
private:
    bool isCreated;
    ElementShape shape;
    void* element;
};

#endif // CHANGEELEMENTACTION_H
