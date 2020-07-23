#ifndef NODEITEM_H
#define NODEITEM_H
#include"QGraphicsItem"
class Node;
/*
 鼠标左键按住拖动
 shift+鼠标左键按住调整大小
 */
class NodeItem:public QObject,public QGraphicsPolygonItem
{
Q_OBJECT
public:
    explicit NodeItem(QObject *parent = nullptr):QObject(parent) {};
    NodeItem(Node* node):node(node){};
    void SetSelected(bool b)
    {
        isSelected=b;
        if(b)
        {
            setZValue(100);
        }
        else
        {
            setZValue(1);
        }
    }
signals:
    void Selected(Node* n,bool b);
    void NewLocation(Node* n,QPointF oldLoc);
    void NewSize(Node* n,double oldWidth,double oldHeight);
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    bool isSelected=false;
    bool isFocus=false;
    bool isResized=false;
    bool isMoved=false;
    double lastWidth,lastHeight;
    QPointF lastLocation;
    Node* node=nullptr;
};

#endif // NODEITEM_H
