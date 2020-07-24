#ifndef NODEITEM_H
#define NODEITEM_H
#include"QGraphicsItem"
class Node;
class Arrow;
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
    Node* GetNode() {return node;}
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
        setSelected(b);
    }

    QPolygonF polygon() const;
    QPointF pos();
    int GetWidth();
    int GetHeight();
    void RemoveAsSource(Arrow* ar);
    void RemoveAsDestination(Arrow* ar);
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
    int mytype=1;
};

#endif // NODEITEM_H
