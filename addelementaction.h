#ifndef ADDELEMENTACTION_H
#define ADDELEMENTACTION_H

#include <QPointF>
#include <QSizeF>

#include "action.h"
#include "elementshape.h"
#include "node.h"


class AddElementAction : public Action
{
    Q_OBJECT
public:
    AddElementAction(ElementShape shape, QPointF point, QSizeF size, bool isAdded = true);

    void Do() override;
    void Undo() override;

private:
    ElementShape shape;
    QPointF point;
    QSizeF size;
    Node* node;
};

#endif // ADDELEMENTACTION_H
