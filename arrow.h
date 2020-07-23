
#ifndef NEWARROW_H
#define NEWARROW_H
#include "graphelement.h"
#include <QPainter>
#include <QPen>
#include <QtMath>
#include<QMouseEvent>
class Node;
class Arrow: public QGraphicsPathItem,public GraphElement
{
public:
    enum { Type = UserType + 4 };

    Arrow(Node *startItem, Node *endItem,
          QGraphicsItem *parent = nullptr);

    int type() const override { return Type; }
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void setColor(const QColor &color) { myColor = color; }
    void setType(int flag);
    void setSize(int size);
    void setId(int size);
    void setList();
    QPolygonF polygon();
    Node *startItem() const { return myStartItem; }
    Node *endItem() const { return myEndItem; }

    void updatePosition();

    void BindToText(QGraphicsScene* qgs) override{}

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;



private:
    Node *myStartItem;
    Node *myEndItem;
    QPolygonF arrowHead;
    QList<QLineF> lines;
    QColor myColor = Qt::black;
    int id=1;
    int atype=1;
    int asize=2;
    QList<QPointF> list;// 箭头结点
    QPainterPath *apath;//箭头路径
};

#endif // NEWARROW_H
