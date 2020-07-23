#include "nodeitem.h"
#include "nodeevents.h"
#include "node.h"
#include "QKeyEvent"
#include "QDebug"
#include "rectangle.h"
#include <cmath>
#include "mainwindow.h"
void NodeItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(isFocus)
    {
        isMoved=true;
        if(event->modifiers()==Qt::ShiftModifier&&isResized)
        {
              QPointF pos = event->pos();
              double nw=sqrt(pow(node->GetLocation().x() - pos.x(), 2)),nh=sqrt(pow(node->GetLocation().y() - pos.y(), 2));
              node->SetHeight(nh*2);
              node->SetWidth(nw*2);
        }
        else
        {
            foreach (auto node, *MainWindow::instance()->selectedNodes())
            {
                node->SetLocation(node->GetLocation()+event->pos()-event->lastPos());
            }
            QGraphicsItem::mouseMoveEvent(event);
        }
    }
}

void NodeItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

}

void NodeItem::keyPressEvent(QKeyEvent *event)
{

}

void NodeItem::keyReleaseEvent(QKeyEvent *event)
{


}

void NodeItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
//    SetSelected(true);
    if(event->button()==Qt::MouseButton::LeftButton)
    {
        isFocus=true;
        lastWidth=node->GetWidth();
        lastHeight=node->GetHeight();
        lastLocation=node->GetLocation();
        if(event->modifiers()==Qt::ShiftModifier)
        {
            isResized=true;
        }
    }
}

void NodeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    if(isFocus)
    {
        if(isMoved)
        {
            if(isResized)
            {
                emit NewSize(node,lastWidth,lastHeight);
            }
            else
            {
                foreach (auto node, *MainWindow::instance()->selectedNodes())
                {
                    emit node->getNodeItem()->NewLocation(node,lastLocation);
                }
            }
        }
    }
/*    if (lastLocation != event->scenePos())
    {
        emit NewLocation(node,lastLocation);
    }*/
    isMoved=false;
    isFocus=false;
    isResized=false;
}

QVariant NodeItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedHasChanged)
    {
        SetSelected(QGraphicsItem::isSelected());
        emit Selected(node, QGraphicsItem::isSelected());
    }
    return value;
}

void NodeItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    NodeEvents::contextMenuEvent(node, event);
}


QPolygonF NodeItem::polygon() const{
    QPolygonF qpf;
    int w=node->GetWidth();
    int h=node->GetHeight();
    Rectangle* ractangle = dynamic_cast<Rectangle*>(node);
    if(ractangle!=nullptr){//表示矩形
        qpf<<QPointF(-w/2,-h/2)<<QPointF(w/2,-h/2)<<QPointF(w/2,h/2)<<QPointF(-w/2,h/2)<<QPointF(w/2,h/2);
    }
    else{//2表示菱形
        qpf<<QPointF(-w/2,0)<<QPointF(0,h/2)<<QPointF(w/2,0)<<QPointF(0,-h/2)<<QPointF(-w/2,0);
    }
    return qpf;
}

QPointF NodeItem::pos() {

    return node->GetLocation();
}
int NodeItem::GetWidth(){
    return node->GetWidth();
}
int NodeItem::GetHeight(){
    return node->GetHeight();
}

