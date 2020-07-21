#ifndef ADDTEXTACTION_H
#define ADDTEXTACTION_H

#include "action.h"
#include "text.h"


class ChangeTextAction : public Action
{
    Q_OBJECT
public:
    ChangeTextAction(bool isCreated, QPointF point, QString string = "", QFont font = QFont(),
                     QColor color = QColor(), Text* text = nullptr, bool isAdded = true);

    void Do() override;
    void Undo() override;
private:
    bool isCreated;
    Text* text;
    QPointF point;
    QString string;
    QFont font;
    QColor color;
};

#endif // ADDTEXTACTION_H
