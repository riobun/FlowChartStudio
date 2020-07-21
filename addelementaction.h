#ifndef ADDELEMENTACTION_H
#define ADDELEMENTACTION_H

#include <QPointF>
#include <QGraphicsScene>

#include "action.h"
#include "elementshape.h"
#include "node.h"


class AddElementAction : public Action
{
    Q_OBJECT
public:
    AddElementAction(ElementShape shape, QPointF point);

    void Do() override;
    void Undo() override;

private:
    ElementShape shape;
    QPointF point;
    QGraphicsScene* scene;
    Node* node;
};

#endif // ADDELEMENTACTION_H
