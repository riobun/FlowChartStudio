#ifndef NODEEVENTS_H
#define NODEEVENTS_H

#include <QGraphicsSceneContextMenuEvent>

#include "node.h"


class NodeEvents
{
public:
    static void contextMenuEvent(Node* node, QGraphicsSceneContextMenuEvent *event);
    static void mousePressEvent(Node* node, QGraphicsSceneMouseEvent *event);
    static void mouseReleaseEvent(Node* node, QGraphicsSceneMouseEvent *event);
};

#endif // NODEEVENTS_H
