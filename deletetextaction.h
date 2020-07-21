#ifndef DELETETEXTACTION_H
#define DELETETEXTACTION_H

#include "action.h"
#include "text.h"


class DeleteTextAction : public Action
{
    Q_OBJECT
public:
    DeleteTextAction(Text* text, bool isAdded = true);

    void Do() override;
    void Undo() override;
private:
    Text* text;
    QPointF point;
    QString string;
    QFont font;
    QColor color;
};

#endif // DELETETEXTACTION_H
