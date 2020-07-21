#ifndef RECTANGLEITEM_H
#define RECTANGLEITEM_H
#include "QGraphicsItem"

class RectangleItem:public QGraphicsRectItem
{
public:
    RectangleItem();
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
};

#endif // RECTANGLEITEM_H
