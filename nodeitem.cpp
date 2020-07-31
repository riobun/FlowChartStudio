#include "nodeitem.h"
#include "nodeevents.h"
#include "node.h"
#include "QKeyEvent"
#include "QDebug"
#include "rectangle.h"
#include <cmath>
#include "mainwindow.h"
#include "groupaction.h"
#include "editelementaction.h"
#include"text.h"
#include"textitem.h"
#include "arrow.h"

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
              foreach (auto arrow, node->getArrows())
              {
                  arrow->update();
              }
        }
        else
        {
            NodeEvents::mouseMoveEvent(event);

            QGraphicsItem::mouseMoveEvent(event);
        }
    }
}

void NodeItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
     QGraphicsItem::mouseDoubleClickEvent(event);
     isDoubleClick=true;
     if(this->GetNode()->GetType()!=3){
     node->BindToText(MainWindow::instance()->scene());
     setSelected(false);
     node->content->getTextItem()->SetSelected(true);}
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
        foreach (auto node, *MainWindow::instance()->selectedNodes())
        {
            auto item = node->getNodeItem();
            item->lastLocation=node->GetLocation();
        }
        if(event->modifiers()==Qt::ShiftModifier)
        {
            isResized=true;
        }
    }
}

void NodeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    isDoubleClick=false;
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
                auto action = new GroupAction;
                foreach (auto node, *MainWindow::instance()->selectedNodes())
                {
                    *action << new EditElementAction(node, ElementShape::Rectangle,
                                                    ElementProperty::Location,
                                                    new QPointF(node->getNodeItem()->lastLocation),
                                                    new QPointF(node->GetLocation()));
                    //emit node->getNodeItem()->NewLocation(node,lastLocation);
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
        qpf<<QPointF(-w/2,-h/2)<<QPointF(w/2,-h/2)<<QPointF(w/2,h/2)<<QPointF(-w/2,h/2)<<QPointF(-w/2,-h/2);
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
void NodeItem::RemoveAsSource(Arrow* ar){
    //node->DisconnectAsSource(ar);
}
void NodeItem::RemoveAsDestination(Arrow* ar){
    //node->DisconnectAsSource(ar);
}

void NodeItem::SetSelected(bool b)
{
    isSelected=b;
    node->ChangeZValue(b);
    setSelected(b);
}
