
#include "arrow.h"
#include "diagramitem.h"

#include <QPainter>
#include <QPen>
#include <QtMath>
#include<QMouseEvent>

//! [0]
Arrow::Arrow(DiagramItem *startItem, DiagramItem *endItem, QGraphicsItem *parent)
    : QGraphicsLineItem(parent), myStartItem(startItem), myEndItem(endItem)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
//    setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    setType(3);

}
//! [0]

//! [1]
QRectF Arrow::boundingRect() const
{
    qreal extra = (pen().width() + 20) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}
//! [1]

//! [2]
QPainterPath Arrow::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(arrowHead);
    return path;
}
//! [2]

//! [3]
void Arrow::updatePosition()
{
    QLineF line(mapFromItem(myStartItem, 0, 0), mapFromItem(myEndItem, 0, 0));
    if(list.length()>0){
    list.replace(0,mapFromItem(myStartItem, 0, 0));
    list.replace(list.length()-1,mapFromItem(myEndItem, 0, 0));}
    setLine(line);
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
void Arrow::setId(int id){
    this->id=id;
}
void Arrow::setList(){
    if (myStartItem->collidesWithItem(myEndItem))
        return;
    qreal arrowSize = 20;
    QLineF centerLine(myStartItem->pos(), myEndItem->pos());
    QPolygonF endPolygon = myEndItem->polygon();
    //得到myEndItem图形所有顶点相对于中点的坐标组
    QPointF p1 = endPolygon.first() + myEndItem->pos();
    //pos()方法得到图形中点相对于窗口左上角的坐标
    //得到myEndItem图形第一个顶点相对于窗口左上角的坐标
    QPointF intersectPoint;
    for (int i = 1; i < endPolygon.count(); ++i) {
        QPointF p2 = endPolygon.at(i) + myEndItem->pos();
        QLineF polyLine = QLineF(p1, p2);
        QLineF::IntersectionType intersectionType =
            polyLine.intersects(centerLine, &intersectPoint);
        if (intersectionType == QLineF::BoundedIntersection)
            break;
        p1 = p2;
    }
    list.insert(0,myStartItem->pos());
    list.insert(1,intersectPoint);
    list.insert(1,QPointF(2400,2400));
    setLine(QLineF(intersectPoint, myStartItem->pos()));
//! [5] //! [6]

    double angle = std::atan2(-line().dy(), line().dx());

    QPointF arrowP1 = line().p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                    cos(angle + M_PI / 3) * arrowSize);
    QPointF arrowP2 = line().p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                    cos(angle + M_PI - M_PI / 3) * arrowSize);

    arrowHead.clear();
    arrowHead << line().p1() << arrowP1 << arrowP2;
//! [6] //! [7]
}
void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                  QWidget *)
{

    setList();
    QPen myPen = pen();
    myPen.setColor(myColor);

    //调整清晰度---------------------------
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(myPen);
    painter->setBrush(myColor);
//! [4] //! [5]


   for(int i=0;i<list.length()-1;i++){
       setLine(QLineF(list.at(i),list.at(i+1)));
       painter->drawLine(line());
   }
    painter->setPen(QPen(myColor, asize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawPolygon(arrowHead);
    if (isSelected()) {
        painter->setPen(QPen(myColor,1, Qt::DashLine));
        QLineF myLine = line();
//        myLine.translate(0, 4.0);
        myLine.translate(0, 12.0);
        //线向上移动
        painter->drawLine(myLine);
//        myLine.translate(0,-8.0);
        myLine.translate(0, -24.0);
        //线向下移动
        painter->drawLine(myLine);
    }
}
//void Arrow::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent){
//    if (!isSelected())
//        return;

//}
//! [7]
