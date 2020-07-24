#include "rectangle.h"

Rectangle::Rectangle()
{

}
Rectangle:: Rectangle(QPointF lc,double wd,double h):Node(lc,wd,h)
{


}
Rectangle::~Rectangle()
{
    delete shape;
}
void Rectangle::Paint(QGraphicsScene* qgs)
{
    QPolygonF polygon;
    polygon<<QPointF(location.x()-width/2,location.y()-height/2)<<QPointF(location.x()+width/2,location.y()-height/2);
    polygon<<QPointF(location.x()+width/2,location.y()+height/2)<<QPointF(location.x()-width/2,location.y()+height/2);
    shape->setPolygon(polygon);
    shape->setVisible(true);
    shape->setFlags(QGraphicsItem::ItemIsSelectable);
    SetBackgroundColor(backgroundColor);
    SetFrameColor(frameColor);
    qgs->addItem(shape);
}

void Rectangle::SetVisibility(bool vis)
{
    shape->setVisible(vis);
}
void Rectangle::SetLocation(const QPointF &qp)
{
    location=qp;
    QPolygonF polygon;
    polygon<<QPointF(location.x()-width/2,location.y()-height/2)<<QPointF(location.x()+width/2,location.y()-height/2);
    polygon<<QPointF(location.x()+width/2,location.y()+height/2)<<QPointF(location.x()-width/2,location.y()+height/2);
    shape->setPolygon(polygon);
    if(content)
    {

    }
}

void Rectangle::SetWidth(double wd)
{
    width=wd;
    QPolygonF polygon;
    polygon<<QPointF(location.x()-width/2,location.y()-height/2)<<QPointF(location.x()+width/2,location.y()-height/2);
    polygon<<QPointF(location.x()+width/2,location.y()+height/2)<<QPointF(location.x()-width/2,location.y()+height/2);
    shape->setPolygon(polygon);
}

void Rectangle::SetHeight(double h)
{
    height=h;
    QPolygonF polygon;
    polygon<<QPointF(location.x()-width/2,location.y()-height/2)<<QPointF(location.x()+width/2,location.y()-height/2);
    polygon<<QPointF(location.x()+width/2,location.y()+height/2)<<QPointF(location.x()-width/2,location.y()+height/2);
    shape->setPolygon(polygon);
}

void Rectangle::SetBackgroundColor(const QColor &qc)
{
    backgroundColor=qc;
    QBrush brush=shape->brush();
    brush.setColor(backgroundColor);
    brush.setStyle(Qt::BrushStyle::SolidPattern);
    shape->setBrush(brush);
}

void Rectangle::SetFrameColor(const QColor &qc)
{
    frameColor=qc;
    QPen pen=shape->pen();
    pen.setColor(frameColor);
    shape->setPen(pen);
}

void Rectangle::Remove(QGraphicsScene *qgs)//等待arrow完成后继续修改
{
    qgs->removeItem(shape);
    if(content) content->delete_text(qgs);

}

void Rectangle::BindToText(QGraphicsScene* qgs)
{
    content=new Text(location);
    content->putup_text(qgs);
    content->build_text();
}

int Rectangle::GetType()
{
    return 1;
}
