#include "arrownode.h"

ArrowNode::ArrowNode()
{

}
ArrowNode:: ArrowNode(QPointF lc,double wd,double h):Node(lc,wd,h)
{


}
ArrowNode::~ArrowNode()
{
    delete shape;
}
void ArrowNode::Paint(QGraphicsScene* qgs)
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

void ArrowNode::SetVisibility(bool vis)
{
    shape->setVisible(vis);
}
void ArrowNode::SetLocation(const QPointF &qp)
{
    location=qp;
    QPolygonF polygon;
    polygon<<QPointF(location.x()-width/2,location.y()-height/2)<<QPointF(location.x()+width/2,location.y()-height/2);
    polygon<<QPointF(location.x()+width/2,location.y()+height/2)<<QPointF(location.x()-width/2,location.y()+height/2);
    shape->setPolygon(polygon);
}

void ArrowNode::SetWidth(double wd)
{

}

void ArrowNode::SetHeight(double h)
{

}

void ArrowNode::SetBackgroundColor(const QColor &qc)
{
    backgroundColor=qc;
    QBrush brush=shape->brush();
    brush.setColor(qc);
    brush.setStyle(Qt::BrushStyle::SolidPattern);
    shape->setBrush(brush);
}

void ArrowNode::SetFrameColor(const QColor &qc)
{
    frameColor=qc;
    QPen pen=shape->pen();
    pen.setColor(frameColor);
    shape->setPen(pen);
}

void ArrowNode::Remove(QGraphicsScene *qgs)//等待arrow完成后继续修改
{
    qgs->removeItem(shape);
    if(content) content->delete_text(qgs);

}
void ArrowNode::SetShape()
{
    QPolygonF polygon;
    polygon<<QPointF(location.x()-width/2,location.y()-height/2)<<QPointF(location.x()+width/2,location.y()-height/2);
    polygon<<QPointF(location.x()+width/2,location.y()+height/2)<<QPointF(location.x()-width/2,location.y()+height/2);
    shape->setPolygon(polygon);
}


int ArrowNode::GetType()
{
    return 3;
}
int ArrowNode::selecttext()
{
    if(this->getNodeItem()->Getisselect()){
        this->content->setSelected(true);
//        QVector<Arrow*> arrows= this->getArrows();
//        foreach(Arrow* ar , arrows){
//            if(ar->getcontent()!=nullptr)
//            ar->getcontent()->move_text(QPointF((ar->getlist().at(0).x()+ar->getlist().at(1).x())/2,
//                                (ar->getlist().at(0).y()+ar->getlist().at(1).y())/2));
//        }
    }
}
