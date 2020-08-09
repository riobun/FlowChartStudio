#include "node.h"
#include"arrow.h"
#include "mainwindow.h"
#include "changeelementaction.h"

Node::Node(){}
Node::Node(QPointF lc,double w,double h):location(lc),width(w),height(h)
{
}

Node::~Node()
{
    delete content;
}
double Node::GetWidth()
{
    return width;
}

double Node::GetHeight()
{
    return height;
}

QColor Node::GetBackgroundColor()
{
    return backgroundColor;
}

QColor Node::GetFrameColor()
{
    return frameColor;
}
QPointF Node::GetLocation()
{
    return location;
}

void Node::ConnectAsSource(Arrow *ar)
{
    if(isRemoved) return;
    sourceArrows[ar->GetID()]=ar;
}

void Node::ConnectAsDestination(Arrow *ar)
{
    if(isRemoved) return;
    destinationArrows[ar->GetID()]=ar;
}

void Node::DisconnectAsSource(Arrow *ar)
{
    if(isRemoved) return;
    sourceArrows.remove(ar->GetID());
}

void Node::DisconnectAsDestination(Arrow *ar)
{
     if(isRemoved) return;
    destinationArrows.remove(ar->GetID());
}

QVector<Arrow*> Node::getArrows()
{
    QVector<Arrow*> vec;
    foreach (auto arrow, sourceArrows)
    {
        vec.append(arrow);
    }
    foreach (auto arrow, destinationArrows)
    {
        vec.append(arrow);
    }
    return vec;
}

void Node::Paint(QGraphicsScene* qgs)
{
    SetShape();
    shape->setVisible(true);
    shape->setFlags(QGraphicsItem::ItemIsSelectable);
    SetBackgroundColor(backgroundColor);
    SetFrameColor(frameColor);
    qgs->addItem(shape);
    if(content) qgs->addItem(content);
}

void Node::SetVisibility(bool vis)
{
    shape->setVisible(vis);
}
void Node::SetLocation(const QPointF &qp)
{
    location=qp;
    SetShape();
}

void Node::SetWidth(double wd)
{
    width=wd;
    SetShape();
}

void Node::SetHeight(double h)
{
    height=h;
    SetShape();
}

void Node::SetBackgroundColor(const QColor &qc)
{
    backgroundColor=qc;
    QBrush brush=shape->brush();
    brush.setColor(backgroundColor);
    brush.setStyle(Qt::BrushStyle::SolidPattern);
    shape->setBrush(brush);
}

void Node::SetFrameColor(const QColor &qc)
{
    frameColor=qc;
    QPen pen=shape->pen();
    pen.setColor(frameColor);
    shape->setPen(pen);
}

void Node::Remove(QGraphicsScene *qgs)//等待arrow完成后继续修改
{
    isRemoved=true;
    qgs->removeItem(shape);
    if(content) content->delete_text(qgs);
     foreach (auto arrow, sourceArrows)
     {
        arrow->removeArrow();
     }
     foreach (auto arrow, destinationArrows)
     {
         arrow->removeArrow();
     }
     isRemoved=false;
      this->deleteID();
}

void Node::BindToText(QGraphicsScene* qgs)
{
    if(content==nullptr)
    {
        QString temp="0x";
        temp+= QString::number(GetID(),16);
        auto text = new Text(location, this, temp, true);
        text->change_content("文本");
        text->setZValue(shape->zValue());
        auto window = MainWindow::instance();
        text->reset_font(QFont(window->fontFamily, window->fontSize));
        text->reset_color(window->textColor);
        (new ChangeElementAction(text, ElementShape::Text, true))->Do();
    }
}

QVector<Arrow*> Node::getSourceArrows()
{
    QVector<Arrow*> vec;
    foreach (auto arrow, sourceArrows)
    {
        vec.append(arrow);
    }
    return vec;
}

void Node::ChangeZValue(bool isSelected)
{
    if(isSelected) shape->setZValue(100);
    else shape->setZValue(1);
    if(content) content->setZValue(shape->zValue());
}
