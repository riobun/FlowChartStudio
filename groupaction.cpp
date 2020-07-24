#include "groupaction.h"


void GroupAction::Do()
{
    foreach (auto action, actions)
    {
        action->Do();
    }
}

void GroupAction::Undo()
{
    for (auto i = actions.size(); i >= 0; i--)
    {
        actions[i]->Undo();
    }
}
