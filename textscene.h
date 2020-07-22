#ifndef TEXTEVENTS_H
#define TEXTEVENTS_H

#include <QGraphicsSceneContextMenuEvent>

#include "text.h"


class TextScene
{
public:
    static void contextMenuEvent(Text* text, QGraphicsSceneContextMenuEvent *event);
    static void mousePressEvent( QGraphicsSceneMouseEvent *event);
    static void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent* event);
};

#endif 
