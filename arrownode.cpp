#include "arrownode.h"

Arrownode::Arrownode()
{

}
Arrownode:: Arrownode(QPointF lc,double wd,double h):Node(lc,wd,h)
{


}
Arrownode::~Arrownode()
{
    delete shape;
}
void Arrownode::Paint(QGraphicsScene* qgs)
{

    QPolygonF polygon;
    polygon<<QPointF(location.x()-width/2,location.y()-height/2)<<QPointF(location.x()+width/2,location.y()-height/2);
    polygon<<QPointF(location.x()+width/2,location.y()+height/2)<<QPointF(location.x()-width/2,location.y()+height/2);
    shape->setPolygon(polygon);
    shape->setVisible(true);
    shape->setFlags(QGraphicsItem::ItemIsSelectable);
    shape->setBrush(Qt::black);
    SetBackgroundColor(backgroundColor);
    SetFrameColor(frameColor);
    qgs->addItem(shape);
}

void Arrownode::SetVisibility(bool vis)
{
    shape->setVisible(vis);
}
void Arrownode::SetLocation(const QPointF &qp)
{
    location=qp;
    QPolygonF polygon;
    polygon<<QPointF(location.x()-width/2,location.y()-height/2)<<QPointF(location.x()+width/2,location.y()-height/2);
    polygon<<QPointF(location.x()+width/2,location.y()+height/2)<<QPointF(location.x()-width/2,location.y()+height/2);
    shape->setPolygon(polygon);
}

void Arrownode::SetWidth(double wd)
{
    width=wd;
    QPolygonF polygon;
    polygon<<QPointF(location.x()-width/2,location.y()-height/2)<<QPointF(location.x()+width/2,location.y()-height/2);
    polygon<<QPointF(location.x()+width/2,location.y()+height/2)<<QPointF(location.x()-width/2,location.y()+height/2);
    shape->setPolygon(polygon);
}

void Arrownode::SetHeight(double h)
{
    height=h;
    QPolygonF polygon;
    polygon<<QPointF(location.x()-width/2,location.y()-height/2)<<QPointF(location.x()+width/2,location.y()-height/2);
    polygon<<QPointF(location.x()+width/2,location.y()+height/2)<<QPointF(location.x()-width/2,location.y()+height/2);
    shape->setPolygon(polygon);
}

void Arrownode::SetBackgroundColor(const QColor &qc)
{
    backgroundColor=qc;
    QBrush brush=shape->brush();
    brush.setColor(Qt::black);
    brush.setStyle(Qt::BrushStyle::SolidPattern);
    shape->setBrush(brush);
}

void Arrownode::SetFrameColor(const QColor &qc)
{
    frameColor=qc;
    QPen pen=shape->pen();
    pen.setColor(frameColor);
    shape->setPen(pen);
}

void Arrownode::Remove(QGraphicsScene *qgs)//等待arrow完成后继续修改
{
    qgs->removeItem(shape);
    if(content) content->delete_text(qgs);

}
void Arrownode::SetShape()
{
    QPolygonF polygon;
    polygon<<QPointF(location.x()-width/2,location.y()-height/2)<<QPointF(location.x()+width/2,location.y()-height/2);
    polygon<<QPointF(location.x()+width/2,location.y()+height/2)<<QPointF(location.x()-width/2,location.y()+height/2);
    shape->setPolygon(polygon);
}


int Arrownode::GetType()
{
    return 3;
}
