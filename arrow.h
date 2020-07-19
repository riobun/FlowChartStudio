
#ifndef ARROW_H
#define ARROW_H
#include<QStyle>
#include <QGraphicsLineItem>

class DiagramItem;

//! [0]
class Arrow : public QGraphicsLineItem
{
public:
    enum { Type = UserType + 4 };

    Arrow(DiagramItem *startItem, DiagramItem *endItem,
          QGraphicsItem *parent = nullptr);

    int type() const override { return Type; }
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void setColor(const QColor &color) { myColor = color; }
    void setType(int flag);
    void setSize(int size);
    void setId(int size);
    void setList();
    DiagramItem *startItem() const { return myStartItem; }
    DiagramItem *endItem() const { return myEndItem; }

    void updatePosition();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;



private:
    DiagramItem *myStartItem;
    DiagramItem *myEndItem;
    QPolygonF arrowHead;
    QColor myColor = Qt::black;
    int id=1;
    int atype=1;
    int asize=2;
    QList<QPointF> list;
};
//! [0]

#endif // ARROW_H
