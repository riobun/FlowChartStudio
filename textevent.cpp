#ifndef TEXTEVENTS_H
#define TEXTEVENTS_H

#include <QGraphicsSceneContextMenuEvent>

#include "text.h"


class TextEvents
{
public:
    static void contextMenuEvent(Text* text, QGraphicsSceneContextMenuEvent *event);
    static void mousePressEvent(Text* text, QGraphicsSceneMouseEvent *event);
    static void mouseReleaseEvent(Text* text, QGraphicsSceneMouseEvent *event);
};

#endif 
