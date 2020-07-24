#ifndef GROUPACTION_H
#define GROUPACTION_H

#include <QVector>

#include "action.h"


class GroupAction : public Action
{
    Q_OBJECT

public:
    GroupAction& operator<<(Action* action) { actions.append(action); }

    void Do() override;
    void Undo() override;

private:
    QVector<Action*> actions;
};

#endif // GROUPACTION_H
