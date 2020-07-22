#ifndef TEXTITEM_H
#define TEXTITEM_H
#include<QGraphicsItem>


#include "text.h"


class TextItem :public QGraphicsItem {
public:
	TextItem()(Text*text) : text(text) {}
protected:
    /*void keyPressEvent(QKeyEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event)override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event)override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event)override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)override;
    void keyReleaseEvent(QKeyEvent* event)override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent* event)override;*/
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
private:
	Text*text;
};


#endif
