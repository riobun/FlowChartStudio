#include "arrow.h"
#include "nodeitem.h"
#include "node.h"
#include "graphelement.h"
#include <QPainter>
#include <QPen>
#include <QGraphicsScene>
#include <QtMath>
#include<QMouseEvent>
#include "nodeevents.h"
#include <QMenu>
#include "changeelementaction.h"
#include "mainwindow.h"

Arrow::Arrow(NodeItem *startItem, NodeItem *endItem, QGraphicsItem *parent)
    : QGraphicsPathItem(parent), myStartItem(startItem), myEndItem(endItem)
{
//    apath=new QPainterPath(startItem->pos());
    startItem->GetNode()->ConnectAsSource(this);
    endItem->GetNode()->ConnectAsDestination(this);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
//    setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    setType(1);
    //xy[11][11]=1;

}
//! [0]

//! [1]
QRectF Arrow::boundingRect() const
{

     return QRectF(0, 0, 5000, 5000);
}
//////! [1]

//! [2]
//QPainterPath Arrow::shape() const
//{
//    QPainterPath path = QGraphicsItem::shape();
//    path.addPolygon(arrowHead);
//    return path;
//}
QPainterPath Arrow::shape() const
{
    QPainterPath path;
    path.addPath(this->path());
    path.addPolygon(arrowHead);
    return path;
}
//! [2]

//! [3]
void Arrow::updatePosition()
{

//    QLineF line(mapFromItem(myStartItem, 0, 0), mapFromItem(myEndItem, 0, 0));
    if(list.length()>0){
    list.replace(0,myStartItem->pos());
    list.replace(list.length()-1,myEndItem->pos());}
//    apath->lineTo(line.dx(),line.dy());
//    setLine(line);
//     update();
}
//! [3]

//! [4]
void Arrow::setType(int flag){
    if(flag==1){
    setPen(QPen(myColor,asize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    atype=1;
    }//实线
    else if(flag==2){
    setPen(QPen(myColor,asize, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));  //标准虚线
    atype=2;
    }
    else if(flag==3){
    setPen(QPen(myColor, asize, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin));   //紧凑虚线
    atype=3;
    }
    else if(flag==4){
    setPen(QPen(myColor, asize,Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin));  //
    atype=4;
    }
    else if(flag==5){
    setPen(QPen(myColor, asize, Qt::DashDotDotLine, Qt::RoundCap, Qt::RoundJoin));   //
    atype=5;
    }
    update();
}
void Arrow::setSize(int size){
    setPen(QPen(myColor, size,Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    this->asize=size;
    setType(atype);
    update();
}

void Arrow::setList(){
//    if (myStartItem->collidesWithItem(myEndItem))
//        return ;
    qreal arrowSize = 20;
    list.clear();

    if(myEndItem->pos()==myStartItem->pos())
    {
        QPointF *pa=new QPointF((myStartItem->pos().x()+myStartItem->GetWidth()), myStartItem->pos().y());
        QPointF *pb=new QPointF((myStartItem->pos().x()+myStartItem->GetWidth()), myStartItem->pos().y()-myStartItem->GetHeight()*3/2);
        QPointF *pc=new QPointF(myStartItem->pos().x(), myStartItem->pos().y()-myStartItem->GetHeight()*3/2);
    //    QLineF centerLine(myStartItem->pos(), myEndItem->pos());
        QLineF centerLine(*pc, myEndItem->pos());
        QPolygonF endPolygon = myEndItem->polygon();
        //得到myEndItem图形所有顶点相对于中点的坐标组
        QPointF p1 = endPolygon.first() + myEndItem->pos();
        //pos()方法得到图形中点相对于窗口左上角的坐标
        //得到myEndItem图形第一个顶点相对于窗口左上角的坐标
        QPointF intersectPoint;
        for (int i = 1; i < endPolygon.count(); ++i) {
            QPointF p2 = endPolygon.at(i) + myEndItem->pos();
            QLineF polyLine = QLineF(p1, p2);
            QLineF::IntersectType intersectType =
                polyLine.intersect(centerLine, &intersectPoint);
            if (intersectType == QLineF::BoundedIntersection)
                break;
            p1 = p2;
        }

        QLineF *ql=new QLineF(intersectPoint,*pc);
    //! [5] //! [6]

        double angle = std::atan2(-ql->dy(), ql->dx());

        QPointF arrowP1 = ql->p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                        cos(angle + M_PI / 3) * arrowSize);
        QPointF arrowP2 = ql->p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                        cos(angle + M_PI - M_PI / 3) * arrowSize);


    //! [6] //! [7]
        list.insert(0,myStartItem->pos());

        list.insert(1,*pa);
        list.insert(2,*pb);
        list.insert(3,*pc);
        list.insert(4, myEndItem->pos());
        arrowHead.clear();
        arrowHead << ql->p1() << arrowP1 << arrowP2;
        return ;
    }

    if(myStartItem->pos().y()>=myEndItem->pos().y()-myEndItem->GetHeight()/2-arrowSize&&myStartItem->pos().y()<=myEndItem->pos().y()+myEndItem->GetHeight()/2+arrowSize)
    {
        QPointF *pa=new QPointF((myEndItem->pos().x()+myStartItem->pos().x())/2, myStartItem->pos().y());
        QPointF *pb=new QPointF((myEndItem->pos().x()+myStartItem->pos().x())/2, myEndItem->pos().y());

    //    QLineF centerLine(myStartItem->pos(), myEndItem->pos());
        QLineF centerLine(*pb, myEndItem->pos());
        QPolygonF endPolygon = myEndItem->polygon();
        //得到myEndItem图形所有顶点相对于中点的坐标组
        QPointF p1 = endPolygon.first() + myEndItem->pos();
        //pos()方法得到图形中点相对于窗口左上角的坐标
        //得到myEndItem图形第一个顶点相对于窗口左上角的坐标
        QPointF intersectPoint;
        for (int i = 1; i < endPolygon.count(); ++i) {
            QPointF p2 = endPolygon.at(i) + myEndItem->pos();
            QLineF polyLine = QLineF(p1, p2);
            QLineF::IntersectType intersectType =
                polyLine.intersect(centerLine, &intersectPoint);
            if (intersectType == QLineF::BoundedIntersection)
                break;
            p1 = p2;
        }

        QLineF *ql=new QLineF(intersectPoint,*pb);
    //! [5] //! [6]

        double angle = std::atan2(-ql->dy(), ql->dx());

        QPointF arrowP1 = ql->p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                        cos(angle + M_PI / 3) * arrowSize);
        QPointF arrowP2 = ql->p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                        cos(angle + M_PI - M_PI / 3) * arrowSize);


    //! [6] //! [7]
        list.insert(0,myStartItem->pos());

        list.insert(1,*pa);
        list.insert(2,*pb);
        list.insert(3, myEndItem->pos());
        arrowHead.clear();
        arrowHead << ql->p1() << arrowP1 << arrowP2;
        return ;
    }else if(myEndItem->pos().x()>=myStartItem->pos().x()-myStartItem->GetWidth()/2&&myEndItem->pos().x()<=myStartItem->pos().x()+myStartItem->GetWidth()/2)
    {
        QPointF *pa=new QPointF(myStartItem->pos().x(),(myEndItem->pos().y()+myStartItem->pos().y())/2);
        QPointF *pb=new QPointF(myEndItem->pos().x(),(myEndItem->pos().y()+myStartItem->pos().y())/2);

    //    QLineF centerLine(myStartItem->pos(), myEndItem->pos());
        QLineF centerLine(*pb, myEndItem->pos());
        QPolygonF endPolygon = myEndItem->polygon();
        //得到myEndItem图形所有顶点相对于中点的坐标组
        QPointF p1 = endPolygon.first() + myEndItem->pos();
        //pos()方法得到图形中点相对于窗口左上角的坐标
        //得到myEndItem图形第一个顶点相对于窗口左上角的坐标
        QPointF intersectPoint;
        for (int i = 1; i < endPolygon.count(); ++i) {
            QPointF p2 = endPolygon.at(i) + myEndItem->pos();
            QLineF polyLine = QLineF(p1, p2);
            QLineF::IntersectType intersectType =
                polyLine.intersect(centerLine, &intersectPoint);
            if (intersectType == QLineF::BoundedIntersection)
                break;
            p1 = p2;
        }

        QLineF *ql=new QLineF(intersectPoint,*pb);
    //! [5] //! [6]

        double angle = std::atan2(-ql->dy(), ql->dx());

        QPointF arrowP1 = ql->p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                        cos(angle + M_PI / 3) * arrowSize);
        QPointF arrowP2 = ql->p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                        cos(angle + M_PI - M_PI / 3) * arrowSize);


    //! [6] //! [7]
        list.insert(0,myStartItem->pos());

        list.insert(1,*pa);
        list.insert(2,*pb);
        list.insert(3, myEndItem->pos());
        arrowHead.clear();
        arrowHead << ql->p1() << arrowP1 << arrowP2;
        return ;
    }else {//if(myStartItem->pos().y()-100-arrowSize>=myEndItem->pos().y()||myEndItem->pos().y()>=myStartItem->pos().y()+100+arrowSize)
            QPointF *p=new QPointF(myEndItem->pos().x(), myStartItem->pos().y());

        //    QLineF centerLine(myStartItem->pos(), myEndItem->pos());
            QLineF centerLine(*p, myEndItem->pos());
            QPolygonF endPolygon = myEndItem->polygon();
            //得到myEndItem图形所有顶点相对于中点的坐标组
            QPointF p1 = endPolygon.first() + myEndItem->pos();
            //pos()方法得到图形中点相对于窗口左上角的坐标
            //得到myEndItem图形第一个顶点相对于窗口左上角的坐标
            QPointF intersectPoint;
            for (int i = 1; i < endPolygon.count(); ++i) {
                QPointF p2 = endPolygon.at(i) + myEndItem->pos();
                QLineF polyLine = QLineF(p1, p2);
                QLineF::IntersectType intersectType =
                    polyLine.intersect(centerLine, &intersectPoint);
                if (intersectType == QLineF::BoundedIntersection)
                    break;
                p1 = p2;
            }

            QLineF *ql=new QLineF(intersectPoint,*p);
            //setLine(QLineF(intersectPoint, list.at(1)));
        //! [5] //! [6]

            double angle = std::atan2(-ql->dy(), ql->dx());

            QPointF arrowP1 = ql->p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                            cos(angle + M_PI / 3) * arrowSize);
            QPointF arrowP2 = ql->p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                            cos(angle + M_PI - M_PI / 3) * arrowSize);


        //! [6] //! [7]
        list.insert(0,myStartItem->pos());
        list.insert(1, *p);
        list.insert(2, myEndItem->pos());
        arrowHead.clear();
        arrowHead << ql->p1() << arrowP1 << arrowP2;
    }
}


void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                  QWidget *)
{

    setList();
    apath=new QPainterPath(list.at(0));
    QPen myPen = pen();
    myPen.setColor(myColor);
    //调整清晰度---------------------------
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(myPen);
   // painter->setBrush(myColor);
//! [4] //! [5]

// painter->drawLine(line());
    for(int i=1;i<=list.length()-1;i++){
        apath->lineTo(list.at(i));
    }

//    apath->lineTo(list.at(1).x()-list.at(0).x(),0);
//    apath->lineTo(0,list.at(2).y()-list.at(1).y());
//    apath->addPolygon(arrowHead);
    setPath(*apath);
    painter->drawPath(path());
    painter->setPen(QPen(myColor, asize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->setBrush(myColor);
    painter->drawPolygon(arrowHead);
    if (isSelected()) {
                QBrush* brush=new QBrush();
                painter->setBrush(*brush);
                painter->setPen(QPen(myColor,1, Qt::DashLine));
                QPainterPath myPath = path();
                if((myEndItem->pos().x()<myStartItem->pos().x()&&myEndItem->pos().y()<myStartItem->pos().y())||(myEndItem->pos().x()>myStartItem->pos().x()&&myEndItem->pos().y()>myStartItem->pos().y())){
        //        myPath.translate(0, 4.0);
                myPath.translate(12.0, -12.0);
                //线向上移动
                painter->drawPath(myPath);
        //        myPath.translate(0,-8.0);
                myPath.translate(-24.0, 24.0);
                //线向下移动
                painter->drawPath(myPath);
                }else if((myEndItem->pos().x()>myStartItem->pos().x()&&myEndItem->pos().y()<myStartItem->pos().y())||(myEndItem->pos().x()<myStartItem->pos().x()&&myEndItem->pos().y()>myStartItem->pos().y())){
                    //        myPath.translate(0, 4.0);
                            myPath.translate(-12.0, -12.0);
                            //线向上移动
                            painter->drawPath(myPath);
                    //        myPath.translate(0,-8.0);
                            myPath.translate(24.0, 24.0);
                            //线向下移动
                            painter->drawPath(myPath);
                }else{
                    //        myPath.translate(0, 4.0);
                            myPath.translate(12.0, -12.0);
                            //线向上移动
                            painter->drawPath(myPath);
                    //        myPath.translate(0,-8.0);
                            myPath.translate(-24.0, 24.0);
                            //线向下移动
                            painter->drawPath(myPath);
                }
            }
}

//void Arrow::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent){
//    if (!isSelected())
//        return;

//}
//! [7]
//new function
//QVariant Arrow::itemChange(GraphicsItemChange change, const QVariant &value)//当图形移动时，调用arrow的updatePosition函数，让箭头跟着图形移动
//{
//    if (change == QGraphicsItem::ItemPositionChange) {
//        for (Arrow *arrow : qAsConst(arrows))
//            arrow->updatePosition();
//    }

//    return value;
//}

void Arrow::removeArrow()
{
    endItem()->RemoveAsDestination(this);
    startItem()->RemoveAsSource(this);
    new ChangeElementAction(this, ElementShape::Arrow, false);
//    delete this;
}
//! [1]

//! [2]
//void Arrow::removeArrows()
//{
//    // need a copy here since removeArrow() will
//    // modify the arrows container
//    const auto arrowsCopy = arrows;
//    for (Arrow *arrow : arrowsCopy) {
//        arrow->startItem()->removeArrow(arrow);
//        arrow->endItem()->removeArrow(arrow);
//        scene()->removeItem(arrow);
//        delete arrow;
//    }
//}
//void Arrow::addArrow(Arrow *arrow)
//{
//    arrows.append(arrow);
//}

void Arrow::BindToText(QGraphicsScene* qgs){
    content=new Text((QPoint((myStartItem->pos().x()+myEndItem->pos().x())/2,
                     (myStartItem->pos().y()+myEndItem->pos().y())/2)));
    content->putup_text(qgs);
    content->build_text();
};
//void Arrow::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent){
//    if (!isSelected())
//        return;

//}

void Arrow::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;
    auto deleteAction = menu.addAction("删除");
    deleteAction->setShortcut(QKeySequence::Delete);
    auto selectedAction = menu.exec(event->screenPos());
    if (selectedAction == deleteAction)
    {
        NodeEvents::deleteElemets();
    }
}

QVariant Arrow::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedHasChanged)
    {
        s(this, QGraphicsItem::isSelected());
    }
    return value;
}
