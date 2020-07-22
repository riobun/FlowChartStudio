#ifndef NODEITEM_H
#define NODEITEM_H
#include"QGraphicsItem"
class Node;
class NodeItem:public QGraphicsPolygonItem
{
public:
    NodeItem(Node* node):node(node){};

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
private:
    bool isSelected=false;
    Node* node;
};

#endif // NODEITEM_H
