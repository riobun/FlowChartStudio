#include "arrow.h"
#include "node.h"
#include "graphelement.h"
#include <QPainter>
#include <QPen>
#include <QtMath>
#include<QMouseEvent>
#include<QLine>
Arrow::Arrow(Node *startItem, Node *endItem, QGraphicsItem *parent)
    : QGraphicsPathItem(parent), myStartItem(startItem), myEndItem(endItem)
{
//    apath=new QPainterPath(startItem->pos());
    setFlag(QGraphicsItem::ItemIsSelectable, true);
//    setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    setType(1);

}
//! [0]

//! [1]
QRectF Arrow::boundingRect() const
{

     return QRectF(0, 0, 5000, 5000);
}

QPainterPath Arrow::shape() const
{
    QPainterPath path;
    path.addPath(this->path());
    path.addPolygon(arrowHead);
    return path;
}



QPolygonF Arrow::polygon(){
    QPolygonF qpf;
    int w=myEndItem->GetWidth();
    int h=myEndItem->GetHeight();
//    if(myEndItem->getType()==1){//1表示矩形
//        qpf<<QPointF(-w/2,-h/2)<<QPointF(w/2,-h/2)<<QPointF(w/2,h/2)<<QPointF(-w/2,-h/2)<<QPointF(w/2,h/2);
//    }
//    if(myEndItem->getType()==2){//2表示菱形
//        qpf<<QPointF(-w/2,0)<<QPointF(0,h/2)<<QPointF(w/2,0)<<QPointF(0,-h/2)<<QPointF(-w/2,0);
//    }
    return qpf;
}
void Arrow::updatePosition()
{

//    QLineF line(mapFromItem(myStartItem, 0, 0), mapFromItem(myEndItem, 0, 0));
    if(list.length()>0){
    list.replace(0,myStartItem->GetLocation());
    list.replace(list.length()-1,myEndItem->GetLocation());}
//    apath->lineTo(line.dx(),line.dy());
//    setLine(line);
//     update();
}

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
//        return;
    qreal arrowSize = 20;
    list.clear();
    if((myStartItem->GetLocation().y()-myStartItem->GetHeight()/2-arrowSize>=myEndItem->GetLocation().y()||myEndItem->GetLocation().y()>=myEndItem->GetLocation().y()+myStartItem->GetHeight()/2+arrowSize)&&
       (myStartItem->GetLocation().x()-myStartItem->GetWidth()/2-arrowSize>=myEndItem->GetLocation().x()||myEndItem->GetLocation().x()>=myEndItem->GetLocation().x()+myStartItem->GetWidth()/2+arrowSize))
    {
        QPointF *p=new QPointF(myEndItem->GetLocation().x(), myStartItem->GetLocation().y());

    //    QLineF centerLine(myStartItem->pos(), myEndItem->pos());
        QLineF centerLine(*p, myEndItem->GetLocation());
        QPolygonF endPolygon = polygon();
        //得到myEndItem图形所有顶点相对于中点的坐标组
        QPointF p1 = endPolygon.first() + myEndItem->GetLocation();
        //pos()方法得到图形中点相对于窗口左上角的坐标
        //得到myEndItem图形第一个顶点相对于窗口左上角的坐标
        QPointF intersectPoint;
        for (int i = 1; i < endPolygon.count(); ++i) {
            QPointF p2 = endPolygon.at(i) + myEndItem->GetLocation();
            QLineF polyLine = QLineF(p1, p2);
            QLineF::IntersectType intersectionType =
                polyLine.intersect(centerLine, &intersectPoint);
            if (intersectionType == QLineF::BoundedIntersection)
                break;
            p1 = p2;
        }

        QLineF *ql=new QLineF(intersectPoint,*p);
    //! [5] //! [6]

        double angle = std::atan2(-ql->dy(), ql->dx());

        QPointF arrowP1 = ql->p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                        cos(angle + M_PI / 3) * arrowSize);
        QPointF arrowP2 = ql->p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                        cos(angle + M_PI - M_PI / 3) * arrowSize);


    //! [6] //! [7]
    list.insert(0,myStartItem->GetLocation());
    list.insert(1, *p);
    list.insert(2, myEndItem->GetLocation());
    arrowHead.clear();
    arrowHead << ql->p1() << arrowP1 << arrowP2;}
    else if(myStartItem->GetLocation().y()-myStartItem->GetHeight()/2-arrowSize<myEndItem->GetLocation().y()&&myEndItem->GetLocation().y()<myStartItem->GetLocation().y()+myStartItem->GetHeight()/2+arrowSize){
        QPointF *pa=new QPointF((myEndItem->GetLocation().x()+myStartItem->GetLocation().x())/2, myStartItem->GetLocation().y());
        QPointF *pb=new QPointF((myEndItem->GetLocation().x()+myStartItem->GetLocation().x())/2, myEndItem->GetLocation().y());

    //    QLineF centerLine(myStartItem->pos(), myEndItem->pos());
        QLineF centerLine(*pb, myEndItem->GetLocation());
        QPolygonF endPolygon = polygon();
        //得到myEndItem图形所有顶点相对于中点的坐标组
        QPointF p1 = endPolygon.first() + myEndItem->GetLocation();
        //pos()方法得到图形中点相对于窗口左上角的坐标
        //得到myEndItem图形第一个顶点相对于窗口左上角的坐标
        QPointF intersectPoint;
        for (int i = 1; i < endPolygon.count(); ++i) {
            QPointF p2 = endPolygon.at(i) + myEndItem->GetLocation();
            QLineF polyLine = QLineF(p1, p2);
            QLineF::IntersectType intersectionType =
                polyLine.intersect(centerLine, &intersectPoint);
            if (intersectionType == QLineF::BoundedIntersection)
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
        list.insert(0,myStartItem->GetLocation());

        list.insert(1,*pa);
        list.insert(2,*pb);
        list.insert(3, myEndItem->GetLocation());
        arrowHead.clear();
        arrowHead << ql->p1() << arrowP1 << arrowP2;
    }
    else if(myStartItem->GetLocation().x()-myStartItem->GetWidth()/2-arrowSize<myEndItem->GetLocation().x()&&myEndItem->GetLocation().x()<myStartItem->GetLocation().x()+myStartItem->GetWidth()/2+arrowSize){
        QPointF *pa=new QPointF( myStartItem->GetLocation().x(),(myEndItem->GetLocation().y()+myStartItem->GetLocation().y())/2);
        QPointF *pb=new QPointF( myEndItem->GetLocation().x(),(myEndItem->GetLocation().y()+myStartItem->GetLocation().y())/2);

    //    QLineF centerLine(myStartItem->pos(), myEndItem->pos());
        QLineF centerLine(*pb, myEndItem->GetLocation());
        QPolygonF endPolygon = polygon();
        //得到myEndItem图形所有顶点相对于中点的坐标组
        QPointF p1 = endPolygon.first() + myEndItem->GetLocation();
        //pos()方法得到图形中点相对于窗口左上角的坐标
        //得到myEndItem图形第一个顶点相对于窗口左上角的坐标
        QPointF intersectPoint;
        for (int i = 1; i < endPolygon.count(); ++i) {
            QPointF p2 = endPolygon.at(i) + myEndItem->GetLocation();
            QLineF polyLine = QLineF(p1, p2);
            QLineF::IntersectType intersectionType =
                polyLine.intersect(centerLine, &intersectPoint);
            if (intersectionType == QLineF::BoundedIntersection)
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
        list.insert(0,myStartItem->GetLocation());

        list.insert(1,*pa);
        list.insert(2,*pb);
        list.insert(3, myEndItem->GetLocation());
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
//    painter->setBrush(myColor);
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
//    if (isSelected()) {
//        painter->setPen(QPen(myColor,1, Qt::DashLine));
//        QLineF myLine = line();
//        myLine.translate(0, 4.0);
//        myLine.translate(0, 12.0);
//        //线向上移动
//        painter->drawLine(myLine);
//        myLine.translate(0,-8.0);
//        myLine.translate(0, -24.0);
//        //线向下移动
//        painter->drawLine(myLine);
 //   }
}

//void Arrow::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent){
//    if (!isSelected())
//        return;

//}
