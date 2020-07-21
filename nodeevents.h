#ifndef NODEEVENTS_H
#define NODEEVENTS_H

#include <QGraphicsSceneContextMenuEvent>

#include "node.h"


class NodeEvents
{
public:
    static void contextMenuEvent(Node* node, QGraphicsSceneContextMenuEvent *event);
};

#endif // NODEEVENTS_H
