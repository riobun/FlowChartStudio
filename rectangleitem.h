#ifndef RECTANGLEITEM_H
#define RECTANGLEITEM_H

#include <QGraphicsItem>

#include "node.h"


class RectangleItem:public QGraphicsRectItem
{
public:
    RectangleItem(Node* node) : node(node) {}

protected:
/*    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;*/
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
private:
    Node* node;
};

#endif // RECTANGLEITEM_H
