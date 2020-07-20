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
    shape->setRect(location.x()-width/2,location.y()-height/2,width,height);
    shape->setVisible(true);
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
    shape->setX(qp.x()-width/2);
    shape->setY(qp.y()-height/2);
}

void Rectangle::SetWidth(double wd)
{
    width=wd;
    shape->setRect(location.x()-width/2,location.y()-height/2,width,height);
}

void Rectangle::SetHeight(double h)
{
    height=h;
    shape->setRect(location.x()-width/2,location.y()-height/2,width,height);
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
    delete this;
}
