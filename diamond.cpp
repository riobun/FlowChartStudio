#include "diamond.h"
#include "QGraphicsItem"
#include "QFont"
Diamond::Diamond()
{

}
Diamond:: Diamond(QPointF lc,double wd,double h):Node(lc,wd,h)
{


}
Diamond::~Diamond()
{
    delete shape;
}
void Diamond::Paint(QGraphicsScene* qgs)
{
    QPolygonF polygon;
    polygon<<QPointF(location.x()-width/2,location.y())<<QPointF(location.x(),location.y()-height/2);
    polygon<<QPointF(location.x()+width/2,location.y())<<QPointF(location.x(),location.y()+height/2);
    shape->setPolygon(polygon);
    shape->setVisible(true);
    shape->setFlags(QGraphicsItem::ItemIsSelectable);
    SetBackgroundColor(backgroundColor);
    SetFrameColor(frameColor);
    qgs->addItem(shape);    
}

void Diamond::SetVisibility(bool vis)
{
    shape->setVisible(vis);
}
void Diamond::SetLocation(const QPointF &qp)
{
    location=qp;
    QPolygonF polygon;
    polygon<<QPointF(location.x()-width/2,location.y())<<QPointF(location.x(),location.y()-height/2);
    polygon<<QPointF(location.x()+width/2,location.y())<<QPointF(location.x(),location.y()+height/2);
    shape->setPolygon(polygon);
    if(content)
    {
        content->move_text(qp);
    }
}

void Diamond::SetWidth(double wd)
{
    width=wd;
    QPolygonF polygon;
    polygon<<QPointF(location.x()-width/2,location.y())<<QPointF(location.x(),location.y()-height/2);
    polygon<<QPointF(location.x()+width/2,location.y())<<QPointF(location.x(),location.y()+height/2);
    shape->setPolygon(polygon);
}

void Diamond::SetHeight(double h)
{
    height=h;
    QPolygonF polygon;
    polygon<<QPointF(location.x()-width/2,location.y())<<QPointF(location.x(),location.y()-height/2);
    polygon<<QPointF(location.x()+width/2,location.y())<<QPointF(location.x(),location.y()+height/2);
    shape->setPolygon(polygon);
}
void Diamond::SetBackgroundColor(const QColor &qc)
{
    backgroundColor=qc;
    QBrush brush=shape->brush();
    brush.setColor(backgroundColor);
    brush.setStyle(Qt::BrushStyle::SolidPattern);
    shape->setBrush(brush);
}

void Diamond::SetFrameColor(const QColor &qc)
{
    frameColor=qc;
    QPen pen=shape->pen();
    pen.setColor(frameColor);
    shape->setPen(pen);
}

void Diamond::Remove(QGraphicsScene *qgs)//等待arrow完成后继续修改
{
    qgs->removeItem(shape);
    if(content) content->delete_text(qgs);
}

void Diamond::BindToText(QGraphicsScene* qgs)
{
    content=new Text(location,width/2,height/2);
    content->build_text();
}
