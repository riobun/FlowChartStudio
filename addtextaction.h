#ifndef ADDTEXTACTION_H
#define ADDTEXTACTION_H

#include "action.h"
#include "text.h"


class AddTextAction : public Action
{
    Q_OBJECT
public:
    AddTextAction(QPointF point, QString string = "", QFont font = QFont(), QColor color = QColor(),
                  bool isAdded = true);

    void Do() override;
    void Undo() override;
private:
    Text* text;
    QPointF point;
    QString string;
    QFont font;
    QColor color;
};

#endif // ADDTEXTACTION_H
